#

QTDIR=/usr/share/qt4

CC = g++
LD = $(CC)
MOC = $(QTDIR)/bin/moc

LDFLAGS =

PACKAGES=QtGui Qt3Support

PROG = PSX_cardmgr
CFLAGS = `pkg-config --cflags $(PACKAGES)` -fPIC
LDFLAGS = `pkg-config --libs $(PACKAGES)`

all: $(PROG)

clean:
	rm -f $(PROG) *.o *.core core *.bak moc_*

all: $(PROG)

$(PROG): MainWindow.o moc_MainWindow.o CardSlots.o moc_CardSlots.o main.o PSX_memory_card.o psxpblib.o card_link.o
	$(LD) $(LDFLAGS) MainWindow.o moc_MainWindow.o CardSlots.o moc_CardSlots.o main.o  PSX_memory_card.o card_link.o psxpblib.o -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

MainWindow.o: MainWindow.cpp MainWindow.h
	$(CC) $(CFLAGS) -c MainWindow.cpp

moc_MainWindow.o: MainWindow.h
	$(MOC) MainWindow.h -o moc_MainWindow.cpp
	$(CC) $(CFLAGS) -c moc_MainWindow.cpp

CardSlots.o: CardSlots.cpp CardSlots.h
	$(CC) $(CFLAGS) -c CardSlots.cpp

moc_CardSlots.o: CardSlots.h
	$(MOC) CardSlots.h -o moc_CardSlots.cpp
	$(CC) $(CFLAGS) -c moc_CardSlots.cpp

PSX_memory_card.o: PSX_memory_card.cpp PSX_memory_card.h
	$(CC) $(CFLAGS) -c PSX_memory_card.cpp

psxpblib.o: psxpblib.c psxpblib.h
	gcc -O2 -D_PSXPB_LINUX_ -D_PSX_LINUX_ -c psxpblib.c

card_link.o: card_link.c card_link.h
	gcc -D_PSXPB_LINUX_ -D_PSX_LINUX_ -c card_link.c

