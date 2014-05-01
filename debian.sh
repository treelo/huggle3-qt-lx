#!/bin/sh

if [ ! -f huggle/version.txt ];then
    echo "There is no version.txt file, please generate it first"
    exit 1
fi

version=`cat huggle/version.txt`

echo "Generating package for huggle $version"

if [ "$#" -lt 1 ];then
    echo "Enter version"
    read v
else
    v="$1"
fi

tar -zcf "huggle_"$v".orig.tar.gz" huggle
cp -r huggle huggle-"$v"
cp "huggle-$v"/huggle.orig "huggle-$v"/huggle.pro
cd huggle-"$v"
echo debuild -S -sa
