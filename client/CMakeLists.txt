## CMAKE VAR
## <=====================================>
set( ABS_PATH ${CMAKE_SOURCE_DIR} CACHE STRING "Some user-specified option" )
cmake_minimum_required( VERSION 3.17...3.20 )
set( CMAKE_BUILD_TYPE Debug ) # Release / RelWithDebInfo / Debug
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ABS_PATH}/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ABS_PATH}/lib/ )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ABS_PATH}/lib/ )
#set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage --coverage -lgcov")
if (UNIX)
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fPIC")
endif()
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
if(MSVC)
    target_compile_options(<target> PRIVATE "/MP")
endif()
## <=====================================>

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

## PROJECT VAR
## <=====================================>
project( Babel
        VERSION
        1.0
        DESCRIPTION
        "Babel"
        LANGUAGES
        CXX
        )
set( EXEC babel_client )
set( EXT cpp )

## SOURCE FOLDERS
set( SRC_FOLDERS
        ./sources/
        ./sources/tcp/
        ./sources/udp/
        ./sources/gui/
        ./sources/gui/qtclass/
        ./sources/audio/
        )
## INCLUDE FOLDERS
set( INC_FOLDERS
        ./includes/
        ./includes/audio/
        ./includes/tcp/
        ./includes/udp/
        ./sources/gui/qtclass/
        )
## IMPORTED SHARED LIBRARY NAME
set( SHARED_LIB_NAME )
## IMPORTED SHARED LIBRARY LOCATION
set( SHARED_LIB_LOCATION )
## <=====================================>


conan_basic_setup()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(Qt5 COMPONENTS Widgets Gui Core Network)
find_package(SqliteOrm REQUIRED)
find_package(portaudio REQUIRED)
find_package(Opus REQUIRED)
file(COPY ${CMAKE_BINARY_DIR}/qt.conf DESTINATION ${CMAKE_BINARY_DIR}/bin)


## GET SOURCES
## <=====================================>
foreach(filePath ${SRC_FOLDERS})
    string(APPEND TMP "${filePath}*.${EXT};")
endforeach()
foreach(filePath ${INC_FOLDERS})
    string(APPEND TMP "${filePath}*.hpp;")
endforeach()
file(GLOB SRC ${TMP})
## <=====================================>


## OUTPUT
## <=====================================>
## EXECUTABLE
add_executable(${EXEC} ${SRC} ${INC_FOLDERS})

## or SHARED LIB
# add_library(${EXEC} SHARED ${SRC})

## or STATIC LIB
# add_library(${EXEC} STATIC ${SRC})
## <=====================================>


## ADD INCLUDES
## <=====================================>
target_include_directories(${EXEC} PUBLIC ${INC_FOLDERS})
include_directories(${INC_FOLDERS})
## <=====================================>

## ADD PARAMETER
## <=====================================>
if (UNIX)
    target_compile_options(${EXEC} PRIVATE -g3)
endif (UNIX)
## <=====================================>


## SHARED LIBRARY LINKING
## <=====================================>
## <=====================================>


## PACKAGE LINKING
## <=====================================>
if (UNIX)
    target_link_libraries(${EXEC} ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui portaudio opus sqlite_orm::sqlite_orm)
endif()
if (WIN32)
    target_link_libraries(${EXEC} ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui portaudio_x64 opus sqlite_orm::sqlite_orm)
endif()
## <=====================================>
