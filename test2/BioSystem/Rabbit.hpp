//
//  Rabbit.hpp
//  test2
//
//  Created by heran zhao on 12/11/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//
#pragma once
#ifndef Rabbit_hpp
#define Rabbit_hpp

#include "Creature.hpp"

#endif /* Fox_hpp */

class Rabbit : public Creature
{
private:

    Creature* home;

    void drawSelf();

    void judgeSelf();

public:
    Rabbit(int id, float x, float y,Creature* h) : Creature(x,y)
    {
        this->id = id;
        size = 0.2;
        
        totalEnergy = 5000;
        curEnergy = totalEnergy;
        walkSpeed = 3;
        runSpeed = 12;
        hungryPercent = 85;
        walkConsume = 0.55;//3
        runConsume = 1.38;//7
        restConsume = 0.27;
        cType = Pray;
        viewDistance = size*7;
        
        
        
        home = h;
        randomStatus();
    }
    
};
