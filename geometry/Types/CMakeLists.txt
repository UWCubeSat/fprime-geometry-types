include_directories(${CMAKE_CURRENT_LIST_DIR})

#set(SOURCE_FILES
#  "${CMAKE_CURRENT_LIST_DIR}/GeometryTypes.fpp"
#)

register_fprime_library(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/GeometryTypes.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Quaternion/Quaternion.cpp"
)


#fprime_add_unit_test_build_target(
register_fprime_ut(
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/test/Matrix/TestMatrix.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/Quaternion/TestQuaternion.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/Vector/TestVector.cpp"
    #DEPENDS
        #STest # For rules-based testing
        #UT_AUTO_HELPERS
)

