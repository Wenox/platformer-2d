#pragma once


class Event {
public:
    virtual ~Event() = default;
    virtual void update() = 0;
};

