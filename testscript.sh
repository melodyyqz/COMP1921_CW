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

# Testing pgmEcho.c with bad magic number
echo "Testing pgmEcho.c with bad magic number: ./pgmEcho badmagicnum.pgm output.pgm"
./pgmEcho badmagicnum.pgm output.pgm
echo ""

# Testing pgmEcho.c with too long comment line
echo "Testing pgmEcho.c with too long comment line: ./pgmEcho longcomment.pgm output.pgm"
./pgmEcho longcomment.pgm output.pgm

# Testing pgmEcho.c with width past max dimensions
echo "Testing pgmEcho.c with width past max dimensions: ./pgmEcho highwidthdimensions.pgm output.pgm"
./pgmEcho highwidthdimensions.pgm output.pgm
echo ""

# Testing pgmEcho.c with width below min dimensions
echo "Testing pgmEcho.c with width below min dimensions: ./pgmEcho lowwidthdimensions.pgm output.pgm"
./pgmEcho lowwidthdimensions.pgm output.pgm
echo ""

# Testing pgmEcho.c with a bad gray value
echo "Testing pgmEcho.c with a bad gray value: ./pgmEcho badgray.pgm output.pgm"
./pgmEcho badgray.pgm output.pgm
echo ""

# Testing pgmEcho.c when there is bad data with a gray value over 255
echo "Testing pgmEcho.c when there is bad data with a gray value over 255: ./pgmEcho highgray.pgm output.pgm"
./pgmEcho highgray.pgm output.pgm
echo ""

# Testing pgmEcho.c when there is bad data with a gray value under 0
echo "Testing pgmEcho.c when there is bad data with a gray value under 0: ./pgmEcho lowgray.pgm output.pgm"
./pgmEcho lowgray.pgm output.pgm
echo ""


# Testing pgmComp.c without any file names
echo "Testing pgmComp.c without any file names: ./pgmComp"
./pgmComp
echo ""

# Testing pgmComp.c with one file name 
echo "Testing pgmComp.c with one file name : ./pgmComp slice0a.pgm"
./pgmComp slice0a.pgm
echo ""

# Testing pgmComp.c with three file names
echo "Testing pgmComp.c with three file names: ./pgmComp slice0a.pgm output.pgm balloons.pgm"
./pgmComp slice0a.pgm output.pgm balloons.pgm
echo ""

# Testing pgmComp.c with an input file name which does not exist
echo "Testing pgmComp.c with an input file name which does not exist: ./pgmComp notexist.pgm output.pgm"
./pgmComp notexist.pgm output.pgm
echo ""

# Testing pgmComp.c with an output file name which does not exist
echo "Testing pgmComp.c with an input file name which does not exist: ./pgmComp output.pgm notexist.pgm"
./pgmComp output.pgm notexist.pgm
echo ""

# Testing pgmComp.c with two identical ASCII files
echo "Testing pgmComp.c with two identical ASCII files: ./pgmComp slice0a.pgm output.pgm"
./pgmComp slice0a.pgm output.pgm
echo ""

# Testing pgmComp.c with two different ASCII files
echo "Testing pgmComp.c with two identical ASCII files: ./pgmComp slice0a.pgm balloons.pgm"
./pgmComp slice0a.pgm balloons.pgm
echo ""

# Testing pgmComp.c with two identical binary files
echo "Testing pgmComp.c with two identical binary files: ./pgmComp coins.pgm binary.pgm"
./pgmEcho binary
./pgma2b 
./pgmComp slice0a.pgm balloons.pgm
echo ""

# Testing pgmComp.c with two different binary files

# Testing pgma2b.c with an ASCII input file

# Testing pgma2b.c with a binary input file

# Testing pgmb2a.c with a binary input file

# Testing pgmb2a.c with an ASCII input file