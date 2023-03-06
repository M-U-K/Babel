## CMAKE VAR
## <=====================================>
set( ABS_PATH ${CMAKE_SOURCE_DIR} CACHE STRING "Some user-specified option" )
cmake_minimum_required( VERSION 3.17...3.20 )
set( CMAKE_BUILD_TYPE Debug ) # Release / RelWithDebInfo / Debug
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ABS_PATH}/build/bin/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ABS_PATH}/lib/ )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ABS_PATH}/lib/ )
#set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage --coverage -lgcov")
if (UNIX)
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fPIC")
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
set( EXEC babel_server )
set( EXT cpp )

## SOURCE FOLDERS
set( SRC_FOLDERS
        ./sources/
        ./sources/tcp/
        ./sources/database/
        )
## INCLUDE FOLDERS
set( INC_FOLDERS
        ./includes/
        ./includes/tcp/
        ./includes/databaseclass/
        )
## IMPORTED SHARED LIBRARY NAME
set( SHARED_LIB_NAME )
## IMPORTED SHARED LIBRARY LOCATION
set( SHARED_LIB_LOCATION )
## <=====================================>

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(SqliteOrm REQUIRED)

## GET SOURCES
## <=====================================>
foreach(filePath ${SRC_FOLDERS})
    string(APPEND TMP "${filePath}*.${EXT};")
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
add_library(asio INTERFACE)
target_compile_options(asio INTERFACE ASIO_STANDALONE)
target_include_directories(asio INTERFACE ${CMAKE_SOURCE_DIR}/asio/include)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(asio REQUIRED)

target_link_libraries(${EXEC}
    PRIVATE
        Threads::Threads
        asio::asio
        sqlite_orm::sqlite_orm
)

# if (UNIX)
#     target_link_libraries(${EXEC} ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui portaudio opus sqlite_orm::sqlite_orm)
# endif()
# if (WIN32)
#     target_link_libraries(${EXEC} ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui portaudio_x64 opus sqlite_orm::sqlite_orm)
# endif()
## <=====================================>