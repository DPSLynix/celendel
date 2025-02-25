#include "Serializer.h"
#include <QDebug>

#define QV(a) if(a.isEmpty()) return true;
#define R(a) if(a.status()!=QDataStream::Ok) return true;

#define HARDCODED_ARBITRARY_SILLY_NETWORK_VERSION 1

unsigned int getHardcodedNetworkVersion() { return HARDCODED_ARBITRARY_SILLY_NETWORK_VERSION; }

QDataStream &operator<<(QDataStream & ds, const PlayerInformations& p)
{
    ds<<p.name<<p.ip;
    return ds;
}

QDataStream &operator>>(QDataStream & ds, PlayerInformations& p)
{
    ds>>p.name>>p.ip;
    return ds;
}

QDataStream &operator<<(QDataStream & ds, const EntityInformations& e)
{
    ds << e.name << e.data;
    return ds;
}

QDataStream &operator>>(QDataStream & ds, EntityInformations& e)
{
    ds >> e.name >> e.data;
    return ds;
}

QDataStream &operator<<(QDataStream & ds, const EntityData& p)
{
    ds << p.shownName << p.data;
    return ds;
}

QDataStream &operator>>(QDataStream & ds, EntityData& p)
{
    ds>>p.shownName>>p.data;
    return ds;
}

QDataStream &operator<<(QDataStream & ds, const QStringPairList& p)
{
    qint32 s = p.size();
    ds<<s;
    for(int i=0;i<s;++i)
        ds<<p[i];

    return ds;
}

QDataStream &operator>>(QDataStream & q, QStringPairList& p)
{
    qint32 s;
    q>>s;

    for(int i=0;i<s;++i)
    {
        QStringPair t;
        q>>t;
        p<<t;
    }
    return q;
}

QDataStream &operator<<(QDataStream & ds, const QStringPair& p)
{
    ds << p.first << p.second;
    return ds;
}

QDataStream &operator>>(QDataStream & q, QStringPair& p)
{
    q>> p.first >> p.second;
    return q;
}

bool extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& language, QString& text, CLID& sender)
{
    QV(data);
    QDataStream in(data);
    in>>canal;
    R(in);
    in>>language;
    R(in);
    in>>text;
    R(in);
    in>>sender;
    R(in);

    return false;
}

QByteArray serialiseChatData(ENUM_TYPE canal, const QString& language, const QString& text, CLID sender)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<ENUM_TYPE>(canal);
    out<<language;
    out<<text;
    out<<static_cast<CLID>(sender);
    return data;
}

bool extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text)
{
    QV(data);
    QDataStream in(data);

    in>>error_type;
    R(in);
    in>>text;
    R(in);
    return false;
}

QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<ENUM_TYPE>(error_type);
    out<<text;

    return data;
}

bool extractGMElectData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseGMElectData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);

    return data;
}

bool extractSetCLIDData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseSetCLIDData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);

    return data;
}

bool extractNewGMData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseNewGMData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);

    return data;
}

bool extractVotedData(QByteArray& data, CLID& fID, CLID& tID)
{
    QV(data);
    QDataStream in(data);

    in>>fID;
    R(in);
    in>>tID;
    R(in);
    return false;
}

QByteArray serialiseVotedData(CLID fID, CLID tID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(fID);
    out<<static_cast<CLID>(tID);

    return data;
}

bool extractNewNickData(QByteArray& data, CLID& ID, QString& nick)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    in>>nick;
    R(in);

    return false;
}

QByteArray serialiseNewNickData(CLID ID, const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);
    out<<nick;

    return data;
}

bool extractSetNickData(QByteArray& data, QString& nick)
{
    QV(data);
    QDataStream in(data);

    in>>nick;
    R(in);
    return false;
}

QByteArray serialiseSetNickData(const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<nick;

    return data;
}

bool extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE& dropType, QString& reason)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    in>>dropType;
    R(in);
    in>>reason;
    R(in);

    return false;
}

QByteArray serialiseGTFOLynixData(CLID ID, ENUM_TYPE dropType, const QString& reason)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);
    out<<static_cast<ENUM_TYPE>(dropType);
    out<<reason;

    return data;
}

bool extractTODData(QByteArray& data, QString& when)
{
    QV(data);
    QDataStream in(data);

    in>>when;
    R(in);

    return false;
}

QByteArray serialiseTODData(const QString& when)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<when;

    return data;
}

bool extractLocationData(QByteArray& data, QString& where)
{
    QV(data);
    QDataStream in(data);

    in>>where;
    R(in);

    return false;
}

QByteArray serialiseLocationData(const QString& where)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<where;

    return data;
}

bool extractServerInformationsData(QByteArray& data, ServerInformations& si)
{
    QByteArray t=qUncompress(data);

    QV(t);

    QDataStream in(t);

    in>>si.players;
    R(in);
    in>>si.gameMasterID;
    R(in);
    in>>si.location;
    R(in);
    in>>si.timeOfDay;
    R(in);
    in>>si.gameStarted;
    R(in);
    in>>si.serverName;
    R(in);
    in>>si.motd;
    R(in);
    in>>si.narration;
    R(in);
    QByteArray l;
    in>>l;
    R(in);
    in>>si.languages;
    R(in);
    in>>si.dictionaries;
    R(in);
    in>>si.scriptList;
    R(in);

    return extractSyncLibsData(l, si.libs);
}

QByteArray serialiseServerInformationsData(const ServerInformations& si)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<si.players;
    out<<si.gameMasterID;
    out<<si.location;
    out<<si.timeOfDay;
    out<<si.gameStarted;
    out<<si.serverName;
    out<<si.motd;
    out<<si.narration;
    out<<serialiseSyncLibsData(si.libs);
    out<<si.languages;
    out<<si.dictionaries;
    out<<si.scriptList;

    return qCompress(data);
}

bool extractMOTDData(QByteArray& data, QString& motd)
{
    QByteArray t=qUncompress(data);
    QV(t);
    QDataStream in(t);

    in>>motd;
    R(in);

    return false;
}

QByteArray serialiseMOTDData(const QString& motd)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<motd;

    return qCompress(data);
}


bool extractMapInformationsData(QByteArray& data, MapInformations& mi)
{
    QByteArray d=qUncompress(data);
    QV(d);

    QDataStream in(d);

    in>>mi.name;
    R(in);

    qint32 size;
    in>>size;
    R(in);
    mi.mapItems.clear();
    for(int i=0; i<size; ++i)
    {
        mi.mapItems.append(MapItem());
        in>>mi.mapItems[i].coords;
        R(in);
        in>>mi.mapItems[i].rsid;
        R(in);
        in>>mi.mapItems[i].text;
        R(in);
        in>>mi.mapItems[i].color;
        R(in);
        in>>mi.mapItems[i].hidden;
        R(in);
    }

    qint32 mapX, mapY;
    in>>mapX>>mapY;
    R(in);

    mi.map.resize(mapDim(mapX, mapY));

    for(int x=0; x<mapX; ++x)
    {
        for(int y=0; y<mapY; ++y)
        {
            in>>mi.map[x][y];
            R(in);
        }
    }


    return false;
}

QByteArray serialiseMapInformationsData(const MapInformations& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<mi.name;

    out<<static_cast<qint32>(mi.mapItems.size());

    for(int i=0; i<mi.mapItems.size(); ++i)
    {
        out<<mi.mapItems[i].coords;
        out<<static_cast<RSID>(mi.mapItems[i].rsid);
        out<<mi.mapItems[i].text;
        out<<mi.mapItems[i].color;
        out<<mi.mapItems[i].hidden;
    }

    qint32 mapX = sizeX(mi.map);
    qint32 mapY = sizeY(mi.map);

    out<<static_cast<qint32>(mapX);
    out<<static_cast<qint32>(mapY);

    for(int x=0; x<mapX; ++x)
    {
        for(int y=0; y<mapY; ++y)
        {
            out<<mi.map[x][y];
        }
    }

    return qCompress(data);
}

bool extractMapItemsInformationsData(QByteArray& data, QList<MapItem>& mi)
{
    QByteArray t=qUncompress(data);
    QV(t);
    QDataStream in(t);

    qint32 size;
    in>>size;
    R(in);
    mi.clear();
    for(int i=0; i<size; ++i)
    {
        mi.append(MapItem());
        in>>mi[i].coords;
        R(in);
        in>>mi[i].rsid;
        R(in);
        in>>mi[i].text;
        R(in);
        in>>mi[i].color;
        R(in);
        in>>mi[i].hueStrenght;
        R(in);
        in>>mi[i].hidden;
        R(in);
    }
    return false;
}

QByteArray serialiseMapItemsInformationsData(const QList<MapItem>& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<qint32>(mi.size());

    for(int i=0; i<mi.size(); ++i)
    {
        out<<mi[i].coords;
        out<<static_cast<RSID>(mi[i].rsid);
        out<<mi[i].text;
        out<<mi[i].color;
        out<<mi[i].hidden;
        out<<mi[i].hueStrenght;
    }

    return qCompress(data);
}

bool extractDiceRollData(QByteArray& data, CLID& ID, quint16& result, quint16& max)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);
    in>>result;
    R(in);
    in>>max;
    R(in);

    return false;
}

QByteArray serialiseDiceRollData(CLID ID, quint16 result, quint16 max)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);
    out<<static_cast<quint16>(result);
    out<<static_cast<quint16>(max);

    return data;
}

bool extractPlaySoundData(QByteArray& data, QString& lib, QString& sound)
{
    QV(data);
    QDataStream in(data);
    in>>lib;
    R(in);
    in>>sound;
    R(in);

    return false;
}

QByteArray serialisePlaySoundData(const QString& lib, const QString& sound)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<lib;
    out<<sound;

    return data;
}

bool extractServerNameData(QByteArray& data, QString& name)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);

    return false;
}

QByteArray serialiseServerNameData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

bool extractClientJoinedData(QByteArray& data, CLID& ID, QString& IP)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);
    in>>IP;
    R(in);

    return false;
}

QByteArray serialiseClientJoinedData(const CLID& ID, const QString& IP)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);
    out<<IP;

    return data;
}

bool extractClientLeftData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);

    return false;
}

QByteArray serialiseClientLeftData(const CLID& ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<CLID>(ID);

    return data;
}

bool extractUnbanData(QByteArray& data, QString& IP)
{
    QV(data);
    QDataStream in(data);
    in>>IP;
    R(in);

    return false;
}

QByteArray serialiseUnbanData(const QString& IP)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<IP;

    return data;
}

bool extractAllNarrationData(QByteArray& data, QString& txt)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);
    in>>txt;
    R(in);

    return false;
}

QByteArray serialiseAllNarrationData(const QString& txt)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<txt;

    return qCompress(data);
}

bool extractSyncLibsData(QByteArray& data, QList<SoundLibInformations>& libs)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);
    int s=0;
    libs.clear();
    in>>s;
    R(in);
    for(int i=0;i<s;++i)
    {
        SoundLibInformations li;
        in>>li.name;
        R(in);
        in>>li.version;
        R(in);
        in>>li.sounds;
        R(in);
        libs.append(li);
    }

    return false;
}

QByteArray serialiseSyncLibsData(const QList<SoundLibInformations>& libs)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);


    out<<libs.size();
    for(int i=0;i<libs.size();++i)
    {
        out<<libs[i].name;
        out<<libs[i].version;
        out<<libs[i].sounds;
    }

    return qCompress(data);
}

bool extractLanguagesData(QByteArray& data, QList<QPair<QString, QString> >& languages)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    languages.clear();
    in>>languages;
    R(in);

    return false;
}

QByteArray serialiseLanguagesData(const QList<QPair<QString, QString> >& languages)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);


    out<<languages;

    return qCompress(data);
}

bool extractAddDicoData(QByteArray& data, QString& name, QString& content)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>name;
    R(in);
    in>>content;
    R(in);

    return false;
}

QByteArray serialiseAddDicoData(const QString& name, const QString& content)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;
    out<<content;

    return qCompress(data);
}

bool extractDicoListData(QByteArray& data, QStringList& names)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    names.clear();
    in>>names;
    R(in);

    return false;
}

QByteArray serialiseDicoListData(const QStringList& names)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<names;

    return qCompress(data);
}

bool extractRemoveDicoData(QByteArray& data, QString& name)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>name;
    R(in);


    return false;
}

QByteArray serialiseRemoveDicoData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return qCompress(data);
}


bool extractUpdateRessourcesData(QByteArray& data, QMap<QString, RSID>& ressources)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>ressources;
    R(in);


    return false;
}

QByteArray serialiseUpdateRessourcesData(const QMap<QString, RSID>& ressources)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<ressources;

    return qCompress(data);
}

bool extractScriptListData(QByteArray& data, QStringList& list)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>list;
    R(in);

    return false;
}

QByteArray serialiseScriptListData(const QStringList& list)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<list;

    return qCompress(data);
}

bool extractSendScriptData(QByteArray& data, QString& name, QString& content)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>name;
    R(in);
    in>>content;
    R(in);

    return false;
}

QByteArray serialiseSendScriptData(const QString& name, const QString& content)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;
    out<<content;

    return qCompress(data);
}

bool extractRequestScriptData(QByteArray& data, QString& name)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);

    return false;
}

QByteArray serialiseRequestScriptData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

bool extractDeleteScriptData(QByteArray& data, QString& name)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);

    return false;
}

QByteArray serialiseDeleteScriptData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

bool extractRenameScriptData(QByteArray& data, QString& name, QString& newName)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);
    in>>newName;
    R(in);

    return false;
}

QByteArray serialiseRenameScriptData(const QString& name, const QString& newName)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;
    out<<newName;

    return data;
}

bool extractEntitiesInformationsData(QByteArray& data, QList<EntityInformations>& list)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>list;
    R(in);

    return false;
}

QByteArray serialiseEntitiesInformationsData(const QList<EntityInformations>& list)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<list;

    return qCompress(data);
}

bool extractUpdateEntityInformationsData(QByteArray& data, EntityInformations& info)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>info;
    R(in);

    return false;
}

QByteArray serialiseUpdateEntityInformationsData(const EntityInformations& info)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<info;

    return qCompress(data);
}

bool extractCreateEntityData(QByteArray& data, QString& name, QString& scriptName)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);
    in>>scriptName;
    R(in);

    return false;
}

QByteArray serialiseCreateEntityData(const QString& name, const QString& scriptName)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;
    out<<scriptName;

    return data;
}

bool extractInjectCodeData(QByteArray& data, QString& entityName, QString& code)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>entityName;
    R(in);
    in>>code;
    R(in);

    return false;
}

QByteArray serialiseInjectCodeData(const QString& entityName, const QString& code)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<entityName;
    out<<code;

    return qCompress(data);
}

bool extractScriptErrorData(QByteArray& data, QString& entityName, QString& error)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>entityName;
    R(in);
    in>>error;
    R(in);

    return false;
}

QByteArray serialiseScriptErrorData(const QString& entityName, const QString& error)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<entityName;
    out<<error;

    return qCompress(data);
}

bool extractScriptMessageData(QByteArray& data, qint32& type, QString& ent, QString& txt)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>type;
    R(in);
    in>>ent;
    R(in);
    in>>txt;
    R(in);

    return false;
}

QByteArray serialiseScriptMessageData(qint32 type, const QString& ent, const QString& txt)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<static_cast<qint32>(type);
    out<<ent;
    out<<txt;

    return qCompress(data);
}

bool extractDeleteEntityData(QByteArray& data, QString& name)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);

    return false;
}

QByteArray serialiseDeleteEntityData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

bool extractCharacterListData(QByteArray& data, QStringList& list)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);
    in>>list;
    R(in);
    return false;
}

QByteArray serialiseCharacterListData(const QStringList& list)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);
    out<<list;
    return qCompress(data);
}

bool extractMapFlareData(QByteArray& data, QPoint& coords, CLID& who)
{
    QV(data);
    QDataStream in(data);
    in>>coords;
    R(in);
    in>>who;
    R(in);

    return false;
}

QByteArray serialiseMapFlareData(const QPoint& coords, CLID who)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<coords;
    out<<who;

    return data;
}

bool extractVOIPBlacklistData(QByteArray& data, CLID& toBL, CLID& who, bool& blacklist)
{
    QV(data);
    QDataStream in(data);
    in>>toBL;
    R(in);
    in>>who;
    R(in);
    in>>blacklist;
    R(in);

    return false;
}

QByteArray serialiseVOIPBlacklistData(CLID toBL, CLID who, bool blacklist)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<toBL;
    out<<who;
    out<<blacklist;

    return data;
}

