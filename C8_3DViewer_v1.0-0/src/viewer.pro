QT       += core gui opengl openglwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affineTransformations.c \
    giflib/3rdParty/giflib/dgif_lib.c \
    giflib/3rdParty/giflib/egif_lib.c \
    giflib/3rdParty/giflib/gif_err.c \
    giflib/3rdParty/giflib/gif_font.c \
    giflib/3rdParty/giflib/gif_hash.c \
    giflib/3rdParty/giflib/gifalloc.c \
    giflib/3rdParty/giflib/quantize.c \
    giflib/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    giflib/gifimage/qgifimage.cpp \
    main.cpp \
    proto1.cpp \
    readObjFile.c \
    s21_matrix.c \
    widget.cpp

HEADERS += \
    affineTransformations.h \
    giflib/3rdParty/giflib/gif_hash.h \
    giflib/3rdParty/giflib/gif_lib.h \
    giflib/3rdParty/giflib/gif_lib_private.h \
    giflib/gifimage/qgifglobal.h \
    giflib/gifimage/qgifimage.h \
    giflib/gifimage/qgifimage_p.h \
    proto1.h \
    readObjFile.h \
    s21_matrix.h \
    widget.h

FORMS += \
    proto1.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/bricks.jpg \
    files/default_setting.txt \
    files/illusion.jpg \
    files/texture1.bmp \
    giflib/3rdParty/giflib.pri \
    giflib/3rdParty/giflib/AUTHORS \
    giflib/3rdParty/giflib/COPYING \
    giflib/3rdParty/giflib/README \
    giflib/gifimage/doc/qtgifimage.qdocconf \
    giflib/gifimage/doc/src/examples.qdoc \
    giflib/gifimage/doc/src/index.qdoc \
    giflib/gifimage/doc/src/qtgifimage.qdoc \
    giflib/gifimage/doc/src/usage.qdoc \
    giflib/gifimage/qtgifimage.pri

SUBDIRS += \
    giflib/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    giflib/gifimage/gifimage.pro \
    giflib/src.pro
