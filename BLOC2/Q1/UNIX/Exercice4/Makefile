CC = g++
CFLAGSQT = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ 
CFLAGSEXE = /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread
CLFAGSTRAITEMENT = -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so


CPP_SOURCES := $(wildcard *.cpp)
CPP_OBJECTS := $(filter-out mainwindowtraitement.o, $(CPP_SOURCES:.cpp=.o))

all: UNIX_Exercice4 Traitement CreationBD

UNIX_Exercice4: $(CPP_OBJECTS)
	$(CC) -o $@ $(filter-out maintraitement.o mainwindowtraitement.o moc_mainwindowtraitement.o, $(CPP_OBJECTS)) $(CFLAGSEXE)

Traitement: $(CPP_OBJECTS)
	$(CC) -o mainwindowtraitement.o -c mainwindowtraitement.cpp $(CFLAGSQT) -I/usr/include/mysql -m64
	$(CC) -o $@ mainwindowtraitement.o $(filter-out mainex4.o mainwindowex4.o moc_mainwindowex4.o, $(CPP_OBJECTS)) $(CLFAGSTRAITEMENT)

CreationBD:
	
	$(MAKE) -C ../Exercice3 CreationBD

%.o: %.cpp
	$(CC) $(CFLAGSQT) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf UNIX_Exercice4
	rm -rf Traitement