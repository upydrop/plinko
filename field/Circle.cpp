#include "Circle.hpp"

Circle::Circle(double r_, Point pos_, double bet_amount_): r(r_), pos(pos_), bet_amount(bet_amount_){
    v.x=0;
    v.y=0;
};
void Circle::fps_update(){
    v.y += g * dt;
    pos.x += v.x * dt;
    pos.y += v.y * dt;
};
void Circle::draw_update(int r_, int g_, int b){
    al_draw_filled_circle(pos.x, pos.y, r, al_map_rgb(r_, g_, b));
};