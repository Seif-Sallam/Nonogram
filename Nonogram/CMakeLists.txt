cmake_minimum_required(VERSION 3.16)

FILE(GLOB SOURCES ./src/*.cpp)

FILE(GLOB HEADERS ./headers/*.h)

add_executable(
    Nonogram
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    Nonogram
    PRIVATE
    ./headers/
)

target_link_libraries(Nonogram
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Nonogram
        PRIVATE
        RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
    )
else()
    target_compile_definitions(Nonogram
        PRIVATE
        RSC_DIR="./rsc/"
    )

    set_target_properties(Nonogram PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    if (NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rsc/)
        file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rsc/)
    endif()

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rsc/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rsc/)
endif()
