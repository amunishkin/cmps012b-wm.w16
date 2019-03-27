# $Id: Makefile,v 1.2 2013-02-19 18:11:44-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCES = nsort.c lsort.c
SOURCES  = ${CSOURCES} Makefile README PARTNER
EXECBINS = nsort   lsort
SUBMIT   = submit cmps012b-wm.w13 lab6

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

