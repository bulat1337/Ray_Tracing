cmake_minimum_required(VERSION 3.10)

project(ray_tracing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES src/*.cpp)

add_library(ray_tracing STATIC ${SRC_FILES})

target_include_directories(ray_tracing PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/include>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:external/include>
)

target_compile_options(ray_tracing PRIVATE
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

target_link_options(ray_tracing PRIVATE
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
)
