###############################################################################
###                                COMPONENT                                ###
###############################################################################
## Define component-specific variables.
###############################################################################


###############################################################################
###                                 LIBRARY                                 ###
###############################################################################
## Settings and steps to build the component library.
###############################################################################

# Create an object library for the component.
add_library (
  ${COMPONENT_LIB} OBJECT
)

# Include directories for the library.
target_include_directories (
  ${COMPONENT_LIB}
    PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/include
)

# Gather source files for the component library.
file (
  GLOB SOURCES
    CONFIGURE_DEPENDS
      "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

# Add the collected source files to the library.
target_sources (
  ${COMPONENT_LIB}
    PRIVATE
      ${SOURCES}
)

# Link the needed libraries.
target_link_libraries (
  ${COMPONENT_LIB}
    common_lib
)

# Add component tests
add_subdirectory (
  ${CMAKE_CURRENT_LIST_DIR}/tests
)