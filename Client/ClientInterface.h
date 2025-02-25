#ifndef DEF_CLIENTINTERFACE
#define DEF_CLIENTINTERFACE

/* Main client class */

#include <QMainWindow>
#include "../Shared/Constants.h"
#include "ClientNetwork.h"
#include "ClientSettings.h"

#define DTA_CLID  Qt::UserRole+42
#define SAVE_EXT ".savegame"

class MapWidget;
class MapEditor;
class ScriptManager;
class EntitiesManager;
class CharactersManager;

class VOIP;

class ClientInterface : public QMainWindow
{
    Q_OBJECT
    public:
        ClientInterface();

        void lg(const QString txt, bool time=true, bool html=true);
        QString getRolePlayName(CLID ID);
        bool isConnected() const { return m_network->isConnected(); }

        bool isGM() const {return m_ID==m_GMID&&isConnected();}

    private slots:
        void sendMessage(); // In ClientChatCommands.cpp
        void chat(CLID sender, QString lang, QString text, ENUM_TYPE canal);
        void changeServerInformations(ServerInformations si);
        void changeClientID(CLID ID);
        void changeClientNickname(CLID ID, QString nick);
        void showError(ENUM_TYPE e, QString txt);

        void changeGameMaster(CLID ID);
        void clientVoted(CLID f, CLID t);

        void connectionEtablished();
        void connectionLost();
        void diceRolled(CLID, quint16, quint16);
        void sanctionned(CLID, ENUM_TYPE, QString);

        void rollDice();
        void rollSpecialDice();
        void serverName(QString);
        void motdChanged(QString);
        void gameLaunched();

        void setTitle();

        void playSound(QString lid, QString rsid);

        void updatePlayerList();

        void clientJoined(CLID, QString IP);
        void clientLeft(CLID);

        void updateGMLabel();
        void updateGMPanel(); //In ClientGMInterface.cpp
        bool addLanguage(); //In ClientGMInterface.cpp
        bool addLanguage(const QString& lang, const QString& dic); //In ClientGMInterface.cpp
        void languageListMenu(const QPoint& pos); //In ClientGMInterface.cpp
        bool removeLanguage(const QString& lang);
        void removeLanguageMenu();
        void importLanguageList();
        void sendLanguageList();
        CLID CLIDFromString(const QString& str); // In ClientChatCommands.cpp

        void switchConnectionState();
        void openSettings();
        void openSoundsGUI();
        void aboutUs();
        void aboutServer();

        void openMapEditor();
        void clearMapEditor();

        void mapFlare();

        void resetData();

        void setCSS(const QString& fileName = ""); // If fileName is empty, the defaut theme (OS dependent) will be loaded
        void setInterface(const QString& path = DEFAULT_INTERFACE);  // If path is empty, the defaut interface will be loaded

        void playerListMenu(const QPoint& pos);
        void actionKick();
        void actionBan();
        void actionVoteGM();
        void actionChangeGM();


        void refresh();
        void textChanged();
        void narrationChanged(QString);

        void syncSoundLibs(QList<SoundLibInformations>);
        void syncLanguagesList(QList<QPair<QString, QString> >);
        void syncDictionariesList(QStringList list);

        void requestScriptDownload(QString name);
        void sendScriptToServer(QString name, QString content);
        void deleteScript(QString name);
        void renameScript(QString name, QString newName);
        void makeEntity(QString name, QString scriptName);
        void deleteEntity(const QString& name);
        void injectCode(QString entityName, QString code);

        void scriptToGMMsg(QString ent, QString txt);
        void scriptToOwnerMsg(QString ent, QString txt);
        void scriptActionMsg(QString ent, QString txt);
        void scriptToPlayerMsg(QString ent, QString txt);
        void scriptMsg(QString ent, QString txt);
        void scriptError(QString ent, QString txt);


        void sendMapToServer(const MapInformations* const map, const QMap<QString, RSID>& ress);

        void addDictionnary();

        void saveGame();
        void loadGame();

        void VOIPRemoveClient();
        void VOIPAddClient();
        void VOIPClientVolume();

        void dataPerSecond(int, int);

    private:

        void buildGUI();
        void buildGMStuff();

        ClientNetwork* m_network;
        QString anonym(CLID ID);
        QString anonym2(CLID ID);

        ScriptManager *m_scriptManager;
        EntitiesManager *m_entitiesManager;

        ///Infos
        bool m_gameStarted;
        bool m_voted;
        CLID m_ID;
        CLID m_GMID;
        QString m_location;
        QString m_TOD;
        QString m_serverName;
        QString m_motd;
        QMap<CLID, PlayerInformations> m_playersMap;


        ///Chat GUI
        QTextEdit* m_chat;
        QTextEdit* m_narrator;
        QTextEdit* m_RPChat;
        QLineEdit* m_chatInput;
        QComboBox* m_RPLanguage;
        QPushButton* m_rollTheDice;
        QPushButton* m_rollSpecialDice;

        ///Map dock
        MapWidget* m_mapWi;
        QPushButton* m_flare;

        ///GM Panel
        QDockWidget *m_GMPanelDock;
        QTableWidget *m_languageManagement;
        QPushButton *m_addLanguage;
        QPushButton *m_importLanguages;
        QPushButton *m_syncroniseLanguages;
        QListWidget *m_dictionnariesList;
        QPushButton *m_addDictionnary;

        ///Player list
        QTreeView *m_v_pl;
        QStandardItemModel *m_playerList;
        QLabel *m_GMLabel;

        ///Menus
        QAction *m_ac_joinOrLeave;

        ///Context Menus
        QAction *m_kick;
        QAction *m_ban;
        QAction *m_voteGM;
        QAction *m_changeGM;
        QAction *m_separator;
        QAction *m_VOIPConnect;
        QAction *m_VOIPDisconnect;
        QAction *m_VOIPVolume;

        QAction *m_removeLanguage;
        QAction *m_addLanguageAct;

        ///Character list
        CharactersManager* m_characterMngr;

        ///GM Menus
        QTimer *m_refreshTimer;
        bool m_needRefresh;

        ///Map rendering
        MapEditor* m_mapEditor;

        ///Status bar
        QLabel* m_dlPerSec;
        QLabel* m_upPerSec;
};

#endif
