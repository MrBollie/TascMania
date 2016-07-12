/*
  ==============================================================================

    MainWindow.cpp
    Created: 8 Jul 2016 6:07:08pm
    Author:  rajan

  ==============================================================================
*/

#include "MainWindow.h"

MainWindow::MainWindow (String name, CTascamUSB *pUSB, RouteWindow *pR)  
                : DocumentWindow (name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new MainContentComponent(pUSB, pR), true);

    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

MainWindow::~MainWindow() {
}

void MainWindow::closeButtonPressed()
{
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
}

RouteWindow* MainWindow::getRouteWindow(){ return pRouteWindow; }
