#ifndef LARTICLES_H_INCLUDED
#define LARTICLES_H_INCLUDED
#ifndef LARTICLE_H_INCLUDED
#include "larticle.h"
#endif
typedef struct
{
	std::vector<Larticle> larticles;
}Larticles;


void Larticles_Initiate(Larticles *larticles);
void Larticles_Doe(Larticles *larticles);

#endif
