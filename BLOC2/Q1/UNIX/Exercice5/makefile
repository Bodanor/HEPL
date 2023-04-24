CC = g++
CFLAGS = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++
CFLAGSQT =  -lpthread /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

CPP_SOURCES := $(filter-out Serveur.cpp, $(wildcard *.cpp))
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)

all: Client Serveur

Client: $(CPP_OBJECTS)
	$(CC) $(CFLAGSQT) -o $@ $(CPP_OBJECTS)

Serveur: Serveur.cpp
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf *.o
	rm -rf Serveur
	rm -rf Client
