.SILENT:

CO=g++
OBJS_QT = main.o applicgaragewindow.o moc_applicgaragewindow.o
PROGRAMS = ApplicGarage

all:	$(PROGRAMS)

ApplicGarage:	$(OBJS_QT)
		echo Creation de ApplicGarage...
		$(CO) -Wl,-O1 -o ApplicGarage $(OBJS_QT) /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread 					
		#rm main.o

main.o:	main.cpp
		echo Creation de main.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

applicgaragewindow.o:	applicgaragewindow.cpp applicgaragewindow.h ui_applicgaragewindow.h
		echo Creation de applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applicgaragewindow.o applicgaragewindow.cpp

moc_applicgaragewindow.o:	moc_applicgaragewindow.cpp applicgaragewindow.h
		echo Creation de moc_applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applicgaragewindow.o moc_applicgaragewindow.cpp

clean:
	@rm -f $(OBJS_QT) core

clobber:	clean
	@rm -f tags $(PROGRAMS) *~ *.log
