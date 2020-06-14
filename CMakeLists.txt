cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -std=c++2a -O3")

set(PROJECT_NAME "platformer-2d")
project(${PROJECT_NAME})


set(EXTERNAL_LIBRARIES_DIR "lib/")
set(SHARED_LIBRARIES_DIR "${EXTERNAL_LIBRARIES_DIR}/shared_lib")
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/SFML-2.5.1/lib/cmake/SFML")
set(TGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/TGUI-0.8/lib/cmake/TGUI")


include_directories(include
        include/States
        include/GUI
        include/GUI/Core
        include/ResourceManager
        include/Encoder
        include/Encoder/Utility
        include/Events
        include/Entities
        include/Entities/Player
        include/GUI/HUD
        googletest/googletest/include
        googletest/googlemock/include)

set(SOURCE_FILES
        src/main.cpp
        src/Game.cpp
        src/Window.cpp
        src/States/StateMachine.cpp
        src/States/StateGame.cpp
        src/States/StateMenu.cpp
        src/States/StateInit.cpp
        src/States/StateID.cpp
        src/ResourceManager/ResourceHolder.cpp
        src/ResourceManager/ResourceManager.cpp
        src/GUI/MenuConfig.cpp
        src/GUI/MenuGUI.cpp
        src/States/StateMapLoader.cpp
        src/GUI/MapLoaderGUI.cpp
        src/GUI/MapLoaderConfig.cpp
        src/Encoder/FileReader.cpp
        src/Encoder/BmpReader.cpp
        src/Encoder/TxtReader.cpp
        src/Encoder/Encoder.cpp
        src/Encoder/MapLoader.cpp
        src/Encoder/Utility/FileNameParser.cpp
        src/Consts.cpp src/Entities/Entity.cpp
        src/Entities/Block.cpp
        src/Entities/Player/Player.cpp
        src/Camera.cpp
        src/Events/CollisionEvent.cpp
        src/Events/MovementEvent.cpp
        src/Entities/Objective.cpp
        src/Events/InputEvent.cpp
        src/Settings.cpp
        src/States/StateOptions.cpp
        src/GUI/OptionsGUI.cpp
        src/GUI/HUD/LivesHUD.cpp
        src/Entities/Life.cpp
        src/GUI/HUD/LivesBorder.cpp
        src/Entities/Spike.cpp
        src/Entities/HeartCollectible.cpp
        src/States/StatePaused.cpp
        src/GUI/PausedGUI.cpp
        src/GUI/PausedConfig.cpp
        src/ActionMap.cpp include/ActionMap.h src/GUI/OptionsConfig.cpp include/GUI/OptionsConfig.h include/Action.h)


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