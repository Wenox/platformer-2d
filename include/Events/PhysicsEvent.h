#pragma once


class PhysicsEvent {
public:
    virtual ~PhysicsEvent() = default;

    virtual void updateAxisX(float dt) = 0;
    virtual void updateAxisY(float dt) = 0;
};