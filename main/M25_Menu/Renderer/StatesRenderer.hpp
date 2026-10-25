#pragma once

class Renderer;
class States;

class StatesRenderer
{
public:
    StatesRenderer(
        Renderer& renderer,
        States& states);

    virtual ~StatesRenderer() = default;

    void RenderS000();
    void RenderS010();
    void RenderS020();
    void RenderS021();
    void RenderS030();
    void RenderS040();
    void RenderS041();
    void RenderS043();
    void RenderS044();
    void RenderS045();
    void RenderS050();
    void RenderS060();
    void RenderS061();
    void RenderS070();
    void RenderS071();
    void RenderS072();
    void RenderS080();
    void RenderS090();
    void RenderDefault();

private:
    Renderer& _renderer;
    States& _states;
};
