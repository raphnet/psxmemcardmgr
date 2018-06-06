#include <qapplication.h>
#include "MainWindow.h"

#define xstr(a) str(a)
#define str(a) #a

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    a.setMainWidget( &w );
	w.setCaption( "PSX Memory Card manager v" xstr(VERSION) );
    w.show();

    return a.exec();
}
