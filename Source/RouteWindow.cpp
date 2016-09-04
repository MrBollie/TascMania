#include "../JuceLibraryCode/JuceHeader.h"
#include "RouteWindow.h"
#include "RouteComponent.h"

RouteWindow::RouteWindow (String name, CRouting *pr)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new RouteComponent(pr), true);

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

 

RouteWindow::~RouteWindow()
{
}

