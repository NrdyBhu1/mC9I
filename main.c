// includes
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

// definitions
#define SDL_MAIN_HANDLED
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//type definitions
typedef enum { true, false } bool;

// gravity
int getAcceleration(float objectMass, float bodyMass, float distance) {
    int force;
    if (distance > 0) {
        force = (bodyMass * objectMass) / distance;
    } else {
        force = 0;
    }
    return force / 10;
}

// player struct declarations
typedef struct {
    SDL_Rect rect;
    bool jumping : false;
    /*SDL_Color color;*/
    /*float speed;*/
    float bodyMass;
} Player;

void update_player(Player *player, float dt) {
    player->rect.y += getAcceleration(player->bodyMass, 500, WINDOW_HEIGHT - player->rect.y-10-player->rect.h) * dt;
    if (player->rect.y > WINDOW_HEIGHT - player->rect.h) {
        player->rect.y = WINDOW_HEIGHT - player->rect.h;
    }
}

void render_player(Player *player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 10, 255);
    SDL_RenderFillRect(renderer, &player->rect);
}

// main
int main(void) {

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        printf("SDL ERROR: %s", SDL_GetError());
        exit(-1);
        return -1;
    }

    // variable declarations
    SDL_Window* window = SDL_CreateWindow("mC9I", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool gameOver = false;
    SDL_Event event;
    SDL_Rect rect = {0, 0, 50, 70};
    Player player = { .rect = rect , .bodyMass = 50.0f};
    float dt = 0.0f;
    float previousTic = 0.1f;

    // main loop
    while (gameOver != true) {
        SDL_PollEvent(&event);
        dt = (SDL_GetTicks() - previousTic ) / 10;
        previousTic = SDL_GetTicks();
        update_player(&player, dt);

        /*printf("%d\n", player.rect.y);*/

        // events
        if (event.type == SDL_QUIT) {
            gameOver = true;
            break;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                gameOver = true;
                break;
            }

            if (event.key.keysym.sym == SDLK_q) {
                gameOver = true;
                break;
            }

            if (event.key.keysym.sym == SDLK_r) {
                player.rect.y = 0;
            }
        }

        // graphics
        SDL_RenderClear(renderer);
        render_player(&player, renderer);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
