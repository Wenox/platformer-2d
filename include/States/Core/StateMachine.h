/** \file */

#pragma once


#include <memory>
#include "State.h"
#include "Window.h"

/** \class StateMachine
 *
 * \ingroup theStates
 *
 * \brief Container for all game States and holds current state pointer. Updates State logic every frame.
 *
 *
 * Main State wrapper. All states are held in #states.
 *
 * #currentState calls processInput(), update(float dt) and draw(Window& window) every frame from within Game class.
 *
 *
 * Holds all State in a map, and holds a pointer to current State.
 * */
class StateMachine {
public:

    /** Switches #currentState to a state found in the #states by the given argument.
     * @param stateID the ID of state to be switched to. */
    void switchTo(int stateID);

    /** Switches to whatever was the previous State held in #previousStateID. */
    void switchToPreviousState();

    /** Switches to a default State.
     *
     * \note Currently not implemented, but might be found useful in a future as an idea.
     *
     *
     * */
    void switchToDefaultState();


    /** Inserts new preallocated state into #states.
     *
     * @param state a shared_pointer to a newly allocated state.
     * @returns int the number of that state ID so that this state can be found later on.
     *
     * */
    int insert(const std::shared_ptr<State>& state);
    /** Erases the state of a given ID. The only explicitly erased state is StateGame when making new map.
     *
     * @param stateID the ID of state to be erased.
     *
     */
    void erase(int stateID);


    /** Pass-through method, calls processInput() of whatever is #currentState.
     *
     * Called by Game.
     * Works as a polymorphic indirection level between Game and Concrete State.
     * */
    void processInput() const;
    /** Pass-through method, calls update(float dt) of whatever is #currentState.
     *
     * Called by Game.
     * Works as a polymorphic indirection level between Game and Concrete State.
     * */
    void update(float dt) const;
    /** Pass-through method, calls draw(Window& window) of whatever is #currentState.
     *
     * Called by Game.
     * Works as a polymorphic indirection level between Game and Concrete State.
     * */
    void draw(Window& window) const;


    /** State can be switched to using operator= or switchTo(int).
     * @param stateID the ID of state to be switched to. */
    StateMachine& operator=(int stateID);
    StateMachine& operator+=(const std::shared_ptr<State>& s);

    /** Sets the #previousStateID to a given ID.
     * @param stateID new #previousStateID.*/
    void setPreviousStateID(int stateID) {
        previousStateID = stateID;
    }

    /** Retrieve the #previousStateID.
     * @returns int #previousStateID. */
    int getPreviousStateID() const { return previousStateID; }

private:
    std::unordered_map<int, std::shared_ptr<State>> states{}; ///< \brief Container for all states. Key: stateID, Value: a Concrete state.
    std::shared_ptr<State> currentState{nullptr}; ///< Current state

    int currentInsertedID{1};
    int previousStateID{};
};


