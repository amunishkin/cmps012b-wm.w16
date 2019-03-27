# $Id: Makefile,v 1.1 2013-03-05 19:08:50-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM

CSOURCE   = debugf.c hashset.c strhash.c spellchk.c
CHEADER   = debugf.h hashset.h strhash.h yyextern.h
OBJECTS   = ${CSOURCE:.c=.o} scanner.o
EXECBIN   = spellchk
SUBMITS   = ${CHEADER} ${CSOURCE} scanner.l ${MKFILE} README PARTNER
SOURCES   = ${SUBMITS}
LISTING   = Listing.code.ps
PROJECT   = cmps012b-wm.w13 asg5

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

scanner.o : scanner.l
	flex -oscanner.c scanner.l
	gcc -g -O0 -std=gnu99 -c scanner.c

%.o : %.c
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core scanner.c ${EXECBIN}.errs

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

