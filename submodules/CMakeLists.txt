###############################################################################
###                         SUBMODULES ORGANIZATION                         ###
###############################################################################
## This section organises all the submodules and compiles the necessary ones
###############################################################################

# Get a list of subdirectories in the current directory
set (
  SUBMODULES
    DEV_COMMON          # common
)

# Iterate over each subdirectory
foreach(SUBMODULE ${SUBMODULES})
  # Set the name of the submodule library.
  set (SUBMODULE_LIB ${SUBMODULE})
  # Enter into the submodule
  add_subdirectory(${SUBMODULE})
endforeach()