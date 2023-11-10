#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
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
bool mouse_hover_on_last_frame[menu_items_count] = {0};
Sound menu_hover_sound = {0};
bool sound_is_loaded = false;
// Função para calcular o bounding box
Rectangle calculate_button_bounding_box(int index)
{
    Vector2 position = text_center_position(menu_items[index], font_size);
    return (Rectangle){
        position.x - item_padding,
        ((GetScreenHeight() / 2) - ((menu_items_count / 2))) + (index * (font_size + (item_padding * 4))) - item_padding,
        MeasureText(menu_items[index], font_size) + (item_padding * 2),
        font_size + (item_padding * 2)};
}

// Função de atualização
void update_menu_screen()
{
    if (!sound_is_loaded)
    {
        menu_hover_sound = LoadSound("assets/menu_hover_sound.wav");
        sound_is_loaded = true;
    }
    // Atualizar lógica de interação do mouse e sons, se necessário
    for (int i = 0; i < menu_items_count; i++)
    {
        Rectangle button_bounding_box = calculate_button_bounding_box(i);

        if (CheckCollisionPointRec(GetMousePosition(), button_bounding_box))
        {
            if (!mouse_hover_on_last_frame[i])
            {
                SetMasterVolume(1.0f);
                SetSoundVolume(menu_hover_sound, 1.0f);
                PlaySound(menu_hover_sound);
            }
            mouse_hover_on_last_frame[i] = true;
        }
        else
        {
            mouse_hover_on_last_frame[i] = false;
        }
    }
}

// Função de renderização
void render_menu_screen()
{
    // Desenhar menu items no centro
    for (int i = 0; i < menu_items_count; i++)
    {
        Rectangle button_bounding_box = calculate_button_bounding_box(i);

        if (CheckCollisionPointRec(GetMousePosition(), button_bounding_box))
        {
            DrawRectangleRounded(button_bounding_box, 0.2f, 30, DARKBLUE);
        }

        DrawText(
            menu_items[i], button_bounding_box.x + item_padding,
            button_bounding_box.y + item_padding,
            font_size, WHITE);
    }
}
