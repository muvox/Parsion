#include <iostream>
#include <SDL.h>
#include <cmath>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace muvoksi;


int main(int argc, char *argv[]) {

    srand(time(NULL));

    Screen screen; //initialize screen with the constructor;

    if (!screen.init()) {
        cout << "Error initialising SDL." << endl;
    }

    Swarm swarm;

    //While loop to keep application running against quit boolean.
    while (true) {

        //Update particles
        //Draw particles

        int elapsed = SDL_GetTicks();

        swarm.update(elapsed);

        unsigned char green = (1 + cos(elapsed * 0.001)) * 128;

        unsigned char red = (1 + sin(elapsed * 0.002)) * 128;

        unsigned char blue = (1 + sin(elapsed * 0.003)) * 128;

/*
        unsigned char qgreen = (1 + sin(elapsed * 0.02)) * 128;
        unsigned char qred = (1 + sin(elapsed * 0.01)) * 128;
        unsigned char qblue = (1 + sin(elapsed * 0.04)) * 128;
        screen.setSquare(100, 100, 350, 250, qgreen, qred, qblue); //My first self made function in this whole mess!!1111
*/
        const Particle *const pParticles = swarm.getParticles();

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH / 2);
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT/2;

            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        screen.update();


        //Check for messages/events
        if (!screen.processEvents()) {
            break;
        }

    }

    screen.close();
    return 0;
}


