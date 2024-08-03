###############################################################################
###                             CMAKE SETTINGS                              ###
###############################################################################
## This section includes settings related to CMake itself, ensuring necessary
## requirements are met before other processes are performed.
###############################################################################

# Set the minimum required CMake version.
cmake_minimum_required (VERSION 3.20)


###############################################################################
###                              C++ SETTINGS                               ###
###############################################################################
## This section includes C++ related settings such as the C++ standard, version,
## compile flags, and more.
###############################################################################

# Set the C++ standard to C++17.
set (CMAKE_CXX_STANDARD 17)

# Disable compiler-specific extensions.
set (CMAKE_CXX_EXTENSIONS OFF)

# Require the specified C++ standard to be used.
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Add common compile options to promote code quality.
add_compile_options (-Wall -Werror -Wextra -Wpedantic -pedantic)


###############################################################################
###                            PROJECT VARIABLES                            ###
###############################################################################
## This section initializes the project environment variables.
###############################################################################

set (ENV{LOGGER_CONFIG_FILE} "${CMAKE_CURRENT_LIST_DIR}/configs/Logger.xml")


###############################################################################
###                         PROJECT INITIALIZATION                          ###
###############################################################################
## This section initializes the project and sets up necessary configurations,
## including enabling testing and adding subdirectories.
###############################################################################

# Set the project name.
project (IPC)

# Set project as a library.
add_library (
  ${PROJECT_NAME}
)

# Enable testing for this project.
enable_testing ()

# Set the binaries output directory.
set (
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}/build/bin
)

# Add the 'submodules' subdirectory for external libs.
add_subdirectory (submodules)

# Add the 'src' subdirectory for further project structure.
add_subdirectory (src)