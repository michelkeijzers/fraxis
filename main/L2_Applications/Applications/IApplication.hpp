#pragma once

class IApplication
{
public:
    IApplication();
    virtual ~IApplication();

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Stop() = 0;
    virtual void Run() = 0;
};
