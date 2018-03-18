CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(EmbedUsartProtocol)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/test)

FILE(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/**.c)
FILE(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/**.h)
ADD_LIBRARY(snoo-cue-protocol ${sources} ${headers})


IF(ENABLE_PROTOCOL_TESTING)
    ENABLE_TESTING()

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest/googletest/include)

    MACRO(COLLECT_TESTS current_path)
        MESSAGE("-- CollectTests -- Searching for test files in ${current_path}")
        FILE(GLOB children RELATIVE ${current_path} ${current_path}/*)
        FOREACH(child ${children})
            IF(IS_DIRECTORY ${current_path}/${child})
                COLLECT_CC(${current_path}/${child})
            ELSE ()
                GET_FILENAME_COMPONENT(test_ext ${current_path}/${child} EXT)
                GET_FILENAME_COMPONENT(test_name ${current_path}/${child} NAME_WE)
                IF ("${test_ext}" STREQUAL ".cpp")
                    ADD_EXECUTABLE(${test_name} ${current_path}/${child})
                    TARGET_LINK_LIBRARIES(${test_name} snoo-cue-protocol pthread gtest)
                    ADD_TEST(${test_name} ${test_name})
                    MESSAGE("-- CollectTests -- Adding executable ${test_name} - done")
                ENDIF ()
            ENDIF()
        ENDFOREACH()
        MESSAGE("-- CollectTests -- Searching for test files in ${current_path} - done")
    ENDMACRO()

    COLLECT_TESTS(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

