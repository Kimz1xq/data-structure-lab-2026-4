QT += widgets
CONFIG += c++17

TARGET = Airline
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    MapWidget.cpp

HEADERS += \
    AirportGraph.h \
    MainWindow.h \
    MapWidget.h
