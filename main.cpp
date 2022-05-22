#include "SDL_utilities.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

Mix_Chunk* sound_eat ;
Mix_Chunk* sound_lost ;
Mix_Music* sound_menu ;
Mix_Music* sound_bg ;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Snake snake;
    Food food;

    sound_eat = Mix_LoadWAV("Sound/Eat.wav");
    sound_lost = Mix_LoadWAV("Sound/Lose.wav");
    sound_bg = Mix_LoadMUS("Sound/bg_audio.wav");
    sound_menu = Mix_LoadMUS("Sound/Menu_audio.wav");

    SDL_Texture* background=IMG_LoadTexture( renderer, "img/background.jpg");
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.h = SCREEN_HEIGHT;
    background_rect.w = SCREEN_WIDTH;

    SDL_Texture* menu=IMG_LoadTexture( renderer, "img/menu.jpg");
    SDL_Rect menu_rect;
    menu_rect.x = 0;
    menu_rect.y = 0;
    menu_rect.h = SCREEN_HEIGHT;
    menu_rect.w = SCREEN_WIDTH;

    SDL_Texture* gameOver=IMG_LoadTexture( renderer, "img/game_over.jpg");
    SDL_Rect gameOver_rect;
    gameOver_rect.x = 0;
    gameOver_rect.y = 0;
    gameOver_rect.h = SCREEN_HEIGHT;
    gameOver_rect.w = SCREEN_WIDTH;

    SDL_Texture* food_img = IMG_LoadTexture( renderer, "img/pickup.png");
    SDL_Rect food_rect;
    food_rect.h = step;
    food_rect.w = step;
    food.newPoint();

    SDL_Texture* snake_body = IMG_LoadTexture( renderer, "img/snake_body.png");
    SDL_Rect body_rect;
    body_rect.h = step;
    body_rect.w = step;

    SDL_Texture* snake_head = IMG_LoadTexture( renderer, "img/snake_head.png");
    SDL_Rect ran_rect;
    ran_rect.h = step;
    ran_rect.w = step;

    // vẽ menu
    Mix_PlayMusic(sound_menu, -1);
    SDL_RenderCopy ( renderer, menu, NULL, &menu_rect);
    SDL_RenderPresent( renderer );
    waitUntilKeyPressed(window, renderer);

    SDL_Event e;
    int tmp=0,n=-1;

    Mix_PlayMusic(sound_bg, -1);
    while (true){
        snake.move();
        if(!snake.checkDie()){
            Mix_PlayMusic(sound_menu, -1);
            Mix_PlayChannel(-1,sound_lost,0) ;
            SDL_RenderCopy ( renderer, gameOver, NULL, &gameOver_rect);
            SDL_RenderPresent( renderer );
            waitUntilKeyPressed(window, renderer);
            quitSDL(window, renderer);
        }

        SDL_RenderCopy ( renderer, background, NULL, &background_rect);

        ran_rect.x = snake.getX();
        ran_rect.y = snake.getY();
        food_rect.x = food.getX();
        food_rect.y = food.getY();

        vector<vector<int>> arr = snake.getPoint();
        if(n < snake.getSize()) n++;
        for(int i=arr.size()-2;i>=arr.size()-1-n;i--){
            body_rect.x = arr[i][0];
            body_rect.y = arr[i][1];
            if(ran_rect.x == body_rect.x && ran_rect.y == body_rect.y){
                Mix_PlayMusic(sound_menu, -1);
                Mix_PlayChannel(-1,sound_lost,0) ;
                SDL_RenderCopy ( renderer, gameOver, NULL, &gameOver_rect);
                SDL_RenderPresent( renderer );
                waitUntilKeyPressed(window, renderer);
                quitSDL(window, renderer);
            }
            SDL_RenderCopy ( renderer, snake_body, NULL, &body_rect);
        }

        SDL_RenderCopy ( renderer, food_img, NULL, &food_rect);
        SDL_RenderCopy ( renderer, snake_head, NULL, &ran_rect);
        SDL_RenderPresent( renderer );
        SDL_RenderClear( renderer );

        if(snake.getSize() < 10){
            SDL_Delay(180);
        }else if(snake.getSize() < 20){
            SDL_Delay(140);
        }else if(snake.getSize() < 100){
            SDL_Delay(80);
        }

        if(snake.eat(food)){
            Mix_PlayChannel(-1,sound_eat,0) ;
            food.newPoint();
        }
        while( SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quitSDL(window, renderer);
            }
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_w:
                    {
                        if(tmp==0){
                            snake.turnUp();
                            tmp=1;
                        }
                        break;
                    }
                    case SDLK_s:
                    {
                        if(tmp==0){
                            snake.turnDown();
                            tmp=1;
                        }
                        break;
                    }
                    case SDLK_a:
                    {
                        if(tmp==1){
                            snake.turnLeft();
                            tmp=0;
                        }
                        break;
                    }
                    case SDLK_d:
                    {
                        if(tmp==1){
                            snake.turnRight();
                            tmp=0;
                        }
                        break;
                    }
                    default: break;
                }
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}

