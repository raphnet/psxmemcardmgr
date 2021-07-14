CONFIG += release
TEMPLATE = app
TARGET = psxcardmgr
DEPENDPATH += .
INCLUDEPATH += .

QT += widgets

DEFINES += VERSION=0.9.1

win32 {
	DEFINES += _PSXPB_WIN32_
} else {
	DEFINES += _PSXPB_LINUX_ _PSX_LINUX_
}

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-parameter

HEADERS += card_link.h CardSlots.h MainWindow.h PSX_memory_card.h psxpblib.h
SOURCES += card_link.c main.cpp PSX_memory_card.cpp CardSlots.cpp MainWindow.cpp psxpblib.c

