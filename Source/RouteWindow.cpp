#include "../JuceLibraryCode/JuceHeader.h"
#include "RouteWindow.h"
#include "RouteComponent.h"

/**
* Constructor for our route window
* \param name   Name of our application or that window
* \param pr     Pointer to routing communication object
* \param pAppProps  Pointer to the application properties store
*/
RouteWindow::RouteWindow (String name, CRouting *pr, 
    ApplicationProperties *pAppProps)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new RouteComponent(pr, pAppProps), true);

    centreWithSize (getWidth(), getHeight());
    setVisible (false);
}


/**
* Catch close button press and just hide the window.
*/
void RouteWindow::closeButtonPressed() {
    // Just hide me
    setVisible(false);
}

/**
* Class destructor
*/ 
RouteWindow::~RouteWindow()
{
}

