#ifndef InputInclude
#define InputInclude
#include "Button.hpp"

class InputField{
    private:
        string text = "";
        int startX = 5;
        int startY;
        int time = 0;
        static const int fontWidth = 8;
        Point pos;
        double width;
        double height;
        ALLEGRO_COLOR tcolor = al_map_rgb(255, 255, 255);
        ALLEGRO_COLOR bgcolor = al_map_rgb(22, 36, 45);
        ALLEGRO_COLOR borderColor = al_map_rgb(162, 162, 162);
        ALLEGRO_COLOR refcolor = bgcolor;
        ALLEGRO_FONT* font = nullptr;
        double error_length = fps;
        double error_frame = 0;
    public:
        bool error = false;
        bool typing = false;
        InputField(Point pos_, double width_, double height_);
        void draw_update();
        virtual ~InputField();
        void set_text(const string& new_text) { text = new_text; }
        const string& get_text() const { return text; }
        Point get_pos() const { return pos; }
        double get_width() const { return width; }
        double get_height() const { return height; }
        int get_fontWidth() const { return fontWidth; };
        int get_startX() const { return startX; }
};

#endif