 #! /bin/bash

file1=/home/lyhhhhh/study/Operating_System/exp/doc/input.txt
file2=/home/lyhhhhh/study/Operating_System/exp/doc/output.txt

diff -q $file1 $file2 

if [ $? != 0 ]

then

    echo "Different!"

else

    echo "Same!"

fi
