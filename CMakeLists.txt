project(audiolink-obs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(audiolink_obs_SOURCES
    src/Plugin.cpp
    src/Dock.cpp
    src/AudioTapManager.cpp
    src/ShaderDispatcher.cpp
    # Add kissfft if local:
    src/kissfft/kiss_fft.c
    src/kissfft/kiss_fftr.c
)

add_library(audiolink-obs MODULE ${audiolink_obs_SOURCES})

target_include_directories(audiolink-obs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against OBS APIs
target_link_libraries(audiolink-obs
    PRIVATE
        libobs
        obs-frontend-api
        Qt6::Widgets
)

# Ensure plugin loads correctly on each platform
if(OS_WINDOWS)
    set_target_properties(audiolink-obs PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
elseif(OS_MACOS)
    set_target_properties(audiolink-obs PROPERTIES
        BUNDLE TRUE
        BUNDLE_EXTENSION ".plugin"
    )
else()
    set_target_properties(audiolink-obs PROPERTIES
        PREFIX ""
        SUFFIX ".so"
    )
endif()
