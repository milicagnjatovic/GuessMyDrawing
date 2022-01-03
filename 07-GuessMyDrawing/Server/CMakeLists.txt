project(Server LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)
add_executable(Server
    server.h
    servermainwindow.h
    thread.h
    servermainwindow.ui
    main.cpp
    server.cpp
    servermainwindow.cpp
    thread.cpp
)
target_link_libraries(Server PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
target_compile_definitions(Server PRIVATE QT_NO_CAST_FROM_ASCII)
set_target_properties(Server PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        VERSION "1.0.0"
        EXPORT_NAME Server
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
