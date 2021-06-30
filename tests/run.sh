#! /bin/sh

for i in $(ls -v *.c | sed "s/\.c//g")
do
	./hw5 < $i.c > $i.llvm
  	lli $i.llvm > $i.res -fatal-warnings
	#diff $i.res $i.out
done