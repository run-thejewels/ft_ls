cmake_minimum_required(VERSION 3.14)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(lib/libft/include)
add_subdirectory(lib/libft)

aux_source_directory(src srcs)

add_executable(ft_ls ${srcs})

target_link_libraries(ft_ls libft)