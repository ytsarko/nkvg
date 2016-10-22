project(nkvg)

if(UNIX)
    find_package(PkgConfig)
    find_package(Freetype)

    add_definitions(
        -std=c99
        -pedantic
        -Wall
        -Wno-unused-but-set-variable
        -Wno-unused-function
        -Wno-unused-variable
        -D_POSIX_C_SOURCE=199309L
    )

elseif(WIN32)
endif(UNIX)

include_directories(
    .
    ./nanovg/src/
    ${FREETYPE_INCLUDE_DIRS}
    )

add_definitions(
    -DNK_INCLUDE_FIXED_TYPES
    -DNK_INCLUDE_DEFAULT_ALLOCATOR
    -DNK_INCLUDE_STANDARD_IO
    -DNK_INCLUDE_STANDARD_VARARGS
    -DNK_ZERO_COMMAND_MEMORY
    -DFONS_USE_FREETYPE
)

set(SOURCES
    nkvg.c
    nuklear-impl.c
    nanovg/src/nanovg.c
)

add_library(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib)
