#pragma once

class IInitializable
{
public:
    IInitializable();

    IInitializable(const IInitializable&) = delete;
    IInitializable& operator=(const IInitializable&) = delete;
    IInitializable(IInitializable&&) = delete;
    IInitializable& operator=(IInitializable&&) = delete;

    virtual ~IInitializable();

    virtual void Initialize() = 0;

    [[nodiscard]] virtual bool IsInitialized() const = 0;
    
    virtual void MarkInitialized() = 0;
};
