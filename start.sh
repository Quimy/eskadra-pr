#!/usr/bin/env bash

if [ $# = 0 ]
then
	nr_of_processes=3
	p=2
	s=1
elif [ $# = 3 ]
then
	nr_of_processes=$1
	p=$2
	s=$3
else
	echo Usage: ./compileAndRun [nr_of_processes=3] [p=2] [s=1]
	exit 1
fi

mpicxx src/main.cpp src/Process.cpp src/Responses.cpp src/ThreadSafeVector.cpp -o main.out -std=c++14 -lpthread

if [ $? = 0 ]
then
	
	mpiexec -n $nr_of_processes ./main.out $nr_of_processes $p $s

fi