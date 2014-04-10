#!/bin/sh

if [ -d targets ];then
  echo "delete targets folder"
  exit 0
fi

if [ "$#" -lt 1 ];then
    echo "Enter version"
    read v
else
    v="$1"
fi

echo "Enter key:"
read gk

./debian.sh $v || exit 1

echo "Targets:"
cat targets.list
mkdir targets || exit 1
for target in `cat targets.list`
do
    echo "Building $target"
    mkdir targets/$target || exit 1
    cp -r "huggle-$v" "targets/$target/huggle-$v" || exit 1
    cp "huggle_$v.orig.tar.gz" "targets/$target/huggle_$v.orig.tar.gz" || exit 1
    if [ -f "targets.info/"$target"_control" ];then
        cp "targets.info/"$target"_control" "targets/$target/huggle_$v/debian/control" || exit 1
    fi
    cd "targets/$target/huggle-$v" || exit 1
    cat debian/changelog | sed "s/precise/$target/" | sed "s/-ppa/-$target/" > debian/.changelog || exit 1
    mv debian/.changelog debian/changelog || exit 1
    debuild -k$gk -S -sa || exit 1
    cd -
done
