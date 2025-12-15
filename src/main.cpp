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
        .text = "0123456789",
        .font_size = 1.0,
        .color = SDL_FColor{.r = 1.0, .g = 0.0, .b = 0.0, .a = 1.0},
        .position{.x = 100, .y = 50},
    },
};

void load_font();
void handle_events();
void render();
void render_label();

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
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    render_label();
    SDL_RenderPresent(app.renderer);
}

void render_label()
{
    const int symbol_height = 16 * app.main_label.font_size;
    const int symbol_width = symbol_height * app.font.width;

    SDL_Texture *texture = SDL_CreateTexture(
        app.renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,
        symbol_height,
        symbol_height
    );

    SDL_FRect render_area
    {
        .x = app.main_label.position.x,
        .y = app.main_label.position.y,
        .w = symbol_width,
        .h = symbol_height
    };
    
    for (auto symbol : app.main_label.text)
    {
        auto &vertices = app.font.table[symbol];
        
        for (auto &v : vertices)
        {
            v.color = app.main_label.color;
        }

        SDL_SetRenderTarget(app.renderer, texture);
        SDL_RenderClear(app.renderer);
        SDL_SetRenderScale(app.renderer, symbol_height, symbol_height);
        SDL_RenderGeometry(app.renderer, nullptr, vertices.data(), vertices.size(), nullptr, 0);
        SDL_SetRenderTarget(app.renderer, nullptr);

        float empty_offset = 0.5 * (symbol_height - symbol_width);
        SDL_FRect texture_area{.x = empty_offset, .y = 0, .w = symbol_width, .h = symbol_height};
        SDL_RenderTexture(app.renderer, texture, &texture_area, &render_area);
        render_area.x += symbol_width;
    }

    SDL_SetRenderTarget(app.renderer, nullptr);
    SDL_DestroyTexture(texture);
}
