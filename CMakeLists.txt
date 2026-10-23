# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.
include_directories("${CMAKE_CURRENT_LIST_DIR}/geometry/Types")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/geometry")
