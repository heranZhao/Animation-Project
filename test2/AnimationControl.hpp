//
//  AnimationControl.hpp
//  test2
//
//  Created by heran zhao on 9/7/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#ifndef AnimationControl_hpp
#define AnimationControl_hpp

#include <stdio.h>
#include "SpeedFunc.hpp"
#include "SplineCalculation.hpp"

enum AnimationType{
    Once,Loop
};


//this class is used to connect the speed function and spline function together by using the same distance
class AnimationControl
{
public:
    
    
    MyPoint3D* input_Pos;
    float input_ax = 0;
    float input_ay = 0;
    float input_az = 0;
    
    int splineType = 0;
    int speedType = 0;
    int pointType = 0;
    bool isBegin = false;
    
    AnimationControl()
    {
        input_Pos = new MyPoint3D(0,0,0);
    }
    
    //initial the relation between speed function and spline function
    void initialState();
    void initialHB();
    
    //In each frame, call this function to get the current point
    MyPoint3D* beginAnimation();
    void beginHBAnimation();
    
    
    
    
    int getKeyFrameSize()
    {
        return (int)myPointList.size();
    }
    
    vector<MyPoint3D*> getKeyFramList()
    {
        return myPointList;
    }
    
    void clearKeyFrameList()
    {
        myPointList.clear();
    }
    
    void addKeyFramePoint()
    {
        MyPoint3D* temp = new MyPoint3D(input_Pos->x,input_Pos->y,input_Pos->z);
        if( (pointType + 1) == (int)Eular)
        {
            temp->setEuler(input_ax,input_ay,input_az);
        }
        else
        {
            temp->setQuat(input_ax,input_ay,input_az);
        }
        myPointList.push_back(temp);
    }
    
    //return false if the list size is 0
    bool rmvKeyFramePoint()
    {
        if(myPointList.size() > 0)
        {
            myPointList.erase(myPointList.end()-1);
            if(myPointList.size() == 0)
            {
                return false;
            }
            return true;
        }
        return false;
    }
    
    void clear()
    {
        delete splinecalculation;
        delete speedfunc;
    }
    
    //return the curve position list
    vector<MyPoint3D*> getCurve()
    {
        return splinecalculation->getPosList();
    }
    

    void reset()
    {
        speedfunc->reset();
        splinecalculation->reset();
    }
    PointType pt;
private:
    SpeedFunc* speedfunc;
    SplineCalculation* splinecalculation;
    SplineType st;
    SpeedType spt;
    
    vector<MyPoint3D*> myPointList;
};

#endif /* AnimationControl_hpp */
