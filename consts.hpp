#ifndef IncludeConsts
#define IncludeConsts

#include "engine.hpp"

struct Point{
    double x,y;
};

const int WIDTH = Engine::WIDTH;
const int HEIGHT = Engine::HEIGHT;
const double fps = Engine::FPS;

const double g = 1500;
const double dt = 1.0/fps;
const double restitution = 0.5; //упругость
const double pegSpacing = 47;//px
const double sCircleR = 7;
const double fCircleR = 10;

#endif