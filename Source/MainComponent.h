#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelStrip.h"
#include "MasterStrip.h"
#include "ChannelEQ.h"
#include "CTascamUSB.h"
#include "RouteWindow.h"


/**
* Main component that holds the mixer.
*/
class MainContentComponent   : public Component,
                                public Button::Listener,
                                public ChannelStrip::Listener
{
public:
    MainContentComponent(CTascamUSB *pUSB, RouteWindow *pR,
        ApplicationProperties *pAppProps);
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;
    void eqRequested(ChannelStrip*) override;
    void compRequested(ChannelStrip*) override;

private:
    ApplicationProperties *pAppProperties;
    ChannelStrip *pChannels[16];
    ChannelEQ *pChannelEQ;
    MasterStrip *pMasterStrip;
    RouteWindow *pRouteWindow;
    TextButton routingButton;
    TextButton sceneButton[4];
    TextButton saveButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
