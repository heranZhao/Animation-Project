//
//  SplineCalculation.cpp
//  test2
//
//  Created by heran zhao on 9/20/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "SplineCalculation.hpp"

void SplineCalculation::setSplineType(SplineType stype)
{
    switch (stype) {
        case Catmull:
            buildCatMullMatrix();
            break;
        case BSpline:
            buildBSplineMatrix();
            break;
        default:
            return;
    }
}

MyPoint3D* SplineCalculation::getPointByDis(float dis)
{
    unsigned long size = disList.size();
    
    for(int i=beginIdx;i<size;i++)
    {
        if(disList[i] >= dis)
        {
            beginIdx = i;
            if(posList[i]->pt == Eular)
            {
                posList[i]->setEuler(eularList[i]->ax, eularList[i]->ay, eularList[i]->az);
            }
            else
            {
                posList[i]->setQuat(quatList[i]->ax, quatList[i]->ay, quatList[i]->az, quatList[i]->aw);
            }
            return posList[i];
        }
    }
    return posList[size - 1];
}


MyEular* SplineCalculation::getRotationByIdx()
{
    if(beginIdx >= eularList.size())
    {
        beginIdx=0;
    }
    return eularList[beginIdx++];
}

void SplineCalculation::beginCaculate(MoveType mt, SplineType stype, PointType pt, vector<MyPoint3D*> pointlist)
{
    curPointType = pt;
    moveType = mt;
    
    setSplineType(stype);
    
    posList.clear();
    disList.clear();
    quatList.clear();
    eularList.clear();
    
    unsigned long size = pointlist.size();
    
    if(size < 4)
    {
        return;
    }
    float preDis = 0;
    
    MyPoint3D begin = pointlist[1];
    preEndPoint = new MyPoint3D(begin.x,begin.y,begin.z);
    
    for(int i = 0; i + 3 < size; i++)
    {
        MyPoint3D* p1 = pointlist[i];
        MyPoint3D* p2 = pointlist[i+1];
        MyPoint3D* p3 = pointlist[i+2];
        MyPoint3D* p4 = pointlist[i+3];
        
        
        
        buildGeoMatrix(Standard, vector<MyPoint3D*>{p1,p2,p3,p4});
        float dis = p2->calDistance(p3);
        preDis = calculateInterpPointsPos(dis,preDis);
        
        buildGeoMatrix(pt, vector<MyPoint3D*>{p1,p2,p3,p4});
        if(pt == Eular)
        {
            calculateInterpPointsEular(dis);
        }
        else
        {
            calculateInterpPointsQuaternion(dis);
        }
    }
}


float SplineCalculation::calculateInterpPointsPos(float curDis, float preEndDis)
{
    
    int numOfPoints = curDis * pointDensity;

    float stepOfU = 1.0 / (float)numOfPoints;
    
    MyPoint3D* pre = new MyPoint3D(preEndPoint->x,preEndPoint->y,preEndPoint->z);
    float allDis = preEndDis;


    for(float i = 0; i <= 1; i+= stepOfU)
    {
        float x = getValueByIdx(0,i);
        float y = getValueByIdx(1,i);
        float z = getValueByIdx(2,i);
        MyPoint3D* p = new MyPoint3D(x,y,z);
        
        allDis += pre->calDistance(p);
        
        pre = p;
        
        posList.push_back(p);
        disList.push_back(allDis);
    }
    preEndPoint = new MyPoint3D(posList.back()->x, posList.back()->y,posList.back()->z);
    
    return allDis;
}

void SplineCalculation::calculateInterpPointsEular(float curDis)
{
    
    int numOfPoints = curDis * pointDensity;
    
    
    
    float stepOfU = 1.0 / (float)numOfPoints;
    
    
    for(float i = 0; i <= 1; i+= stepOfU)
    {
        float x = getValueByIdx(0,i);
        float y = getValueByIdx(1,i);
        float z = getValueByIdx(2,i);
        
        unsigned long size = eularList.size();
        MyEular* e = new MyEular(x,y,z);
        eularList.push_back(e);

        posList[size]->pt = Eular;

    }
}

void SplineCalculation::calculateInterpPointsQuaternion(float curDis)
{
    
    int numOfPoints = curDis * pointDensity;
    
    float stepOfU = 1.0 / (float)numOfPoints;
    
    for(float i = 0; i <= 1; i+= stepOfU)
    {
        float x = getValueByIdx(0,i);
        float y = getValueByIdx(1,i);
        float z = getValueByIdx(2,i);
        float w = getValueByIdx(3,i);
        
        unsigned long size = quatList.size();
        MyQuaternion* q = new MyQuaternion(x,y,z,w);
        quatList.push_back(q);
        
        posList[size]->pt = Quaternion;
        //posList[size]->setQuat(x, y, z, w);
    }
}


void SplineCalculation::buildGeoMatrix(PointType type, vector<MyPoint3D*> pointList)
{
    MatrixG.clear();
    
    switch(type)
    {
        case Standard:
        {
            for(int i=0;i<4;i++)
            {
                MatrixG.push_back( {pointList[i]->x, pointList[i]->y, pointList[i]->z} );
            }
            break;
        }
        case Eular:
        {
            for(int i=0;i<4;i++)
            {
                MyEular* e = pointList[i]->getEuler();
                MatrixG.push_back( {e->ax, e->ay, e->az} );
            }
            break;
        }
        case Quaternion:
        {
            for(int i=0;i<4;i++)
            {
                MyQuaternion* q = pointList[i]->getQuat();
                MatrixG.push_back( {q->ax, q->ay, q->az, q->aw} );
            }
            break;
        }
    }
}

void SplineCalculation::buildCatMullMatrix()
{
    MatrixM.clear();
    
    vector<float> row1 = {-0.5,1.5,-1.5,0.5};
    vector<float> row2 = {1,-2.5,2,-0.5};
    vector<float> row3 = {-0.5,0,0.5,0};
    vector<float> row4 = {0,1,0,0};
    
    MatrixM = vector<vector<float>>{row1, row2,row3,row4};
}

void SplineCalculation::buildBSplineMatrix()
{
    MatrixM.clear();
    
    vector<float> row1 = {-(1.0/6.0),0.5,-0.5,1.0/6.0};
    vector<float> row2 = {0.5,-1.0,0.5,0};
    vector<float> row3 = {-0.5,0,0.5,0};
    vector<float> row4 = {(1.0/6.0),(2.0/3.0),(1.0/6.0),0};
    
    MatrixM = vector<vector<float>>{row1, row2,row3,row4};
}

float SplineCalculation::getValueByIdx(int idx, float u)
{
    
    vector<float> coefficientList;
    vector<float> uList = vector<float>{ pow(u,3.0f), pow(u, 2.0f), u, 1.0f};
    
    for(int i=0;i<4;i++)
    {
        //cout<<"coloum: "<<i<<endl;
        float temp = 0;
        for(int j = 0;j<4;j++)
        {
            temp += uList[j]*MatrixM[j][i];
        }
        coefficientList.push_back(temp);
    }
    
    float res = 0;
    for(int i=0;i<4;i++)
    {
        res += coefficientList[i]*MatrixG[i][idx];
    }
    return res;
}
