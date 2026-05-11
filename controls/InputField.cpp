#include "InputField.hpp"

using namespace std;

InputField::InputField(Point pos_, double width_, double height_): pos(pos_), width(width_), height(height_){}

void InputField::draw_update(){
    if (!font) {
        font = al_create_builtin_font();
        startY = (height-al_get_font_line_height(font))/2;
    };
    if (error){
        float r, g, b;
        al_unmap_rgb_f(refcolor, &r, &g, &b);
        float t = (float)error_frame / error_length;
        r = 1 - (1.0f - r) * t;
        g = g * t;
        b = b * t;
        bgcolor = al_map_rgb_f(r, g, b);
        error_frame++;
        if (error_frame >= error_length) {
            error_frame = 0;
            error = false;
        }
    }
    al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, bgcolor);
    al_draw_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, borderColor, 1);
    if (typing){
        if (time/fps <= 0.5){
            double x = pos.x+startX+text.size()*fontWidth;
            al_draw_line(x, pos.y+startY-5, x, pos.y+startY+al_get_font_line_height(font)+5, al_map_rgb(255, 255, 255), 2);
        } else if (time/fps >= 1){
            time = 0;
        }
        time++;
    }
    string dollar_sign = "$";
    al_draw_text(font, tcolor, 
        pos.x+startX, pos.y+startY, 
        ALLEGRO_ALIGN_LEFT, text.c_str());
    al_draw_text(font, tcolor, 
        pos.x+width-startX-fontWidth, pos.y+startY, 
        ALLEGRO_ALIGN_LEFT, dollar_sign.c_str());
}

InputField::~InputField(){ if (font) al_destroy_font(font); }