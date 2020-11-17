
#include "larticles.h"
void Larticles_Initiate(Larticles *larticles)
{
    larticles->larticles.clear();
	for (int i = 0; i < LARTICLES_START_AMOUNT; i++)
	{
		Larticle p;
		p.r = LARTICLE_SIZE;
		p.m = 5.0f;
		float r;
		float a;
		r = (float)rand()*(UNIVERSE_SIZE/4.0f)/RAND_MAX;
		if(r < 200)
        {
            r = (float)rand()*(UNIVERSE_SIZE/4.0f)/RAND_MAX;

        }
		a = (float)rand()*(M_PI*2.0f)/RAND_MAX;
		p.x = UNIVERSE_SIZE/2.0f + r*cos(a);//(float)rand()*UNIVERSE_SIZE/RAND_MAX;
		p.y = UNIVERSE_SIZE/2.0f + r*sin(a);//(float)rand()*UNIVERSE_SIZE/RAND_MAX;
		p.vx = 0.0f;
		p.vy = 0.0f;
		p.ax = 0.0f;
		p.ay = 0.0f;
		p.color[0] = 0;
		p.color[1] = 0;
		p.color[2] = 0;
		p.color[3] = 255;
		p.angle = (float)(rand()%200 - 100) / 100.0f * M_PI;
		p.anglespeed = 0.0f;
		p.time = LARTICLE_INITIATE_TIME;
		p.state = 0;

		p.health = LARTICLE_MAX_HEALTH;
		p.alive = 1;

		p.connections_length = -1;
		for (int i=0; i<NEURONS_AMOUNT; i++)
		{
			p.potentials[i] = (float)NEURONS_START_POTENTIAL + ((float)(rand()) / (float)(RAND_MAX)- 0.5f) / 10.0f;
			//p.errors[i] = 0.0f;
		}
		for (int i=0; i<NEURONS_CONNECTIONS; i++)
		{
			p.connections[i][0] = -13.0f;
			p.connections[i][1] = -13.0f;
			p.weights[i] = 0.0f;
		}
		Larticle_Add_Connection(&p,NEURON_ALIVE_1, NEURON_EAT,1.0f);
		Larticle_Add_Connection(&p,NEURON_ALIVE_1, NEURON_SPLIT,1.0f);
		//Larticle_Create_Connections(&p,1);
		Larticle_Add_Connection(&p,NEURON_ALIVE_1, NEURON_MOVE_X,1.0f);
		larticles->larticles.push_back(p);
	}
	Larticle_Calculate_All(&larticles->larticles[0]);
	//Larticle_Print(&larticles->larticles[0]);
}



void Larticles_Doe(Larticles *larticles)
{

	for (int i=0; i<larticles->larticles.size(); i++)
	{
		if(larticles->larticles[i].health > 0.0f)
		{
			larticles->larticles[i].time += 1;
			if((larticles->larticles[i].time) % 1000 == 0)
            {
                Larticle_Heridity(&larticles->larticles[i],&larticles->larticles[i],0);
            }

			Larticle_Gravitate(&larticles->larticles[i]);



			larticles->larticles[i].vx += larticles->larticles[i].ax;
			larticles->larticles[i].vy += larticles->larticles[i].ay;

			float sinn = sin(larticles->larticles[i].angle);
			float coss = cos(larticles->larticles[i].angle);

			if (larticles->larticles[i].time > LARTICLE_TIME)
			{

				larticles->larticles[i].r = LARTICLE_SIZE + larticles->larticles[i].health / LARTICLE_MAX_HEALTH *
				 LARTICLE_SIZE_SCALE;
				larticles->larticles[i].m = larticles->larticles[i].r;
				larticles->larticles[i].potentials[NEURON_ALIVE_1] = 1.0f;
				larticles->larticles[i].potentials[NEURON_ALIVE_2] = -1.0f;
				//larticles->larticles[i].potentials[NEURON_SINE_1] = sin((float)larticles->larticles[i].time / 10.0f);
				larticles->larticles[i].potentials[NEURON_IN_1] = larticles->larticles[i].potentials[NEURON_OUT_1];
				larticles->larticles[i].potentials[NEURON_IN_2] = larticles->larticles[i].potentials[NEURON_OUT_2];
				larticles->larticles[i].potentials[NEURON_IN_3] = larticles->larticles[i].potentials[NEURON_OUT_3];
				larticles->larticles[i].potentials[NEURON_SENSE_ANGLE] = larticles->larticles[i].angle / M_PI;
				larticles->larticles[i].potentials[NEURON_SENSE_HEALTH] = (float)larticles->larticles[i].health /
				((float)LARTICLE_MAX_HEALTH);

				//float cx = larticles->larticles[i].x - (float)UNIVERSE_SIZE / 2.0f;
				//float cy = larticles->larticles[i].y - (float)UNIVERSE_SIZE / 2.0f;
				//larticles->larticles[i].potentials[NEURON_SENSE_GRAVITY] = 2.0f * (cx*cx+cy*cy)/((float)(UNIVERSE_SIZE*UNIVERSE_SIZE));
				//larticles->larticles[i].potentials[NEURON_SENSE_GRAVITY_ANGLE] = (larticles->larticles[i].angle - atan2(-cy,-cx))/(float)M_PI;
				//larticles->larticles[i].potentials[NEURON_SENSE_ANGLE_SPEED] = larticles->larticles[i].anglespeed;

				Larticle_Calculate_All(&larticles->larticles[i]);

				float smax = -1.0f;
				larticles->larticles[i].state = 0;
				if (larticles->larticles[i].potentials[NEURON_STATE_1] > smax)
				{
					larticles->larticles[i].state = 1;
					smax = larticles->larticles[i].potentials[NEURON_STATE_1];
				}
				if (larticles->larticles[i].potentials[NEURON_STATE_2] > smax)
				{
					larticles->larticles[i].state = 2;
					smax = larticles->larticles[i].potentials[NEURON_STATE_2];
				}
				if (larticles->larticles[i].potentials[NEURON_STATE_3] > smax)
				{
					larticles->larticles[i].state = 3;
					smax = larticles->larticles[i].potentials[NEURON_STATE_3];
				}

				if(larticles->larticles[i].state ==1)
				{
					larticles->larticles[i].health += (float)LARTICLES_REGEN;
					larticles->larticles[i].color[0] = 50;
					larticles->larticles[i].color[1] = 50;
					larticles->larticles[i].color[2] = 255;
					if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.0f)
					{
                        larticles->larticles[i].color[0] = 0;
						larticles->larticles[i].color[1] = 200;
						larticles->larticles[i].health -= UNIVERSE_DAMAGE *
                        (float)larticles->larticles[i].connections_length/(float)NEURONS_AMOUNT;
					}
				}
				else
				{
					if(larticles->larticles[i].state == 2)
					{
						larticles->larticles[i].color[0] = 255;
						larticles->larticles[i].color[1] = 0;
						larticles->larticles[i].color[2] = 0;
						if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.0f)
						{
                            larticles->larticles[i].color[0] = 255;
							larticles->larticles[i].color[1] = 160;
                            larticles->larticles[i].color[2] = 0;
							larticles->larticles[i].health -= UNIVERSE_DAMAGE *
                            (float)larticles->larticles[i].connections_length/(float)NEURONS_AMOUNT;
						}
					}
					else
					{
						larticles->larticles[i].color[0] = 50;
						larticles->larticles[i].color[1] = 255;
						larticles->larticles[i].color[2] = 70;
						if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.0f)
						{
                            larticles->larticles[i].color[0] = 0;
                            larticles->larticles[i].color[1] = 140;
                            larticles->larticles[i].color[2] = 20;
							larticles->larticles[i].health -= UNIVERSE_DAMAGE *
                            (float)larticles->larticles[i].connections_length/(float)NEURONS_AMOUNT;
						}
					}
				}

				if (larticles->larticles[i].state != 0)
				{
					larticles->larticles[i].health -= UNIVERSE_DAMAGE *
					(float)larticles->larticles[i].connections_length/(float)NEURONS_AMOUNT;
				}

				float dva = 1.0f;
                if(larticles->larticles[i].state == 3)
                {
                    dva = (float)LARTICLES_SPEED_MULTIPLIER;
                }
                if(larticles->larticles[i].state == 1)
                {
                    dva = 1.0f/(float)LARTICLES_SPEED_MULTIPLIER;
                }
                larticles->larticles[i].angle += (larticles->larticles[i].potentials[NEURON_MOVE_ANGLE] / 2.0f) * (float)(LARTICLE_FOV) * dva;//larticles->larticles[i].anglespeed;
                if (larticles->larticles[i].angle > (float)M_PI)
                {
                    larticles->larticles[i].angle = -(float)M_PI;
                }
                if (larticles->larticles[i].angle < -(float)M_PI)
                {
                    larticles->larticles[i].angle = (float)M_PI;
                }

				larticles->larticles[i].vx += (0.5f/((float)LARTICLE_SPEED)*(coss*
				(larticles->larticles[i].potentials[NEURON_MOVE_X] / 2.0f) - sinn*
				(larticles->larticles[i].potentials[NEURON_MOVE_Y] / 2.0f)));

				larticles->larticles[i].vy += (0.5f/((float)LARTICLE_SPEED)*(coss*
				(larticles->larticles[i].potentials[NEURON_MOVE_Y] / 2.0f) + sinn*
				(larticles->larticles[i].potentials[NEURON_MOVE_X] / 2.0f)));


				if (larticles->larticles[i].potentials[NEURON_SPLIT] > 0.0f &&
				larticles->larticles[i].health > (float)LARTICLE_SPLIT_HEALTH*1.1f)
				{
					larticles->larticles[i].health -= (float)LARTICLE_SPLIT_HEALTH;
					Larticle p;
					p.x = larticles->larticles[i].x - 2.1f*(float)LARTICLE_SIZE*coss;
					p.y = larticles->larticles[i].y - 2.1f*(float)LARTICLE_SIZE*sinn;
					p.r = LARTICLE_SIZE;
					p.m = 5.0f;
					p.vx = larticles->larticles[i].vx;
					p.vy = larticles->larticles[i].vy;
					p.ax = 0.0f;
					p.ay = 0.0f;
					p.color[0] = 0;
					p.color[1] = 0;
					p.color[2] = 0;
					p.color[3] = 255;
					p.angle = (float)(rand()%200 - 100) / 100.0f * M_PI;
					p.anglespeed = 0.0f;
					p.time = 0;
					p.state = 0;

					p.health = (float)LARTICLE_SPLIT_HEALTH*0.9f;
					p.alive = 1;

					p.connections_length = -1;
					for (int j=0; j<NEURONS_AMOUNT; j++)
					{
						p.potentials[j] = larticles->larticles[i].potentials[j];
						//p.errors[j] = 0.0f;
					}
					for (int j=0; j<NEURONS_CONNECTIONS; j++)
					{
						p.connections[j][0] = -13.0f;
						p.connections[j][1] = -13.0f;
						p.weights[j] = 0.0f;
					}
					int r = rand()%NEURON_MUTATIONRATE;
					Larticle_Heridity(&larticles->larticles[i], &p, 1);
					for(int j=0; j<r; j++)
                    {
                        Larticle_Heridity(&p, &p, 0);
                    }
					larticles->larticles.push_back(p);

				}



                float see_d = 0.0f;
                float see_a = 0.0f;
                int insight = 0;
                float distance = (float)LARTICLE_VISUAL_RANGE;
                Larticle lsee;
                float hear1 = 0.0f;
                float hear2 = 0.0f;
                float hear3 = 0.0f;

                for (int j=0; j<larticles->larticles.size(); j++)
                {
                    if(larticles->larticles[j].health>0.0f)
                    {
                        if (i!=j)
                        {
                            float dx = larticles->larticles[j].x - larticles->larticles[i].x;
                            float dy = larticles->larticles[j].y - larticles->larticles[i].y;
                            float dr = larticles->larticles[i].r + larticles->larticles[j].r;
                            float d = dx*dx + dy*dy;
                            if (d==0.0f)
                            {
                                d = 0.01f;
                            }
                            if (d < dr*dr)
                            {
                                Larticle_Collide(&larticles->larticles[i],&larticles->larticles[j]);
                            }
                            if (d < LARTICLE_VISUAL_RANGE * LARTICLE_VISUAL_RANGE)
                            {
                                float drr = 1.0f/d;
                                float daa = (atan2(dy,dx) - larticles->larticles[i].angle) / d;
                                see_d += drr;
                                see_a += daa;

                                hear1 += larticles->larticles[j].potentials[NEURON_SPEAK_1]/d;
                                hear2 += larticles->larticles[j].potentials[NEURON_SPEAK_2]/d;
                                hear3 += larticles->larticles[j].potentials[NEURON_SPEAK_3]/d;

                                float m;
                                if (coss != 0.0f)
                                {
                                    m = sinn/coss;
                                }
                                else
                                {
                                    if (sinn < 0.0f)
                                    {
                                        m = -100000000000.0f;
                                    }
                                    else
                                    {
                                        m = 100000000000.0f;
                                    }
                                }
                                float b = -m*larticles->larticles[i].x + larticles->larticles[i].y;
                                float D1 = (2.0f*m*b-2.0f*m*larticles->larticles[j].y-2.0f*larticles->larticles[j].x);
                                float D2 = -4.0f*(m*m+1.0f)*(b*b - 2.0f*b*larticles->larticles[j].y+
                                larticles->larticles[j].x*larticles->larticles[j].x+
                                larticles->larticles[j].y*larticles->larticles[j].y-
                                larticles->larticles[j].r*larticles->larticles[j].r);
                                float D = D1*D1 + D2;
                                int tttt = 0;
                                if (D > 0.0f)
                                {
                                    if(sinn > 0.0f && larticles->larticles[j].y>larticles->larticles[i].y)
                                    {
                                        if(coss > 0.0f && larticles->larticles[j].x>larticles->larticles[i].x)
                                        {
                                            tttt = 1;
                                        }
                                        if(coss <= 0.0f && larticles->larticles[j].x<=larticles->larticles[i].x)
                                        {
                                            tttt = 1;
                                        }
                                    }
                                    if(sinn <= 0.0f && larticles->larticles[j].y<=larticles->larticles[i].y)
                                    {
                                        if(coss > 0.0f && larticles->larticles[j].x>larticles->larticles[i].x)
                                        {
                                            tttt = 1;
                                        }
                                        if(coss <= 0.0f && larticles->larticles[j].x<=larticles->larticles[i].x)
                                        {
                                            tttt = 1;
                                        }
                                    }
                                }
                                if (tttt == 1)
                                {
                                    insight = 1;
                                    if (d < distance)
                                    {
                                        lsee = larticles->larticles[j];
                                        distance = d;
                                    }
                                }

                            }


                        }


                    }
                    else
                    {
                        larticles->larticles.erase(larticles->larticles.begin() + j);
                    }
                }

                larticles->larticles[i].potentials[NEURON_HEAR_1] = hear1;
                larticles->larticles[i].potentials[NEURON_HEAR_2] = hear2;
                larticles->larticles[i].potentials[NEURON_HEAR_3] = hear3;

                if(insight == 1)
                {
                    float dangle = atan2(larticles->larticles[i].y - lsee.y, larticles->larticles[i].x - lsee.x);
                    //larticles->larticles[i].potentials[NEURON_SEE_GRAVITY] = lsee.potentials[NEURON_SENSE_GRAVITY] -
                    //larticles->larticles[i].potentials[NEURON_SENSE_GRAVITY];
                    larticles->larticles[i].potentials[NEURON_SEE_DISTANCE_1] = distance /
                    ((float)UNIVERSE_SIZE*(float)UNIVERSE_SIZE);
                    larticles->larticles[i].potentials[NEURON_SEE_DISTANCE_2] = 1.0f / distance;
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_1] = (float)lsee.potentials[NEURON_STATE_1];
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_2] = (float)lsee.potentials[NEURON_STATE_2];
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_3] = (float)lsee.potentials[NEURON_STATE_3];
                    larticles->larticles[i].potentials[NEURON_SEE_ANGLE] = dangle - larticles->larticles[i].angle;
                    larticles->larticles[i].potentials[NEURON_SEE_HEALTH] = lsee.health/(larticles->larticles[i].health + 1.0f);
                    larticles->larticles[i].potentials[NEURON_SEE] = 1.0f;
                }
                else
                {
                    //larticles->larticles[i].potentials[NEURON_SEE_GRAVITY] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_DISTANCE_1] = (float)(UNIVERSE_SIZE*UNIVERSE_SIZE);
                    larticles->larticles[i].potentials[NEURON_SEE_DISTANCE_2] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_1] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_2] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_STATE_3] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_ANGLE] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE_HEALTH] = 0.0f;
                    larticles->larticles[i].potentials[NEURON_SEE] = 0.0f;
                }

                larticles->larticles[i].potentials[NEURON_FIELD_DISTANCE] = see_d;
                larticles->larticles[i].potentials[NEURON_FIELD_ANGLE] = see_a;
			}
			else
			{
				larticles->larticles[i].color[0] = 255;
				larticles->larticles[i].color[1] = 255;
				larticles->larticles[i].color[2] = 255;
				for (int j=0; j<larticles->larticles.size(); j++)
                {
                    if(larticles->larticles[j].health>0.0f)
                    {
                        if (i!=j)
                        {
                            float dx = larticles->larticles[j].x - larticles->larticles[i].x;
                            float dy = larticles->larticles[j].y - larticles->larticles[i].y;
                            float dr = larticles->larticles[i].r + larticles->larticles[j].r;
                            float d = dx*dx + dy*dy;
                            if (d==0.0f)
                            {
                                d = 0.01f;
                            }
                            if (d < dr*dr)
                            {
                                Larticle_Collide(&larticles->larticles[i],&larticles->larticles[j]);
                            }
                        }
                    }
                    else
                    {
                        larticles->larticles.erase(larticles->larticles.begin() + j);
                    }
                }
			}


			//larticles->larticles[i].anglespeed *= (1.0f - 20.0f * UNIVERSE_FRICTION);




			float dv = larticles->larticles[i].vx*larticles->larticles[i].vx +
			larticles->larticles[i].vy*larticles->larticles[i].vy;
			float dvv = (float)LARTICLE_MAX_SPEED*(float)LARTICLE_MAX_SPEED;
			float dva = 1.0f;
            if(larticles->larticles[i].state == 3)
            {
                dva = (float)LARTICLES_SPEED_MULTIPLIER;
            }
            if(larticles->larticles[i].state == 1)
            {
                dva = 1.0f/(float)LARTICLES_SPEED_MULTIPLIER;
            }
            dvv *= dva*dva;
			if (dv > dvv)
			{
				float sdv = sqrt(dv);
				larticles->larticles[i].vx = (float)LARTICLE_MAX_SPEED * larticles->larticles[i].vx / sdv;
				larticles->larticles[i].vy = (float)LARTICLE_MAX_SPEED * larticles->larticles[i].vy / sdv;
			}

			larticles->larticles[i].vx *= (1.0f - (float)UNIVERSE_FRICTION);
			larticles->larticles[i].vy *= (1.0f - (float)UNIVERSE_FRICTION);
			larticles->larticles[i].x += larticles->larticles[i].vx;
			larticles->larticles[i].y += larticles->larticles[i].vy;
			if (larticles->larticles[i].health > (float)LARTICLE_MAX_HEALTH)
			{
				larticles->larticles[i].health = LARTICLE_MAX_HEALTH;
			}
		}
		else
		{
			larticles->larticles.erase(larticles->larticles.begin() + i);
		}
	}
}
