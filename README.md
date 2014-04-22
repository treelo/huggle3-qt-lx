huggle3-qt-lx
=============

Huggle 3 QT-LX is an anti-vandalism tool for use on Wikipedia and other Wikimedia projects, written in C++ (QT framework).  It is officialy supported for Windows (2000 or newer) and Linux (debian/ubuntu), but it may work on other distributions as well as MacOS.

This is a repository that is used to build debian packages

Easy
=====

 * git merge master debian
 * run debian.sh

Help
======

 * First we need to download a zip of this package to /tmp
 * Now we can unzip it
 * Now we need to switch to huggle3-qt-lx and create a tarball of huggle folder

Linux
-------------

run ./ubuntu.sh

Huggle is using google breakpad so when it crash a minidump should be generated.
In addition a core dump may be produced on linux systems. Both of these, or at
least minidump is very useful for developers to track the problems. So if the
minidump is generated during crash (you will see that in system log) you can
send this to developers in order to get the issue analysed and fixed.
