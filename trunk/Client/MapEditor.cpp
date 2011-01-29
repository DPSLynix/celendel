#include "MapEditor.h"
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDockWidget>
#include <QLayout>
#include <QDebug>
#include <QSpinBox>
#include <QLabel>
#include <QTableWidget>

MapEditor::MapEditor(QWidget* parent, const QString& map):QMainWindow(parent)
{
    m_mapWidgetScroll = NULL;
    m_needSave = false;

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    setDockNestingEnabled(true);

    setWindowTitle(tr("�diteur de carte"));

    { ///MAP PROPERTIES DOCK
    QDockWidget* dw_mapProperties = new QDockWidget(tr("Propri�t�s de la carte"), this);
    dw_mapProperties->setWhatsThis(tr("Un dock regroupant quelques propri�t�s de la carte"));
    dw_mapProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_mapProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_mapProperties = new QWidget(dw_mapProperties);
    dw_mapProperties->setWidget(w_mapProperties);

    addDockWidget(Qt::RightDockWidgetArea, dw_mapProperties);

    QVBoxLayout *l_mapProperties = new QVBoxLayout(w_mapProperties);
    w_mapProperties->setLayout(l_mapProperties);

    {
        QHBoxLayout *lay=new QHBoxLayout();
        l_mapProperties->addLayout(lay);
        m_mapSizeX = new QSpinBox(this);
        m_mapSizeX->setRange(0,MAP_MAX_SIZE);
        m_mapSizeX->setEnabled(false);
        m_mapSizeX->setSingleStep(16);
        connect(m_mapSizeX, SIGNAL(valueChanged(int)), this, SLOT(changeMapSizeX(int)));
        lay->addWidget(m_mapSizeX);


        m_mapSizeY = new QSpinBox(this);
        m_mapSizeY->setRange(0,MAP_MAX_SIZE);
        m_mapSizeY->setEnabled(false);
        m_mapSizeY->setSingleStep(16);
        connect(m_mapSizeY, SIGNAL(valueChanged(int)), this, SLOT(changeMapSizeY(int)));
        lay->addWidget(m_mapSizeY);
    }
    {
        m_mapNameLabel=new QLabel(this);
        l_mapProperties->addWidget(m_mapNameLabel);
    }
    }

    { ///CASE PROPERTIES DOCK
    QDockWidget* dw_caseProperties = new QDockWidget(tr("Propri�t�s de la case"), this);
    dw_caseProperties->setWhatsThis(tr("Un dock regroupant quelques propri�t�s de la case s�lectionn�e"));
    dw_caseProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_caseProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_caseProperties = new QWidget(dw_caseProperties);
    dw_caseProperties->setWidget(w_caseProperties);

    addDockWidget(Qt::RightDockWidgetArea, dw_caseProperties);

    QVBoxLayout *l_caseProperties = new QVBoxLayout(w_caseProperties);
    w_caseProperties->setLayout(l_caseProperties);

    {

        m_selectedCaseLabel = new QLabel(this);
        l_caseProperties->addWidget(m_selectedCaseLabel);

        m_selectedCaseRSID = new QSpinBox(this);
        m_selectedCaseRSID->setRange(0,MAX_LOADED_RESSOURCES);
        m_selectedCaseRSID->setEnabled(false);
        l_caseProperties->addWidget(m_selectedCaseRSID);
        connect(m_selectedCaseRSID, SIGNAL(valueChanged(int)), this, SLOT(changeCurrentCaseRSID(int)));
    }
    }

    { ///RSSMNGR PROPERTIES DOCK
    QDockWidget* dw_rssMngrProperties = new QDockWidget(tr("Gestionnaire de ressources"), this);
    dw_rssMngrProperties->setWhatsThis(tr("Un dock regroupant les diff�rentes ressources charg�es dans l'�diteur"));
    dw_rssMngrProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_rssMngrProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_rssMngrProperties = new QWidget(dw_rssMngrProperties);
    dw_rssMngrProperties->setWidget(w_rssMngrProperties);

    addDockWidget(Qt::RightDockWidgetArea, dw_rssMngrProperties);

    QVBoxLayout *l_rssMngrProperties = new QVBoxLayout(w_rssMngrProperties);
    w_rssMngrProperties->setLayout(l_rssMngrProperties);
    {
        m_rsMngrWidget = new QTableWidget(0,2, this);
        l_rssMngrProperties->addWidget(m_rsMngrWidget);
    }
    }

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
    QAction *ac_open= fileMenu->addAction(tr("&Charger une carte..."));
    connect(ac_open, SIGNAL(triggered()), this, SLOT(loadMap()));

    QAction *ac_save = fileMenu->addAction(tr("&Sauvegarder la carte..."));
    connect(ac_save, SIGNAL(triggered()), this, SLOT(saveMap()));

    QAction *ac_saveAs = fileMenu->addAction(tr("&Sauvegarder sous..."));
    connect(ac_saveAs, SIGNAL(triggered()), this, SLOT(saveMapAs()));

    QAction *ac_quit = fileMenu->addAction(tr("&Quitter..."));
    connect(ac_quit, SIGNAL(triggered()), this, SLOT(close()));

    m_hoveredCaseLabel = new QLabel(this);
    statusBar()->addWidget(m_hoveredCaseLabel);

    m_mapName=map;
    if(!map.isEmpty())
    {
        loadMap(map);
    }
}

void MapEditor::closeEvent (QCloseEvent *event)
{
    saveCheck();

    delete m_mapWidgetScroll;
    m_mapWidgetScroll=NULL;
}

bool MapEditor::isMapValid() const
{
    return m_mapWidgetScroll!=NULL&&m_mapWidgetScroll->getMapWidget()->isMapValid()&&!m_mapName.isEmpty();
}

bool MapEditor::saveCheck()
{
    if(!needSave())
        return false;

    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Attention"), tr("Tout travail non sauvegard� sera perdu."), QMessageBox::Save|QMessageBox::Ignore|QMessageBox::Abort);
    if(ret == QMessageBox::Abort)
        return true;

    if(ret == QMessageBox::Ignore)
        return false;

    return saveMap();
}

bool MapEditor::saveMap()
{
    return saveMapAs(m_mapName);
}

bool MapEditor::saveMapAs(QString fileName)
{
    if(!isMapValid())
        return true;

    if(fileName.isEmpty())
        fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder une carte..."),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(fileName.isEmpty())
        return true;

    if(m_mapWidgetScroll->getMapWidget()->saveMap(fileName))
        return true;

    m_mapName=fileName;

    return false;
}

bool MapEditor::needSave() const
{
    return m_needSave&&isMapValid();
}

void MapEditor::changeMapSizeX(int x)
{
  /*  if(!isMapValid())
        return;
    m_mapWidgetScroll->getMapWidget()->m_map->map.resize(mapDim(x, m_mapWidgetScroll->getMapWidget()->m_map->mapSizeY()));
    m_mapWidgetScroll->getMapWidget()->setMaximumWidth(x*BLOC_SIZE);
    m_mapWidgetScroll->viewport()->setMaximumWidth(x*BLOC_SIZE);*/
}

void MapEditor::changeMapSizeY(int y)
{
   /* if(!isMapValid())
        return;
    m_mapWidgetScroll->getMapWidget()->m_map->map.resize(mapDim(m_mapWidgetScroll->getMapWidget()->m_map->mapSizeX(), y));
    m_mapWidgetScroll->getMapWidget()->setMaximumHeight(y*BLOC_SIZE);
    m_mapWidgetScroll->viewport()->setMaximumHeight(y*BLOC_SIZE);*/
}

void MapEditor::changeCasePos(QPoint newCase) //Hovered
{
    if(!isMapValid())
        return;
    m_hoveredCaseLabel->setText(tr("Case : (%1;%2)").arg(newCase.x()).arg(newCase.y()));
}

void MapEditor::changeCurrentCase(QPoint newCase) //Selected
{
    if(!isMapValid())
        return;
    m_selectedCase=newCase;
    m_selectedCaseLabel->setText(tr("Case : (%1;%2)").arg(newCase.x()).arg(newCase.y()));
    m_selectedCaseRSID->setValue(m_mapWidgetScroll->getMapWidget()->m_map->map[newCase.x()][newCase.y()]);
}

void MapEditor::changeCurrentCaseRSID(int n)
{
    if(!isMapValid())
        return;

    m_mapWidgetScroll->getMapWidget()->m_map->map[m_selectedCase.x()][ m_selectedCase.y()] = (RSID)n;
}

void MapEditor::updateRessourcesList()
{
    if(!isMapValid())
        return;

    const QMap<QString, RSID>& mp = m_mapWidgetScroll->getMapWidget()->m_loadedRessourcesName;

    QMap<QString, RSID>::const_iterator i = mp.constBegin();
    while (i != mp.constEnd())
    {
        int row=m_rsMngrWidget->rowCount(); m_rsMngrWidget->setRowCount(row+1);
        m_rsMngrWidget->setItem(row, 0, new QTableWidgetItem(QString::number(i.value())));
        m_rsMngrWidget->setItem(row, 1, new QTableWidgetItem(i.key()));

        ++i;
    }
}

bool MapEditor::loadMap(QString mapName, QString ressPack)
{
    saveCheck();

    if(mapName.isEmpty())
        mapName = QFileDialog::getOpenFileName(this, tr("Charger une carte..."),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(mapName.isEmpty())
        return true;

    if(ressPack.isEmpty())
        ressPack = QFileDialog::getOpenFileName(this, tr("Charger un pack de ressources..."),QString(), tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));

    m_needSave=false;

    delete m_mapWidgetScroll;
    m_mapWidgetScroll = new MapWidgetScroll(this);
    setCentralWidget(m_mapWidgetScroll);

    MapWidget* mapRender = m_mapWidgetScroll->getMapWidget();
    mapRender->setHighlight(true);
    mapRender->setCursor(Qt::CrossCursor);
    if(mapRender->loadRessourcesPack(ressPack).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressPack));
        return true;
    }

    m_mapName=mapName;
   /* m_mapSizeX->setEnabled(true);
    m_mapSizeY->setEnabled(true);*/
    m_mapSizeX->setValue(mapRender->getMap()->mapSizeX());
    m_mapSizeY->setValue(mapRender->getMap()->mapSizeY());

    connect(mapRender, SIGNAL(highlightedCaseChanged(QPoint)), this, SLOT(changeCasePos(QPoint)));
    changeCasePos(QPoint(0,0));

    connect(mapRender, SIGNAL(mapClicked(QPoint)), this, SLOT(changeCurrentCase(QPoint)));
    changeCurrentCase(QPoint(0,0));

    m_mapNameLabel->setText(tr("Nom de la carte : %1").arg(m_mapName));

    m_selectedCaseRSID->setEnabled(true);

    updateRessourcesList();

    return false;
}
