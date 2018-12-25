//
//  Grass.hpp
//  test2
//
//  Created by heran zhao on 12/15/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//
#pragma once

#ifndef Grass_hpp
#define Grass_hpp

#include <stdio.h>
#include "Creature.hpp"
#endif /* Grass_hpp */

class Grass: public Creature
{
private:
    
    void judgeSelf()
    {
    }
    void drawSelf()
    {
        glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(curPos->x,curPos->y,-1);
        glutSolidSphere(size,50,50);
        glPopMatrix();
    }
public:
    Grass(int id, float x, float y) : Creature(x,y)
    {
        cType = Plant;
        curStatus = Rest;
        size = 0.1;
        curEnergy = 2500;
        restConsume = -0.27;
    }
};
