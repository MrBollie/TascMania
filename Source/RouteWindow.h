/*
  ==============================================================================

    RouteWindow.h
    Created: 8 Jul 2016 12:20:30pm
    Author:  rajan

  ==============================================================================
*/

#ifndef ROUTEWINDOW_H_INCLUDED
#define ROUTEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CRouting.h"

//==============================================================================
/*
*/
class RouteWindow    : public DocumentWindow
{
public:
    RouteWindow(String, CRouting*);
                                    
    ~RouteWindow();

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RouteWindow)

};


#endif  // ROUTEWINDOW_H_INCLUDED
