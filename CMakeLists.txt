cmake_minimum_required(VERSION 3.0)

project(Hust_os_labs)

aux_source_directory(src SRC_DIR)

file(GLOB labs RELATIVVE "src/*.c")

link_libraries(-lpthread -lm)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

foreach(lab IN LISTS labs)
    get_filename_component(labname ${lab} NAME_WE)
    add_executable(${labname} ${lab})
endforeach()

