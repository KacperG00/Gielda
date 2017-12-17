cmake_minimum_required(VERSION 3.5.0)
project(Gielda)

message("Project name: ${PROJECT_NAME}")

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")

set(	SRC_FILES
	"src/*.cpp"
	"src/ui/*.cpp"
	"src/grafika/*.cpp"
)

file(GLOB SOURCES
	${SRC_FILES}
)

add_executable(${PROJECT_NAME} ${SOURCES})
set(EXECUTABLE_OUTPUT_PATH ../)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(SFML REQUIRED audio network graphics window system)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
