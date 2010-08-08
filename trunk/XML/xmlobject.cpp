#include "xmlobject.h"
#include <QtXml>
#include <QString>

XMLObject::XMLObject()
{
    m_name = "Objet XML";
    m_infos = "Cr�� par XMLObjet";
}

XMLObject::~XMLObject()
{
    QMultiMap<TRIGGER_TYPE, Event>::const_iterator i = m_eventMap.constBegin();
    while (i != m_eventMap.constEnd())
    {
        if(i.value().action==ALERT_SPECIAL_PLAYER)
        {
            delete i.value().data.plyPatern; //Must be NULL or allocated, else behavior is undefined.
        }
        ++i;
    }
}

/*QByteArray XMLObject::serialiseXMLDocument()
{



}*/

QString XMLObject::findAttribute(const QString& attribute)
{
    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.attribute(attribute,"") != "")
        {
            return e.attribute(attribute);
        }
        n = n.nextSibling();
    }
    return QString();
}

bool XMLObject::addAttributeOnTag(const QString& tagName, const QString& attribute, const QString& value)
{
    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.tagName() == tagName)
        {
            e.setAttribute(attribute, value);

            n.replaceChild(e,n.toElement());
            m_isSynced = false;
            return true;
        }
        n = n.nextSibling();
    }
    return false;
}

void XMLObject::addAttributeWithTag(const QString& NewTagName, const QString& attribute, const QString& value)
{
    QDomElement docElem = m_dom.documentElement();

    QDomElement newElement = m_dom.createElement(NewTagName);
    newElement.setAttribute(attribute,value);
    docElem.appendChild(newElement);

    m_isSynced = false;
}

bool XMLObject::save(const QString& filename)
{

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        file.close();
        qDebug() << tr("Impossible to write file ") << filename;
        return false;
    }

    QTextStream stream(&file);

    stream << m_dom.toString();

    file.close();
    qDebug() << tr("File successfuly written ");
    return true;
    m_isSynced = true;
}

bool XMLObject::doAction(const Event& e)
{
    if(e.action==NOT_AN_ACTION)
        return false;

    if(e.action==ALERT_OWNER)
    {
        qDebug() << "ALERT OWNER : " << e.text;
        emit alertOwner(e.text);
        return true;
    }
    else if(e.action==ALERT_ALL_PLAYERS)
    {
        qDebug() << "ALERT ALL PLAYERS : " << e.text;
        emit alertAllPlayers(e.text);
        return true;
    }
    else if(e.action==ALERT_SPECIAL_PLAYER)
    {
        qDebug() << "ALERT SPECIAL PLAYER ("<<e.data.plyPatern->nameRegExp << ") : " << e.text;
        emit alertPlayers(e.text, *e.data.plyPatern);
        return true;
    }

    return false;
}

bool XMLObject::onEvent(TRIGGER_TYPE trig)
{
    if(trig==NOT_A_TRIGGER)
        return false;

    QList<Event> list=m_eventMap.values(trig);
    bool ret=false;

    for(int i=0;i<list.size();++i)
    {
        doAction(list[i]);
    }

    return ret;
}

#define CAR(x) if(t==#x) return x; //Check&return

TRIGGER_TYPE stringToTrigger(const QString& s)
{
    QString t=s.toUpper();

    CAR(ON_CREATION);
    CAR(ON_DESTRUCTION);
    CAR(ON_THROWN);
    CAR(ON_EQUIPPED);
    CAR(ON_OWNER_CHANGE);

    return NOT_A_TRIGGER;
}



ACTION_TYPE stringToAction(const QString& s)
{
    QString t=s.toUpper();

    CAR(ALERT_GM);
    CAR(ALERT_ALL_PLAYERS);
    CAR(ALERT_OWNER);
    CAR(ALERT_SPECIAL_PLAYER);

    return NOT_AN_ACTION;
}

#undef CAR

void XMLObject::loadEvents()
{
    m_eventMap.clear();

    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();

        if(e.tagName()=="Event")
        {
            QDomNamedNodeMap d=e.attributes();

            QDomNode dn;
            if(!(dn=d.namedItem("trigger")).isNull())
            {
                QDomAttr ta=dn.toAttr();
                if(ta.isNull())
                {
                    qDebug() << "Error casting to attribute...";
                }
                else
                {
                    TRIGGER_TYPE tt=stringToTrigger(ta.value().toUpper());

                    if(tt==NOT_A_TRIGGER)
                    {
                        qDebug() << "Error : unknown trigger type";
                    }
                    else
                    {
                        Event ev;

                        for(int i=0;i<d.size();++i)
                        {
                            QDomAttr attr=d.item(i).toAttr();
                            QString name=attr.name().toUpper();


                            if(name=="TRIGGER"){/* Do nothing */}
                            else if(name=="NAME")
                            {
                                ev.name=attr.value();
                            }
                            else if(name=="ACTION")
                            {
                                ACTION_TYPE at=stringToAction(attr.value());
                                if(at==NOT_AN_ACTION)
                                {
                                    qDebug() << "Error : unknow action.";
                                }
                                else
                                {
                                    if(ev.data.ptr==NULL&&ev.action==NOT_AN_ACTION)
                                    {
                                        ev.action=at;
                                    }
                                    else
                                    {
                                        qDebug() << "Error : multiple 'action' attribute in a single event. Keeping the first one...";
                                    }
                                }
                            }
                            else if(name=="TEXT")
                            {
                                ev.text=attr.value();
                            }
                            else if(name=="PLAYER_NAME_REGEXP")
                            {
                                if(ev.action==ALERT_SPECIAL_PLAYER)
                                {
                                    if(ev.data.plyPatern==NULL)
                                    {
                                        ev.data.plyPatern=new PlayerPatern;
                                    }
                                    ev.data.plyPatern->nameRegExp=attr.value();

                                }
                                else
                                {
                                    qDebug() << "Error : attribute " << name << " does not match with action type.";
                                }
                            }
                            else if(name=="PLAYER_CLASS_REGEXP")
                            {
                                if(ev.action==ALERT_SPECIAL_PLAYER)
                                {
                                    if(ev.data.ptr==NULL)
                                    {
                                        ev.data.plyPatern=new PlayerPatern;
                                    }
                                    ev.data.plyPatern->classRegExp=attr.value();

                                }
                                else
                                {
                                    qDebug() << "Error : attribute " << name << " does not match with action type.";
                                }
                            }
                            else if(name=="PLAYER_NAME")
                            {

                            }
                            else
                            {
                                qDebug() << "Error : unknow attribute.";
                            }
                        }

                        if(ev.isValid())
                            m_eventMap.insert(tt,ev);
                    }
                }
            }
            else
            {
                qDebug() << "Error : event without trigger";
            }
        }

        n = n.nextSibling();
    }
}

bool XMLObject::load(const QString& filename)
{
    if(!m_isSynced)
    {
        qDebug() << tr("RAM document is modified, please save before");
        return false;
    }

    m_dom.clear();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        file.close();
        qDebug() << tr("Impossible to open file ") << filename;
        return false;
    }
    if(!m_dom.setContent(&file))
    {
        qDebug() << tr("An error occured during XML association in RAM");
        return false;
    }

    loadEvents();

    onEvent(ON_CREATION);

    return true;
}
