###############################################################################
###                                  TESTS                                  ###
###############################################################################
## Settings and steps to build the component tests.
###############################################################################

# Set the name of the component library.
set (COMPONENT_TESTS ${COMPONENT}_tests)

# Create an executable for tests related to the component.
add_executable (
  ${COMPONENT_TESTS}
)

# Include directories for the library.
target_include_directories (
  ${COMPONENT_TESTS}
    PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/../include
)

# Gather source files for the component tests.
file (
  GLOB SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)

# Add the collected source files to the tests executable.
target_sources (
  ${COMPONENT_TESTS}
    PRIVATE
      ${SOURCES}
)

# Link the necessary libraries for the tests.
target_link_libraries (
  ${COMPONENT_TESTS}
    ${COMPONENT_LIB}
    GTest::GTest
    GTest::Main
)

# Register the tests with CTest.
add_test (
  ${COMPONENT_TESTS}
    ${COMPONENT_TESTS}
)