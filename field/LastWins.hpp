#ifndef IncludeLastWins
#define IncludeLastWins
#include "../controls/ParameterBox.hpp"

class LastWin{
    private:
        int width = 99;
        int height = 100;
        string multi;
        string win;
        ALLEGRO_COLOR bgcolor;
        ALLEGRO_COLOR tcolor = al_map_rgb(255, 255, 255);
    public:
        LastWin(string multi_, string win_, ALLEGRO_COLOR bgcolor);
        void draw_update(ALLEGRO_FONT* font, Point pos) const;
        int get_height() const { return height; }
};

class LastWinController{
    private:
        Point pos = {WIDTH*0.9, 30};
        vector<unique_ptr<LastWin>> wins;
        int width = 100;
        int height = 502;
        int max_wins = height/width;
        mutable ALLEGRO_FONT* font = nullptr;
        ALLEGRO_COLOR bgcolor = al_map_rgb(46, 46, 46);
        ALLEGRO_COLOR border_color = al_map_rgb(255, 255, 255);
    public:
        LastWinController();
        void draw_update() const;
        void add_win(unique_ptr<LastWin> lWin);
        Point get_pos() const { return pos; }
        virtual ~LastWinController();
};

#endif