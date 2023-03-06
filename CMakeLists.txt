cmake_minimum_required(VERSION 3.10)

project(bench_tool)

set(DCMAKE_CXX_COMPLIER g++)

include_directories(
	./
)

link_directories(
	/usr/lib/
)

add_executable(bench_tool 
	bench_tools.cc
)

