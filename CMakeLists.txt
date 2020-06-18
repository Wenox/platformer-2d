cmake_minimum_required(VERSION 3.16)

set(ALL_WARNING_FLAGS "-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

set(PROJECT_NAME "platformer-2d")
project(${PROJECT_NAME})


set(EXTERNAL_LIBRARIES_DIR "lib/")
set(SHARED_LIBRARIES_DIR "${EXTERNAL_LIBRARIES_DIR}/shared_lib")
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/SFML-2.5.1/lib/cmake/SFML")
set(TGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_LIBRARIES_DIR}/TGUI-0.8/lib/cmake/TGUI")


include_directories(include
        include/Core
        include/States
        include/States/Core
        include/GUI
        include/GUI/Core
        include/GUI/Views/
        include/GUI/Configs/
        include/ResourceManager
        include/Encoder
        include/Encoder/Utility
        include/Events
        include/Entities
        include/Entities/Player
        include/Entities/Overlay
        include/GUI/HUD
        googletest/googletest/include
        googletest/googlemock/include)

set(SOURCE_FILES
        src/Core/main.cpp
        src/Core/Game.cpp
        src/Core/Window.cpp
        src/States/Core/StateMachine.cpp
        src/States/StateGame.cpp
        src/States/StateMenu.cpp
        src/States/Core/StateID.cpp
        src/ResourceManager/ResourceHolder.cpp
        src/ResourceManager/ResourceManager.cpp
        src/GUI/Configs/MenuConfig.cpp
        src/GUI/Views/MenuView.cpp
        src/States/StateMapLoader.cpp
        src/GUI/Views/MapLoaderView.cpp
        src/GUI/Configs/MapLoaderConfig.cpp
        src/Encoder/FileReader.cpp
        src/Encoder/BmpReader.cpp
        src/Encoder/TxtReader.cpp
        src/Encoder/Encoder.cpp
        src/Encoder/MapLoader.cpp
        src/Encoder/Utility/MapNameValidator.cpp
        src/Core/Consts.cpp src/Entities/Entity.cpp
        src/Entities/Block.cpp
        src/Entities/Player/Player.cpp
        src/Core/Camera.cpp
        src/Events/CollisionEvent.cpp
        src/Events/MovementEvent.cpp
        src/Entities/Objective.cpp
        src/Events/InputEvent.cpp
        src/Core/Settings.cpp
        src/States/StateOptions.cpp
        src/GUI/Views/OptionsView.cpp
        src/Entities/Overlay/LivesOverlay.cpp
        src/Entities/Life.cpp
        src/Entities/Overlay/LivesBorder.cpp
        src/Entities/Spike.cpp
        src/Entities/HeartCollectible.cpp
        src/States/StatePaused.cpp
        src/GUI/Views/PausedView.cpp
        src/GUI/Configs/PausedConfig.cpp
        src/Core/ActionMap.cpp
        src/GUI/Configs/OptionsConfig.cpp
        src/States/StateKeybinds.cpp
        src/States/StateRestart.cpp
        src/GUI/Views/RestartView.cpp
        src/GUI/Configs/RestartConfig.cpp
        src/Entities/Overlay/FpsOverlay.cpp
        src/States/StateAbout.cpp src/GUI/Views/KeybindsView.cpp src/GUI/Configs/KeybindsConfig.cpp)


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