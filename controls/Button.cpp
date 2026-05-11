#include "Button.hpp"

using namespace std;

Button::Button(string text_, Point pos_, double width_, double height_, ALLEGRO_COLOR tcolor_, ALLEGRO_COLOR bgcolor_, ALLEGRO_COLOR onColor_, ALLEGRO_COLOR hover_color_, bool hit_): 
            text(text_), pos(pos_), width(width_), height(height_), tcolor(tcolor_), bgcolor(bgcolor_), onColor(onColor_), hover_color(hover_color_), hit(hit_){};

void Button::draw_update(){
    if (!font) font = al_create_builtin_font();
    if (hit){
        al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, onColor);
    } else if (hover){
        al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, hover_color);
    }
    else{
        al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, bgcolor);
    }
    al_draw_text(font, tcolor, 
        (pos.x+pos.x+width)/2, (pos.y+pos.y+height)/2 - al_get_font_line_height(font)/2, 
        ALLEGRO_ALIGN_CENTRE, text.c_str());
}

Button::~Button(){ if (font) al_destroy_font(font); }