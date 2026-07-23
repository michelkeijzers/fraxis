#pragma once

#include <memory>

// Forward declarations of domain models
class LedStrips;
class IoPins;
class Lcd2004;
class Tm1637;

class DomainModelsContext
{
public:
    DomainModelsContext();
    ~DomainModelsContext();

    // Builder injects all domain models at once
    void Set(
        std::unique_ptr<LedStrips> ledStrips,
        std::unique_ptr<IoPins> ioPins,
        std::unique_ptr<Lcd2004> lcd2004,
        std::unique_ptr<Tm1637> tm1637CentralPanel,
        std::unique_ptr<Tm1637> tm1637Player1,
        std::unique_ptr<Tm1637> tm1637Player2);


    LedStrips& GetLedStrips()           { return *_ledStrips; } 
    IoPins& GetIoPins()                  { return *_ioPins; }
    Lcd2004& GetLcd2004()               { return *_lcd2004; }
    Tm1637& GetTm1637CentralPanel()     { return *_tm1637CentralPanel; }
    Tm1637& GetTm1637Player1()          { return *_tm1637Player1; }
    Tm1637& GetTm1637Player2()          { return *_tm1637Player2; }

private:
    // Domain models owned by the context
    std::unique_ptr<LedStrips> _ledStrips;
    std::unique_ptr<IoPins> _ioPins;
    std::unique_ptr<Lcd2004> _lcd2004;
    std::unique_ptr<Tm1637> _tm1637CentralPanel;
    std::unique_ptr<Tm1637> _tm1637Player1;
    std::unique_ptr<Tm1637> _tm1637Player2;
};
