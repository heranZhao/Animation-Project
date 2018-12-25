//
//  Animal.cpp
//  test2
//
//  Created by heran zhao on 12/10/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "Creature.hpp"

void Creature::eatBehaviour()
{
    if(curTarget!=NULL)
    {
        curTarget->curEnergy -= size*8;
        curEnergy += size*8;
    }
}


vector<Creature*> Creature::findTargetInView(CreatureType type)
{
    vector<Creature*> temp;
    for(int i=0;i<viewList.size();i++)
    {
        if(viewList[i]->cType == type)
        {
            temp.push_back(viewList[i]);
        }
    }
    return temp;
}
void Creature::randomStatus() //rest or search
{
    int type = rand() % 2;
    if(type == 0)
    {
        curStatus = Rest;
    }
    else
    {
        targetPos = NULL;
        curStatus = Searching;
    }
}

Creature::Creature(float x,float y)
{
    curPos = new MyPoint3D(x,y,0);
}

void Creature::restBehaviour()
{
    curEnergy -= restConsume;
}
void Creature::runBehaviour()
{
    float dis = calculateDistance(curTarget->curPos->x,curTarget->curPos->y);
    dirX = (curTarget->curPos->x - curPos->x)/dis;
    dirY = (curTarget->curPos->y - curPos->y)/dis;
    
    float degree = atan(abs(dirY)/abs(dirX));
    float distance = runSpeed/5000;
    float x = cos(degree)*distance;
    float y = sin(degree)*distance;
    if(dirX < 0)
    {
        x = -x;
    }
    if(dirY<0)
    {
        y = -y;
    }
    
    curPos->x = curPos->x + x;
    curPos->y = curPos->y + y;
    curEnergy -= runConsume;
    
}

void Creature::setTarget(Creature* target)
{
    curTarget = target;
    float dis = calculateDistance(curTarget->curPos->x,curTarget->curPos->y);
    dirX = (curTarget->curPos->x - curPos->x)/dis;
    dirY = (curTarget->curPos->y - curPos->y)/dis;
    
    //cout<<cType<<" "<<dirX << " "<<dirY<<endl;
}


void Creature::setSearchTargetPos()
{
    if(targetPos == NULL || calculateDistance(targetPos->x,targetPos->y) < 0.25) // choose a new target
    {
        targetPos = new MyPoint3D(0,0,0);
        while(true)
        {
            float xdir = (double)rand() / (RAND_MAX + 1.0);
            float ydir = (double)rand() / (RAND_MAX + 1.0);
            int xNeg = rand() % 2;
            int yNeg = rand() % 2;
            if(xNeg == 0)
            {
                xdir = -xdir;
            }
            if(yNeg == 0)
            {
                ydir = -ydir;
            }
            
            float degree = atan(abs(ydir)/abs(xdir));
            float distance = 2;
            float x = cos(degree)*distance;
            float y = sin(degree)*distance;
            if(xdir < 0)
            {
                x = -x;
            }
            if(ydir<0)
            {
                y = -y;
            }
            
            float newX = curPos->x + x;
            float newY = curPos->y + y;
            
            bool isInside = checkPointIsOutSide(newX, newY);
            if(isInside)
            {
                targetPos->x = newX;
                targetPos->y = newY;
                dirX = xdir;
                dirY = ydir;
                break;
            }
        }
    }
}

void Creature::walkBehaviour()
{
    setSearchTargetPos();
    float degree = atan(abs(dirY)/abs(dirX));
    float distance = walkSpeed/5000;
    float x = cos(degree)*distance;
    float y = sin(degree)*distance;
    if(dirX < 0)
    {
        x = -x;
    }
    if(dirY<0)
    {
        y = -y;
    }
    
    curPos->x = curPos->x + x;
    curPos->y = curPos->y + y;
    curEnergy -= walkConsume;
}

void Creature::lifeCircle()
{
    judgeSelf();
    
    switch(curStatus)
    {
        case Eating:
            eatBehaviour();
            break;
        case Rest:
            restBehaviour();
            break;
        case Searching:
            walkBehaviour();
            break;
        case Hunting:
            runBehaviour();
            break;
        case Dieing:
            //dieBehaviour();
            break;
    }
    
    //model->drawModel();
    drawSelf();
}

bool Creature::isHungry()
{
    if(curEnergy < totalEnergy*hungryPercent/100.0)
    {
        return true;
    }
    return false;
}

void Creature::setViewList(vector<Creature*> nearby)
{
    viewList.clear();
    for(int i=0;i<nearby.size();i++)
        viewList.push_back(nearby[i]);
}

bool Creature::isTargetInView()
{
    if(curTarget == NULL)
        return false;
    
    for(int i=0;i<viewList.size();i++)
    {
        if(viewList[i]->id == curTarget->id)
        {
            return true;
        }
    }
    return false;
}

float Creature::calculateDistance(float tx,float ty)
{
    float dis = sqrt(pow(curPos->x - tx,2)
                     + pow(curPos->y - ty,2));
    return dis;
}

bool Creature::checkPointIsOutSide(float x, float y)
{
    if(x< -12 || x > 12)
    {
        return false;
    }
    else if(y < -6 || y > 6)
    {
        return false;
    }
    return true;
    }
