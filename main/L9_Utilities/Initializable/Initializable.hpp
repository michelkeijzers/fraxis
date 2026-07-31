#pragma once

#include "IInitializable.hpp"

class Initializable : public IInitializable
{
public:
    Initializable();
    ~Initializable();

    virtual bool IsInitialized() const override;
    virtual void MarkInitialized() override;

private:
    bool _isInitialized = false;    
};
