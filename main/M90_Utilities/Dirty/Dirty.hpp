#pragma once

#include "IDirty.hpp"

class Dirty : public IDirty
{
public:
    Dirty();

    Dirty(const Dirty&) = delete;
    Dirty& operator=(const Dirty&) = delete;
    Dirty(Dirty&&) = delete;
    Dirty& operator=(Dirty&&) = delete;

    ~Dirty() override;
    
    [[nodiscard]] bool IsDirty() const override;
    void MarkDirty() override;
    void ClearDirty() override;

private:
    bool _isDirty = false;    
};
