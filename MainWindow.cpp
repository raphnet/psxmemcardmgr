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
#include <QMenuBar>
#include <qtoolbar.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <QProgressDialog>

#include "CardSlots.h"
#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow(nullptr)
{
	setObjectName("PSX");
	cardslots = new CardSlots( this, "carte");  // Create the card widget
	psx_card = new PSX_memory_card();  // Create a memory card

	/****************** Set up the menu bar ********************/
	QMenu *mnuFile = new QMenu("&File", this);
	QMenu *mnuEdit = new QMenu("&Edit", this);
	QMenu *mnuMemCard = new QMenu("Mem&Card", this);
	QMenu *mnuModify = new QMenu("&Modify", this);

	QMenu *mnuHelp = new QMenu("&Help", this);


	menuBar()->addMenu(mnuFile);
		mnuFile->addAction( "&New Memory Card Image", this, SLOT( new_mc_image() ),Qt::CTRL+Qt::Key_N);
		mnuFile->addSeparator();
		mnuFile->addAction( "&Open Image", this, SLOT( load_mc_image() ),Qt::CTRL+Qt::Key_O);
		mnuFile->addAction( "&Save Image", this, SLOT( save_mc_image() ),Qt::CTRL+Qt::Key_S);
		mnuFile->addSeparator();
		mnuFile->addAction( "Load Single Game Save", this, SLOT( load_single_game() ));
		mnuFile->addAction( "Save Single Game Save", this, SLOT( save_single_game() ));
		mnuFile->addSeparator();
		mnuFile->addAction( "&Quit", qApp, SLOT( quit() ), Qt::CTRL+Qt::Key_Q);

	menuBar()->addMenu(mnuEdit);
		mnuEdit->addAction("Cut", this, SLOT( dummy() ) );
		mnuEdit->addAction("Copy", this, SLOT( dummy() ) );
		mnuEdit->addAction("Paste", this, SLOT( dummy() ) );
		mnuEdit->addSeparator();
		mnuEdit->addAction("Delete block", this, SLOT( del() ) );
		mnuEdit->addAction("UnDelete block", this, SLOT( undel() ) );

	menuBar()->addMenu(mnuModify);
		mnuModify->addAction("Edit Product code...", this, SLOT( set_gamePcode() ) );
		mnuModify->addAction("Edit Game ID...", this, SLOT( set_gameID() ) );
		mnuModify->addAction("Edit Title...", this, SLOT( dummy() ) );

	menuBar()->addMenu(mnuMemCard);
		mnuMemCard->addAction( "Write to memory card", this, SLOT( upload() ) );
		mnuMemCard->addAction( "Read from memory card", this, SLOT( download() ) );


	menuBar()->addMenu(mnuHelp);
		mnuHelp->addAction("&About...", this, SLOT( showabout() ));
		mnuHelp->addAction("About &Qt...", this, SLOT( showaboutQt() ));


	setCentralWidget(cardslots);
	statusBar()->showMessage( "Ready", 2000 );
	resize( 550, 400 );

    clear();   // just in case
}

void MainWindow::new_mc_image()
{
	clear();
}

void MainWindow::load_mc_image()
{
	QString fn = QFileDialog::getOpenFileName( this, QString::null, QString::null, "Memory Card images(*.mc *.mcr *.gme)");
    if ( !fn.isEmpty() )
        load( fn );
    else
        statusBar()->showMessage( "Loading aborted", 2000 );
}


void MainWindow::save_mc_image()
{
	QString fn = QFileDialog::getSaveFileName( this, QString::null, QString::null, "*.mc");
    if ( !fn.isEmpty() )
        save( fn );
    else
        statusBar()->showMessage( "Saving aborted", 2000 );
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


	QString fn = QFileDialog::getSaveFileName( this, QString::null, QString::null, "*.mcs");
	if ( !fn.isEmpty() )
        psx_card->save_single_game(fn, selected_slot);
    else
        statusBar()->showMessage( "Saving aborted", 2000 );


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

	QString fn = QFileDialog::getOpenFileName(this, QString::null, QString::null, "*.mcs");
	if ( !fn.isEmpty() )
	{
        psx_card->load_single_game(fn, selected_slot);
		updateSlots();
	}
    else
        statusBar()->showMessage( "Loading aborted", 2000 );

}

void MainWindow::set_gameID()
{
	bool ok = false;
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
		statusBar()->showMessage("Change game ID aborted", 2000);

}

void MainWindow::set_gamePcode()
{
	bool ok = false;
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
		statusBar()->showMessage("Change game ID aborted", 2000);

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

	QProgressDialog qp("label 1","Stop",0,1024,this);

	qp.setModal(true);
	qp.setValue(0);
	qp.setAutoClose(true);
	qp.setMinimumDuration(0);
	qp.setWindowTitle("Writing to memory card...");
	qp.show();
	for (int i=0; i<1024; i++)
	{
		qp.setValue( i );
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
		if (qp.wasCanceled())
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

	QProgressDialog qp("label 1","Stop",0,1024,this);

	qp.setModal(true);
	qp.setAutoClose(true);
	qp.setMinimumDuration(0);
	qp.setWindowTitle("Reading from memory card...");
	qp.show();
	for (int i=0; i<1024; i++)
	{
		qp.setValue( i );
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

		if (qp.wasCanceled()) { return; }

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
