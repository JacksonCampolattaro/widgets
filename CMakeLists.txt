cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

project(widgets)

include(FetchContent)
FetchContent_Declare(
        blueprint
        GIT_SHALLOW TRUE
        GIT_REPOSITORY https://gitlab.gnome.org/jwestman/blueprint-compiler.git
        GIT_TAG v0.10.0
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(blueprint)
set(BLUEPRINT_COMPILER ${blueprint_SOURCE_DIR}/blueprint-compiler.py)

set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(COMPILED_RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)

# We'll compile all .blp files found in the resources directory
file(GLOB BLUEPRINT_FILE_NAMES RELATIVE ${RESOURCE_DIR} ${RESOURCE_DIR}/*.blp)
set(BLUEPRINT_FILE_PATHS ${BLUEPRINT_FILE_NAMES})
list(TRANSFORM BLUEPRINT_FILE_PATHS PREPEND ${RESOURCE_DIR}/)

# Output widget files have the same name, but with the .ui extension
set(UI_FILE_NAMES ${BLUEPRINT_FILE_NAMES})
list(TRANSFORM UI_FILE_NAMES REPLACE "[.]blp$" ".ui")
set(UI_FILE_PATHS ${UI_FILE_NAMES})
list(TRANSFORM UI_FILE_PATHS PREPEND ${COMPILED_RESOURCE_DIR}/)

# Produce the xml files using blueprint-compiler
add_custom_command(
        OUTPUT ${UI_FILE_PATHS}
        COMMAND ${BLUEPRINT_COMPILER} batch-compile ${COMPILED_RESOURCE_DIR} ${RESOURCE_DIR} ${BLUEPRINT_FILE_PATHS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${BLUEPRINT_FILE_PATHS}
        VERBATIM
)

# Create a gresource.xml file by adding all resources to a template
set(GRESOURCE_XML_IN ${RESOURCE_DIR}/gresource.xml.in)
set(GRESOURCE_XML ${COMPILED_RESOURCE_DIR}/gresource.xml)
set(GRESOURCE_C ${COMPILED_RESOURCE_DIR}/gresource.c)
set(GRESOURCE_PREFIX campolattaro/jackson/widgets/)
set(GRESOURCE_FILES ${UI_FILE_NAMES})
list(TRANSFORM GRESOURCE_FILES PREPEND "<file>")
list(TRANSFORM GRESOURCE_FILES APPEND "</file>")
string(REPLACE ";" "\n\t\t" GRESOURCE_FILES "${GRESOURCE_FILES}")
configure_file(${GRESOURCE_XML_IN} ${GRESOURCE_XML} @ONLY)

add_subdirectory(demo)
