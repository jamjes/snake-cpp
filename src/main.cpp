#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>

using namespace std;

Color green = Color{173, 204, 96, 255};
Color darkGreen = Color{43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();

    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

class Snake 
{
    public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction = Vector2{1,0};

    void Draw()
    {
        for(unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, .5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }

};

class Food 
{
    public:
        Vector2 position;
        Texture2D texture;

        Food()
        {
            position = GenerateRandomPos();
            Image image = LoadImage("img/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
        }
        
        void Draw()
        {
            DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        }

        Vector2 GenerateRandomPos()
        {
            float x = GetRandomValue(0, cellCount - 1);
            float y = GetRandomValue(0, cellCount - 1);
            return Vector2{x,y};
        }

        ~Food()
        {
            UnloadTexture(texture);
        }
};

class Game
{
    public:
    Snake snake = Snake{};
    Food food = Food{};

    void Draw()
    {
        snake.Draw();
        food.Draw();
    }

    void Update()
    {
        snake.Update();
    }
};

int main() 
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    Game game = Game{};

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (EventTriggered(.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = Vector2{0,-1};
        }

        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = Vector2{0,1};
        }

        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = Vector2{1,0};
        }

        if (IsKeyPressed(KEY_LEFT)  && game.snake.direction.x != 1)
        {
            game.snake.direction = Vector2{-1,0};
        }

        ClearBackground(green);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}