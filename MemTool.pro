#hand-generate-code
QT	+= core gui
TARGET = MemTool
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS	+= -L/usr/lib/mysql -lmysqlclient
#INCLUDEPATH += /usr/include/mysql

#auto-generate-code#

HEADERS += \
	define.h \
	DisplayOption.h \
	KWidgetUtils.h \
	MemInitWindow.h \
	MemoryWindow.h 

SOURCES += \
	DisplayOption.cpp \
	KWidgetUtils.cpp \
	main.cpp \
	MemInitWindow.cpp \
	MemoryWindow.cpp \
	utilities.cpp

FORMS += \
	MemInitWindow.ui \
	MemoryWindow.ui 