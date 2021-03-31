#!/bin/sh

cp $1.cpp $2.cpp
cp $1.h $2.h

sed -i s/$1/$2/g $2.cpp
sed -i s/$1/$2/g $2.h

