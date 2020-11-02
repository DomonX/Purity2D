#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "libs/engine.hpp"

using namespace std;

int main()
{ 
	Engine * en = Engine::getInstance();
	en->init();
	en->start();
	en->stop();
    return 0;
}
