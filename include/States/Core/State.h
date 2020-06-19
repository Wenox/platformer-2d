/** \file */


#pragma once

#include <SFML/Graphics.hpp> ///< Pass-through
#include "Window.h"

/** \class State
 *
 * \ingroup theStates
 *
 * \brief An abstract class working as a polymorphic interface for Concrete States.
 *
 * All States have to override this class and implement pure virtual processInput() and draw(Window&) methods.
 *
 * Other methods are empty definion body pass-through method - the user can override only the method he needs in his Concrete State.
 *
 * */
class State {
public:
    /** Enable default destructor. */
    virtual ~State() = default;

    /** Empty pass-through method called by StateMachine when inserting new State. */
    virtual void onCreate() {};
    /** Empty pass-through method called by StateMachine when erasing existing State. */
    virtual void onDestroy() {};

    /** Empty pass-through method called by StateMachine when State was transitioned to. */
    virtual void onActivate() {};
    /** Empty pass-through method called by StateMachine when State was transitioned from. */
    virtual void onDeactivate() {};

    /** At the highest call level, invoked by Game class.
     *
     * <em>Perfect</em> interface: meaningfully overriden in all 8 States.
     *
     *
     * */
    virtual void processInput() = 0;

    /** At the highest call level, invoked by Game class.
    *
    * @param float Likely a time-elapsed since previous frame.
    *
    * */
    virtual void update(float) {};

    /** At the highest call level, invoked by Game class.
     *
     * <em>Perfect</em> interface: meaningfully overriden in all 8 States.
     *
     *
     * */
    virtual void draw(Window&) = 0;
};