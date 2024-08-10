project(examples)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../ ${CMAKE_BINARY_DIR}/ray_tracing)

file(GLOB EXAMPLE_SOURCES *.cpp)

foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})

    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    # Создаем исполняемый файл с именем, совпадающим с именем .cpp файла
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})

    # Линкуем с библиотекой ray_tracing
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ray_tracing)

    # Указываем, что для компиляции примеров нужны заголовочные файлы из include и external/include
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/include
    )

    # Можно также добавить флаги компиляции, аналогичные тем, что используются для библиотеки
    target_compile_options(${EXAMPLE_NAME} PRIVATE
        -D_DEBUG
        -ggdb3
        -O0
        -Wall
        -Wextra
        -Weffc++
        -Wc++14-compat
        -Wmissing-declarations
        -Wcast-align
        -Wcast-qual
        -Wchar-subscripts
        -Wconversion
        -Wctor-dtor-privacy
        -Wempty-body
        -Wfloat-equal
        -Wformat-nonliteral
        -Wformat-security
        -Wformat=2
        -Winline
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wpacked
        -Wpointer-arith
        -Winit-self
        -Wredundant-decls
        -Wshadow
        -Wsign-conversion
        -Wsign-promo
        -Wstrict-overflow=2
        -Wsuggest-override
        -Wswitch-default
        -Wswitch-enum
        -Wundef
        -Wunreachable-code
        -Wunused
        -Wvariadic-macros
        -Wno-missing-field-initializers
        -Wno-narrowing
        -Wno-old-style-cast
        -Wno-varargs
        -Wstack-protector
        -fcheck-new
        -fsized-deallocation
        -fstack-protector
        -fstrict-overflow
        -fno-omit-frame-pointer
        -Wlarger-than=8192
        -fPIE
        -Werror=vla
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )

    target_link_options(${EXAMPLE_NAME} PRIVATE
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )
endforeach()
