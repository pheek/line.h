#!/bin/bash
# run the compiled test file
echo "testfile.txt"
./testLineReader <tst/testfile.txt

echo "testfileHavingEmptyLineAtEnd.txt"
./testLineReader <tst/testfileHavingEmptyLineAtEnd.txt

echo "testfileWithoutNewLineAtTheEnd.txt"
./testLineReader <tst/testfileWithoutNewLineAtTheEnd.txt
