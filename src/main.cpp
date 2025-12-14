#include <iostream>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <text.h>
#include <label.h>

struct triangle
{
    SDL_FPoint a, b, c;
};

namespace renderer
{
    struct font
    {
        float width;
        std::unordered_map<char, std::vector<SDL_Vertex>> table;
    };
}

struct app_context
{
    bool running;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    label main_label;
    triangle t;
    renderer::font font;
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
        .text = "0",
        .font_size = 12,
        .color = SDL_FColor{.r = 1.0, .g = 0.0, .b = 0.0, .a = 0.0},
    },
};

void load_font();
void handle_events();
void render();
void render_label();
void render_experimenting();

int main(int argc, char *argv[])
{
    load_font();
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

void load_font()
{
    text::load_font("asset/font.json");
    app.font.width = text::loaded_font.width;

    for (auto &s : text::loaded_font.symbols)
    {
        for (auto &v : s.vertices)
        {
            app.font.table[s.code].push_back(SDL_Vertex
            {
                .position = SDL_FPoint{.x = v.x, .y = v.y},
                .color = SDL_FColor{.r = 0.0, .g = 0.0, .b = 0.0, .a = 0.0}
            });
        }
    }
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
    SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 0);
    render_label();
    SDL_RenderPresent(app.renderer);
}

void render_label()
{
    for (auto symbol : app.main_label.text)
    {
        std::vector<SDL_Vertex> &vertices = app.font.table[symbol];

        for (auto &v : vertices)
        {
            v.color = app.main_label.color;
        }

        const float scale = 4.0;

        SDL_SetRenderScale(app.renderer, scale, scale);
        SDL_RenderGeometry(
            app.renderer,
            nullptr,
            vertices.data(),
            vertices.size(),
            nullptr,
            0
        );
    }
}

void render_experimenting()
{
    SDL_Rect original_viewport;
    SDL_GetRenderViewport(app.renderer, &original_viewport);

    // Vertices
    {
        const int length = 3;
        SDL_Vertex vertices[] =
        {
            SDL_Vertex
            {
                .position = {0.0, 1.0},
                .color = {255, 0, 0, 0},
            },
            SDL_Vertex
            {
                .position = {0.5, 0.0},
                .color = {255, 0, 0, 0},
            },
            SDL_Vertex
            {
                .position = {1.0, 1.0},
                .color = {255, 0, 0, 0},
            },
        };

        SDL_SetRenderScale(app.renderer, 16.0, 16.0);
        SDL_RenderGeometry(app.renderer, nullptr, vertices, length, nullptr, 0);
        SDL_SetRenderScale(app.renderer, 1.0, 1.0);
    }

    {
        SDL_Rect viewport = {50, 0, 800, 600};
        SDL_SetRenderViewport(app.renderer, &viewport);

        const int length = 3;
        SDL_Vertex vertices[] =
        {
            SDL_Vertex
            {
                .position = {0.0, 16.0},
                .color = {0, 255, 0, 0},
            },
            SDL_Vertex
            {
                .position = {8.0, 0.0},
                .color = {0, 255, 0, 0},
            },
            SDL_Vertex
            {
                .position = {16.0, 16.0},
                .color = {0, 255, 0, 0},
            },
        };

        SDL_RenderGeometry(app.renderer, nullptr, vertices, length, nullptr, 0);
    }

    SDL_SetRenderViewport(app.renderer, &original_viewport);

    // Lines
    // {
    //     SDL_FPoint lines[] = {
    //         {0.0, 16.0},
    //         {8.0, 0.0},
    //         {16.0, 16.0},
    //         {0.0, 16.0},
    //     };
    //     SDL_RenderLines(app.renderer, lines, 4);
    // }
}
