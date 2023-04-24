# cphex\makefile

LIBS=
all:	cli	ser	udplib.o	admin



LibSerBG.o:	LibSerBG.c	LibSerBG.h	data.h
	echo "Compilation de LibSerBG"
	gcc -c LibSerBG.c
		
udplib.o:	../udplib/udplib.h	../udplib/udplib.c
	echo "Compilation de udplib.o"
	gcc -c ../udplib/udplib.c	

cli:	cli.c	RequeteBG.h data.h udplib.o
	echo "Compilation de client"
	gcc  -o cli  cli.c udplib.o	$(LIBS)

ser:	ser.c	 RequeteBG.h data.h	udplib.o LibSerBG.o
	echo "Compilation de serveur"
	gcc -o ser  ser.c udplib.o LibSerBG.o	$(LIBS)
	
admin:	data.h admin.c LibSerBG.o
	echo "Compilation de admin"
	gcc -o admin admin.c LibSerBG.o

