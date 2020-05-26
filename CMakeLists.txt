cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

set(PROJECT_NAME "platformer-2d")
project(${PROJECT_NAME})


set(EXTERNAL_LIBRARIES_DIR "lib/")
set(SHARED_LIBRARIES_DIR "${EXTERNAL_LIBRARIES_DIR}/shared_lib")
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/SFML-2.5.1/lib/cmake/SFML")
set(TGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/TGUI-0.8/lib/cmake/TGUI")


include_directories(include
        include/States
        googletest/googletest/include
        googletest/googlemock/include)

set(SOURCE_FILES
        src/main.cpp
        src/Game.cpp
        src/Window.cpp src/States/StateMachine.cpp include/States/StateMachine.h src/States/StateGame.cpp include/States/StateGame.h src/States/StateMenu.cpp include/States/StateMenu.h src/States/StateInit.cpp include/States/StateInit.h include/States/StateID.h src/States/StateID.cpp src/ResourceManager/ResourceHolder.cpp include/ResourceManager/ResourceHolder.h src/ResourceManager/ResourceManager.cpp include/ResourceManager/ResourceManager.h include/ResourceManager/Resources.h include/ResourceManager/ResourceInserter.h src/MenuGUI.cpp include/MenuGUI.h include/MenuItems.h src/MenuItems.cpp include/GUI.h include/Config.h include/Utility.h)


find_package(SFML 2.5.1 COMPONENTS graphics network audio REQUIRED)
find_package(TGUI 0.8 REQUIRED)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})


set(SFML_LIBRARIES sfml-graphics sfml-audio sfml-network)
set(TGUI_LIBRARIES tgui)
set(PROJECT_LIBRARIES ${SFML_LIBRARIES} ${TGUI_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARIES})


# copy the sfml libraries into the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_LIST_DIR}/${SHARED_LIBRARIES_DIR}/"
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_subdirectory(test)