#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "engine.hpp"
#include "vector2d.hpp"
#include "transform.hpp"

using namespace std;

int main()
{
    al_init();

    Engine * en = Engine::getInstance();
    Vector2D down = Vector2D::DOWN;
    Vector2D x = down * 2.44413453453453453453452312312L;
    cout << x.toString() << endl;

    ALLEGRO_DISPLAY * display = NULL;
    al_install_keyboard();
    al_init_primitives_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    Transform t = Transform(Vector2D(100, 100), Vector2D(5, 5));
    Transform t2 = Transform(Vector2D(200, 150), Vector2D(125, 70));
    display = al_create_display(640, 480);
    while(true) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_rectangle(
            t.getLeftUp().getX(),
            t.getLeftUp().getY(),
            t.getRightDown().getX(),
            t.getRightDown().getY(),
            al_map_rgb(0, 0, 255),
            1
        );
        al_draw_rectangle(
            t2.getLeftUp().getX(),
            t2.getLeftUp().getY(),
            t2.getRightDown().getX(),
            t2.getRightDown().getY(),
            al_map_rgb(255, 0, 0),
            1
        );
        al_draw_line(
            0, 0, 
            t.getLeftUp().getX(),
            t.getLeftUp().getY(),
            al_map_rgb(150, 0, 0),
            1
        );
        al_draw_line(
            t.getLeftUp().getX(),
            t.getLeftUp().getY(),
            t.getRightDown().getX(),
            t.getRightDown().getY(),
            al_map_rgb(75, 0, 0),
            1
        );
        al_flip_display();
        al_get_keyboard_state(&keyboard);
        if(al_key_down(&keyboard, ALLEGRO_KEY_W)) {
            Vector2D mov = Vector2D::UP;
            mov = mov * 0.01;
            t = t + mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_S)) {
            Vector2D mov = Vector2D::DOWN;
            mov = mov * 0.01;
            t = t + mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_D)) {
            Vector2D mov = Vector2D::RIGHT;
            mov = mov * 0.01;
            t = t + mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_A)) {
            Vector2D mov = Vector2D::LEFT;
            mov = mov * 0.01;
            t = t + mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_Q)) {
            Vector2D mov = Vector2D(1, 0);
            mov = mov * 0.01;
            t = t * mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_Z)) {
            Vector2D mov = Vector2D(-1, 0);
            mov = mov * 0.01;
            t = t * mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_E)) {
            Vector2D mov = Vector2D(0, 1);
            mov = mov * 0.01;
            t = t * mov;
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_C)) {
            Vector2D mov = Vector2D(0, -1);
            mov = mov * 0.01;
            t = t * mov;
        }
    }
    al_destroy_display( display );
    return 0;
}
