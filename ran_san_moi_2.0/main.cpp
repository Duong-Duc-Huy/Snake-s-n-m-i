#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int buoc = 25;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake";

class Food{
private:
    int x;
    int y;
public:
    food(){
        x = ramdomPointX();
        y = ramdomPointY();
    }
    int ramdomPointX(){
        return (rand() % (SCREEN_WIDTH/buoc))*buoc;
    }
    int ramdomPointY(){
        return (rand() % (SCREEN_HEIGHT/buoc))*buoc;
    }
    void newPoint(){
        x = ramdomPointX();
        y = ramdomPointY();
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
};

class Snake{
private:
    int x;
    int y;
    int size_snake;
    int stepX,stepY;
    vector<vector<int>> point;
public:
    Snake(){
        x = 0;
        y = 100;
        size_snake = 3;
        stepX = buoc;
        stepY = 0;
        point = { {0,100} };
    }
    vector<vector<int>> getPoint(){
        return point;
    }
    int getSize(){
        return size_snake;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void turnUp(){
        stepX = 0;
        stepY = - buoc;
    }
    void turnDown(){
        stepX = 0;
        stepY = buoc;
    }
    void turnLeft(){
        stepX = - buoc;
        stepY = 0;
    }
    void turnRight(){
        stepX = buoc;
        stepY = 0;
    }
    void move(){
        x += stepX;
        y += stepY;
        vector<int> temp { x , y };
        point.push_back(temp);
    }
    bool checkDie(){
        if (x >= SCREEN_WIDTH || x < 0 || y >=SCREEN_HEIGHT || y < 0){
            return false;
        }
        return true;
    }
    bool eat(Food foodSnake){
        if (foodSnake.getX() == x && foodSnake.getY() == y){
            size_snake++;
            return true;
        }
        return false;
    }
};

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Snake snake;
    Food food;

    SDL_Texture * background=IMG_LoadTexture( renderer, "background.jpg");
    SDL_Rect background_rect;
    background_rect.x=0;
    background_rect.y=0;
    background_rect.h = 600;
    background_rect.w = 800;

    SDL_Texture* food_img = IMG_LoadTexture( renderer, "pickup.png");
    SDL_Rect food_rect;
    food_rect.h = buoc;
    food_rect.w = buoc;
    food.newPoint();

    SDL_Texture* snake_body = IMG_LoadTexture( renderer, "snake_body.png");
    SDL_Rect body_rect;
    body_rect.h = buoc;
    body_rect.w = buoc;

    SDL_Texture* snake_head = IMG_LoadTexture( renderer, "snake_head.png");
    SDL_Rect ran_rect;
    ran_rect.h = buoc;
    ran_rect.w = buoc;

    SDL_Event e;
    int tmp=0,n=-1;
    while (true) {
//      draw background
        SDL_RenderCopy ( renderer, background, NULL, &background_rect);

        snake.move();

        ran_rect.x = snake.getX();
        ran_rect.y = snake.getY();
        food_rect.x = food.getX();
        food_rect.y = food.getY();

        vector<vector<int>> arr = snake.getPoint();
        if(n < snake.getSize()) n++;
        for(int i=arr.size()-2;i>=arr.size()-1-n;i--){
            body_rect.x = arr[i][0];
            body_rect.y = arr[i][1];
            if(ran_rect.x == body_rect.x && ran_rect.y == body_rect.y) quitSDL(window, renderer);
            SDL_RenderCopy ( renderer, snake_body, NULL, &body_rect);
        }

        SDL_RenderCopy ( renderer, food_img, NULL, &food_rect);
        SDL_RenderCopy ( renderer, snake_head, NULL, &ran_rect);
        SDL_RenderPresent( renderer );
        SDL_RenderClear( renderer );
        SDL_Delay(250);

        if(snake.eat(food)){
            food.newPoint();
        }

        if( SDL_PollEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT || !snake.checkDie()) break;
        if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_w:
                {
                    if(tmp==0){
                        snake.turnUp();
                        tmp=1;
                        break;
                    }else{
                        break;
                    }
                }
                case SDLK_s:
                {
                    if(tmp==0){
                        snake.turnDown();
                        tmp=1;
                        break;
                    }else{
                        break;
                    }
                }
                case SDLK_a:
                {
                    if(tmp==1){
                        snake.turnLeft();
                        tmp=0;
                        break;
                    }else{
                        break;
                    }
                }
                case SDLK_d:
                {
                    if(tmp==1){
                        snake.turnRight();
                        tmp=0;
                        break;
                    }else{
                        break;
                    }
                }
                default: break;
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

