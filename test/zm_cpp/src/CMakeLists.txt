# CMakeLists.txt for the ZoneMinder binaries
cmake_minimum_required (VERSION 2.8.7)
project (zoneminder)
mark_as_advanced( 
    FORCE ZM_EXTRA_LIBS 
    CMAKE_INSTALL_FULL_BINDIR 
)

set (CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Default CLFAGS and CXXFLAGS:
set(CMAKE_C_FLAGS_RELEASE "-Wall -D__STDC_CONSTANT_MACROS -O2")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -D__STDC_CONSTANT_MACROS -O2")
set(CMAKE_C_FLAGS_DEBUG "-Wall -D__STDC_CONSTANT_MACROS -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -D__STDC_CONSTANT_MACROS -g")
set(CMAKE_C_FLAGS_OPTIMISED "-Wall -D__STDC_CONSTANT_MACROS -O3")
set(CMAKE_CXX_FLAGS_OPTIMISED "-Wall -D__STDC_CONSTANT_MACROS -O3")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_INSTALL_FULL_BINDIR "/zm")
set(BINDIR "${CMAKE_INSTALL_FULL_BINDIR}")
# Create files from the .in files
#configure_file(zm_config.h.in "${CMAKE_CURRENT_BINARY_DIR}/zm_config.h" @ONLY)

# Group together all the source files that are used by all the binaries (zmc, zma, zmu, zms etc)
set(ZM_BIN_SRC_FILES zm_utils.cpp)

# Create a target for man pages
include(Pod2Man)
ADD_MANPAGE_TARGET()

# A fix for cmake recompiling the source files for every target.
add_library(zm STATIC ${ZM_BIN_SRC_FILES})
#link_directories(libbcrypt)

add_executable(zmc zmc.cpp)

# JWT is a header only library. 
#include_directories(libbcrypt/include/bcrypt)
#include_directories(jwt-cpp/include/jwt-cpp)

target_link_libraries(zmc zm ${ZM_EXTRA_LIBS} ${ZM_BIN_LIBS} ${CMAKE_DL_LIBS})

# Generate man files for the binaries destined for the bin folder
#FOREACH(CBINARY zmc )
#    POD2MAN(${CMAKE_CURRENT_SOURCE_DIR}/${CBINARY}.cpp zoneminder-${CBINARY} 8 ${ZM_MANPAGE_DEST_PREFIX})
#ENDFOREACH(CBINARY zmc)

install(TARGETS zmc RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_BINDIR}" PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)