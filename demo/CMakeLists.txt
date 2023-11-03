
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0 glibmm-2.68 giomm-2.68)
pkg_check_modules(adwaita REQUIRED IMPORTED_TARGET libadwaita-1)

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
add_custom_command(
        OUTPUT ${GRESOURCE_C}
        COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --target=${GRESOURCE_C} ${GRESOURCE_XML}
        WORKING_DIRECTORY ${COMPILED_RESOURCE_DIR}
        DEPENDS ${GRESOURCE_XML} ${UI_FILE_PATHS}
        VERBATIM
)

add_executable(
        demo
        main.cpp
        ${GRESOURCE_C}
        BuilderWidget.h
)
target_link_libraries(
        demo PUBLIC

        PkgConfig::gtkmm
        PkgConfig::adwaita
)
