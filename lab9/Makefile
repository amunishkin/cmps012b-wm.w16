# $Id: Makefile,v 1.2 2013-03-12 15:54:38-07 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhcahu)

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = inssort.c numsort.c linesort.c
CHEADER   = inssort.h 
EXECBINS  = ${BIN1} ${BIN2}
BIN1      = numsort
BIN2      = linesort
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE} README PARTNER
SOURCES   = ${SUBMITS}
LAB       = cmps012b-wm.w13 lab9

all : ${EXECBINS}

${BIN1} : numsort.o inssort.o
	${GCC} -o $@ numsort.o inssort.o 

${BIN2} : linesort.o inssort.o
	${GCC} -o $@ linesort.o inssort.o

%.o : %.c
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

test : ${EXECBINS}
	${GRIND} ${BIN1} >num.valgrind.out
	${GRIND} ${BIN2} >line.valgrind.out

clean :
	- rm core *.o ${BIN1}.errs ${BIN2}.errs *.valgrind.out

spotless : clean
	- rm ${EXECINS}

submit : ${SUBMITS}
	submit ${LAB} ${SUBMITS}

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${GMAKE} deps

again :
	${GMAKE} spotless deps ci all

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif
