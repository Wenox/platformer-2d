/** @file */

/** @defgroup theEvents Events
 *  Events updating the game logic within StateGame class.
 *  @{
 */

/** @} */ // end of group1

#pragma once

/** \class Event
 *
 *  \ingroup theEvents
 *
 *  \brief Event class with update() pure virtual method handling trivial events. */
class Event {
public:

    /** \brief Default the destructor. */
    virtual ~Event() = default;

    /** \brief Handles simplest events. Pure virtual update method to be overriden by deriving classes. */
    virtual void update() = 0;
};


