#include <iostream>
#include <raylib.h>

using namespace std;

Color green = Color{173, 204, 96, 255};
Color darkGreen = Color{43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

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

int main() 
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    Food apple = Food();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);

        apple.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}