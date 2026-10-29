#pragma once

#include "ApplicationIds.hpp"
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
        EApplicationId applicationId,
        Context& context, 
        ApplicationsManager& applicationsManager);
        
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    ~Application() override = default;

    Context& GetContext();
    ApplicationsManager& GetApplicationsManager();

    [[nodiscard]] bool IsFavorite() const;
    void SetFavorite(
        bool isFavorite);

    [[nodiscard]] bool IsNew() const;
    void SetNew(
        bool isNew);

    [[nodiscard]] uint32_t GetNrOfStarts() const;
    void SetNrOfStarts(
        uint32_t nrOfStarts);

    [[nodiscard]] uint32_t GetLastStartTime() const;
    void SetLastStartTime(
        uint32_t lastStartTime);

    [[nodiscard]] EState GetState() const;
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;

    Send& GetSend();

private:
    EApplicationId _applicationId;
    Context& _context;
    ApplicationsManager& _applicationsManager;
    EState _state;

    // To be defined after _applicationsManager because of -w ordering

    bool _isFavorite;
    bool _isNew;
    uint32_t _nrOfStarts;
    uint32_t _lastStartTime;

    void DisplayName();
};
