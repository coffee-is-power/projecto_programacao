#include <raylib.h>
#include <raymath.h>
#include "menu_screen.h"
Vector2 text_center_position(const char *text, int font_size)
{
    return (Vector2){GetScreenWidth() / 2 - MeasureText(text, font_size) / 2, GetScreenHeight() / 2};
}
const int font_size = 20;
const char *menu_items[] = {
    "Ferramentas de limpeza",
    "Ferramentas de optimização",
    "Ver Informações de sistema",
    "Ver configurações de ip",
    "Sair do programa"};
#define menu_items_count sizeof(menu_items) / sizeof(menu_items[0])
const int item_padding = 2;
bool mouse_hover[menu_items_count] = {0};
void render_menu_screen(Sound *menu_hover_sound)
{
    // Draw menu items in the center
    for (int i = 0; i < menu_items_count; i++)
    {
        Vector2 position = text_center_position(menu_items[i], font_size);
        Rectangle button_bounding_box = (Rectangle){
            position.x-item_padding,
            ((GetScreenHeight() / 2) - ((menu_items_count / 2))) + (i * (font_size + (item_padding * 4)))-item_padding,
            MeasureText(menu_items[i], font_size) + (item_padding * 2),
            font_size + (item_padding * 2)
        };
        if (CheckCollisionPointRec(GetMousePosition(), button_bounding_box))
        {
            DrawRectangleRounded(button_bounding_box, 0.2f, 30, DARKBLUE);
            if (!mouse_hover[i])
            {
                SetSoundVolume(*menu_hover_sound, 1.0f);
                PlaySound(*menu_hover_sound);
                printf("mouse_hover[%d]: %s\n", i, mouse_hover[i] ? "true" : "false");
            }
            mouse_hover[i] = true;
        }
        else
        {
            mouse_hover[i] = false;
        }
        DrawText(
            menu_items[i], button_bounding_box.x+item_padding,
            button_bounding_box.y + item_padding,
            font_size, WHITE);
    }
}