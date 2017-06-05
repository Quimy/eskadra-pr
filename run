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
	nr_of_processes=3
	p=2
	s=1
fi

if [ $? = 0 ]
then
	
	mpiexec -n $nr_of_processes ./main.out $nr_of_processes $p $s

fi