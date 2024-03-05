cmake_minimum_required (VERSION 3.15)

set(PROJECT_NAME Editor)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)
project(${PROJECT_NAME})

include_directories(
	interfaces
)

add_executable(
	${PROJECT_NAME}
	main.cpp
	interfaces/buffer.h
	interfaces/buffer.cpp
)

