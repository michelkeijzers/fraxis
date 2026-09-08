#pragma once

#include "IApplication.hpp"
#include "../IEventListener.hpp"
#include "Send.hpp"
#include <string>

class Context;
class ApplicationsManager;

class Application : public IApplication, public IEventListener
{
public:
    Application(
        Context& context, 
        ApplicationsManager& applicationsManager);
        
    virtual ~Application() = default;
        
    Context& GetContext();
    ApplicationsManager& GetApplicationsManager();

    bool IsFavorite() const;
    void SetFavorite(
        bool isFavorite);

    bool IsNew() const;
    void SetNew(
        bool isNew);

    uint32_t GetNrOfStarts() const;
    void SetNrOfStarts(
        uint32_t nrOfStarts);

    uint32_t GetLastStartTime() const;
    void SetLastStartTime(
        uint32_t lastStartTime);

protected:
    Send& GetSend();

private:
    Context& _context;
    ApplicationsManager& _applicationsManager;
    EType _type;

    // To be defined after _applicationsManager because of -w ordering
    Send _send;

    bool _isFavorite;
    bool _isNew;
    uint32_t _nrOfStarts;
    uint32_t _lastStartTime;

};
