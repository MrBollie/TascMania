#include "MainComponent.h"
#include "CChannelStrip.h"


/**
* Constructor for our main component
* \param pUSB   Pointer to our USB communication layer
* \param pR     Pointer to the route window, to open and close it from this 
*               component
* \param pAppProps  Pointer to the application properties store
*/
MainContentComponent::MainContentComponent(CTascamUSB *pUSB, RouteWindow *pR, 
    ApplicationProperties *pAppProps)
{
    setSize (1024, 600);
    pRouteWindow = pR;
    pAppProperties = pAppProps;

    // Making channel strips
    for (int i = 0 ; i < 16 ; i++) {
        CChannelStrip *pCS = new CChannelStrip(i+1,pUSB);    
        pChannels[i] = new ChannelStrip(pCS);
        pChannels[i]->addListener(this); 
        pChannels[i]->setTopLeftPosition(i*60+2, 201);
        addAndMakeVisible(pChannels[i]);
    }

    // EQ Window on top. The first channel will be selected as default
    pChannelEQ = new ChannelEQ(pChannels[0]->getCChannelStrip());
    pChannels[0]->engageSelButton();
    pChannelEQ->setTopLeftPosition(2,2);
    addAndMakeVisible(pChannelEQ);
        
    // Adding Route button
    addAndMakeVisible(routingButton);
    routingButton.addListener(this);
    routingButton.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    routingButton.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
    routingButton.setTopLeftPosition(963,2);
    routingButton.setSize(60,25);
    routingButton.setButtonText("Routing");

    // Adding scene buttons
    int x = 0;
    int y = 0;
    for (int i = 0 ; i < 4 ; i++) {
        addAndMakeVisible(sceneButton[i]);
        sceneButton[i].addListener(this);
        sceneButton[i].setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
        sceneButton[i].setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
        sceneButton[i].setTopLeftPosition(963 + x, 28 + y);
        sceneButton[i].setSize(30, 25);
        sceneButton[i].setButtonText(String(i+1));
        sceneButton[i].setRadioGroupId(1);
        sceneButton[i].setClickingTogglesState(true);
        if (i == 1) {
            y += 25;
            x = 0;
        }
        else {
            x += 30;
        }
    }
    
    // Adding Scene save button
    addAndMakeVisible(saveButton);
    saveButton.addListener(this);
    saveButton.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    saveButton.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
    saveButton.setTopLeftPosition(963,78);
    saveButton.setSize(60,25);
    saveButton.setButtonText("Save");

    // Master strip
    pMasterStrip = new MasterStrip();
    pMasterStrip->setTopLeftPosition(963,106);
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


/**
* Click handler, making the route window visible
* \param button Button that has been clicked.
*/
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
            pChannels[i]->disengageSelButton();
    }
}
