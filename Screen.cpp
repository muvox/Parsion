//
// Created by Master on 09/06/2019.
//
#include <iostream>
#include "Screen.h"

using namespace std;

namespace muvoksi {

    Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {

    }

    bool Screen::init() {


        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            string error = "Error Initializing";
            SDL_Log(error.c_str());
            SDL_Log(SDL_GetError());
            SDL_Quit();
            return false;
        }

        m_window = SDL_CreateWindow("Muvoksis Magical Splosions", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (m_window == NULL) {
            string error = "Error creating a m_window";
            SDL_Log(error.c_str());
            SDL_Log(SDL_GetError());
            SDL_Quit();
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                                      SCREEN_WIDTH, SCREEN_HEIGHT);
        if (m_renderer == NULL) {
            string error = "Could not create renderer";
            SDL_Log(error.c_str());
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;

        }

        if (m_texture == NULL) {
            string error = "Could not create texture";
            SDL_Log(error.c_str());
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;

        }

        m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        memset(m_buffer1, 0 , SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_buffer2, 0 , SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));



        return true;
    }

    bool Screen::processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return false;
        }
        return true;
    }

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

       if(x < 0 || x >= SCREEN_WIDTH || y < 0 ||y >= SCREEN_HEIGHT){
           return;
       }

        Uint32 color = 0;

        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        //R<-G<-B<-A!

        m_buffer1[(y * SCREEN_WIDTH) + x] = color;
    }

    //First function i've made myself. Draws width x height box starting from x and y 'coordinates' with rgb colors.
    void Screen::setSquare(int width, int height, int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        for (int i = 0; i <= width; i++) {
            for (int j = 0; j <= height; j++) {
                Uint32 color = 0;

                color += red;
                color <<= 8;
                color += green;
                color <<= 8;
                color += blue;
                color <<= 8;
                color += 0xFF; //alpha
                color <<= 8;

                m_buffer1[((y + i) * SCREEN_WIDTH) + (x + j)] = color;
            }
        }
    }

    void Screen::update() {
        SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);

    }

/*    void Screen::clear(){
        memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT* sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT* sizeof(Uint32));
    }*/

    void Screen::log(string output){
        SDL_Log(output.c_str());
    }

    void Screen::boxBlur(){  //Applies blurr effect to the pixels
        //Swap buffers
        Uint32 * temp = m_buffer1;
        m_buffer1 = m_buffer2;
        m_buffer2 = temp;

        //loop through all the pixels
        for(int y = 0; y < SCREEN_HEIGHT; y++){
            for(int x = 0; x < SCREEN_WIDTH; x++){

                /* rows and columns visualized
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 */

                //color values to hold next loops
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                //loop through the rows and columns visualized above
                for(int row = -1; row <= +1; row++){
                    for(int col = -1; col <=1; col++ ){
                        //set current x and y coordinates
                        int currentX = x + col;
                        int currentY = y + row;
                        //check to see that all targeted pixels are contained within the screen
                        if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT){
                            //store corrent pixels color
                            Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

                            //store each individual color by bitshifting
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            //add to the total for division
                            redTotal += red;
                            greenTotal+= green;
                            blueTotal += blue;

                        }

                    }
                }

                //set the new values from total, divide by 9 to get an avarage color
                Uint8 red = redTotal/9;
                Uint8 green = greenTotal/9;
                Uint8 blue = greenTotal/9;

                //finally set the pixel
                setPixel(x, y, red, green, blue);

            }
        }


    }

    void Screen::close() {


        delete[] m_buffer1;
        delete[] m_buffer2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

    }
}
