CC=gcc
CCFLAGS = -g -std=c99 -fmax-errors=1 -Wall -Werror
MODULES = fileHandling.o fileWrite.o pgmReadWrite.o pgmConversion.o
MAINS = pgmEcho.o pgmComp.o
TARGETS = pgmEcho pgmComp

all: ${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}
pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}
