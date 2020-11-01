#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "core/engine/engine.hpp"
#include "core/vector2d/vector2d.hpp"
#include "core/transform/transform.hpp"

using namespace std;

int main()
{ 
	Engine * en = Engine::getInstance();
	en->init();
	en->start();
	en->stop();
    return 0;
}
