#pragma once

#include "IDirty.hpp"

class Dirty : public IDirty
{
public:
    Dirty();
    virtual ~Dirty();

    virtual bool IsDirty() const override;
    virtual void MarkDirty() override;
    virtual void ClearDirty() override;

private:
    bool _isDirty = false;    
};
