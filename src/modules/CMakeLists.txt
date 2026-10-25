if(QT_VERSION_MAJOR EQUAL 5)
    function(qt_add_qml_module TARGET)
        cmake_parse_arguments(PARSE_ARGV 1 arg "" "" "SOURCES")
        add_library(${TARGET} SHARED ${arg_SOURCES})
        configure_file(qmldir qmldir COPYONLY)
    endfunction()
endif()

add_subdirectory(QtMir)
