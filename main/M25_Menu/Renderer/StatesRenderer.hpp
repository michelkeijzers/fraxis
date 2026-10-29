#pragma once

class Renderer;
class States;

class StatesRenderer
{
public:
    StatesRenderer(
        Renderer& renderer,
        States& states);

    StatesRenderer(const StatesRenderer&) = delete;
    StatesRenderer& operator=(const StatesRenderer&) = delete;
    StatesRenderer(StatesRenderer&&) = delete;
    StatesRenderer& operator=(StatesRenderer&&) = delete;

    virtual ~StatesRenderer() = default;

    void RenderS000();
    void RenderS010();
    void RenderS020();
    void RenderS021();
    void RenderS030();
    void RenderS040();
    //void RenderS041(); // NOSONAR VCR001 TODO Menu
    //void RenderS043();
    //void RenderS044();
    //void RenderS045();
    void RenderS050();
    //void RenderS060(); // NOSONAR VCR001 TODO menu
    //void RenderS061();
    //void RenderS070();
    //void RenderS071();
    //void RenderS072();
    //void RenderS080();
    //void RenderS090();
    void RenderDefault();

private:
    Renderer& _renderer;
    States& _states;
};
