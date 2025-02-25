/*

Copyright (C) 2009, Etienne Moutot <e.moutot@gmail.com>

This file is part of colorPickerWidget.

    colorPickerWidget is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    colorPickerWidget is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Modified by Gigotdarnaud, for the Celendel project */

#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QSlider;
class QLabel;
class QSpinBox;
class QGroupBox;
class QtColorTriangle;
class QColorViewer;
class Screen;

class QColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    QColorPickerWidget(QWidget *parent=NULL);

    QColor color() const;

    void setAlphaEnabled(bool b);
    bool isAlphaEnabled() const { return m_alphaEnabled; }

    void setSpinBoxesEnabled(bool b);
    bool isSpinBoxesEnabled() const { return m_spinBoxesEnabled; }

    void changeAlpha(quint8 alpha);

Q_SIGNALS:
    void colorChanged(const QColor &col);

public Q_SLOTS:
    void setColor(const QColor &col);

private slots:
    void pickMode();
    void colorChgd();
    void spinBoxesChgd();
    void changeAlphaSB(int alpha);
    void changeAlphaSL(int alpha);

private:


    void refresh();

    QtColorTriangle *m_colorTriangle;
    QColorViewer *m_colorView;
    QPushButton *m_pickColor;

    QSpinBox *m_alphaSB, *m_redSB, *m_blueSB, *m_greenSB;
    QGroupBox *m_spinBoxesGB;

    QSlider *m_alphaSlider;

    QLabel* m_alphaLabel;

    QGridLayout *layout;

    bool m_alphaEnabled;
    bool m_spinBoxesEnabled;

    bool m_SBchanged;

    Screen *scr;
};

#endif // COLORPICKERWIDGET_H
