#! /bin/sh

for i in $(ls -v *.in | sed "s/\.in//g")
do
	./hw5 < $i.in > $i.llvm
  	lli $i.llvm > $i.res -fatal-warnings
	#diff $i.res $i.out
done