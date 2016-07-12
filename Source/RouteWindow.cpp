/*
  ==============================================================================

    RouteWindow.cpp
    Created: 8 Jul 2016 12:20:30pm
    Author:  rajan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "RouteWindow.h"
#include "RouteComponent.h"

//==============================================================================
RouteWindow::RouteWindow (String name, CRouting *pr)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new RouteComponent(pr), true);

    centreWithSize (getWidth(), getHeight());
    setVisible (false);
}

void RouteWindow::closeButtonPressed() {
            // Just hide me
            setVisible(false);
}

 

RouteWindow::~RouteWindow()
{
}

