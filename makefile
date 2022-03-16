CC=gcc
CCFLAGS = -g -std=c99 -fmax-errors=1 -Wall -Werror
MODULES = fileHandling.o fileWrite.o pgmReadWrite.o
MAINS = pgmEcho.o pgmComp.o  pgma2b.o
TARGETS = pgmEcho pgmComp pgma2b

all: ${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}
pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}
pgma2b:		pgma2b.o ${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o ${MODULES}
