cmake_minimum_required (VERSION 2.6)

project (PoseEstimation_SelectFrames)

# g++ needs a compiler flag to enable C++11 support
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++11 HAS_CXX11_FLAG)
if (HAS_CXX11_FLAG)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#set(CEREAL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Thirdparty/cereal-1.1.1/include")
#set(glm_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Thirdparty/glm")

include_directories(${CMAKE_SOURCE_DIR}/include)

# Header files:
set(HEADERS
	${CMAKE_SOURCE_DIR}/include/selectFrames.h
)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Find dependencies:
# Add header includes:
#OpenCV-3.0.0
find_package(OpenCV 2.4 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR}/opencv)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR}/opencv2)
LINK_DIRECTORIES(${OpenCV_LIB_DIR})
message(STATUS "=====  OpenCV include dir found at ${OpenCV_INCLUDE_DIRS}")
message(STATUS "=====  OpenCV lib dir found at ${OpenCV_LIB_DIR}")

#boost
find_package( Boost REQUIRED COMPONENTS filesystem system)
#find_package( Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS}/boost)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})	
message(STATUS "=====  Boost include dir found at ${Boost_INCLUDE_DIRS}")
message(STATUS "=====  Boost lib dir found at ${Boost_LIBRARY_DIRS}")

#tbb
find_package( TBB REQUIRED)
message(STATUS "=====  TBB include dir found at ${TBB_INCLUDE_DIRS}")
message(STATUS "=====  TBB lib dir found at ${TBB_LIBRARIES}")

#load static lib (.a)
#add_library(selectFrames_StaticLib STATIC IMPORTED)
#add_library(poseEstimateEosCPP_StaticLib STATIC IMPORTED)
#set_target_properties(selectFrames_StaticLib PROPERTIES 
#			           IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/libs/libGlasses_PoseEstimation_SelectFrames.a )

#set_target_properties(poseEstimateEosCPP_StaticLib PROPERTIES  
#			           IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/libs/libFaceAR_PoseEstimateClark_EosCPP_StaticLib_Server.a )


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} 	${CMAKE_SOURCE_DIR}/libs/libGlasses_PoseEstimation_SelectFrames.a
					${CMAKE_SOURCE_DIR}/libs/libFaceAR_PoseEstimateClark_EosCPP_StaticLib_Server.a
					${OpenCV_LIBS}   ${Boost_LIBRARIES}  ${TBB_LIBRARIES} )

install (TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
message(STATUS "=====  TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin")
message(STATUS "=====  TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin")
message(STATUS "=====  TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin")



















