/* Cette classe a pour but de gerer l'affichage du contenu de la carte
memoire, soit les icones, les descriptions et le pays d'origine. */
#include <qpixmap.h>
#include <qlayout.h>
#include <qframe.h>
#include <q3listview.h>
#include "CardSlots.h"

CardSlots::CardSlots( QWidget *parent, const char *name ) : QFrame(parent,name)
{
	// create a 3 X 15 grid
	// Parent, row, cols, border, space, name
	//QGridLayout *grid = new QGridLayout( this, 5, 15, 1,0,"name" );
	QVBoxLayout *box = new QVBoxLayout(this, 0,0,"layout");
	this->setFrameStyle(QFrame::Panel | QFrame::Sunken);

	listview = new Q3ListView(this,"listview");
	listview->addColumn("Blk");
	listview->addColumn("Ico");
	listview->addColumn("Title",-1);
	listview->addColumn("Game ID");
	listview->addColumn("Product Code");

	//listview->setColumnWidthMode(2,Maximum);
	listview->setAllColumnsShowFocus(true);
	listview->setSorting(-1,true);

	for (int i=14; i>=0; i--)
	{
    	card_slots[i] = new Q3ListViewItem( listview, QString::number(i+1,10),"", "","","");
	}
	pmEmptyIcon.resize(16,16);

	box->addWidget(listview);

}

void CardSlots::changeIcon(int num, QPixmap pixmap)
{
	card_slots[num]->setText(1,"");
	card_slots[num]->setPixmap(1,pixmap);
}

void CardSlots::changeText(int num, QString string)
{
	card_slots[num]->setText(2,string);
}

void CardSlots::changePcode(int num, QString pcode)
{
	card_slots[num]->setText(4,pcode);
}

void CardSlots::changeGameID(int num, QString gameID)
{
	card_slots[num]->setText(3,gameID);
}

void CardSlots::changeCountry(int num, int cnum)
{
	// Not very useful so not implemented yet...
}

void CardSlots::clearAll()
{
	for (int i=0; i<15; i++)
		clear(i);

}

void CardSlots::clear(int num)
{
    changeIcon(num, pmEmptyIcon);
    changeText(num, "Free");
}

int CardSlots::get_selected_slot()
{
	for (int i=0; i<15; i++)
	{
		if (card_slots[i]->isSelected()) { return i; }
	}
	return -1;  //no slot is selected
}
