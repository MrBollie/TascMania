#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterStrip.h"
#include "MainWindow.h"

/**
* Constructor for the master strip component.
* Sets up all the controls.
*/
MasterStrip::MasterStrip()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(59, 519);

    // Adding Mute button
    addAndMakeVisible(muteToggle);
    muteToggle.addListener(this);
    muteToggle.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    muteToggle.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xff6f0202));
    muteToggle.setTopLeftPosition(2,189);
    muteToggle.setSize(50,25);
    muteToggle.setClickingTogglesState(true);
    muteToggle.setName("Mute");
    muteToggle.setButtonText("M");
    
    // Adding the main fader
    addAndMakeVisible (volumeSlider);
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    volumeSlider.setRange (-128, 6,1);
    volumeSlider.setTextValueSuffix (" dB");
    volumeSlider.addListener (this);
    volumeSlider.setTopLeftPosition(3,276);
    volumeSlider.setSize(30,192);
    volumeSlider.setColour(Slider::ColourIds::thumbColourId, Colour(0xff90470c));    
    
    // Adding a strip label
    addAndMakeVisible(stripLabel);
    stripLabel.setText("Master", NotificationType::dontSendNotification);
    stripLabel.setTopLeftPosition(2,470);
    stripLabel.setSize(55,19);
    stripLabel.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    stripLabel.setColour(Label::ColourIds::textColourId, Colours::black);
}

MasterStrip::~MasterStrip()
{
}

void MasterStrip::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colour(0xff262626));   // clear the background

    g.setColour (Colours::grey);
 
}

void MasterStrip::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void MasterStrip::sliderValueChanged (Slider* slider) {
}

void MasterStrip::buttonClicked (Button* button) {

}
