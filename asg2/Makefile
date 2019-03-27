# $Id: Makefile,v 1.3 2013-02-03 23:16:32-08 - - $
# Partner: Alexey Munishkin (amunishk)
# Partner: Diem Phuong Chau (dhchau)

JAVASRC    = jxref.java listmap.java intqueue.java misc.java
SOURCES    = ${JAVASRC} Makefile README PARTNER
MAINCLASS  = jxref
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES} intqueue\$$*.class listmap\$$*.class
JARFILE    = jxref
LISTING    = ../asg2j-jxref.code.ps
SUBMITDIR  = cmps012b-wm.w13 asg2

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis
	
