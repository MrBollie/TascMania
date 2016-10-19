#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelStrip.h"

/**
* Constructor
* \param pChan CChannelStrip communication object.
*/
ChannelStrip::ChannelStrip(CChannelStrip *pChan)
{
    // this is for interchannel communication
    pChannel = pChan;
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(59,399);
    
    // Adding Phase button
    addAndMakeVisible(selToggle);
    selToggle.addListener(this);
    selToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    selToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff0b338d));
    selToggle.setTopLeftPosition(2,13);
    selToggle.setSize(25,25);
    selToggle.setClickingTogglesState(true);
    selToggle.setName("Select");
    selToggle.setButtonText("^");    
    
    // Adding Phase button
    addAndMakeVisible(phaseToggle);
    phaseToggle.addListener(this);
    phaseToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    phaseToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff0f9624));
    phaseToggle.setTopLeftPosition(29,13);
    phaseToggle.setSize(25,25);
    phaseToggle.setClickingTogglesState(true);
    phaseToggle.setName("Phase");
    phaseToggle.setButtonText("P");       
    
    // Adding Comp button
    addAndMakeVisible(compToggle);
    compToggle.addListener(this);
    compToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    compToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff0f9624));
    compToggle.setTopLeftPosition(2,40);
    compToggle.setSize(52,25);
    compToggle.setClickingTogglesState(true);
    compToggle.setName("Comp");
    compToggle.setButtonText("Comp");       
    
    // Adding EQ button
    addAndMakeVisible(eqToggle);
    eqToggle.addListener(this);
    eqToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    eqToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff0f9624));
    eqToggle.setTopLeftPosition(2,67);
    eqToggle.setSize(52,25);
    eqToggle.setClickingTogglesState(true);
    eqToggle.setName("EQ");
    eqToggle.setButtonText("EQ");    

    // Adding Mute button
    addAndMakeVisible(muteToggle);
    muteToggle.addListener(this);
    muteToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    muteToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
    muteToggle.setTopLeftPosition(2,94);
    muteToggle.setSize(25,25);
    muteToggle.setClickingTogglesState(true);
    muteToggle.setName("Mute");
    muteToggle.setButtonText("M");
    
    // Adding Solo button
    addAndMakeVisible(soloToggle);
    soloToggle.addListener(this);
    soloToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    soloToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xffd2e00a));
    soloToggle.setTopLeftPosition(29,94);
    soloToggle.setSize(25,25);
    soloToggle.setClickingTogglesState(true);
    soloToggle.setName("Solo");
    soloToggle.setButtonText("S");
    
        
    // Adding pan fader
    addAndMakeVisible(panSlider);
    panSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    panSlider.setRange(-20,20,0.5);
    panSlider.addListener(this);
    panSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 15);
    panSlider.setTopLeftPosition(1,120);
    panSlider.setSize(57,50);
    panSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colour(0xffafafaf));
    panSlider.setColour(Slider::ColourIds::textBoxBackgroundColourId, Colour(0xff262626));
    panSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colour(0xffdadada));
    panSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colour(0xffb9b7b4));
    
    // Adding the main fader
    addAndMakeVisible (volumeSlider);
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    volumeSlider.setRange (-97, 6,1);
    volumeSlider.setTextValueSuffix (" dB");
    volumeSlider.addListener (this);
    volumeSlider.setTopLeftPosition(3,181);
    volumeSlider.setSize(30,192);
    volumeSlider.setColour(Slider::ColourIds::thumbColourId, Colour(0xff90470c));
    
    // Adding a strip label
    addAndMakeVisible(stripLabel);
    stripLabel.setText(String(pChan->getId()) + ".", NotificationType::dontSendNotification);
    stripLabel.setTopLeftPosition(2,375);
    stripLabel.setSize(55,19);
    stripLabel.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    stripLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    
    
}

ChannelStrip::~ChannelStrip()
{
}

/** 
* Adds ChannelStrip::Listener for ChannelStrip events
* \param l listener to be added
*/
void ChannelStrip::addListener(ChannelStrip::Listener* const l) {
    channelStripListeners.add(l);
}


/** 
* Removes ChannelStrip::Listener for ChannelStrip events
* \param l listener to be removed
*/
void ChannelStrip::removeListener(ChannelStrip::Listener* const l) {
    channelStripListeners.remove(l);
}


/**
* Event handler to paint things.
*/
void ChannelStrip::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colour(0xff262626));   // clear the background

    g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    /*g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("ChannelStrip", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text*/
}


/**
* Event handler for when the component is being resized.
*/
void ChannelStrip::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


/**
* Event handler for changed sliders
*/
void ChannelStrip::sliderValueChanged (Slider* slider) {
    if (slider == &volumeSlider) {
        try {
            pChannel->setVolume(slider->getValue());
        }
        catch(const char* s) {
            std::cerr << "set Volume Error: " << s << std::endl;
        }
    }
    else if (slider == &panSlider) {
        try {
            char v = slider->getValue();
            pChannel->setPan(v*6.35);
        }
        catch(const char* s) {
            std::cerr << "set Volume Error: " << s << std::endl;
        }
    }
}


/**
* Click handler for all the buttons
* \todo Make phase button functional
* \todo Make solo button functional
*/
void ChannelStrip::buttonClicked (Button* button) {
    if (button == &muteToggle) {
        pChannel->setMuteOn(button->getToggleState());
    }
    else if (button == &phaseToggle) {
        pChannel->setPhaseOn(button->getToggleState());
    }
    else if (button == &eqToggle) {
        pChannel->setEQLowOn(button->getToggleState());
        pChannel->setEQLowMidOn(button->getToggleState());    
        pChannel->setEQHiMidOn(button->getToggleState());
        pChannel->setEQHiOn(button->getToggleState());
    }
    else if (button == &selToggle) {
        // In case the user tries to disengage the button
        // manually, we re-set it to being pushed.
        // Otherwise we'd risk some weird state
        if (!selToggle.getToggleState()) {
            selToggle.setToggleState(true, dontSendNotification);
        }
        else {
            // Request the EQ pannel to show this channel's
            // parameters
            sendEQRequest();
        }
    }
    else if (button == &soloToggle) {
        // In case the user tries to disengage the button
        // manually, we re-set it to being pushed.
        // Otherwise we'd risk some weird state
        if (!soloToggle.getToggleState()) {
            soloToggle.setToggleState(true, dontSendNotification);
        }
        else {
            // Request the EQ pannel to show this channel's
            // parameters
            sendSoloRequest();
        }
    }
}


/**
* Sets the EQ button's state to toggle on
*/
void ChannelStrip::engageSelButton() {
    selToggle.setToggleState(true, dontSendNotification);
}


/**
* Sets the EQ button's state to toggle off
*/
void ChannelStrip::disengageSelButton() {
    selToggle.setToggleState(false, dontSendNotification);
}


/**
* Sends out an eqRequested to all compatible listeners in order
* to tell MainComponent, that this object wants to show its 
* EQ and compressor parameters on the ChannelEQ panel.
*/
void ChannelStrip::sendEQRequest() {
    Component::BailOutChecker checker (this);

    if (! checker.shouldBailOut())
        channelStripListeners.callChecked (checker, &Listener::eqRequested, this);
}


/**
* Sends out an soloRequested to all compatible listeners in order
* to tell MainComponent, that this object wants to show its 
* EQ and compressor parameters on the ChannelEQ panel.
*/
void ChannelStrip::sendSoloRequest() {
    Component::BailOutChecker checker (this);

    if (! checker.shouldBailOut())
        channelStripListeners.callChecked (checker, &Listener::soloRequested, this);
}


/**
* Getter function to return the associated CChannelStrip object.
*/
CChannelStrip* ChannelStrip::getCChannelStrip() { return pChannel; }

