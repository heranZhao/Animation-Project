//
//  Animal.hpp
//  test2
//
//  Created by heran zhao on 12/10/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#pragma once
#ifndef Creature_hpp
#define Creature_hpp

#include <stdio.h>
#include<GLUT/glut.h>
#include <GLUI/GLUI.h>
#include "MyData.hpp"
using namespace std;
#endif /* Animal_hpp */

enum CreatureType
{
    Predator, Pray, Plant, Hole
};
enum CreatureStatus{
    Rest, Searching, Hunting, Eating, Dieing
};

class Creature
{
public:
    
    
    int id;
    vector<Creature*> viewList;
    
    CreatureType cType = Pray;
    float curEnergy;
    float totalEnergy;
    float walkSpeed;
    float runSpeed;
    float viewDistance;
    float size;
    
    float hungryPercent;
    
    float walkConsume;
    float restConsume;
    float runConsume;
    
    CreatureStatus curStatus = Rest;
    
    Creature* curTarget = NULL;
    
    MyPoint3D* curPos = NULL;
    MyPoint3D* targetPos = NULL;
    float dirX;
    float dirY;
    
    
public:
    
    Creature(float x,float y);
    
    //The action when creature is in rest
    void restBehaviour();
    //the behavious when creature is running
    void runBehaviour();
    //the behavious when creature is eating
    void eatBehaviour();
    //the behavious when creature is walking
    void walkBehaviour();
    //judge if the creature is in hungry status
    bool isHungry();
    
    //set a target postion for searching
    void setSearchTargetPos();
    
    //the life circle logic of a creature
    void lifeCircle();
    
    //give the creature a random status from rest and search, usually called in constructor function
    void randomStatus();
    
    //update the items in creature's view
    void setViewList(vector<Creature*> nearby);
    
    //set the current target
    void setTarget(Creature* target);
    
    //judge whether the current is in view list
    bool isTargetInView();
    
    //find the specific type of creature in view list
    vector<Creature*> findTargetInView(CreatureType type);
    
    //calculate the distance from tx, ty to self position
    float calculateDistance(float tx,float ty);
    
    //let the creature judge itselves to uodate its status
    virtual void judgeSelf() = 0;
    
    //draw it in the panels
    virtual void drawSelf() = 0;
    
private:
    
    //judge if x,y is out of the screens
    bool checkPointIsOutSide(float x, float y);
};
