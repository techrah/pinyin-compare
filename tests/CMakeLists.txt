# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Configure tests
#file(GLOB SOURCES "*.cpp")
#add_executable(test_app ${SOURCES})

add_executable(test_a test_a.cpp)
target_link_libraries(test_a pinyincompare gtest_main)
add_test(NAME test_a COMMAND test_a)

add_executable(test_e test_e.cpp)
target_link_libraries(test_e pinyincompare gtest_main)
add_test(NAME test_e COMMAND test_e)

add_executable(test_i test_i.cpp)
target_link_libraries(test_i pinyincompare gtest_main)
add_test(NAME test_i COMMAND test_i)

add_executable(test_o test_o.cpp)
target_link_libraries(test_o pinyincompare gtest_main)
add_test(NAME test_o COMMAND test_o)

add_executable(test_u test_u.cpp)
target_link_libraries(test_u pinyincompare gtest_main)
add_test(NAME test_u COMMAND test_u)

add_executable(test_u_diaeresis test_u_diaeresis.cpp)
target_link_libraries(test_u_diaeresis pinyincompare gtest_main)
add_test(NAME test_u_diaeresis COMMAND test_u_diaeresis)
