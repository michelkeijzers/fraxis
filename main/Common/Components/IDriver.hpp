#pragma once

class IDriver
{
public:
    virtual ~IDriver() = default;

    virtual void Initialize() = 0;
};
