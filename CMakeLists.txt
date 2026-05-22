cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(PokeRogue_Vita C)
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

set(VITA_APP_NAME "PokeRogue Vita")
set(VITA_TITLEID  "PKRG00001") 
set(VITA_VERSION  "00.05")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB ALL_SOURCES CONFIGURE_DEPENDS "src/*.c" "src/*.h")

add_executable(${PROJECT_NAME}
  ${ALL_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    src
)

target_compile_options(${PROJECT_NAME} PRIVATE
    ${SDL2_CFLAGS_OTHER}
    ${SDL2_IMAGE_CFLAGS_OTHER}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  SceCtrl_stub
  SceDisplay_stub
  SceGxm_stub
  SceSysmodule_stub
  SceCommonDialog_stub
  SceAudio_stub
  png
  jpeg
  z
)

set(VPK_STAGING_DIR "${CMAKE_CURRENT_BINARY_DIR}/temp_images")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory "${VPK_STAGING_DIR}/assets/images"

    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/images" "${VPK_STAGING_DIR}/assets/images"
    
    COMMENT "Staging images directory for VPK packaging..."
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/pfg.png sce_sys/livearea/contents/pfg.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE "${VPK_STAGING_DIR}/assets" "assets"
)