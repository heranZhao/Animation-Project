//
//  SpeedFunc.hpp
//  test2
//
//  Created by heran zhao on 9/22/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#ifndef SpeedFunc_hpp
#define SpeedFunc_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
enum SpeedType{
    Constant, EIEO
};

//this class is used to build a relation between time and distance for each speed type
class SpeedFunc
{
    
private:
    //vector<float> timeList;
    vector<float> disList;
    
    //timeInterval, if the framerate is 60, them time interval should be 1/60 = 0.016
    float timeInterval = 0.016;
    
    //the current time
    float currentIdx = 0;
    
    //the total time interval to finish the animation
    float totalIdx = 0;
    
    //build a list of distance for constant speed
    void setConstantSpeedFunc(float speed, float dis);
    
    //build a list of distance for EIEO
    void setEIEOSpeedFunc(float speed, float dis);
    
    //method to calculate the distance of EIEO
    float ParametricBlend(float t);
    
public:
    
    
    //set the speed type and the total arc distance which comes from the spline calculation
    SpeedFunc(SpeedType st, float dis)
    {
        switch (st) {
            case Constant:
                setConstantSpeedFunc(4,dis);
                break;
                
            case EIEO:
                setEIEOSpeedFunc(4,dis);
                break;
        }
    }
    
    ~SpeedFunc()
    {
        disList.clear();
    }
    
    void reset()
    {
        currentIdx = 0;
    }
    
    //return the current arc distance that the object should be
    float getDisByT();

};


#endif /* SpeedFunc_hpp */
