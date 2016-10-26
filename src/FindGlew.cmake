# - Glew module

include(FindPackageHandleStandardArgs)

if(GLEW_ROOT_DIR)
    find_path(GLEW_INCLUDE_DIRS glew.h
        PATHS ${GLEW_ROOT_DIR}/include/GL/
        NO_DEFAULT_PATH)
    find_library(GLEW_LIBRARIES glew32
        PATHS ${GLEW_ROOT_DIR}/lib
            ${GLEW_ROOT_DIR}/lib
        NO_DEFAULT_PATH)
endif()

find_path(GLEW_INCLUDE_DIRS glew.h)
find_library(GLEW_LIBRARIES glew32)

mark_as_advanced(GLEW_ROOT_DIR GLEW_INCLUDE_DIRS GLEW_LIBRARIES)

find_package_handle_standard_args(GLEW DEFAULT_MSG
    GLEW_LIBRARIES GLEW_INCLUDE_DIRS)
