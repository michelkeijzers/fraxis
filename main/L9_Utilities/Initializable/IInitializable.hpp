#pragma once

class IInitializable
{
public:
    IInitializable();
    ~IInitializable();

    virtual void Initialize() = 0;

    virtual bool IsInitialized() const = 0;
    virtual void MarkInitialized() = 0;
};
