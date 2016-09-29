#include "MainWindow.h"

/**
* Constructor for our main window.
* \param name Name of the application
* \param pUSB Pointer to our USB connection layer
* \param pR Pointer to our route window. We need that to hide it and make it
*           visible, when the corresponding button is pressed in the main 
*           component
* \param pAppProperties Pointer to the app properties store.
*/
MainWindow::MainWindow (String name, CTascamUSB *pUSB, RouteWindow *pR,
                ApplicationProperties *pAppProperties)  
                : DocumentWindow (name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new MainContentComponent(pUSB, pR, pAppProperties), true);

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
