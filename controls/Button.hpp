#ifndef IncludeButton
#define IncludeButton
#include "../generator.hpp"

class Button {
    private:
        string text;
        Point pos;
        double width;
        double height;
        ALLEGRO_COLOR tcolor;
        ALLEGRO_COLOR bgcolor;
        ALLEGRO_COLOR onColor;
        ALLEGRO_COLOR hover_color;
        ALLEGRO_FONT* font = nullptr;
    public:
        bool hit = false;
        bool hover = false;
        Button(string text_, Point pos_, double width_, double height_, ALLEGRO_COLOR tcolor_, ALLEGRO_COLOR bgcolor_, ALLEGRO_COLOR onColor_, ALLEGRO_COLOR hover_color_, bool hit_ = false);
        void draw_update();
        virtual ~Button();
        string get_text() const { return text; }
        Point get_pos() const { return pos; }
        double get_width() const { return width; }
        double get_height() const { return height; }
};

#endif