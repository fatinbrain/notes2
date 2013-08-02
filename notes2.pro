#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T08:34:15
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notes2
TEMPLATE = app


SOURCES +=	main.cpp					\
			notes2.cpp					\
			datastruct/noterecord.cpp 	\
			datastruct/notesbase.cpp 	\
			newnotedialog.cpp 			\
			tools/mapTool.cpp			\
			markdown/docheader.c 		\
			markdown/dumptree.c  		\
			markdown/generate.c  		\
			markdown/markdown.c  		\
			markdown/mkdio.c     		\ 
			markdown/resource.c  		\
			markdown/version.c   		\
			markdown/markdowncxx.cpp

HEADERS  +=	notes2.h 				\
			datastruct/noterecord.h \
			datastruct/notesbase.h 	\
			newnotedialog.h 		\
			tools/mapTool.h			\
			markdown/amalloc.h     	\
			markdown/config.h      	\
			markdown/cstring.h     	\
			markdown/markdowncxx.h 	\
			markdown/markdown.h

FORMS    += notes2.ui \
    newnotedialog.ui

RESOURCES += \
    notes2.qrc
