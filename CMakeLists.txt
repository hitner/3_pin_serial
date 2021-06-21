cmake_minimum_required(VERSION 3.10.0)
project(3_pin_serial)

set(LIB_SERIAL_PORT libserialport)

## Sources
set(SERIAL_SOURCE
    include/serial_port.h
)
if(APPLE)
    # If OSX
    list(APPEND SERIAL_SOURCE src/serial_port_apple.cc)
elseif(UNIX)
    # If unix
    list(APPEND SERIAL_SOURCE src/serial_port_linux.cc)
else()
    # If windows
    list(APPEND SERIAL_SOURCE src/serial_port_win.cc)
endif()

## Add serial library
add_library(${LIB_SERIAL_PORT} ${SERIAL_SOURCE})
if(APPLE)
    target_link_libraries(${LIB_SERIAL_PORT} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
    target_link_libraries(${LIB_SERIAL_PORT} rt pthread)
else()
    target_link_libraries(${LIB_SERIAL_PORT} setupapi)
endif()

## Include headers
target_include_directories(${LIB_SERIAL_PORT} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if(BUILD_TESTING)
    add_executable(serial_example examples/serial_example.cc)
    target_link_libraries(serial_example ${LIB_SERIAL_PORT})

    add_subdirectory(tests)
endif()