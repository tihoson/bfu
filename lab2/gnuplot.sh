#!/bin/bash

GNU=$1
LIB=$2

if [[ $# = 0 ]]
	then
		echo 'Enter ./gnuplot <GNUPLOT VER> <LIBGD VER> to install'
	else 
mkdir -p $HOME/gnuplotAndLibs
BASE=$HOME/gnuplotAndLibs

mkdir -p $BASE/downloads

mkdir -p $BASE/downloads/gnuplot
if [[ -d $BASE/downloads/gnuplot/$GNU ]]
        then
                echo "This version of GNUPLOT is already downloaded."
        else
                mkdir $BASE/downloads/gnuplot/$GNU
                cd $BASE/downloads/gnuplot/$GNU
                wget https://kent.dl.sourceforge.net/project/gnuplot/gnuplot/$GNU/gnuplot-$GNU.tar.gz --no-check-certificate
                tar -xvf gnuplot-$GNU.tar.gz
fi

mkdir -p $BASE/downloads/libgd
if [[ -d $BASE/downloads/libgd/$LIB ]]
	then
		echo "This version of LIBGD is already downloaded."
	else
		mkdir $BASE/downloads/libgd/$LIB
		cd $BASE/downloads/libgd/$LIB
		wget https://github.com/libgd/libgd/releases/download/gd-$LIB/libgd-$LIB.tar.gz -O $LIB.tar.gz #
		tar -xvf $LIB.tar.gz #
fi

mkdir -p $BASE/installed

mkdir -p $BASE/installed/libgd
if [[ -d $BASE/installed/libgd/$LIB ]]
        then
                echo "This version of LIBGD is already installed."
        else
                mkdir $BASE/installed/libgd/$LIB
                cd $BASE/downloads/libgd/$LIB/libgd-$LIB
		./configure --prefix=$BASE/installed/libgd/$LIB #
		make install #
		echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BASE/installed/libgd/$LIB/lib" >> $HOME/.bash_profile 
fi

mkdir -p $BASE/installed/gnuplot
if [[ -d $BASE/installed/gnuplot/$GNU ]]
        then
                echo "This version of GNUPLOT is already installed."
        else
                mkdir $BASE/installed/gnuplot/$GNU
                cd $BASE/downloads/gnuplot/$GNU/gnuplot-$GNU
		./configure --prefix=$BASE/installed/gnuplot/$GNU --with-gd=$BASE/installed/libgd/$LIB
                make install
fi

mkdir -p $HOME/bin
if [[ -e $HOME/bin/gnuplot-$GNU-libgd-$LIB ]]
	then
		echo "DONE"
	else
		ln -s $BASE/installed/gnuplot/$GNU/bin/gnuplot $HOME/bin/gnuplot-$GNU-libgd-$LIB
		echo "DONE"
fi

fi
