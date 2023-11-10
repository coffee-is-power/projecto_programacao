#include <raylib.h>
#include <raymath.h>
#include "menu_screen.h"
Vector2 text_center_position(char *text, int font_size)
{
    return (Vector2){GetScreenWidth() / 2 - MeasureText(text, font_size) / 2, GetScreenHeight() / 2 - font_size / 2};
}
void render_menu_screen()
{
    const int font_size = 20;
    const char **menu_items = {
        "Ferramentas de limpeza", 
        "Ferramentas de optimização", 
        "Ver Informações de sistema", 
        "Ver configurações de ip", 
        "Sair"
    };
    const int menu_items_count = sizeof(menu_items) / sizeof(menu_items[0]);
    // Draw menu items in the center
    for (int i = 0; i < menu_items_count; i++)
    {
        Vector2 position = text_center_position(menu_items[i], font_size);
        DrawText(menu_items[i], position.x, position.y + (font_size * i), font_size, WHITE);
    }
}