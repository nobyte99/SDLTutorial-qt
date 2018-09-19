
win32: LIBS += -LD:/Qt/Qt5.9.6/Tools/mingw530_32/lib/ -lSDL2

INCLUDEPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include
DEPENDPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include

win32:!win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/SDL2.lib
else:win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/libSDL2.a

win32: LIBS += -LD:/Qt/Qt5.9.6/Tools/mingw530_32/lib/ -lSDL2main

INCLUDEPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include
DEPENDPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include

win32:!win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/SDL2main.lib
else:win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/libSDL2main.a

win32: LIBS += -LD:/Qt/Qt5.9.6/Tools/mingw530_32/lib/ -lSDL2_image

INCLUDEPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include
DEPENDPATH += D:/Qt/Qt5.9.6/Tools/mingw530_32/include

win32:!win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/SDL2_image.lib
else:win32-g++: PRE_TARGETDEPS += D:/Qt/Qt5.9.6/Tools/mingw530_32/lib/libSDL2_image.a
