# Default CMake Setup. Used for Mac OS x builds using SDL 2

# Set SDL2 instead of SDL1
set(SDL2 1)

# For INTeL 64bit Mac OS X 10.7+
set(CMAKE_CXX_FLAGS "-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk -mmacosx-version-min=10.7")

find_library(COCOA_LIBRARY Cocoa)

link_libraries(
    ${COCOA_LIBRARY}
)

# This is for Homebrew
set(lib_base /usr/local/Cellar)

include_directories("~/Library/Frameworks/SDL2.framework/Headers" "${lib_base}/boost/1.60.0_1/include")

add_definitions(-O3 -DSDL2)
 
# Location for Cannonball to create save files
# Used to auto-generate setup.hpp with various file paths
set(xml_directory ./)
set(sdl_flags "SDL_WINDOW_RESIZABLE")
