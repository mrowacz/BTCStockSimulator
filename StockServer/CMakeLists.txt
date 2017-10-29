cmake_minimum_required(VERSION 3.5.1)

project(StockServer)

include(ExternalProject)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_DEBUG "-O2 -g")
SET(CMAKE_C_FLAGS_DEBUG "-O2")
FILE(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

FIND_PACKAGE(Boost COMPONENTS system REQUIRED)
FIND_PACKAGE(libbsoncxx)
FIND_PACKAGE(libmongocxx)

ExternalProject_Add(crow
        GIT_REPOSITORY https://github.com/ipkn/crow.git
        #-- Configure step --
        CONFIGURE_COMMAND ""
        #-- Build Step --
        BUILD_COMMAND ""
        BUILD_IN_SOURCE 1
        UPDATE_DISCONNECTED 1
        INSTALL_COMMAND ""
)

add_executable(StockServer ${SOURCE_FILES})

target_include_directories(StockServer PUBLIC 
	${CMAKE_BINARY_DIR}/crow-prefix/src/crow/include
	${LIBMONGOCXX_INCLUDE_DIRS}
	${LIBBSONCXX_INCLUDE_DIRS}
)
message(${LIBMONGOCXX_INCLUDE_DIRS})
target_link_libraries(StockServer      
        pthread
        mongocxx
        bsoncxx
        ${Boost_LIBRARIES}
)

