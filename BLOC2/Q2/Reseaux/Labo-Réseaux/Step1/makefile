
# cphex\makefile

LIBS=
all:	admin	LibSerPB.o


LibSerPB.o:	LibSerPB.c	LibSerPB.h	data.h	
	echo "compilation de LibSerPB"
	gcc -g -c LibSerPB.c

admin:	data.h	admin.c	LibSerPB.o			
	echo "Compilation de admin"
	gcc -g -o admin	admin.c	LibSerPB.o 

clean:
	rm -rf *.o
	rm admin
