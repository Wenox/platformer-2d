/** @file */
#pragma once

#include <SFML/Audio/Sound.hpp>
#include "MapLoader.h"
#include "StateRestart.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "MovementEvent.h"
#include "InputEvent.h"
#include "FpsOverlay.h"
#include "Objective.h"
#include "Spike.h"
#include "HeartCollectible.h"


/** \class StateGame
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the main game logic within one StateGame class.
 *
 *  \note All possible transitions from StateGame are:
 *    - StateOptions
 *    - StatePaused
 *    - StateMenu
 *    - StateRestart
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateGame : public State {
public:
    /** \brief Create the StateGame.
     *
     * @param stateMachine
     * @param window
     * @param resourceManager
     * @param mapLoader either a Bmp or Txt variant, depending on map type.
     *
     * \details
     * Sets the #camera, #background image and default sounds.
     * Constructor invoked from Game, or StateMapLoader depending if user chose default or custom map.
     *
     * */
    StateGame(StateMachine &stateMachine,
              Window& window,
              ResourceManager& resources,
              std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader);

    /** \brief Called when the State is created. Generates the World by visiting a variant.
     *
     * - 1. Generate the World using static polymorphism.
     * - 2. Set the World textures.
     * - 3. Set Camera controller.
     * - 4. Create Event / PhysicsEvent classes.
     *
     *  */
    void onCreate() override;

    /** \brief Called when the StateGame is destroyed, which is either upon Window close (end Game); or when new map is loaded. */
    void onDestroy() override;

    /** \brief Called when StateMenu is activated. Updates activation StateGame logic.
     *
     *  StateGame activation logic:
     * - Because player can re-enter StateGame from PausedState, checks if getPreviousStateIF() is state::restartID. Only in such a case, a restartGameLevel() is performed.
     * - Plays the #music
     * - Updates the sound volume.
     * */
    void onActivate() override;

    /** \brief Called when StateMenu is left. Pause the music and store previous state as state::gameID. */
    void onDeactivate() override;

    /** \brief Call InputEvent->update() method, and process activation StatePause keypress input.
     *
     * \note
     * Also, process keypresses events trying to switch to a different State.
     *
     */
    void processInput() override;

    /** \brief Performs a frame cycle of a main game loop.
     *  @param dt Time elapsed since previous frame.
     *
     * \details The following is called:
     * - updatePhysics(dt);
     * - window.updateView(camera.getCameraView());
     * - fps.update(dt);
     * - updatePlayerLife();
     * - updateGameStatus();
     *
     * The physics is updated in an axis independent way: first the X axis, then the Y axis. This greatly simplified collision logic.
     * */
    void update(float dt) override;
    /** \brief Draws the game onto the screen.
     *
     * @param window The window the game is drawn onto.
     *
     * \note
     * \details The following entities are drawn:
     * - 1. #background
     * - 2. #blocks Entities (collidables)
     * - 3. #spikes Entities (killing entities)
     * - 4. #hearts Entities (collectibles)
     * - 5. #objective, an Entity
     * - 6. #player, a controlling Entity
     * - 7. #lives, an overlay Entity HUD
     * - 8. #fps, an overlay Entity HUD
     *
     * \note
     * Points **2, 3, 4**: only Entities in a drawable range are rendered.
     * Point **4**: collected Entities are no longer displayed.
     * Point **8**: may be disabled/enabled in StateOptions during run-time.
     *
     *
     * */
    void draw(Window& window) override;

private:

    /** \brief Update: MovementEvent, CollisionEvent and Camera on axis X, then on axis Y.
     *
     * Called every frame:
     * movementsEvent->updateAxisY(dt);
     * collisionEvent->updateAxisY(dt);
     * camera.updateY();
     *
     * movementsEvent->updateAxisY(dt);
     * collisionEvent->updateAxisY(dt);
     * camera.updateY();
     *
     * \*/
    void updatePhysics(float dt);

    /** \brief Update the status of player life (lose or gain life). */
    void updatePlayerLife();

    /** \brief Player collects heart if he touches a visible heart and Player is missing lives. */
    void updateGainLifeLogic();
    /** \brief Player loses life if he touches the Spike */
    void updateLoseLifeLogic();

    /** \brief Checks if a given heart can be collected.
     *
     * @param heart checked heart if it can be collected
     * @returns Can the heart be collected?
     * A heart can be collected if all are satisifed:
     * - it was not collected before
     * - #player is intersecting it
     * - #player has missing life(s) */
    bool canCollect(const HeartCollectible& heart);

    /** \brief Update the game status: checks if game was won or lost in current frame. */
    void updateGameStatus();

    /** \brief Check if current frame was a losing frame. Lose condition: #player lost all #lives.*/
    void checkLoseCondition();

    /** \brief Check if current frame was a winning frame. Win condition: reach #objective. */
    void checkWinCondition();

    /** Checks if #player is in draw range of #entity. Draw range is a range that fts on screen.
     *
     * @returns Is entity within view range? */
    bool isInDrawRange(const Entity& entity) const;

    /** Checks if #player fell to death by falling below the map edge.
     *
     * @returns Did player fell to death?
     *
     * */
    bool playerFellToDeath() const;


    /** \brief Generate world from a Bmp. Allocate blocks and set them to proper position. */
    void generateWorldFromBmp();
    /** \brief Generate world from a Txt. Allocate blocks and set them to proper position. */
    void generateWorldFromTxt();

    /** \brief Load the #music. */
    void loadMusic();

    /** \brief Sets the textures of all Entity objects. */
    void setEntitiesTextures();
    /** \brief Set the textures of Block entities. */
    void setBlocksTextures();
    /** \brief Set the spike texture facing correct direction to each Spike entity. */
    void setSpikesTextures();
    /** \brief Set the collectible texture to all Collectible entities. */
    void setCollectiblesTextures();

    /** Refill Player #lives and respawn #hearts. Set player to starting position. */
    void restartGameLevel();


    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;


    /** todo: Simplifiable to WorldLoader class */
    std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader;
    std::queue<res::Texture> blocksQueue;


    /** todo: Simplifiable to World class */
    Player player;
    Objective objective;
    std::vector<std::unique_ptr<Entity>> blocks;
    std::vector<std::unique_ptr<Spike>> spikes;
    std::vector<std::unique_ptr<HeartCollectible>> hearts;
    sf::Sprite background;


    Camera camera;


    /** todo: Simplifiable to e.g. EventsList class */
    std::unique_ptr<MovementEvent>  movementsEvent;
    std::unique_ptr<CollisionEvent> collisionEvent;
    std::unique_ptr<InputEvent>     inputEvent;


    /** todo: Simplifiable to Overlay class */
    LivesOverlay lives;
    FpsOverlay   fps;


    /** todo: Simplifiable to e.g. SoundPlayer class */
    sf::Sound collectSound;
    sf::Sound deathSound;
    sf::Sound winGameSound;
    sf::Music music;


    const int bottomBorderHeight = config::entityHeight * config::blocksCountHeight;
};


