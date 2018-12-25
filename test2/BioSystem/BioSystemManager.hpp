//
//  BioSystemManager.hpp
//  test2
//
//  Created by heran zhao on 12/12/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#ifndef BioSystemManager_hpp
#define BioSystemManager_hpp

#include <stdio.h>
#include <vector>
#include "Fox.hpp"
#include "Rabbit.hpp"
#include "Shelter.hpp"
#include "Grass.hpp"
#endif /* BioSystemManager_hpp */
using namespace std;

class BioSystemManager
{
public:
    vector<Creature*> totalList;
    int shelterIdx = 0;
    int grassIdx = 100;
    int rabbitIdx = 1000;
    int foxIdx = 10000;
    
    int width = 12;
    int height = 6;
    
public:
    BioSystemManager();
    
    void runSystem();
    
    void removeDeadBody();
    
    void updateView(Creature* cur, int curIdx);
    
    bool isInView(float x1,float y1, float x2, float y2, float viewSize);
    
};
