# $Id: Makefile,v 1.3 2013-01-21 11:28:15-08 - - $
# Partner: Alexey Munishkin (amunishk)
# Partner; Diem Phoung Chau (dhchau)
#

JAVASRC = wordct.java misclib.java
ALLSOURCE = ${JAVASRC} Makefile README PARTNER
MAINCLASS = wordct
CLASSES = wordct.class misclib.class
JARCLASSES = ${CLASSES} wordct\$$counts.class wordct\$$options.class
JARFILE = wordct
LISTING = ../asg1j-wordct.code.ps
SUBMITDIR = cmps012b-wm.w13 asg1

all : ${JARFILE}
	- checksource ${ALLSOURCE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${ALLSOURCE}
	checksource ${ALLSOURCE}
	cid + ${ALLSOURCE}

lis : ${ALLSOURCE}
	mkpspdf ${LISTING} ${ALLSOURCE}

submit : ${ALLSOURCE}
	submit ${SUBMITDIR} ${ALLSOURCE}

again : ${ALLSOURCE}
	gmake spotless ci all lis

