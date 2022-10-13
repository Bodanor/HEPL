CC = g++
CFLAGS =-pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ 

CFLAGSDB := -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl
CPP_SOURCES := $(wildcard *.cpp)
CPP_OBJECTS := $(filter-out CreationBD.o Lecture.o, $(CPP_SOURCES:.cpp=.o))

all: UNIX_Exercice3 Lecture CreationBD

UNIX_Exercice3: $(CPP_OBJECTS)
	$(CC) -o $@ $(CPP_OBJECTS) /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

Lecture: Lecture.cpp
	$(CC) -o $@  $(CFLAGSDB) Lecture.cpp

CreationBD: CreationBD.cpp
	$(CC) -o $@ $(CFLAGSDB) CreationBD.cpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	rm -rf UNIX_Exercice3
	rm -rf *.o
	rm -rf Lecture
	rm -rf CreationBD
