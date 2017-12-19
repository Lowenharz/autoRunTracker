# Add python executables to bin directory

function(add_python_application _target _source_files)

    add_custom_command(
            OUTPUT ${_source_files}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_source_files} $<TARGET_FILE_DIR:interop2csv>
    )
endfunction()

#IUO
add_python_application(plot_distortion_curves plot_distortion_curves.py)
