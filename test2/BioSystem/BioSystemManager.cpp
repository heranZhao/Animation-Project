//
//  BioSystemManager.cpp
//  test2
//
//  Created by heran zhao on 12/12/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "BioSystemManager.hpp"

BioSystemManager::BioSystemManager()
{
    //ADD Fox
    for(int i=0;i<5;i++)
    {
        float xpos = (rand() % (100*width) )/100.0;
        float ypos = (rand() % (100*height) )/100.0;
        int xNeg = rand() % 2;
        int yNeg = rand() % 2;
        if(xNeg == 0)
        {
            xpos = -xpos;
        }
        if(yNeg == 0)
        {
            ypos = -ypos;
        }
        Fox* fox = new Fox(foxIdx+i,xpos,ypos);
        totalList.push_back(fox);
    }
    
    //ADD Rabbit
    for(int i=0;i<15;i++)
    {
        float xpos = (rand() % (100*width) )/100.0;
        float ypos = (rand() % (100*height) )/100.0;
        int xNeg = rand() % 2;
        int yNeg = rand() % 2;
        if(xNeg == 0)
        {
            xpos = -xpos;
        }
        if(yNeg == 0)
        {
            ypos = -ypos;
        }
        
        Shelter* shelter = new Shelter(shelterIdx+i,xpos,ypos);
        Rabbit* rabbit = new Rabbit(rabbitIdx+i,xpos,ypos,shelter);
        totalList.push_back(rabbit);
        totalList.push_back(shelter);
    }
    
    //ADD GRASS
    for(int i=0;i<55;i++)
    {
        float xpos = (rand() % (100*width) )/100.0;
        float ypos = (rand() % (100*height) )/100.0;
        int xNeg = rand() % 2;
        int yNeg = rand() % 2;
        if(xNeg == 0)
        {
            xpos = -xpos;
        }
        if(yNeg == 0)
        {
            ypos = -ypos;
        }
        Grass* grass = new Grass(grassIdx+i,xpos,ypos);
        totalList.push_back(grass);
    }
}

void BioSystemManager::runSystem()
{
    
    removeDeadBody();
    
    for(int i=0;i<totalList.size();i++)
    {
        totalList[i]->lifeCircle();
        updateView(totalList[i],i);
    }
}

void BioSystemManager::removeDeadBody()
{
    vector<Creature*> newList(totalList);
    
    vector<int> removeList;
    for(int i=0;i<totalList.size();i++)
    {
        if(totalList[i]->curEnergy <= 0)
        {
            removeList.push_back(i);
        }
    }
    if(removeList.size()<=0)
        return;
    
    totalList.clear();
    int rmvIdx = 0;
    for(int i=0;i<newList.size();i++)
    {
        if(i != removeList[rmvIdx])
        {
            totalList.push_back(newList[i]);
        }
        else
        {
            rmvIdx++;
            if(rmvIdx >= removeList.size())
            {
                rmvIdx = -1;
            }
        }
    }
    newList.clear();
}


void BioSystemManager::updateView(Creature* cur, int curIdx)
{
    vector<Creature*> nearby;
    for (int i=0; i<totalList.size(); i++) {
        if(i != curIdx)
        {
            if(isInView(cur->curPos->x,cur->curPos->y,
                        totalList[i]->curPos->x,totalList[i]->curPos->y,cur->viewDistance))
            {
                nearby.push_back(totalList[i]);
            }
            
        }
    }
    cur->setViewList(nearby);
}

bool BioSystemManager::isInView(float x1,float y1, float x2, float y2, float viewSize)
{
    float dis = sqrt(pow(x1 - x2,2)
                     + pow(y1 - y2,2));
    return (dis <= viewSize);
}
