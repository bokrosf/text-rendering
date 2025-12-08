#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <text.h>
#include <label.h>

struct app_context
{
    bool running;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    label main_label;
};

app_context app = app_context
{
    .running = true,
    .width = 800,
    .height = 600,
    .window = nullptr,
    .renderer = nullptr,
    .main_label = label
    {
        .text = "ababbba",
        .font_size = 12,
        .color = SDL_Color{255, 0, 0, 0},
    },
};

void handle_events();
void render();
void render_label();

int main(int argc, char *argv[])
{
    text::load_font("asset/font.json");

    const SDL_InitFlags init_flags = SDL_INIT_EVENTS | SDL_INIT_VIDEO;
    const SDL_WindowFlags window_flags = 0;
    SDL_Init(init_flags);
    SDL_CreateWindowAndRenderer(
        "text-rendering",
        app.width,
        app.height,
        window_flags,
        &app.window,
        &app.renderer
    );

    while (app.running)
    {
        handle_events();
        render();
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_QuitSubSystem(init_flags);
    SDL_Quit();

    return 0;
}

void handle_events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            app.running = false;
            
            return;
        }
        
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            // Handle keypress: event.key.key == SDLK_A
        }
    }
}

void render()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.renderer);
    render_label();
    SDL_RenderPresent(app.renderer);
}

void render_label()
{
    SDL_Rect original_viewport;
    SDL_GetRenderViewport(app.renderer, &original_viewport);

    SDL_SetRenderDrawColor(
        app.renderer,
        app.main_label.color.r,
        app.main_label.color.g,
        app.main_label.color.b,
        app.main_label.color.a
    );

    SDL_Rect font_area
    {
        .x = 0,
        .y = 0,
        .w = text::loaded_font.width,
        .h = text::loaded_font.height,
    };

    for (char c : app.main_label.text)
    {
        SDL_SetRenderViewport(app.renderer, &font_area);

        for (const auto &sequence : text::loaded_font.table[c])
        {
            SDL_RenderLines(
                app.renderer,
                reinterpret_cast<const SDL_FPoint *>(sequence.data()),
                sequence.size()
            );
        }

        font_area.x += text::loaded_font.width;
    }

    SDL_SetRenderViewport(app.renderer, &original_viewport);
}
