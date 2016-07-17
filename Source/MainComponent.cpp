/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "CChannelStrip.h"
#include <vector>

//==============================================================================
MainContentComponent::MainContentComponent(CTascamUSB *pUSB, RouteWindow *pR)
{
    setSize (1024, 600);
    pRouteWindow = pR;

    // Making channel strips
    for (int i = 0 ; i < 16 ; i++) {
        CChannelStrip *pCS = new CChannelStrip(i+1,pUSB);    
        pChannels[i] = new ChannelStrip(pCS);
        pChannels[i]->addListener(this); 
        pChannels[i]->setTopLeftPosition(i*60+2, 201);
        addAndMakeVisible(pChannels[i]);
    }

    // EQ Window on top
    pChannelEQ = new ChannelEQ(pChannels[0]->getCChannelStrip());
    pChannelEQ->setTopLeftPosition(2,2);
    addAndMakeVisible(pChannelEQ);
        
    // Adding Route button
    addAndMakeVisible(routingButton);
    routingButton.addListener(this);
    routingButton.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    routingButton.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
    routingButton.setTopLeftPosition(963,2);
    routingButton.setSize(59,25);
    routingButton.setButtonText("Routing");
    
    // Master strip
    pMasterStrip = new MasterStrip();
    pMasterStrip->setTopLeftPosition(963,29);
    addAndMakeVisible(pMasterStrip);
}

MainContentComponent::~MainContentComponent()
{
        delete pChannelEQ;
        for (int i = 0 ; i < 16 ; i++) {
            CChannelStrip *pCS = pChannels[i]->getCChannelStrip();
            delete pCS;
            delete pChannels[i];
        }
        delete pMasterStrip;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff000000));

    /*g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);*/
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::buttonClicked (Button* button) {
    if (button == &routingButton) {
        pRouteWindow->setVisible(true);
    }
}

void MainContentComponent::compRequested(ChannelStrip *pC) {
    //pChannelEQ->setChannelStrip(pC->getCChannelStrip());
}


/** 
* Signal handler for when a channel strip requests to be controlled by
* the ChannelEQ-component. The EQ buttons of all other channel strips
* will be disengaged
*/
void MainContentComponent::eqRequested(ChannelStrip *pC) {
    // hand over the channel strip communication object
    // to the EQ component
    pChannelEQ->setChannelStrip(pC->getCChannelStrip());
    
    // Take care of consistent button states
    for (int i = 0 ; i < 16 ; i++) {
        if (pChannels[i] != pC)
            pChannels[i]->disengageEQ();
    }
}
