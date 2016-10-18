#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_TESTS)
#---------------------------------------------------------------------------
#generate test
add_executable(json_test ${DIR_TESTS})
#---------------------------------------------------------------------------
#add include path
#include_directories(${LIBRARY_OUTPUT_PATH_INC})
#---------------------------------------------------------------------------
#add lib path
#link_directories(${LIBRARY_OUTPUT_PATH_LIB})
#---------------------------------------------------------------------------
#add link lib
target_link_libraries(json_test json)
#---------------------------------------------------------------------------
#install target 
#install(TARGETS json_test DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#---------------------------------------------------------------------------
#add test
add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/json_test)
#---------------------------------------------------------------------------
