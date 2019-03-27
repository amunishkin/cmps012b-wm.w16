# $Id: Makefile,v 1.1 2013-02-28 13:58:06-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhcahu)

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM

CSOURCE   = debugf.c stack.c bigint.c token.c main.c
CHEADER   = debugf.h stack.h bigint.h token.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = mydc
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE} README PARTNER
SOURCES   = ${SUBMITS}
PROJECT   = cmps012b-wm.w13 asg4

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${EXECBIN}.errs

spotless : clean
	- rm ${EXECBIN}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${GMAKE} deps

again :
	${GMAKE} spotless deps ci all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

