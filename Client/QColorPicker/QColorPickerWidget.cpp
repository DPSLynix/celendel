#include "QColorPickerWidget.h"

#include <QLabel>
#include <QPushbutton>
#include <QLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>
#include "qtcolortriangle.h"
#include "QColorViewer.h"
#include "screen.h"

#include <QDebug>

QColorPickerWidget::QColorPickerWidget(QWidget *par):QWidget(par)
{
    m_SBchanged=false;
    m_alphaEnabled=true;
    m_spinBoxesEnabled=true;
    scr=NULL;
    m_colorTriangle = new QtColorTriangle(this);

    connect(m_colorTriangle, SIGNAL(colorChanged(QColor)), this, SLOT(colorChgd()));

    m_colorView = new QColorViewer(this);
    m_colorView->setColor(m_colorTriangle->color());
    connect(m_colorTriangle, SIGNAL(colorChanged(QColor)), m_colorView, SLOT(changeColor(QColor)));

    m_pickColor = new QPushButton(tr("Sélectionner une couleur..."), this);
    connect(m_pickColor, SIGNAL(released()), this, SLOT(pickMode()));

    m_alphaSlider=new QSlider(Qt::Horizontal,this); m_alphaSlider->setRange(0,255); m_alphaSlider->setValue(255);
    connect(m_alphaSlider, SIGNAL(valueChanged(int)), this, SLOT(changeAlphaSB(int)));
    m_alphaLabel=new QLabel(tr("Alpha"),this); m_alphaLabel->setAlignment(Qt::AlignHCenter);

    m_spinBoxesGB=new QGroupBox(tr("Valeurs :"),this);
    QVBoxLayout* lay=new QVBoxLayout();
    m_spinBoxesGB->setLayout(lay);

        m_redSB=new QSpinBox(this); m_redSB->setRange(0,255); m_redSB->setAccelerated(true); m_redSB->setPrefix(tr("Rouge :")); lay->addWidget(m_redSB);
        connect(m_redSB, SIGNAL(valueChanged(int)), this, SLOT(spinBoxesChgd()));
        m_greenSB=new QSpinBox(this); m_greenSB->setRange(0,255); m_greenSB->setAccelerated(true); m_greenSB->setPrefix(tr("Vert :")); lay->addWidget(m_greenSB);
        connect(m_greenSB, SIGNAL(valueChanged(int)), this, SLOT(spinBoxesChgd()));
        m_blueSB=new QSpinBox(this); m_blueSB->setRange(0,255); m_blueSB->setAccelerated(true); m_blueSB->setPrefix(tr("Bleu :")); lay->addWidget(m_blueSB);
        connect(m_blueSB, SIGNAL(valueChanged(int)), this, SLOT(spinBoxesChgd()));
        m_alphaSB=new QSpinBox(this); m_alphaSB->setRange(0,255); m_alphaSB->setAccelerated(true); m_alphaSB->setPrefix(tr("Alpha :")); lay->addWidget(m_alphaSB);
        connect(m_alphaSB, SIGNAL(valueChanged(int)), this, SLOT(changeAlphaSL(int)));

    layout = new QGridLayout;
    layout->addWidget(  m_colorTriangle,  0, 0, 4, 2);
    layout->addWidget(  m_colorView,      1, 5, 2, 2);
    layout->addWidget(  m_pickColor,      0, 5, 1, -1);
    layout->addWidget(  m_alphaSlider,    3, 3, 1, 2);
    layout->addWidget(  m_alphaLabel,     3, 2, 1, 1);
    layout->addWidget(  m_spinBoxesGB,    0, 2, 3, 3);

    setLayout(layout);

    setColor(QColor("grey"));
    changeAlpha(255);
}

void QColorPickerWidget::pickMode()
{
    delete scr;
    scr = new Screen();
    connect(scr, SIGNAL(colorSelected(QColor)), m_colorTriangle, SLOT(setColor(QColor)));
}

void QColorPickerWidget::setAlphaEnabled(bool b)
{
    m_alphaEnabled=b;
    refresh();
}

void QColorPickerWidget::setSpinBoxesEnabled(bool b)
{
     m_spinBoxesEnabled=b;
     refresh();
}

void QColorPickerWidget::refresh()
{
    m_alphaSlider->setVisible(m_alphaEnabled);
    m_alphaLabel->setVisible(m_alphaEnabled);
    m_spinBoxesGB->setVisible(m_spinBoxesEnabled);
    m_alphaSB->setVisible(m_spinBoxesEnabled&&m_alphaEnabled);
}

void QColorPickerWidget::setColor(const QColor &col)
{
    m_colorTriangle->setColor(col);
    m_colorView->setColor(col);
}

QColor QColorPickerWidget::color() const
{
    return QColor(m_colorView->color().red(),m_colorView->color().green(),m_colorView->color().blue(),m_alphaSlider->value());
}

void QColorPickerWidget::changeAlphaSB(int alpha)
{
    m_alphaSB->setValue(alpha);
}

void QColorPickerWidget::changeAlphaSL(int alpha)
{
    m_alphaSlider->setValue(alpha);
}

void QColorPickerWidget::changeAlpha(quint8 alpha)
{
    m_alphaSB->setValue(alpha);
}

void QColorPickerWidget::spinBoxesChgd()
{
    if(m_SBchanged)
        return;

    m_SBchanged=true;
    setColor(QColor(m_redSB->value(),m_greenSB->value(),m_blueSB->value()));
}


void QColorPickerWidget::colorChgd()
{
    QColor col=color();

    if(!m_SBchanged)
    {
        m_SBchanged=true;
        m_redSB->setValue(col.red());
        m_blueSB->setValue(col.blue());
        m_greenSB->setValue(col.green());
    }
    m_SBchanged=false;

    emit colorChanged(col);
}
