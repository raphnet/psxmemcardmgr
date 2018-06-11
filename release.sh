#!/bin/bash

PREFIX=psx_memory_card_manager

echo "Release script for $PREFIX"

if [ $# -ne 1 ]; then
	echo "Syntax: ./release.sh releasedir"
	echo
	exit
fi

VERSION=`cat psxcardmgr.pro | grep VERSION | cut -d '=' -f 3`
RELEASEDIR=$1
DIRNAME=$PREFIX-$VERSION
FILENAME=$PREFIX-$VERSION.tar.gz
TAG=v$VERSION

echo "Version: $VERSION"
echo "Filename: $FILENAME"
echo "Release directory: $RELEASEDIR"
echo "--------"
echo "Ready? Press ENTER to go ahead (or CTRL+C to cancel)"

read

if [ -f $RELEASEDIR/$FILENAME ]; then
	echo "Release file already exists!"
	exit 1
fi

git tag $TAG -f
git archive --format=tar --prefix=$DIRNAME/ HEAD | gzip > $RELEASEDIR/$FILENAME
