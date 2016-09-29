#ifndef ROUTEWINDOW_H_INCLUDED
#define ROUTEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CRouting.h"


/**
* Our route window showing the output routing component.
*/
class RouteWindow    : public DocumentWindow
{
public:
    RouteWindow(String, CRouting*, ApplicationProperties*);
                                    
    ~RouteWindow();

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RouteWindow)
    ApplicationProperties *pAppProperties;
};


#endif  // ROUTEWINDOW_H_INCLUDED
