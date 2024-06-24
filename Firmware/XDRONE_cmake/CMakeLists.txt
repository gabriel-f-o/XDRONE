# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	XDRONE
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_XDRONE target,
# which contains the content of the SLC project
include(XDRONE.cmake)

file(GLOB_RECURSE SOURCES ../XDRONE/*.c)

add_executable(XDRONE
    # Add additional sources here
    ${SOURCES}
)

target_include_directories(XDRONE PUBLIC
    # Add additional include paths here
)

target_compile_definitions(XDRONE PUBLIC
    # Add additional macros here
)

target_compile_options(XDRONE PUBLIC
    # Set additional compiler flags here
    -Os
)

target_link_options(XDRONE PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(XDRONE PRIVATE
    slc_XDRONE
)

# Include managed project content if available
include(XDRONE_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(XDRONE PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET XDRONE
    POST_BUILD
    #COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:XDRONE>" "$<TARGET_FILE_DIR:XDRONE>/$<TARGET_FILE_BASE_NAME:XDRONE>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:XDRONE>" "$<TARGET_FILE_DIR:XDRONE>/$<TARGET_FILE_BASE_NAME:XDRONE>.hex"
    #COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:XDRONE>" "$<TARGET_FILE_DIR:XDRONE>/$<TARGET_FILE_BASE_NAME:XDRONE>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET XDRONE
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()