# Authors: Alexey Munishkin (amunishk)
#          Diem Phuong Chau (dhchau)
# $Id: Makefile,v 1.1 2013-01-22 19:48:15-08 amunishk - $

all : exit255

exit255 : exit255.class
	echo Main-class: exit255 >Manifest
	jar cvfm exit255 Manifest exit255.class
	yes | rm -i Manifest exit255.class
	chmod +x exit255

exit255.class : exit255.java
	javac exit255.java

test :
	exit255 >255.output>>$$? ; echo "Exit Status = $$?"

