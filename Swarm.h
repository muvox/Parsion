//
// Created by Master on 09/06/2019.
//

#ifndef PARSION_SWARM_H
#define PARSION_SWARM_H

#include "Particle.h"

namespace muvoksi {

    class Swarm {

    public:
        const static int NPARTICLES = 10000;

    private:
        Particle *m_pParticles;
        int lastTime;

    public:
        Swarm();

        ~Swarm();

        const Particle *const getParticles() { return m_pParticles; };

        void update(int elapsed);
    };

}


#endif //PARSION_SWARM_H
