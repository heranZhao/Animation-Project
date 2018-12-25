//
//  MyData.hpp
//  test2
//
//  Created by heran zhao on 9/13/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#ifndef MyData_hpp
#define MyData_hpp

#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

enum PointType{
    Standard, Eular, Quaternion
};




class MyEular
{
public:
    float ax;
    float ay;
    float az;
    
    MyEular(float tax,float tay, float taz)
    {
        ax = tax;
        ay = tay;
        az = taz;
    }
};

class MyQuaternion
{
public:
    float ax;
    float ay;
    float az;
    float aw;
    
    MyQuaternion(float roll,float pitch, float yaw)
    {
        yaw /= 57.28835;
        roll /= 57.28835;
        pitch /= 57.28835;
        
        double cy = cos(yaw * 0.5);
        double sy = sin(yaw * 0.5);
        double cr = cos(roll * 0.5);
        double sr = sin(roll * 0.5);
        double cp = cos(pitch * 0.5);
        double sp = sin(pitch * 0.5);
        
        aw = cy * cr * cp + sy * sr * sp;
        ax = cy * sr * cp - sy * cr * sp;
        ay = cy * cr * sp + sy * sr * cp;
        az = sy * cr * cp - cy * sr * sp;
    }
    MyQuaternion(float x,float y, float z, float w)
    {
        ax = x;
        ay = y;
        az = z;
        aw = w;
    }
};

class MyPoint3D
{
private:
    MyEular* eular = NULL;
    MyQuaternion* quat = NULL;
    
public:
    float x;
    float y;
    float z;
    
    float matrix[16];
    
    PointType pt;
    
    float* getMatrix()
    {
        return matrix;
    }
    
    MyEular* getEuler()
    {
        return eular;
    }
    MyQuaternion* getQuat()
    {
        return quat;
    }
    void setQuat(float ax,float ay, float az, float aw)
    {
        quat = new MyQuaternion(ax,ay,az,aw);
        matrix[0] = 1- 2 * ( ay * ay + az * az );
        matrix[1] = 2 * ( ax * ay - az * aw );
        matrix[2] = 2 * ( ax * az + ay * aw );
        matrix[3] = 0.0f;
        
        matrix[4] = 2 * ( ax * ay + az * aw );
        matrix[5] = 1- 2 * ( ax * ax + az * az );
        matrix[6] = 2 * ( ay * az - ax * aw );
        matrix[7] = 0.0f;
        
        matrix[8] = 2 * ( ax * az - ay * aw );
        matrix[9] = 2 * ( ay * az + ax * aw );
        matrix[10] = 1- 2 * ( ax * ax + ay * ay );
        matrix[11] = 0.0f;
        
        matrix[12] = x;
        matrix[13] = y;
        matrix[14] = z;
        matrix[15] = 1;
    }
    void setQuat(float tax,float tay, float taz)
    {
        quat = new MyQuaternion(tax,tay,taz);
        float ay = quat->ay, ax = quat->ax, az = quat->az, aw = quat->aw;
        matrix[0] = 1- 2 * ( ay * ay + az * az );
        matrix[1] = 2 * ( ax * ay - az * aw );
        matrix[2] = 2 * ( ax * az + ay * aw );
        matrix[3] = 0.0f;
        
        matrix[4] = 2 * ( ax * ay + az * aw );
        matrix[5] = 1- 2 * ( ax * ax + az * az );
        matrix[6] = 2 * ( ay * az - ax * aw );
        matrix[7] = 0.0f;
        
        matrix[8] = 2 * ( ax * az - ay * aw );
        matrix[9] = 2 * ( ay * az + ax * aw );
        matrix[10] = 1- 2 * ( ax * ax + ay * ay );
        matrix[11] = 0.0f;
        
        matrix[12] = x;
        matrix[13] = y;
        matrix[14] = z;
        matrix[15] = 1;
    }
    
    void setEuler(float ax,float ay,float az)
    {
        eular = new MyEular(ax,ay,az);
        
        float az1 =-1*eular->az / 57.28835;
        float el1 = -1*eular->ay / 57.28835;
        float ro1 = -1*eular->ax / 57.28835;
        
        
        matrix[0] = cos(az1)*cos(el1); // CA*CE;
        matrix[1] = cos(az1)*sin(el1)*sin(ro1) - sin(az1)*cos(ro1); // CA*SE*SR - SA*CR
        matrix[2] = cos(az1)*sin(el1)*cos(ro1) + sin(az1)*sin(ro1); // CA*SE*CR + SA*SR
        matrix[3] = 0;
        
        matrix[4] = sin(az1)*cos(el1); // SA*CE
        matrix[5] = cos(az1)*cos(ro1) + sin(az1)*sin(el1)*sin(ro1); // CA*CR + SA*SE*SR
        matrix[6] = sin(az1)*sin(el1)*cos(ro1) - cos(az1)*sin(ro1); // SA*SE*CR – CA*SR
        matrix[7] = 0;
        
        matrix[8] = -1*sin(el1); // -SE
        matrix[9] = cos(el1)*sin(ro1); // CE*SR
        matrix[10] = cos(el1)*cos(ro1); // CE*CR
        matrix[11] = 0;
        
        matrix[12] = x;
        matrix[13] = y;
        matrix[14] = z;
        matrix[15] = 1;
    }
    
    MyPoint3D(float tx,float ty,float tz)
    {
        x = tx;
        y = ty;
        z= tz;
        //eular = new MyEular(0,0,0);
        //quat = new MyQuaternion(0,0,0,0);
    }
    ~MyPoint3D()
    {

    }
    
    MyPoint3D(MyPoint3D* temp)
    {
        x = temp->x;
        y = temp->y;
        z = temp->z;
        
        if(temp->eular != NULL)
        {
            eular = new MyEular(temp->eular->ax,temp->eular->ay,temp->eular->az);
        }
        
        if(temp->quat != NULL)
        {
            quat = new MyQuaternion(temp->quat->ax,temp->quat->ay,temp->quat->az);
        }
        
    }
    
    float calDistance(MyPoint3D temp)
    {
        return pow( (pow(x-temp.x, 2) + pow(y - temp.y, 2) + pow(z - temp.z, 2)), 0.5f);
    }
};

class MyColor
{
public:
    float r,g,b;
    MyColor(float tr, float tg, float tb)
    {
        r = tr;
        g = tg;
        b = tb;
    }
};

class KeyFrameList
{
private:
    vector<MyPoint3D>* kfqueue = new vector<MyPoint3D>();
    
public:

    void addPoint(MyPoint3D point)
    {
        kfqueue->push_back(point);
    }
    MyPoint3D getPoint(int idx)
    {
        return kfqueue->at(idx);
    }
    void rmvPoint(int idx)
    {
        kfqueue->erase(kfqueue->begin());
    }
    
    int getSize()
    {
        return (int)kfqueue->size();
    }
};



class MatrixCalculator
{
public:
    
    void buildTransformMatrix(float* res, MyPoint3D* tran)
    {
        *(res + 0) = 1;
        *(res + 1) = 0;
        *(res + 2) = 0;
        *(res + 3) = 0;
        
        *(res + 4) = 0;
        *(res + 5) = 1;
        *(res + 6) = 0;
        *(res + 7) = 0;
        
        *(res + 8) = 0;
        *(res + 9) = 0;
        *(res + 10) = 1;
        *(res + 11) = 0;
        
        *(res + 12) = tran->x;
        *(res + 13) = tran->y;
        *(res + 14) = tran->z;
        *(res + 15) = 1;
    }
    
    
    void buildRotationMatrix(float* res, MyEular* rota)
    {
        float az1 =-1*rota->az / 57.3;
        float el1 = -1*rota->ay / 57.3;
        float ro1 = -1*rota->ax / 57.3;
        
        
        res[0] = setPercision(cos(az1)*cos(el1)); // CA*CE;
        res[1] = setPercision(cos(az1)*sin(el1)*sin(ro1) - sin(az1)*cos(ro1)); // CA*SE*SR - SA*CR
        res[2] = setPercision(cos(az1)*sin(el1)*cos(ro1) + sin(az1)*sin(ro1)); // CA*SE*CR + SA*SR
        res[3] = 0;
        
        res[4] = setPercision(sin(az1)*cos(el1)); // SA*CE
        res[5] = setPercision(cos(az1)*cos(ro1) + sin(az1)*sin(el1)*sin(ro1)); // CA*CR + SA*SE*SR
        res[6] = setPercision(sin(az1)*sin(el1)*cos(ro1) - cos(az1)*sin(ro1)); // SA*SE*CR – CA*SR
        res[7] = 0;
        
        res[8] = setPercision(-1*sin(el1)); // -SE
        res[9] = setPercision(cos(el1)*sin(ro1)); // CE*SR
        res[10] = setPercision(cos(el1)*cos(ro1)); // CE*CR
        res[11] = 0;
        
        res[12] = 0;
        res[13] = 0;
        res[14] = 0;
        res[15] = 1;
    }
    
    float setPercision(float num)
    {
        int scaled = num * 1000;
        num = static_cast<float>(scaled)/1000.0;
        return num;
    }
    
    void multiplyMatrix(float* m3, float m1[16], float m2[16])
    {
        int col =0 , row = 0;
        for(int i=0;i<16;i++)
        {
            col = i % 4;
            row = i / 4;
            m3[i] = m1[row*4]*m2[col] + m1[row*4+1]*m2[col+4] + m1[row*4+2]*m2[col+8] + m1[row*4+3]*m2[col+12];
        }
    }
};



#endif /* MyData_hpp */
