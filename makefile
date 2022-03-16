CC=gcc
CCFLAGS = -g -std=c99 -fmax-errors=1 -Wall -Werror
MODULES = fileHandling.o fileWrite.o pgmReadWrite.o
MAINS = pgmEcho.o pgmComp.o  pgma2b.o pgmb2a.o
TARGETS = pgmEcho pgmComp pgma2b pgmb2a

all: ${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}
pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}

pgma2b:		pgma2b.o ${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o ${MODULES}

pgmb2a:		pgmb2a.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.o ${MODULES}