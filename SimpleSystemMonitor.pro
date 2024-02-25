QT += gui core widgets testlib

CONFIG += c++17
CONFIG -= app_bundle
LIBS += -lstdc++fs

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# DEFINES += BUILD_WITH_TESTS

SOURCES += main.cpp \
    core/cpuinfo.cpp \
    core/meminfo.cpp \
    core/netinfo.cpp \
    widgets/totalwidget.cpp \
    systemmonitor.cpp \
    widgets/cpuwidget.cpp \
    widgets/emulateablewidget.cpp \
    widgets/memorywidget.cpp \
    charts/networkchart.cpp \
    charts/percenttimerealtimechart.cpp \
    charts/realtimechart.cpp \
    utils.cpp \
    widgets/networkwidget.cpp \
    widgets/optionswidget.cpp \
    core/parsers/cpu_parsers.cpp \
    core/parsers/memory_parsers.cpp \
    core/parsers/network_parsers.cpp \
    infomanager.cpp \
    core/hddinfo.cpp \
    core/procinfo.cpp \
    core/parsers/processes_parsers.cpp \
    charts/PieChart/labeled_piechart.cpp \
    charts/PieChart/piechart.cpp \
    widgets/configurablewidget.cpp \
    widgets/hddwidget.cpp \
    widgets/processwidget/processwidgetmodel.cpp \
    widgets/processwidget/processeswidget.cpp \
    system/system.cpp

HEADERS += \
    core/cpuinfo.hpp \
    core/meminfo.hpp \
    core/netinfo.hpp \
    core/parsers/interfaces/parser.hpp \
    core/parsers/interfaces/cpu_parser.h \
    core/parsers/interfaces/hdd_parser.h \
    core/parsers/interfaces/memory_parser.h \
    core/parsers/interfaces/network_parser.h \
    widgets/totalwidget.hpp \
    systemmonitor.hpp \
    widgets/emulateablewidget.hpp \
    widgets/cpuwidget.hpp \
    widgets/memorywidget.hpp \
    charts/networkchart.hpp \
    charts/percenttimerealtimechart.hpp \
    charts/realtimechart.hpp \
    utils.hpp \
    widgets/networkwidget.hpp \
    widgets/optionswidget.hpp \
    settings.hpp \
    charts/chartsnamespace.hpp \
    applicationnamespace.hpp \
    core/parsers/cpu_parsers.hpp \
    core/parsers/memory_parsers.hpp \
    core/parsers/network_parsers.hpp \
    core/parsers/parseerror.hpp \
    infomanager.hpp \
    core/hddinfo.hpp \
    core/procinfo.hpp \
    core/parsers/processes_parsers.hpp \
    charts/PieChart/labeled_piechart.hpp \
    charts/PieChart/piechart.hpp \
    widgets/configurablewidget.hpp \
    widgets/hddwidget.hpp \
    widgets/processwidget/processwidgetmodel.hpp \
    widgets/processwidget/processeswidget.hpp \
    system/system.hpp

win32 {
SOURCES += \
    core/parsers/windows/hdd_parser.cpp

HEADERS += \
    core/parsers/windows/hdd_parser.h
}

unix {
SOURCES += \
    core/parsers/linux/hdd_parser.cpp

HEADERS += \
    core/parsers/linux/hdd_parser.hpp
}

TRANSLATIONS += \
    translation.ts

RESOURCES += \
    resources.qrc
