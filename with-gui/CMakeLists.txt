cmake_minimum_required(VERSION 3.5)

project(FinanceTracker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adjust this path to your Qt installation
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS 
    Core
    Gui
    Widgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS 
    Core
    Gui
    Widgets
)

set(PROJECT_SOURCES
    src/main.cpp
    src/views/mainwindow.cpp
    src/views/mainwindow.h
    src/views/mainwindow.ui
    src/views/transactiondialog.cpp
    src/views/transactiondialog.h
    src/views/transactiondialog.ui
    src/models/transaction.cpp
    src/models/transaction.h
    src/models/financemanager.cpp
    src/models/financemanager.h
)

add_executable(FinanceTracker
    ${PROJECT_SOURCES}
)

target_link_libraries(FinanceTracker PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)