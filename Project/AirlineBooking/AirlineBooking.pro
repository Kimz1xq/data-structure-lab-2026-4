QT += widgets

CONFIG += c++17
TEMPLATE = app
TARGET = AirlineBooking

SOURCES += \
    AirlineBooking/main.cpp \
    AirlineBooking/MainWindow.cpp \
    AirlineBooking/MapWidget.cpp

HEADERS += \
    AirlineBooking/AirportGraph.h \
    AirlineBooking/MainWindow.h \
    AirlineBooking/MapWidget.h
