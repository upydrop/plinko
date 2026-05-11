#include <windows.h>
#include "field/LastWins.hpp"
#include <iostream>
#include <chrono>

using namespace std;

class Screen: public Engine {
    private:
        vector<unique_ptr<Circle>> balls = {};
        vector<unique_ptr<Circle>> pegs = {};
        string risk;
        LastWinController lastWinsC;
        vector<unique_ptr<WinBox>> win_boxes = {};
        ALLEGRO_FONT *m_font = nullptr;
        ALLEGRO_COLOR m_tcolor = al_map_rgb(255, 255, 255);
        Parameters params;
        int rows;
        double money_amount = 100000;
        string moneyT = "100000$";
        double xStart;
        double yStart;
    public:
        Screen(std::string risk_="low"){
            rows = 8;
            win_boxes=create_win_boxes(rows, risk_);
            pegs = create_field(rows);
            risk = risk_;
        }
        void add_ball(unique_ptr<Circle> obj) { balls.push_back(std::move(obj)); }
        void physics_process() override {
            params.event_update(balls.size());
            if (rows != stoi(params.get_dropdownRows()->selected_item()) && balls.size() == 0){
                rows = stoi(params.get_dropdownRows()->selected_item());
                pegs = create_field(rows);
                win_boxes = create_win_boxes(rows, risk);
            }
            if (params.get_selectedRisk() != risk && balls.size() == 0){
                risk = params.get_selectedRisk();
                win_boxes = create_win_boxes(rows, risk);
            }
            for (size_t i = 0; i < balls.size(); ++i) {
                Circle& ball = *balls[i];
                if (ball.get_pos().y >= HEIGHT || ball.get_pos().x <= 0 || ball.get_pos().x >=WIDTH){
                    balls.erase(balls.begin() + i);
                    i--;
                    continue;
                }
                for (size_t y = 0; y < pegs.size(); ++y) {
                    Circle& peg = *pegs[y];

                    float dx = ball.get_pos().x - peg.get_pos().x;
                    float dy = ball.get_pos().y - peg.get_pos().y;
                    float dist = sqrt(dx*dx + dy*dy); //расстояние между центрами шаров

                    if (dist < ball.get_r() + peg.get_r()) {
                        //значения х и у вектора нормали
                        float nx = dx / dist;
                        float ny = dy / dist;

                        //интенсивность отражения скорости в сторону нормали
                        float dot = ball.v.x * nx + ball.v.y * ny;

                        // отражение
                        if (dot < 0) {
                            ball.v = Point{ball.v.x - (1 + restitution) * dot * nx, ball.v.y - (1 + restitution) * dot * ny};
                        }
                        
                        //rand
                        ball.v.x += (rand() / (double)RAND_MAX - 0.5) * 0.5;
                        ball.v.y += (rand() / (double)RAND_MAX - 0.5) * 0.5;

                        // выталкивание из штыря
                        float overlap = ball.get_r() + peg.get_r() - dist;
                        ball.set_pos(Point{ball.get_pos().x + nx * overlap, ball.get_pos().y + ny * overlap});
                        ball.set_pos(Point{ball.get_pos().x, ball.get_pos().y + ny * overlap});
                    }
                }
                for (size_t y = 0; y < win_boxes.size(); ++y) {
                    WinBox& wb = *win_boxes[y];
                    if (ball.get_pos().x >= wb.get_pos().x && ball.get_pos().x <= wb.get_pos().x + wb.get_width() && ball.get_pos().y >= wb.get_pos().y){
                        std::cout<<wb.get_multi()<<endl;
                        money_amount += ball.get_bet_amount()*wb.get_multi();
                        moneyT = std::to_string(money_amount).substr(0, std::to_string(money_amount).find('.') + 3) + std::string("$");
                        balls.erase(balls.begin() + i);
                        i--;
                        wb.hit = true;
                        lastWinsC.add_win(make_unique<LastWin>(to_string(wb.get_multi()).substr(0, to_string(wb.get_multi()).find('.') + 3), to_string(ball.get_bet_amount()*wb.get_multi()).substr(0, to_string(ball.get_bet_amount()*wb.get_multi()).find('.') + 3), wb.get_refcolor()));
                        break;
                    };
                }
                ball.fps_update();
            }
            if (params.get_playB()->hit == true){
                params.get_playB()->hit = false;
                try {
                    double value = std::stod(params.get_betInput()->get_text());
                    int b_amount = std::stod(params.get_dropdownBCount()->selected_item());
                    if (value*b_amount <= money_amount){
                        money_amount -= b_amount*value;
                        moneyT = std::to_string(money_amount).substr(0, std::to_string(money_amount).find('.') + 3) + std::string("$");
                        for (int i = 0; i < b_amount; ++i){
                            add_ball(make_unique<Circle>(fCircleR, Point{WIDTH*2/3 + ((double)rand()/RAND_MAX - 0.5) * pegSpacing, HEIGHT/2 - (rows*pegSpacing)/2-fCircleR*5}, value)); //for testing
                        }
                    } else {
                        cout<<"Not enough money!"<<endl;
                        params.get_betInput()->error = true;
                    }
                } catch (const std::invalid_argument&) {
                    cout<<"Invalid input: not a number"<<endl;
                    params.get_betInput()->error = true;
                } catch (const std::out_of_range&) {
                    cout<<"Invalid input: number out of range"<<endl;
                    params.get_betInput()->error = true;
                }
            }
        };
        void render_process() override {
            al_clear_to_color(al_map_rgb(30,34,47));
            for (size_t y = 0; y < balls.size(); y++) {
                balls[y]->draw_update(252, 252, 251);
            };
            for (size_t i = 0; i < pegs.size(); i++) {
                pegs[i]->draw_update(251, 31, 59);
            };
            for (size_t i = 0; i < win_boxes.size(); i++) {
                win_boxes[i]->draw_update();
            };
            params.draw_update();
            if (!m_font) m_font = al_create_builtin_font();
            al_draw_text(m_font, m_tcolor, 
                100, 50, 
                ALLEGRO_ALIGN_LEFT, moneyT.c_str());
            lastWinsC.draw_update();
        };
        ~Screen(){
            if (m_font) al_destroy_font(m_font);
        }
};

int main()
{
    srand(time(0));

    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();

    int rows = 8;
    Screen screen = Screen();
    double startX = WIDTH*2/3 + ((double)rand()/RAND_MAX - 0.5) * pegSpacing -2;
    screen.add_ball(make_unique<Circle>(fCircleR, Point{startX, HEIGHT/2 - (rows*pegSpacing)/2-fCircleR*5}, 100));
    try {
        screen.start();
    } catch (char const *error) {
        cout << error << endl;
    };
    return 0;
}

