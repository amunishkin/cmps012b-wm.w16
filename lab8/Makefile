# $Id: Makefile,v 1.1 2013-03-05 17:02:53-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
GRIND     = valgrind --leak-check=full

CSOURCE   = 18stat.c
EXECBIN   = 18stat
SOURCES   = ${CSOURCE} Makefile PARTNER README
SUBMITDIR = cmps012b-wm.w13 lab8

all : ${EXECBIN}

${EXECBIN} : ${CSOURCE}
	${GCC} ${CSOURCE} -o ${EXECBIN}

ci : ${SOURCES}
	cid + ${SOURCES}

submit : all
	submit ${SUBMITDIR} ${SOURCES}

clean :
	- rm ${EXECBIN} 18.*.* 

test : ${EXECBIN}
	- cd ~/12b/Labs-cmps012m/lab8s-unixprog-stat/testdata/
	- ~/private/cmps012b/lab8/${EXECBIN} * >18.c.out 2>18.c.err
	- *.perl * >18.p.out 2>18.p.err
	- diff 18.c.out 18.p.out 
	- diff 18.c.err 18.p.err
	- mv 18.*.* ~/private/cmps012b/lab8/
	- ${GRIND} ~/private/cmps012b/lab8/${EXECBIN} * >18.c.valgrind
	- mv 18.c.v* ~/private/cmps012b/lab8/
	- cd ~/private/cmps012b/lab8/

again :
	gmake clean ci all

