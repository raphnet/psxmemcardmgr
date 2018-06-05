#include <qobject.h>
#include <qmainwindow.h>
#include "CardSlots.h"
#include "PSX_memory_card.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
    MainWindow( QWidget *parent=0, const char *name=0 );

private slots:
	void load_mc_image();
	void save_mc_image();
	void save_single_game();
	void load_single_game();
	void set_gameID();
	void set_gamePcode();
	void new_mc_image();
	void del();
	void undel();
	void upload();
	void download();
	void dummy();
	void showabout();
	void showaboutQt();
private:
	CardSlots *cardslots;   // Gui representation of the memory card
	PSX_memory_card *psx_card;   // Class holding the card data
	void load(QString filename);
	void save(QString filename);
	void clear();  // Clear screen and PSX_memory_card data
	void updateSlots(); //read data from the card object and write it to the screen
};

#endif // MAINWINDOW_H