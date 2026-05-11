#ifndef IncludeCircle
#define IncludeCircle
#include "../consts.hpp"

class Circle{
    private:
        double r;
        Point pos;
        double bet_amount;
    public:
        Point v;
        virtual ~Circle()=default;
        Circle(double r_, Point pos_, double bet_amount_);
        Point get_pos() const { return pos; }
        double get_r() const { return r; }
        double get_bet_amount() const { return bet_amount; }

        void set_pos(Point new_pos) { pos = new_pos; }

        void fps_update();
        void draw_update(int r_, int g_, int b);
};

#endif