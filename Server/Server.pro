TEMPLATE = app


CONFIG += console
QT += network
QT += xml

LIBS += -llua5.1


QMAKE_CXXFLAGS += -O3 -s -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wshadow  -Wredundant-decls -Wswitch


SOURCES += main.cpp Network.cpp ../Shared/Packet.cpp Client.cpp Server.cpp Player.cpp ../Shared/Serializer.cpp ServerSwitch.cpp ../Shared/Miscelaneous.cpp Translator.cpp ScriptEnvironnement.cpp VOIPServer.cpp
HEADERS += Network.h ../Shared/Packet.h Client.h Server.h ../Shared/Constants.h Player.h ../Shared/Serializer.h Translator.h ScriptEnvironnement.h VOIPServer.h

SOURCES += \
    ../Shared/LuaSystem/ScriptedEntity.cpp \
    ../Shared/LuaSystem/ScriptedEntityCallbacks.cpp

HEADERS += \
    ../Shared/LuaSystem/ScriptedEntity.h \
    ../Shared/LuaSystem/luaHeader.h
