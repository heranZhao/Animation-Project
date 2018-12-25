//
//  Fox.cpp
//  test2
//
//  Created by heran zhao on 12/11/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "Fox.hpp"

void Fox::drawSelf()
{
    glColor3f(0.8, 0.2, 0.1);
    glPushMatrix();
    glTranslatef(curPos->x,curPos->y,0);
    glutSolidSphere(size,50,50);
    glPopMatrix();
}

bool Fox::isTargetInView()
{
    if(curTarget == NULL)
        return false;
    
    for(int i=0;i<viewList.size();i++)
    {
        if(viewList[i]->id == curTarget->id)
        {
            if(viewList[i]->curStatus == Rest)//like the pray in shelter, can't be hunted
            {
                curTarget = NULL;
                return false;
            }
            else
                return true;
        }
    }
    return false;
}

void Fox::judgeSelf()
{
    switch(curStatus)
    {
        case Rest:
            if(isHungry())
            {
                targetPos = NULL;
                curStatus = Searching;
            }
            break;
        case Searching:
        {
            vector<Creature*> pray = findTargetInView(Pray);
            if(pray.size() != 0)
            {
                for(int i=0;i<pray.size();i++)
                {
                    if(pray[i]->curStatus != Rest)
                    {
                        setTarget(pray[i]);
                        curStatus = Hunting;
                    }
                }
            }
            break;
        }
        case Hunting:
            if(!isTargetInView())//can't see the target anymore
            {
                targetPos = NULL;
                curTarget = NULL;
                curStatus = Searching;
            }
            else if(curTarget->curStatus == Rest)//target in the shelter
            {
                targetPos = NULL;
                curTarget = NULL;
                curStatus = Searching;
            }
            else if(calculateDistance(curTarget->curPos->x,curTarget->curPos->y) < size)//catch the pray
            {
                targetPos = NULL;
                curTarget->curStatus = Dieing;
                curStatus = Eating;
            }
            break;
        case Eating:
            if(curTarget->curEnergy <= 0)
            {
                targetPos = NULL;
                curTarget = NULL;
                //randomStatus();
                curStatus = Searching;
            }
            break;
        case Dieing:
            break;
    }
}
