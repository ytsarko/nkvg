project(nkvg)

set(SOURCES
    nkvg.c
    nuklear-impl.c
    nanovg/src/nanovg.c
)

add_library(${PROJECT_NAME} ${SOURCES})

add_definitions(
    -std=c99
    -pedantic
    -Wall
    -Wno-unused-but-set-variable
    -Wno-unused-function
    -Wno-unused-variable
    -DNKVG_USE_GLEW
    -DNK_INCLUDE_FIXED_TYPES
    -DNK_INCLUDE_DEFAULT_ALLOCATOR
    -DNK_INCLUDE_STANDARD_IO
    -DNK_INCLUDE_STANDARD_VARARGS
    -DNK_ZERO_COMMAND_MEMORY
)

if(UNIX)
    find_package(PkgConfig)
    find_package(Freetype)
    pkg_check_modules(GLEW REQUIRED glew>=1.10.0)

    add_definitions(
        -D_POSIX_C_SOURCE=199309L
    )

    target_include_directories(${PROJECT_NAME} PRIVATE
        .
        ./nanovg/src/
        ${FREETYPE_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME}
        ${FREETYPE_LIBRARIES}
        ${GLEW_LDFLAGS}
    )
elseif(WIN32)
    find_package(Glew)
    target_include_directories(${PROJECT_NAME} PRIVATE
        .
        ./nanovg/src/
        ${GLEW_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME}
        #${GLEW_LIBRARIES}
    )
endif(UNIX)

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib)
