cmake_minimum_required(VERSION 3.24)
project(sdl2)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/Users/sdlig/libs/app/include)
set(SDL2_LIB_DIR C:/Users/sdlig/libs/app/lib/x86)
set(SDL2IMAGE_LIB_DIR C:/Users/sdlig/libs/app/SDL2_image-2.6.3/lib/x86)
set(SDL2IMAGE_INCLUDE_DIR C:/Users/sdlig/libs/app/SDL2_image-2.6.3/include)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2IMAGE_LIB_DIR})
add_executable(sdl2 main.cpp RenderWindow.cpp Entity.cpp Math.hpp math.cpp Generation.cpp Generation.hpp Blocks.hpp StringManipulation.cpp StringManipulation.hpp InventoryItem.cpp InventoryItem.hpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)
