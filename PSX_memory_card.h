#include <qstring.h>
#include <qpixmap.h>
#include <qimage.h>
#include "card_link.h"

#ifndef PSX_MEM_CARD_H
#define PSX_MEM_CARD_H

class PSX_memory_card
{
public:
	PSX_memory_card();
	~PSX_memory_card();

	// action commands
	int load_file(QString filename);
    int save_file(QString filename);
	int clearData();

	int load_card();
	int save_card();

	int load_card_block(int block);
	int save_card_block(int block);

	int load_card_frame(int frame);
	int save_card_frame(int frame);
	void update_data();
	int save_single_game(QString filename, int src_slot);
	int load_single_game(QString filename, int dest_slot);
	int delete_slot(int slot);
	int undelete_slot(int slot);

	// informaton commands
	QString get_slot_Pcode(int slot);
	QString get_slot_title(int slot);
	QString get_slot_gameID(int slot);
	QPixmap get_slot_icon(int slot);

	// information change command
	void set_slot_gameID(int slot, QString newID);
	void set_slot_title(int slot, QString newTitle);
	void set_slot_Pcode(int slot, QString newPcode);

	bool get_slot_is_used(int slot);
	bool get_slot_is_free(int slot);


private:
	char memoryCard[131072];   //a memory card can hold 128K
	bool slot_is_used[15];
	bool slot_is_deleted[15];  // deleted, but SC still there
	bool slot_has_icon[15];
	unsigned char block_type[15]; // 0 not used, 1 top block, 2 link, 3 link end block
	QString slot_Pcodes[15];
	QString slot_gameID[15];
	QString slot_titles[15];
	QImage *slot_icons[15];
	void update();
	void update_slot_is_used();  // also updates block_type
	void update_slot_is_deleted();
	void update_slot_has_icon();
	void update_slot_Pcodes();
	void update_slot_gameIDs();
	void update_slot_titles();
	void update_slot_iconImages();
};

#endif   // PSX_MEM_CARD_H