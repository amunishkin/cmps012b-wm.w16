# $Id: Makefile,v 1.4 2013-02-26 19:50:58-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = main.c queue.c
CHEADER   =        queue.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = catqueue
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE} PARTNER README
LISTSRC   = ${SOURCES} ${DEPSFILE}
OUTPUT    = output*.lis
SUBMITDIR = cmps012b-wm.w13 lab7

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES} test*.data

submit : all
	submit ${SUBMITDIR} ${SOURCES}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${OUTPUT}

spotless : clean
	- rm ${EXECBIN}

test : ${EXECBIN}
	- runprogram.perl -x output1.lis -0test1.data ${EXECBIN}
	- runprogram.perl -x output2.lis ${EXECBIN} test*.data
	- ${GRIND} ${EXECBIN} <test1.data >output3.lis 2>&1

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps


again :
	gmake spotless deps ci all

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

