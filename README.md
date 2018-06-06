# Playstation memory card image manipulation tool

This is a graphical tool for managing PSX memory card images.

It still has a few limitations:

* Does not handle correctly multiple block saves
* Edit title not available
* No way to read or edit dexdrive comments
* No configuration dialog(and no configuration file)

The project homepage is located at: http://www.raphnet.net/programmation/psxmemcardmgr/index_en.php

## Compilation

### Linux version

To compile, generate a Makefile by running qmake first. Note that on some systems,
you may need to use qmake-qt4 instead). You also have to install some packages such
as libqt4-dev.

If you want to change the parallel port IO port, edit card_link.c

### Windows version

To cross-compile the Windows version under Linux using mxe, simply run the qmake
executable from your mxe installation (eg: /opt/mxe/mxe/usr/i686-w64-mingw32.static/qt/bin/qmake)

## License

General Public License version 3.

## Authors

* **Raphael Assenat**

## Acknowledgments

* **Richard Davies** - For psxpblib
