#include <qapplication.h>
#include "MainWindow.h"

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    a.setMainWidget( &w );
	w.setCaption( "PSX Memory Card manager v0.9" );
    w.show();
    return a.exec();
}