//
// Created by Master on 09/06/2019.
//

#ifndef PARSION_PARTICLE_H
#define PARSION_PARTICLE_H

namespace muvoksi {

    struct Particle {
        double m_x;
        double m_y;
        double m_speed;
        double m_direction;

        /*
        double m_xspeed;
        double m_yspeed;*/

    public:
        Particle();
        ~Particle();
        void update(int interval);
    private:
        void init();


    };

}


#endif //PARSION_PARTICLE_H
