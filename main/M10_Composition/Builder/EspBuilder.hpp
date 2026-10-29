#ifdef ESP_PLATFORM

#pragma once

#include "Builder.hpp"

// Forward declarations of Context
class Context;

class EspBuilder : public Builder
{
public:
    EspBuilder(
        Context& context);

    EspBuilder(const EspBuilder&) = delete;
    EspBuilder& operator=(const EspBuilder&) = delete;
    EspBuilder(EspBuilder&&) = delete;
    EspBuilder& operator=(EspBuilder&&) = delete;
    
    ~EspBuilder() override = default;

protected:
    void BuildServicesContext() override;
};

#endif // ESP_PLATFORM
