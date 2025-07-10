#GraphicsEngine project should later be packaged as a module, that can be included and linked
#in other projects.



set(PROJECT_NAME GraphicsEngine)
cmake_minimum_required(VERSION 4.1.0)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C)



include(CTest)
enable_testing()



#When in the future GraphicsEngine is it's own module, take another look at how the files are added to the executable.
file(GLOB_RECURSE SRC_FILES "src/*.c")
#Not necessary, but in case others using Visual Studio have troubles seeing the header files in the explorer.
file(GLOB_RECURSE HEADER_FILES "src/*.h")
add_executable(${PROJECT_NAME}
        #src includes glad.c
        ${SRC_FILES}
        ${HEADER_FILES}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 23)
#If wanting to set the C standard for ALL targets, use:
#set(CMAKE_C_STANDARD 23)
#set(CMAKE_C_STANDARD_REQUIRED ON)



#Libraries
# GLFW
add_subdirectory(external/glfw)
# Include directories
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
            #Own include folder
            include
            #Include folder of glfw library
            external/glfw/include
)



# Link libraries
#First argument is the target, this project, the rest are libraries or dependencies the target links against.
target_link_libraries(
        ${PROJECT_NAME}
        #PRIVATE, so that other projects including GraphicsEngine are not forced to link glfw themselves for their own project.
        PRIVATE glfw
)

if(UNIX)
    target_link_libraries(
            ${PROJECT_NAME}
            PRIVATE
                ${CMAKE_DL_LIBS}
    )
endif()