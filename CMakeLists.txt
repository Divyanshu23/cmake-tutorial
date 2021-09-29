cmake_minimum_required(VERSION 3.20.5)

project(OLAS VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp)

find_package(GLEW MODULE REQUIRED)

# find_library(GLEW_LIB glew NAMES glew2 GLEW GLEW2 DOC "glew library")
# if (${GLEW_LIB} STREQUAL GLEW_LIB-NOTFOUND)
#     message(FATAL_ERROR "glew library not found")
# else()
#     message(STATUS "glew found at ${GLEW_LIB}")
# endif()

# find_library(GLU_LIB glu NAMES GLU DOC "glu library")
# if (${GLU_LIB} STREQUAL GLU_LIB-NOTFOUND)
#     message(FATAL_ERROR "glu library not found")
# else()
#     message(STATUS "glu found at ${GLU_LIB}")
# endif()

# find_library(GL_LIB gl NAMES GL DOC "gl library")
# if (${GL_LIB} STREQUAL GL_LIB-NOTFOUND)
#     message(FATAL_ERROR "gl library not found")
# else()
#     message(STATUS "gl found at ${GL_LIB}")
# endif()

option(USE_ADDER "Basic C++ Library to add two floats" ON)

if(USE_ADDER)
    add_subdirectory(Adder)

    target_include_directories(${PROJECT_NAME} 
        PUBLIC Adder 
    )

    target_link_directories(${PROJECT_NAME} 
        PRIVATE Adder
    )

    list(APPEND EXTRA_LINK_LIBS adder)
endif()

configure_file(OLASConfig.h.in OLASConfig.h)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include
    PUBLIC ${PROJECT_BINARY_DIR}
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE external/glfw/src
)

target_link_libraries(${PROJECT_NAME} ${EXTRA_LINK_LIBS} glfw)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/OLASConfig.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)