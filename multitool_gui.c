#include <raylib.h>
#include <math.h>
#include <windows.h>
bool is_windows() {
    #ifdef _WIN32
        return true;
    #else
        return false;
    #endif
}

int calculate_centered_text_x()
{
    return (GetScreenWidth() / 2) - (image->width / 2);
}
int calculate_centered_image_y(Texture *image)
{
    return (GetScreenHeight() / 2) - (image->height / 2);
}
int calculate_centered_image_x(Texture *image)
{
    return (GetScreenWidth() / 2) - (image->width / 2);
}
int calculate_centered_image_y(Texture *image)
{
    return (GetScreenHeight() / 2) - (image->height / 2);
}
void render_loading_screen(Texture *logo_image)
{
    static float rotation = 0.0f;
    static float angle = 0.0f;
    DrawTexture(*logo_image,
                calculate_centered_image_x(logo_image),
                calculate_centered_image_y(logo_image),
                ColorAlpha(WHITE, (sinf(GetTime()) / 2) + 0.5f));
    angle += 0.05f; // Velocidade de "carregamento"

    // Draw spinner track
    DrawRing(
        // Center
        (Vector2){GetScreenWidth() / 2, (GetScreenHeight() / 10) * 8},
        // Inner radius and outer radius of the ring
        10, 15,
        // Start angle and end angle of the ring
        0 + *angle, 300 + *angle,
        // Segments
        100,
        // Color
        LIGHTGRAY);
    // Draw spinner thingy
    DrawRing(
        // Center
        (Vector2){GetScreenWidth() / 2, (GetScreenHeight() / 10) * 8},
        // Inner radius and outer radius of the ring
        10, 15,
        // Start angle and end angle of the ring
        300 + *angle, 360 + *angle,
        // Segments
        100,
        // Color
        BLACK);
}
typedef enum {
    LOADING,
    MENU,
} State;
void render_menu_screen() {
    DrawRectangle(posx, posy, width, height, DARKBLUE);
    DrawText("Ferramentas de limpeza", 0, 0, 20, LIGHTGRAY);

    DrawRectangle(posX, posY, width, height, DARKBLUE);
    DrawText("Ferramentas de optimização", 0, 0, 20, LIGHTGRAY);

    DrawRectangle(posX, posY, width, height, DARKBLUE);
    DrawText("Ver Informações de sistema", 0, 0, 20, LIGHTGRAY);

    DrawRectangle(posX, posY, width, height, DARKBLUE);
    DrawText("Ver configurações de ip", 0, 0, 20, LIGHTGRAY);

    DrawRectangle(posX, posY, width, height, DARKBLUE);
    DrawText("Sair", 0, 0, 20, LIGHTGRAY);
}
int main()
{
    if(!is_windows()) {
        printf("Este programa só funciona no Windows!\n");
        return 1;
    }
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(0, 0, "Multitool do Windows");
    SetWindowState(FLAG_FULLSCREEN_MODE);
    Texture image = LoadTexture("../assets/logo.png");
    SetTextureFilter(image, TEXTURE_FILTER_TRILINEAR);
    State state = LOADING;
    double start_time = GetTime();
    while (!WindowShouldClose())
    {
        if(start_time - GetTime() > 2.0f)
            state = MENU;
        BeginDrawing();
        ClearBackground(BLACK);
        if(state == LOADING)
            render_loading_screen(&image);
        if(state == MENU)
            render_menu_screen();

        EndDrawing();
    }
    CloseWindow();
}