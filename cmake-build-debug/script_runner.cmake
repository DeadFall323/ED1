file(GLOB EXECUTABLES ${CMAKE_SOURCE_DIR}/executable/*)

foreach(EXE ${EXECUTABLES})
    execute_process(COMMAND ${EXE})
endforeach()
