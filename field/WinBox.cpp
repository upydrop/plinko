#include "WinBox.hpp"

WinBox::WinBox(Point pos_, float multi_, ALLEGRO_COLOR color_): pos(pos_), multi(multi_), bgcolor(color_), refcolor(color_){
    std::string s = std::to_string(multi);
    label = s.substr(0, s.find('.') + 2);
}
void WinBox::draw_update(){
    if (!font) font = al_create_builtin_font();
        if (hit){
            float r, g, b;
            al_unmap_rgb_f(refcolor, &r, &g, &b);
            float t = (float)frame / total_frames;
            r = 1 - (1.0f - r) * t;
            g = 1 - (1.0f - g) * t;
            b = 1 - (1.0f - b) * t;
            bgcolor = al_map_rgb_f(r, g, b);
            frame++;
            if (frame >= total_frames) {
                frame = 0;
                hit = false;
            }
        }
        al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x+width, pos.y+height, 10, 10, bgcolor);
        al_draw_text(font, tcolor, 
            (pos.x+pos.x+width)/2, (pos.y+pos.y+height)/2 - al_get_font_line_height(font)/2, 
            ALLEGRO_ALIGN_CENTRE, label.c_str());
};
WinBox::~WinBox(){
    if (font) {
        al_destroy_font(font);
    }
}