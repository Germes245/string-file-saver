cmake_minimum_required(VERSION 3.10)
project(saving_strings_in_files)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Собираем список исходников
file(GLOB SOURCE_FILES "src/*.c")

# Создаём разделяемую (динамическую) библиотеку
add_library(saving_strings_in_files SHARED ${SOURCE_FILES})
target_include_directories(saving_strings_in_files PRIVATE include)

include(GNUInstallDirs)

# Устанавливаем библиотеку и заголовки
install(TARGETS saving_strings_in_files
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/saving_strings_in_files)