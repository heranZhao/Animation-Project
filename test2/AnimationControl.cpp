//
//  AnimationControl.cpp
//  test2
//
//  Created by heran zhao on 9/7/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "AnimationControl.hpp"

void AnimationControl::initialState()
{
    st = (SplineType)(splineType);
    spt = (SpeedType)speedType;
    pt = (PointType)(pointType+1);
    
    splinecalculation = new SplineCalculation();
    splinecalculation->beginCaculate(Both,st,pt,myPointList);
    
    float totalDis = splinecalculation->getTotalDis();
    
    speedfunc = new SpeedFunc(spt, totalDis);
}

MyPoint3D* AnimationControl::beginAnimation()
{
    float dis = speedfunc->getDisByT();
    if(dis == -1)
    {
        reset();
        dis = speedfunc->getDisByT();
    }
    
    MyPoint3D* point = splinecalculation->getPointByDis(dis);
    return point;
}

void AnimationControl::initialHB()
{
    initialState();
}

void AnimationControl::beginHBAnimation()
{
    MyPoint3D* temp = beginAnimation();

}
