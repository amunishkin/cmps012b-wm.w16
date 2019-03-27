# $Id: Makefile,v 1.2 2013-02-14 19:31:25-08 - - $
# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)

JAVASRC    = airport.java treemap.java misc.java
SOURCES    = ${JAVASRC} Makefile README PARTNER
MAINCLASS  = airport
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES} treemap\$$tree.class
JARFILE    = airport

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

submit : ${SOURCES}
	submit cmps012b-wm.w13 asg3 ${SOURCES}
	
again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

