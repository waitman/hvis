QT       += core gui widgets webkitwidgets

TARGET = hvis
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp\
	hvisscene.cpp

HEADERS  += mainwindow.h \
		hvisscene.h

FORMS    += hvis.ui 

#debugging
#QMAKE_CXXFLAGS += -g

#FreeBSD
unix {
	LIBS 		+= -L/usr/local/lib 
	INCLUDES	+= -I/usr/local/include 
}

