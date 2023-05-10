cmake_minimum_required(VERSION 3.12)
project(StockManager_C_Project)

# Definir o diretório de saída dos arquivos binários
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adicionar os arquivos de origem
set(SOURCES
    src/menu.c
    src/product.c
    src/main.c
)

# Adicionar o executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Definir o diretório de inclusão
target_include_directories(${PROJECT_NAME} PUBLIC include)