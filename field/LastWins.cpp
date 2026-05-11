#include "LastWins.hpp"

LastWin::LastWin(string multi_, string win_, ALLEGRO_COLOR bgcolor_) {
    multi = multi_;
    win = win_;
    bgcolor = bgcolor_;
}


void LastWin::draw_update(ALLEGRO_FONT* font, Point pos) const {
    al_draw_filled_rounded_rectangle(pos.x, pos.y,
                             pos.x + width, pos.y + height,
                             10, 10, bgcolor);

    al_draw_rounded_rectangle(pos.x, pos.y,
                      pos.x + width, pos.y + height,
                      10, 10, bgcolor, 1.0f);

    if (font){
        string text = multi + "x";
        string text2 = win + "$";
        int text_h = al_get_font_line_height(font);
        float text_y = pos.y + (height - static_cast<float>(text_h)) * 0.5f;
        al_draw_text(font, tcolor,
                     pos.x + width/2, pos.y+height/2-text_h/2-2,
                     ALLEGRO_ALIGN_CENTER, text.c_str());
        al_draw_text(font, tcolor,
                     pos.x + width/2, pos.y+height/2 + text_h/2+2,
                     ALLEGRO_ALIGN_CENTER, text2.c_str());
    }
}


LastWinController::LastWinController() {}

void LastWinController::add_win(unique_ptr<LastWin> lWin) {
    printf("wins count: %zu\n", wins.size());
    wins.insert(wins.begin(), std::move(lWin));
    if (wins.size() > max_wins)
        wins.pop_back();
}

void LastWinController::draw_update() const {
    if (!font) font = al_create_builtin_font();
    al_draw_rounded_rectangle(pos.x, pos.y,
                      pos.x + width, pos.y + height,
                      10, 10, border_color, 2.0f);
    al_draw_filled_rounded_rectangle(pos.x, pos.y,
                             pos.x + width, pos.y + height,
                             10, 10, bgcolor);
    for (int i = 0; i < wins.size(); ++i) {
        float y = pos.y + 1 + i * wins[i]->get_height();
        if (y >= pos.y + height) break;   
        wins[i]->draw_update(font, Point{pos.x+1, y}); 
    }
}

LastWinController::~LastWinController() {
    if (font) al_destroy_font(font);
}