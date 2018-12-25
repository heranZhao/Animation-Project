//
//  Fox.hpp
//  test2
//
//  Created by heran zhao on 12/11/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//


#pragma once
#ifndef Fox_hpp
#define Fox_hpp

#include <stdio.h>
#include "Creature.hpp"

#endif /* Fox_hpp */

class Fox : public Creature
{
private:

    void drawSelf();
    
    bool isTargetInView();
    
    void judgeSelf();
    
public:
    Fox(int id, float x, float y): Creature(x,y)
    {
        this->id = id;
        size = 0.4;
        totalEnergy = 10000;
        curEnergy = totalEnergy;
        walkSpeed = 5;
        runSpeed = 15;
        hungryPercent = 70;
        walkConsume = 0.75;
        runConsume = 1.77;
        restConsume = 0.55;
        cType = Predator;
        viewDistance = size*8;
        
        //randomStatus();
        targetPos = NULL;
        curStatus = Searching;
    }
};
