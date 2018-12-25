#include <iostream>
#include "OpenGLWindow.hpp"
//using namespace std;

int main(int argc, char *argv[]) {

    
    OpenGLWindow* window = OpenGLWindow::getInstance();

    window->createWindow(argc, argv);

    return 0;
}

