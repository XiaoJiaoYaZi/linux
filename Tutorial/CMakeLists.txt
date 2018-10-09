cmake_minimum_required(VERSION 2.8)

project(Tutorial)
#version number
set(Tutorial_VERSION_MAJOR 1)
SET(Tutorial_VERSION_MINOR 0)

#config a header file to pass some of the CMake settings
#to the source code
#TutorialConfig.h.in  is config file ,will auto create TutorialConfig.h
configure_file(
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h"
    )
# should we use our own math functions?
option (USE_MYMATH
        "Use tutorial provided math implementation" ON)

#add the binary tree to the search path for include files
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
# does this system provide the log and exp functions?
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries (Tutorial  ${EXTRA_LIBS})
# add the install targets
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
         DESTINATION include)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)

