//
//  Shelter.hpp
//  test2
//
//  Created by heran zhao on 12/12/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//
#pragma once
#ifndef Shelter_hpp
#define Shelter_hpp

#include <stdio.h>
#include "Creature.hpp"
#endif /* Shelter_hpp */


class Shelter: public Creature
{
private:
    
    void judgeSelf()
    {
    }
    void drawSelf()
    {
        glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(curPos->x,curPos->y,-1);
        glutSolidSphere(size,50,50);
        glPopMatrix();
    }
public:
    Shelter(int id, float x, float y) : Creature(x,y)
    {
        cType = Hole;
        curStatus = Rest;
        size = 0.3;
        curEnergy = 1;
        restConsume = 0;
    }
};
