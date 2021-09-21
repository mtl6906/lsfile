project(lsfile)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

aux_source_directory(src/ls/file SRC)

aux_source_directory(sample SRC_SAMPLE)

include_directories(include)

link_directories(/usr/local/lib)

add_library(lsfile SHARED ${SRC})

add_executable(testcase ${SRC} ${SRC_SAMPLE})

target_link_libraries(testcase lsexception lsio lsbuffer lscstring)

install(TARGETS lsfile DESTINATION lib)
install(DIRECTORY include/ls/file DESTINATION include/ls)
