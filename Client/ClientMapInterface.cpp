#include "ClientInterface.h"
#include "MapWidget.h"
#include <QDebug>

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

bool ClientInterface::openRenderWindow(QString mapName, QString ressList)
{
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
    if(mapRender->loadRessourcesPack(ressList).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressList));
        return true;
    }

    QHBoxLayout l;
    l.addWidget(mapRenderWidg);
    dia.setLayout(&l);
    dia.exec();
    return false;
}

