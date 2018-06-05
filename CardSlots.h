#include <qwidget.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <qpixmap.h>
#include <qframe.h>
#include <qlistview.h>

#ifndef CARDSLOTS_H
#define CARDSLOTS_H

class CardSlots : public QFrame
{
	Q_OBJECT

public:
	CardSlots(QWidget *parent=0, const char *name=0);
	int get_selected_slot();
public slots:
	void changeIcon(int num, QPixmap pixmap);
	void changeText(int num, QString string);
	void changePcode(int num, QString pcode);
	void changeGameID(int num, QString gameID);
	void changeCountry(int num, int cnum);
	void clearAll();
	void clear(int num);

private:
	QListViewItem *card_slots[15];

	QLabel *lblIcons[15];
	QRadioButton *radioBtn[15];
	QLabel *lblCountry[15];
	QLabel *lblPcode[15];
	QLabel *lblGameID[15];
	QPixmap pmEmptyIcon;
	QListView *listview;
};

#endif    // CARDSLOTS_H