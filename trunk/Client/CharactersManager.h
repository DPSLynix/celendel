#ifndef CHARACTERSMANAGER_H
#define CHARACTERSMANAGER_H

#include <QWidget>
#include <QStringList>
#include <QMap>

class EntitiesManager;
class QTreeView;
class QStandardItemModel;
class EntityInformations;

class CharactersManager : public QWidget
{
    Q_OBJECT

    public:
        CharactersManager(EntitiesManager* entMngr, QWidget *parent = 0);

        QString getName(const EntityInformations& e) const;
        QString getPlayerCharacter(const QString& ply) const;

    public slots:
        void updateCharacterList(const QStringList& list);

    private slots:
        void update();

    private:

        EntitiesManager* m_entMngr;

        QStringList m_characters;

        QMap<QString, QString> m_chPlyMap; //First = player, second = character

        QTreeView *m_v_cl;
        QStandardItemModel *m_list;
};

#endif
