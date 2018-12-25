//
//  SplineCalculation.hpp
//  test2
//
//  Created by heran zhao on 9/20/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#ifndef SplineCalculation_hpp
#define SplineCalculation_hpp

#include<iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <map>

#include"MyData.hpp"



enum SplineType{
    Catmull, BSpline
};

enum MoveType{
    Transform, Rotation, Both
};

//this class is used to build the relation between arc distance and position of each spline type
class SplineCalculation
{
public:
    
    SplineCalculation()
    {
        preEndPoint = new MyPoint3D(0,0,0);
    }
    ~SplineCalculation()
    {
        delete preEndPoint;
        disList.clear();
        eularList.clear();
        posList.clear();
        quatList.clear();
        MatrixM.clear();
        MatrixG.clear();
    }
    
    vector<MyPoint3D*> getPosList()
    {
        return posList;
    }
    
    float getTotalDis()
    {
        unsigned long size = disList.size();
        return disList[size-1];
    }
    
    void reset()
    {
        beginIdx = 0;
    }
    
    //begin to calculate the interpolation value
    void beginCaculate(MoveType mt, SplineType stype, PointType pt, vector<MyPoint3D*> pointlist);
    
    //return the point postion and dis is the arc length from begining to current time
    MyPoint3D* getPointByDis(float dis);
    
    MyEular* getRotationByIdx();
    
private:
    
    //this value record the current index of the animation
    int beginIdx = 0;
    int rotateIdx = 0;
    
    //the density of points between two key frame points
    float pointDensity = 25;
    
    MyPoint3D* preEndPoint;
    PointType curPointType = Standard;
    MoveType moveType = Both;
    
    //the matrix for the interpolation calculation
    vector<vector<float>> MatrixM;
    vector<vector<float>> MatrixG;
    
    vector<MyPoint3D*> posList;
    vector<float> disList;
    vector<MyEular*> eularList;
    vector<MyQuaternion*> quatList;
    
    //calculate the interplation value of position
    float calculateInterpPointsPos(float curDis, float preEndDis);
    
    //calculate the interplation value of euler
    void calculateInterpPointsEular(float curDis);
    
    //calculate the interplation value of quaternion
    void calculateInterpPointsQuaternion(float curDis);
    
    //build G matrix
    void buildGeoMatrix(PointType ctype, vector<MyPoint3D*> pointList);
    
    //build M matrix for catMull
    void buildCatMullMatrix();
    
    //build M matrix matrix for B Spline
    void buildBSplineMatrix();

    //idx is the row of G matrix, and u is the time from 0-1, for example,
    //when idx is 0 and u is 0.1, it will return the value of x in 0.1
    float getValueByIdx(int idx, float u);
    
    //set the spline type and built the specific M matrix
    void setSplineType(SplineType stype);

};


#endif /* SplineCalculation_hpp */
