//
//  SpeedFunc.cpp
//  test2
//
//  Created by heran zhao on 9/22/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "SpeedFunc.hpp"

void SpeedFunc::setConstantSpeedFunc(float speed, float dis)
{
    float totalT = dis/speed;
    
    for(float t = 0; t < totalT; t+=timeInterval)
    {
        totalIdx++;
        disList.push_back(speed*t);
    }
}

void SpeedFunc::setEIEOSpeedFunc(float speed, float dis)
{
    float totalT = dis/speed;
    
    for(float t = 0; t < totalT; t+=timeInterval)
    {
        totalIdx++;
        float distance = ParametricBlend(t/totalT)*dis;
        disList.push_back(distance);
    }
}

float SpeedFunc::ParametricBlend(float t)
{
    float sqt = pow(t, 0.5);
    return sqt / (2.0f * (sqt - t) + 1.0f);
}

float SpeedFunc::getDisByT()
{
    if(currentIdx >= totalIdx)
        return -1;
    
    float dis = disList[currentIdx];
    currentIdx++;
    return dis;
}
