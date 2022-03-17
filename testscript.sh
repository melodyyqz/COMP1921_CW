#!/bin/bash

# Testing pgmEcho.c without any file names
echo "Testing pgmEcho.c without any file names: ./pgmEcho"
./pgmEcho
echo ""

# Testing pgmEcho.c with one file name 
echo "Testing pgmEcho.c with one file name : ./pgmEcho slice0a.pgm"
./pgmEcho slice0a.pgm
echo ""

# Testing pgmEcho.c with two file names
echo "Testing pgmEcho.c with two file names: ./pgmEcho slice0a.pgm output.pgm"
./pgmEcho slice0a.pgm output.pgm
echo ""

# Testing pgmEcho.c with three file names
echo "Testing pgmEcho.c with three file names: ./pgmEcho slice0a.pgm output.pgm balloons.pgm"
./pgmEcho slice0a.pgm output.pgm balloons.pgm
echo ""

# Testing pgmEcho.c with an input file name which does not exist
echo "Testing pgmEcho.c with an input file name which does not exist: ./pgmEcho notexist.pgm output.pgm"
./pgmEcho notexist.pgm output.pgm
echo ""

# Testing pgmComp.c without any file names

# Testing pgmComp.c with one file name 

# Testing pgmComp.c with two file names

# Testing pgmComp.c with three file names

# Testing pgmComp.c with an input file name which does not exist

# Testing pgmComp.c with an output file name which does not exist

# Testing pgma2b.c with an ASCII input file

# Testing pgma2b.c with a binary input file

# Testing pgmb2a.c with a binary input file

# Testing pgmb2a.c with an ASCII input file