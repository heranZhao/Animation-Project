//
//  OpenGLWindow.hpp
//  test2
//
//  Created by heran zhao on 9/6/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//
#pragma once
#ifndef OpenGLWindow_hpp
#define OpenGLWindow_hpp

#include <stdio.h>
#include<GLUT/glut.h>
#include <GLUI/GLUI.h>
#include "AnimationControl.hpp"
#include "BioSystemManager.hpp"
#define GLEW_STATIC


class OpenGLWindow
{
public:
    
    static OpenGLWindow* getInstance();
    void createWindow(int argc, char *argv[]);
    
private:
    static OpenGLWindow* Instance;
    //GLUI the press button call back function
    static void ui_create_CallBack(int arg);
    
    //initial the opengl window
    void initWindow();
    
    //the reshape call back function
    static void reshapeWindow(int w, int h);
    
    //the display call back function
    static void displayWindow();
    
    static void openLight();
    //the idle function of user interface
    static void myGlutIdle();
    
    //the initial function to create the user interface
    static GLUI *glui_create;
    void initUI();
    
    static BioSystemManager* bioSystem;
};

#endif /* OpenGLWindow_hpp */
