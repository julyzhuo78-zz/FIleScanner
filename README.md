This file scanner is programmed in C++ and it is used to count the number of single comments, block comments, to-do's and so on.

Sample expected output:
Total # of lines: 60
Total # of comment lines: 28
Total # of single line comments: 6
Total # of comment lines within block comments: 22
Total # of block line comments: 2
Total # of TODO’s: 1

How to run it:
1. Run "g++ -std=c++11 -Wall -Wextra -Werror main.cc ScanningFailure.cc ScanningFile.cc -o main" in your terminal.
2. Run “./main” in your terminal.
3. Enter the file you want the program to read (ie. test1, test2, test3)
Things to note:
1. The # of comment lines within block comments is calculated by counting the no of lines in between and including "/*" and "*/".
eg. "/*
Some code..
*/" is counted as 3
2. When the block is in one row (eg:"/* */"), the no of lines in this block is counted as 1.
3. Invalid or non-existent file leads to an error message "Fail to scan due to invalid file" printed on the screen.
4. All comment styles should be strictly following either c++ style ("// or /* */") or python script style ("#").
Thank you for reading and happy testing!
