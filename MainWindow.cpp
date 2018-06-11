/****************************************************************
**
** Qt tutorial 6
**
****************************************************************/
#include <qapplication.h>

#include <qpushbutton.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <qfont.h>

#include <qmessagebox.h>
#include <qstatusbar.h>
#include <qmenubar.h>
#include <q3popupmenu.h>
#include <qtoolbar.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <q3progressdialog.h>

#include "CardSlots.h"
#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( 0, "PSX")
{

	cardslots = new CardSlots( this, "carte");  // Create the card widget
	psx_card = new PSX_memory_card();  // Create a memory card

	/****************** Set up the menu bar ********************/
	Q3PopupMenu *mnuFile = new Q3PopupMenu(this);
	Q3PopupMenu *mnuEdit = new Q3PopupMenu(this);
	Q3PopupMenu *mnuMemCard = new Q3PopupMenu(this);
	Q3PopupMenu *mnuModify = new Q3PopupMenu(this);

	Q3PopupMenu *mnuHelp = new Q3PopupMenu(this);


	menuBar()->insertItem("&File", mnuFile);
		mnuFile->insertItem( "&New Memory Card Image", this, SLOT( new_mc_image() ),Qt::CTRL+Qt::Key_N);
		mnuFile->insertSeparator();
		mnuFile->insertItem( "&Load Image", this, SLOT( load_mc_image() ),Qt::CTRL+Qt::Key_O);
		mnuFile->insertItem( "&Save Image", this, SLOT( save_mc_image() ),Qt::CTRL+Qt::Key_S);
		mnuFile->insertSeparator();
		mnuFile->insertItem( "Load Single Game Save", this, SLOT( load_single_game() ));
		mnuFile->insertItem( "Save Single Game Save", this, SLOT( save_single_game() ));
		mnuFile->insertSeparator();
		mnuFile->insertItem( "&Quit", qApp, SLOT( quit() ) );

    menuBar()->insertItem("&Edit", mnuEdit);
		mnuEdit->insertItem("Cut", this, SLOT( dummy() ) );
		mnuEdit->insertItem("Copy", this, SLOT( dummy() ) );
		mnuEdit->insertItem("Paste", this, SLOT( dummy() ) );
		mnuEdit->insertSeparator();
		mnuEdit->insertItem("Delete block", this, SLOT( del() ) );
		mnuEdit->insertItem("UnDelete block", this, SLOT( undel() ) );

	menuBar()->insertItem("&Modify", mnuModify);
		mnuModify->insertItem("Edit Product code...", this, SLOT( set_gamePcode() ) );
		mnuModify->insertItem("Edit Game ID...", this, SLOT( set_gameID() ) );
		mnuModify->insertItem("Edit Title...", this, SLOT( dummy() ) );

	menuBar()->insertItem("&MemCard", mnuMemCard);
		mnuMemCard->insertItem( "Write to memory card", this, SLOT( upload() ) );
		mnuMemCard->insertItem( "Read from memory card", this, SLOT( download() ) );


	menuBar()->insertItem("&Help", mnuHelp);
		mnuHelp->insertItem("&About...", this, SLOT( showabout() ));
		mnuHelp->insertItem("&About Qt...", this, SLOT( showaboutQt() ));


	setCentralWidget(cardslots);
	statusBar()->message( "Ready", 2000 );
	resize( 400, 340 );

    clear();   // just in case
}

void MainWindow::new_mc_image()
{
	clear();
}

void MainWindow::load_mc_image()
{
	QString fn = QFileDialog::getOpenFileName( QString::null, "Memory Card images(*.mc *.mcr *.gme)",
                                               this);
    if ( !fn.isEmpty() )
        load( fn );
    else
        statusBar()->message( "Loading aborted", 2000 );
}


void MainWindow::save_mc_image()
{
	QString fn = QFileDialog::getSaveFileName( QString::null, "*.mc", this);
    if ( !fn.isEmpty() )
        save( fn );
    else
        statusBar()->message( "Saving aborted", 2000 );
}

void MainWindow::save_single_game()
{
	int selected_slot = cardslots->get_selected_slot();

    if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}
	if (psx_card->get_slot_is_free(selected_slot))
	{
		QMessageBox::information(this,"Error","Cannot save an empty block");
		return;
	}


	QString fn = QFileDialog::getSaveFileName( QString::null, "*.mcs", this);
	if ( !fn.isEmpty() )
        psx_card->save_single_game(fn, selected_slot);
    else
        statusBar()->message( "Saving aborted", 2000 );


}

void MainWindow::load_single_game()
{
	int selected_slot = cardslots->get_selected_slot();

	if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}
	if (!psx_card->get_slot_is_free(selected_slot))
	{
		if (QMessageBox::warning(this, "Warning","This will overwrite current block. Continue?","Yes","No",0,0,1)==1)
		{
			return;
		}

	}

	QString fn = QFileDialog::getOpenFileName( QString::null, "*.mcs", this);
	if ( !fn.isEmpty() )
	{
        psx_card->load_single_game(fn, selected_slot);
		updateSlots();
	}
    else
        statusBar()->message( "Loading aborted", 2000 );

}

void MainWindow::set_gameID()
{
	bool ok = FALSE;
	int selected_slot = cardslots->get_selected_slot();
	if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}

	QString oldtext = psx_card->get_slot_gameID(selected_slot);
	QString text = QInputDialog::getText(this, "Edit game ID","Please enter the new game ID.", QLineEdit::Normal, oldtext , &ok);
	if ( ok && !text.isEmpty() )
    {
		psx_card->set_slot_gameID(selected_slot, text);
		updateSlots();
	}
	else
		statusBar()->message("Change game ID aborted", 2000);

}

void MainWindow::set_gamePcode()
{
	bool ok = FALSE;
	int selected_slot = cardslots->get_selected_slot();
	if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}

	QString oldtext = psx_card->get_slot_Pcode(selected_slot);
	QString text = QInputDialog::getText(this, "Edit game Product Code","Please enter the new product code.", QLineEdit::Normal, oldtext , &ok );
	if ( ok && !text.isEmpty() )
    {
		psx_card->set_slot_Pcode(selected_slot, text);
		updateSlots();
	}
	else
		statusBar()->message("Change game ID aborted", 2000);

}

void MainWindow::del()
{
	int selected_slot = cardslots->get_selected_slot();

	if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}

	if (psx_card->get_slot_is_free(selected_slot))
	{
		QMessageBox::information(this,"Error","This block is already deleted.");
		return;
	}

	psx_card->delete_slot(selected_slot);
	updateSlots();
}

void MainWindow::undel()
{
	int selected_slot = cardslots->get_selected_slot();

	if (selected_slot==-1)
	{
		QMessageBox::information(this,"Error","Please select a block first.");
		return;
	}

	if (!psx_card->get_slot_is_free(selected_slot))
	{
		QMessageBox::information(this,"Error","This block is used.");
		return;
	}

	psx_card->undelete_slot(selected_slot);
	updateSlots();
}

void MainWindow::upload()
{
	int retry=0;

	if (!get_perm())
	{
		QMessageBox::information(this,"Error","Cannot obtain I/O permissions\n\n"
		"Please run this program with\n"
		"super user privileges.");
		return;
	}

	Q3ProgressDialog qp("label 1","Stop",1024,this,"qp",true);

    qp.setProgress(0);
    qp.setAutoClose(true);
	qp.setMinimumDuration(0);
	qp.setCaption("Writing to memory card...");
	qp.show();
	for (int i=0; i<1024; i++)
	{
		qp.setProgress( i );
		qApp->processEvents();

		//qp.setLabelText("Writing Block "+QString::number((i/64)+1,10)+"/16");
		if (retry==0) { qp.setLabelText("Writing Block "+QString::number((i/64)+1,10)+"/16"); }
		else
		{
			if (retry<1023)
			{
				qp.setLabelText("Retry #"+QString::number(retry));
			}
			else
			{
				qp.setLabelText("Still trying...(is there a memory card?)");
			}
		}
		if (qp.wasCancelled())
		{
			QMessageBox::warning(this,"Error","Data on memory card may be corrupted.");
			return;
		}

		//psx_card->save_card_frame(i);
		if (!psx_card->save_card_frame(i))
		{
			retry++;
			if (retry>=1024) { retry=1024; }
			i--;
		}
		else
		{
			retry=0;

		}
	}
	psx_card->update_data();
	updateSlots();
}

void MainWindow::download()
{
	int retry=0;

	if (!get_perm())
	{
		QMessageBox::information(this,"Error","Cannot obtain I/O permissions\n\n"
		"Please run this program with\n"
		"super user privileges.");
		return;
	}

	Q3ProgressDialog qp("label 1","Stop",1024,this,"qp",true);

    //qp.setProgress(0);
    qp.setAutoClose(true);
	qp.setMinimumDuration(0);
	qp.setCaption("Reading from memory card...");
	qp.show();
	for (int i=0; i<1024; i++)
	{
		qp.setProgress( i );
		qApp->processEvents();

		if (retry==0) { qp.setLabelText("Reading Block "+QString::number((i/64)+1,10)+"/16"); }
		else
		{
			if (retry<1023)
			{
				qp.setLabelText("Retry #"+QString::number(retry));
			}
			else
			{
				qp.setLabelText("Still trying...(is there a memory card?)");
			}
		}

		if (qp.wasCancelled()) { return; }

		if (psx_card->load_card_frame(i))
		{
			retry++;
			if (retry>=1024) { retry=1024; }
			i--;
		}
		else
		{
			retry=0;

		}
	}
	psx_card->update_data();
	updateSlots();
}

/**************************************************/

void MainWindow::dummy()
{
	QMessageBox::information(this,"Sorry","Not available yet...");
}

#define xstr(a) str(a)
#define str(a) #a

void MainWindow::showabout()
{
	QMessageBox::about(this,"About","PSX Memory Card Manager v" xstr(VERSION) "\n"
	"By Raphael Assenat\n"
	"Memory Card I/O by Richard Davies\n"
	"\nhttp://www.raphnet.net/programmation/psxmemcardmgr/index_en.php");
}

void MainWindow::showaboutQt()
{
	QMessageBox::aboutQt(this,"PSX Memory Card Manager v0.1");
}

void MainWindow::load(QString filename)
{
	psx_card->load_file(filename);  // Fill in the data holder
    updateSlots();
}

void MainWindow::save(QString filename)
{
	psx_card->save_file(filename);  // Fill in the data holder
}

void MainWindow::clear()
{
	psx_card->clearData();
	updateSlots();
}

void MainWindow::updateSlots()
{
	// Read data from the PSX_memory_card object
	// Write it into the cardslots widget
	for (int i=0; i<15; i++)
	{
		cardslots->changePcode(i,psx_card->get_slot_Pcode(i));
		cardslots->changeText(i,psx_card->get_slot_title(i));
		cardslots->changeIcon(i,psx_card->get_slot_icon(i));
		cardslots->changeGameID(i,psx_card->get_slot_gameID(i));
	}
}
