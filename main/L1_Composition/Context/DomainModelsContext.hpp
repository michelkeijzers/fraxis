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
        std::unique_ptr<Displays> displays,
        std::unique_ptr<IoPins> ioPins,
        std::unique_ptr<LedStrips> ledStrips
    );

    Displays& GetDisplays()             { return *_displays; }
    IoPins& GetIoPins()                 { return *_ioPins; }
    LedStrips& GetLedStrips()           { return *_ledStrips; } 

private:
    std::unique_ptr<Displays> _displays;
    std::unique_ptr<IoPins> _ioPins;
    std::unique_ptr<LedStrips> _ledStrips;
};
