#pragma once

#include "IInitializable.hpp"

class Initializable : public IInitializable
{
public:
    Initializable();
    
    Initializable(const Initializable&) = delete;
    Initializable& operator=(const Initializable&) = delete;
    Initializable(Initializable&&) = delete;
    Initializable& operator=(Initializable&&) = delete;

    ~Initializable() override;

    [[nodiscard]] bool IsInitialized() const override;
    void MarkInitialized() override;

private:
    bool _isInitialized = false;    
};
