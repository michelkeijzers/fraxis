#pragma once

#include <memory>

// Forward declarations of domain models
class LedStrips;
class IoPins;
class Displays;

class DomainModelsContext
{
public:
    DomainModelsContext();
    ~DomainModelsContext();

    void Set(
        std::unique_ptr<LedStrips> ledStrips,
        std::unique_ptr<IoPins> ioPins,
        std::unique_ptr<Displays> displays);

    LedStrips& GetLedStrips()           { return *_ledStrips; } 
    IoPins& GetIoPins()                 { return *_ioPins; }
    Displays& GetDisplays()             { return *_displays; }

private:
    std::unique_ptr<LedStrips> _ledStrips;
    std::unique_ptr<IoPins> _ioPins;
    std::unique_ptr<Displays> _displays;
};
