//
//  Rabbit.cpp
//  test2
//
//  Created by heran zhao on 12/11/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "Rabbit.hpp"
void Rabbit::drawSelf()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(curPos->x,curPos->y,0);
    glutSolidSphere(size,50,50);
    glPopMatrix();
}

void Rabbit::judgeSelf()
{
    
    vector<Creature*> predator = findTargetInView(Predator);
    
    switch(curStatus)
    {
        case Rest:
            if(isHungry())
            {
                if(predator.size() == 0)
                {
                    targetPos = NULL;
                    curStatus = Searching;
                }
            }
            break;
        case Searching:
            if(predator.size() != 0)//see a predator, then back to home
            {
                setTarget(home);
                curStatus = Hunting; // run back to home
            }
            else //no predator found, then find grass
            {
                vector<Creature*> grass = findTargetInView(Plant);
                if(grass.size() != 0)
                {
                    setTarget(grass[0]);
                    curStatus = Hunting; //run to the grass
                }
                
            }
            
            break;
        case Hunting:
            if(curTarget == home)//running back to home
            {
                if(calculateDistance(curTarget->curPos->x,curTarget->curPos->y) < size/2)//get home
                {
                    curPos->x = curTarget->curPos->x;
                    curPos->y = curTarget->curPos->y;
                    curTarget = NULL;
                    curStatus = Rest;
                }
            }
            else
            {
                if(!isTargetInView())//can't see the target anymore
                {
                    targetPos = NULL;
                    curStatus = Searching;
                }
                else if(calculateDistance(curTarget->curPos->x,curTarget->curPos->y) < size)//catch the pray
                {
                    //curTarget->curStatus = Dieing;
                    curStatus = Eating;
                }
            }
            break;
        case Eating:
            if(predator.size() != 0)//see a predator, then back to home
            {
                setTarget(home);
                curStatus = Hunting; // run back to home
            }
            else if(curTarget->curEnergy <= 0)
            {
                curTarget = NULL;
                if(isHungry())
                {
                    targetPos = NULL;
                    curStatus = Searching;
                }
                else
                {
                    setTarget(home);
                    curStatus = Hunting;
                }
            }
            break;
        case Dieing:
            break;
    }
    }
