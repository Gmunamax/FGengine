cmake_minimum_required(VERSION 2.8)

target_sources(FGengine
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/windowBase.cpp
)

add_subdirectory(scene)
