#!/bin/bash

PACKAGENAME=timberwolf
VERSION=6.3.6
rm -rf createdeb/
mkdir createdeb
#rm -rf createdeb/$PACKAGENAME-$VERSION
mkdir createdeb/$PACKAGENAME-$VERSION
git archive master | tar -x -C createdeb/$PACKAGENAME-$VERSION
cd createdeb
tar -czvf $PACKAGENAME\_$VERSION.orig.tar.gz $PACKAGENAME-$VERSION
#tar -xvf $PACKAGENAME\_$VERSION.orig.tar.gz
cp -r -v ../debian $PACKAGENAME-$VERSION/
cd $PACKAGENAME-$VERSION
dpkg-buildpackage
