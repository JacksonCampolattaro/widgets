
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtk REQUIRED IMPORTED_TARGET gtk4)

set(PARENT_SCOPE)
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
add_custom_command(
        OUTPUT ${GRESOURCE_C}
        COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --target=${GRESOURCE_C} ${GRESOURCE_XML}
        WORKING_DIRECTORY ${COMPILED_RESOURCE_DIR}
        # DEPENDS ${GRESOURCE_XML} ${UI_FILE_PATHS}
        DEPENDS blueprint-compilation ${GRESOURCE_XML} ${UI_FILE_PATHS}
        VERBATIM
)
#add_dependencies(gresources blueprint-compilation)

add_executable(
        demo-c
        main.c
        ${GRESOURCE_C}
)
target_link_libraries(
        demo-c PUBLIC

        PkgConfig::gtk
)
#add_dependencies(demo gresources)
