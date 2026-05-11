#include "ParameterBox.hpp"

using namespace std;

ALLEGRO_EVENT_QUEUE* queue = nullptr;

Parameters::Parameters(){
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    float risksize = 65;
    int spacing = 5;
    ALLEGRO_COLOR bgcolor = al_map_rgb(22, 36, 45);
    ALLEGRO_COLOR oncolor = al_map_rgb(58, 81, 107);
    playB = make_unique<Button>("Lose money:)", Point{(float)WIDTH/11, HEIGHT/2+spacing*6+risksize/2}, risksize*3+spacing*2, risksize/1.5, al_map_rgb(255, 255, 255), al_map_rgb(20, 117, 224), bgcolor, bgcolor);
    dropdownRows = make_unique<DropdownMenu>(WIDTH/11, HEIGHT/2-risksize/2+spacing*2, risksize*3+spacing*2, risksize/2, vector<string>{"8","9","10","11","12","13","14", "15", "16"}, DropdownMenu::default_colors());
    dropdownBCount = make_unique<DropdownMenu>(WIDTH/11, HEIGHT/2-risksize/2+spacing*2+risksize/2+spacing*2, risksize*3+spacing*2, risksize/2, vector<string>{"1","2","3","4", "5"}, DropdownMenu::default_colors());
    betInput = make_unique<InputField>(Point{(float)WIDTH/11, HEIGHT/2-risksize*1.5-spacing*2-risksize/2}, risksize*3+spacing*2, risksize/2);
    riskLevels.push_back(std::move(make_unique<Button>("low", Point{(float)WIDTH/11, HEIGHT/2-risksize*1.5}, risksize, risksize, al_map_rgb(255, 255, 255), bgcolor, oncolor, bgcolor, true)));
    riskLevels.push_back(std::move(make_unique<Button>("medium", Point{(float)WIDTH/11+risksize+spacing, HEIGHT/2-risksize*1.5}, risksize, risksize, al_map_rgb(255, 255, 255), bgcolor, oncolor, bgcolor)));
    riskLevels.push_back(std::move(make_unique<Button>("high", Point{(float)WIDTH/11+risksize*2+spacing*2, HEIGHT/2-risksize*1.5}, risksize, risksize, al_map_rgb(255, 255, 255), bgcolor, oncolor, bgcolor)));
}

void Parameters::event_update(int ball_count){
    ALLEGRO_EVENT ev;
    
    while (al_get_next_event(queue, &ev)){
        switch (ev.type){
            case ALLEGRO_EVENT_MOUSE_AXES:
                for (size_t i = 0; i < riskLevels.size(); i++) {
                    if (ev.mouse.x >= riskLevels[i]->get_pos().x && ev.mouse.x <= riskLevels[i]->get_pos().x + riskLevels[i]->get_width() && ev.mouse.y >= riskLevels[i]->get_pos().y && ev.mouse.y <= riskLevels[i]->get_pos().y + riskLevels[i]->get_height()){
                        riskLevels[i]->hover = true;
                    } else{
                        riskLevels[i]->hover = false;
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (!dropdownRows->is_open() && !dropdownBCount->is_open() && ev.mouse.x >= playB->get_pos().x && ev.mouse.x <= playB->get_pos().x + playB->get_width() && ev.mouse.y >= playB->get_pos().y && ev.mouse.y <= playB->get_pos().y + playB->get_height()){
                    playB->hit = true;
                }
                if (ev.mouse.x >= betInput->get_pos().x && ev.mouse.x <= betInput->get_pos().x + betInput->get_width() && ev.mouse.y >= betInput->get_pos().y && ev.mouse.y <= betInput->get_pos().y + betInput->get_height()) {
                    betInput->typing = true;
                } else{
                    betInput->typing = false;
                }
                if (ball_count == 0){
                    for (size_t i = 0; i < riskLevels.size(); i++) {
                        bool isHit = (ev.mouse.x >= riskLevels[i]->get_pos().x && 
                        ev.mouse.x <= riskLevels[i]->get_pos().x + riskLevels[i]->get_width() && 
                        ev.mouse.y >= riskLevels[i]->get_pos().y && 
                        ev.mouse.y <= riskLevels[i]->get_pos().y + riskLevels[i]->get_height());
                        if (isHit) {
                            selectedRisk = riskLevels[i]->get_text();
                            for (auto& btn : riskLevels) btn->hit = false;
                            riskLevels[i]->hit = true;
                            break;
                        }
                    }
                }
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (betInput->typing){
                    int keycode = ev.keyboard.keycode;
                    int unichar = ev.keyboard.unichar;
                    bool less_than_2_decimals = betInput->get_text().find('.') == string::npos || betInput->get_text().size() - betInput->get_text().find('.') <= 2;
                    if ((betInput->get_text().size()*betInput->get_fontWidth() < betInput->get_width() - betInput->get_startX() - betInput->get_fontWidth()*2) && less_than_2_decimals && (unichar >= '0' && unichar <= '9') || unichar == '.') {
                        if (unichar == '.' && betInput->get_text().find('.') != string::npos) break;
                        betInput->set_text(betInput->get_text() + (char)unichar);
                    } else if (keycode == ALLEGRO_KEY_BACKSPACE && !betInput->get_text().empty()) {
                        betInput->set_text(betInput->get_text().substr(0, betInput->get_text().size()-1));
                    }
                }
                break;
        }
        dropdownRows->handle_event(ev);
        dropdownBCount->handle_event(ev);
    }
}

void Parameters::draw_update(){
    if (!font) font = al_create_builtin_font();
    al_draw_filled_rectangle(0, 0, WIDTH/3, HEIGHT, bgcolor);
    al_draw_filled_rounded_rectangle(WIDTH/3/8, HEIGHT/8, WIDTH/3/8*7, HEIGHT/8*7, 10, 10, bg_param_color);
    for (size_t i = 0; i < riskLevels.size(); i++) {
        riskLevels[i]->draw_update();
    }
    playB->draw_update();
    dropdownBCount->draw();
    dropdownRows->draw();
    betInput->draw_update();
}

Parameters::~Parameters(){
    if (font) al_destroy_font(font);
}