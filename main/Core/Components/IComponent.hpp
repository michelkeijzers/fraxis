#pragma once

class IComponent
{
public:
    virtual ~IComponent() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
};
