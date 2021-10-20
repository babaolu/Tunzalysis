cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tunzalysis VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# add the executable
add_executable(Tunzalysis main.cpp 
	ErrorHandle.cpp 
	Imatters.cpp 
	ProcessComp.cpp)

configure_file(TunzalysisConfig.h.in TunzalysisConfig.h)
target_include_directories(Tunzalysis PUBLIC "${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}")

