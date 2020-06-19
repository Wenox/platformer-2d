/** @file */

#pragma once

/** \class PhysicsEvent
 *
 *  \ingroup theEvents
 *
 *  \brief Specified Base PhysicsEvent class handling physics-related events on two separate axises. */
class PhysicsEvent {
public:

    /** \brief Default the destructor. */
    virtual ~PhysicsEvent() = default;

    /** \brief Handles the events on X axis. */
    virtual void updateAxisY(float dt) = 0;
    /** \brief Handles the events on Y axis. */
    virtual void updateAxisX(float dt) = 0;
};