/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelStrip.h"
#include "MasterStrip.h"
#include "ChannelEQ.h"
#include "CTascamUSB.h"
#include "RouteWindow.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                                public Button::Listener,
                                public ChannelStrip::Listener
{
public:
    //==============================================================================
    MainContentComponent(CTascamUSB *pUSB, RouteWindow *pR);
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;
    void eqRequested(ChannelStrip*) override;
    void compRequested(ChannelStrip*) override;

private:
    //==============================================================================
    ChannelStrip *pChannels[16];
    ChannelEQ *pChannelEQ;
    MasterStrip *pMasterStrip;
    RouteWindow *pRouteWindow;
    TextButton routingButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
