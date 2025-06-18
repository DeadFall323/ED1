cmake_minimum_required(VERSION 3.10)
project(MeuProjeto)

#pode usar mais de um desses
#para usar c
set(CMAKE_C_STANDARD 99)
#para usar cpp
#set(CMAKE_CXX_STANDARD 17)

# Definir diretório de saída dos executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/executable)

# Criar uma variável para armazenar os executáveis
set(EXEC_LIST "")

# Buscar todos os arquivos fonte na pasta 'source'
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/source/*.c)

# Criar os executáveis dinamicamente
foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${EXEC_NAME} ${SOURCE_FILE}
            headers/eventos.h
            source/eventos.c
            headers/atividades.h
            source/atividades.c
            headers/participantes.h
            source/participantes.c
            headers/checkin.h
            source/checkin.c
            headers/desfazer.h
            source/desfazer.c
            headers/ordenacao.h
            source/ordenacao.c)

    # Garantir que cada executável seja colocado na pasta 'executable'
    set_target_properties(${EXEC_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/executable
    )

    list(APPEND EXEC_LIST ${EXEC_NAME})
endforeach()

# Criar um alvo para rodar todos os executáveis
add_custom_target(run_all
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/script_runner.cmake
        DEPENDS ${EXEC_LIST}
)

# Copiar script de execução para a pasta de build
configure_file(${CMAKE_SOURCE_DIR}/script_runner.cmake ${CMAKE_BINARY_DIR}/script_runner.cmake COPYONLY)
