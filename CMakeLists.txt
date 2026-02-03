cmake_minimum_required(VERSION 3.16)

project(LibraryManagementSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/models/Book.cpp
    src/models/Member.cpp
    src/models/Transaction.cpp
    src/core/DataManager.cpp
    src/core/LibraryController.cpp
    src/ui/LoginDialog.cpp
    src/ui/MainWindow.cpp
)

set(HEADERS
    include/models/Book.h
    include/models/Member.h
    include/models/Transaction.h
    include/core/DataManager.h
    include/core/LibraryController.h
    include/ui/LoginDialog.h
    include/ui/MainWindow.h
)

add_executable(LibraryManagementSystem ${SOURCES} ${HEADERS})

target_link_libraries(LibraryManagementSystem PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)
