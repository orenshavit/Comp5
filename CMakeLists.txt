cmake_minimum_required(VERSION 3.10)
project(try1) # <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< project name

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

add_executable(${CMAKE_PROJECT_NAME} output.cpp parser.tab.cpp lex.yy.c bp.cpp SymbolsTable.cpp ManageIR.cpp) # <<<<<<<<<<<<<<<<<<<<<<< add cpp files

add_custom_command(
        # Generates Flex file
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND flex scanner.lex
        DEPENDS scanner.lex
)

add_custom_command(
        # Generates Bison files
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser.tab.cpp
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/parser.tab.hpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND bison -d parser.ypp
        DEPENDS parser.ypp
)

#  # TESTS

set(TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests) # <<<<<<<<<<<<<<<<<<<< tests directory

add_custom_command(
        # Copy executable to test directory
        OUTPUT ${TEST_DIRECTORY}/hw5
        WORKING_DIRECTORY ${TEST_DIRECTORY}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME} ./hw5
        DEPENDS ${CMAKE_PROJECT_NAME}
)

add_custom_target(
        # Build this target to run tests (only build don't run)
        TESTS
        WORKING_DIRECTORY ${TEST_DIRECTORY}
        COMMAND ./run.sh    # <<<<<<<<<<<<<<<<<<<< runs tests bash file
        DEPENDS ${TEST_DIRECTORY}/hw5
)

add_custom_target(
		# Build this target to clean flex and bison output (only build don't run)
        CleanFlexBisonFiles
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND rm -f lex.yy.c parser.tab.*pp
)

add_custom_target(
        # Build this target to clean flex and bison output (only build don't run)
        CleanTestDir
        WORKING_DIRECTORY ${TEST_DIRECTORY}
        COMMAND rm -f *.res *.llvm hw5
)

# compile lex.yy.c as c++
set_source_files_properties(lex.yy.c PROPERTIES LANGUAGE CXX )

