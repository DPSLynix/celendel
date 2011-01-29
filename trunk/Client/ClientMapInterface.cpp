#include "ClientInterface.h"
#include "MapEditor.h"
#include <QDebug>
#include "..\Shared\Serializer.h"

bool ClientInterface::loadRessourcesListGUI()
{
    QString file=QFileDialog::getOpenFileName(this,tr("Charger une liste d'images"),QString(),tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
    if(file.isEmpty())
        return true;

    prev:
    QMessageBox::StandardButton but=QMessageBox::question(this,tr("Exclusivit� ?"),tr("Voulez-vous d�charger d'abord les ressources actuelles (exclusivit�) ?"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Abort|QMessageBox::Help);

    if(but==QMessageBox::Abort)
        return true;
    if(but==QMessageBox::Help)
    {
        QMessageBox::information(this, tr("Lire tu dois, jeune padawan"), tr("\"L'exclusivit�\" d'un set d'image est lorsque ce set d'image est charg�, dans l'ordre, dans le cache de ressource interne du moteur de rendu. Ainsi, chaque image d'une liste en mode \'exclusif\' aura syst�matiquement le m�me RSID, ce qui est essentiel pour une carte. Cependant, ce mode d'ouverture implique de vider le cache enti�rement, et si une carte est d�j� charg�e son set d'image sera remplac�. Notez que pour des raisons de modularit� (traduisez, parce que le programmeur �tait trop feignant pour faire un ressource manager), chaque fen�tre de rendu poss�de son propre cache d'image, et que seul le cache de la carte principale sera vidang� dans votre cas."));
        goto prev; // Why are you starring at me ? Is it THAT bad ? I don't care, I love spaghetti anyway.
    }

    qDebug() << m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes);

    return 0;//m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes).isEmpty();
}

void ClientInterface::openMapEditor()
{
    delete m_mapEditor;
    m_mapEditor = new MapEditor(this);
    m_mapEditor->setWindowModality(Qt::WindowModal);
    m_mapEditor->show();
}

bool ClientInterface::openRenderWindow(QString mapName, QString ressList)
{
    m_renderedMap=NULL;

    if(mapName.isEmpty())
    {
        mapName=QFileDialog::getOpenFileName(this, tr("Charger une carte"),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));
        if(mapName.isEmpty())
            return true;

    }
    if(ressList.isEmpty())
    {
       ressList=QFileDialog::getOpenFileName(this,tr("Charger une liste d'images"),QString(),tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
        if(ressList.isEmpty())
            return true;
    }

    QDialog dia(this);
    MapWidgetScroll* mapRenderWidg = new MapWidgetScroll(&dia);
    MapWidget* mapRender = mapRenderWidg->getMapWidget();
    mapRender->setHighlight(true);
    if(mapRender->loadRessourcesPack(ressList).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressList));
        return true;
    }

    QPushButton sendToServer(tr("Envoyer la carte au serveur"));

    if(!isGM())
        sendToServer.hide();

    m_renderedMap=mapRender->getMap();

    connect(&sendToServer, SIGNAL(pressed()), this, SLOT(sendMapToServer()));

    QHBoxLayout l;
    l.addWidget(mapRenderWidg);
    l.addWidget(&sendToServer);
    dia.setLayout(&l);
    dia.exec();
    m_renderedMap=NULL;
    return false;
}

void ClientInterface::sendMapToServer()
{
    if(!isGM())
        return;
    if(m_renderedMap==NULL)
        return;

    qDebug() << "Oki !";
    m_network->send(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_renderedMap));
}

