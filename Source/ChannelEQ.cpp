#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelEQ.h"

/**
* Constructor for the channel EQ component.
* \param pC ChannelStrip that is selected.
*/
ChannelEQ::ChannelEQ(CChannelStrip *pC)
{
    pChannel = pC;
    setSize(959, 198);
    
    // Adding EQ Graph
    addAndMakeVisible(&eqGraph);
    eqGraph.setTopLeftPosition(2, 2);

    // Gain Label
    addAndMakeVisible(&gainLabel);
    gainLabel.setText("Gain", dontSendNotification);
    gainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    gainLabel.setTopLeftPosition(300, 1);
    gainLabel.setSize(50,20);

    // Freq Label
    addAndMakeVisible(&freqLabel);
    freqLabel.setText("Freq", dontSendNotification);
    freqLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    freqLabel.setTopLeftPosition(400, 1);
    freqLabel.setSize(50,20);
    
    // Adding hi gain slider
    addAndMakeVisible(hiGainSlider);
    hiGainSlider.setRange(-12,12,0.1);
    hiGainSlider.setTopLeftPosition(300,22);
    hiGainSlider.addListener(this);
    addAndMakeVisible(hiGainLabel);
    hiGainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    hiGainLabel.setText("Hi", dontSendNotification);
    hiGainLabel.attachToComponent(&hiGainSlider, true);

    // Adding hi mid gain slider
    addAndMakeVisible(hiMidGainSlider);
    hiMidGainSlider.setRange(-12,12,0.1);
    hiMidGainSlider.setTopLeftPosition(300,52);
    hiMidGainSlider.addListener(this);
    addAndMakeVisible(hiMidGainLabel);
    hiMidGainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    hiMidGainLabel.setText("Hi Mid", dontSendNotification);
    hiMidGainLabel.attachToComponent(&hiMidGainSlider, true);

    // Adding low mid gain slider
    addAndMakeVisible(lowMidGainSlider);
    lowMidGainSlider.setRange(-12,12,0.1);
    lowMidGainSlider.setTopLeftPosition(300,82);
    lowMidGainSlider.addListener(this);
    addAndMakeVisible(lowMidGainLabel);
    lowMidGainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    lowMidGainLabel.setText("Low Mid", dontSendNotification);
    lowMidGainLabel.attachToComponent(&lowMidGainSlider, true);

    // Adding low gain slider
    addAndMakeVisible(lowGainSlider);
    lowGainSlider.setRange(-12,12,0.1);
    lowGainSlider.setTopLeftPosition(300,112);
    lowGainSlider.addListener(this);
    addAndMakeVisible(lowGainLabel);
    lowGainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    lowGainLabel.setText("Low", dontSendNotification);
    lowGainLabel.attachToComponent(&lowGainSlider, true);


    // Adding hi freq slider
    pHiFreqSlider = new FreqSlider(pChannel->getEQHiFreqList());
    addAndMakeVisible(pHiFreqSlider);
    pHiFreqSlider->setTopLeftPosition(400,22);
    pHiFreqSlider->addListener(this);

    // Adding hi mid freq slider
    pHiMidFreqSlider = new FreqSlider(pChannel->getEQLowFreqList());
    addAndMakeVisible(pHiMidFreqSlider);
    pHiMidFreqSlider->setTopLeftPosition(400,52);
    pHiMidFreqSlider->addListener(this);

    // Adding low mid freq slider
    pLowMidFreqSlider = new FreqSlider(pChannel->getEQHiMidFreqList());
    addAndMakeVisible(pLowMidFreqSlider);
    pLowMidFreqSlider->setTopLeftPosition(400,82);
    pLowMidFreqSlider->addListener(this);

    // Adding low freq slider
    pLowFreqSlider = new FreqSlider(pChannel->getEQLowFreqList());
    addAndMakeVisible(pLowFreqSlider);
    pLowFreqSlider->setTopLeftPosition(400,112);
    pLowFreqSlider->addListener(this);
    
    // Adding hi mid Q slider
    pHiMidQSlider = new QSlider(pChannel->getEQLowMidQList());
    addAndMakeVisible(pHiMidQSlider);
    pHiMidQSlider->setTopLeftPosition(500,52);
    pHiMidQSlider->addListener(this);

    // Adding low mid Q slider
    pLowMidQSlider = new QSlider(pChannel->getEQLowMidQList());
    addAndMakeVisible(pLowMidQSlider);
    pLowMidQSlider->setTopLeftPosition(500,82);
    pLowMidQSlider->addListener(this);

    // Adding LCF button
    addAndMakeVisible(&lcfButton);
    lcfButton.setSize(40,30);
    lcfButton.setTopLeftPosition(530,120);
    lcfButton.setButtonText("LCF");
    lcfButton.setColour(TextButton::ColourIds::buttonColourId, Colour(0xff797979));
    lcfButton.setColour(TextButton::ColourIds::buttonOnColourId, Colour(0xffd2e00a));
    lcfButton.setClickingTogglesState(true);

    /******************
    * Compressor
    */
    
    // Adding threshold slider
    addAndMakeVisible(&compThresholdSlider);
    compThresholdSlider.setRange(-32,0);
    compThresholdSlider.setTopLeftPosition(860,2);
    compThresholdSlider.addListener(this);
    compThresholdLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    compThresholdLabel.setText("Threshold", dontSendNotification);
    compThresholdLabel.attachToComponent(&compThresholdSlider, true);

    // Adding ratio slider
    pCompRatioSlider = new RatioSlider(pChannel->getCompRatioList());
    addAndMakeVisible(pCompRatioSlider);
    pCompRatioSlider->setTopLeftPosition(860,32);
    pCompRatioSlider->addListener(this);
    compRatioLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    compRatioLabel.setText("Ratio", dontSendNotification);
    compRatioLabel.attachToComponent(pCompRatioSlider, true);

    // Adding Gain slider
    addAndMakeVisible(compGainSlider);
    compGainSlider.setRange(0,20);
    compGainSlider.setTopLeftPosition(860,62);
    compGainSlider.addListener(this);
    compGainLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    compGainLabel.setText("Gain", dontSendNotification);
    compGainLabel.attachToComponent(&compGainSlider, true);

    // Adding Attack slider
    addAndMakeVisible(compAttackSlider);
    compAttackSlider.setRange(2,200);
    compAttackSlider.setTopLeftPosition(860,92);
    compAttackSlider.addListener(this);
    compAttackLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    compAttackLabel.setText("Attack", dontSendNotification);
    compAttackLabel.attachToComponent(&compAttackSlider, true);

    // Adding Release slider
    addAndMakeVisible(compReleaseSlider);
    compReleaseSlider.setRange(10,1000);
    compReleaseSlider.setTopLeftPosition(860,122);
    compReleaseSlider.addListener(this);
    compReleaseLabel.setColour(Label::ColourIds::textColourId, Colours::white);
    compReleaseLabel.setText("Release", dontSendNotification);
    compReleaseLabel.attachToComponent(&compReleaseSlider, true);

    // Everything is set up, now load the channels values
    reloadValues();  
}

ChannelEQ::~ChannelEQ()
{
    delete pLowFreqSlider;
    delete pLowMidFreqSlider;
    delete pHiMidFreqSlider;
    delete pHiFreqSlider;
    delete pLowMidQSlider;
    delete pHiMidQSlider;
    delete pCompRatioSlider;
}

void ChannelEQ::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colour(0xff262626));   // clear the background
    g.setColour (Colours::grey);
}

void ChannelEQ::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


/**
* Event handler for a changed slider value.
* It updates the corresponding pChannel
*/
void ChannelEQ::sliderValueChanged(Slider* slider) {
    try {
        if (slider == pLowFreqSlider) {
            std::cerr << "Freq: " << std::to_string(((FreqSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Freq after cast:" << std::to_string((int)((FreqSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQLowFreq((unsigned int)((FreqSlider*)slider)->getValue());
        }
        else if (slider == pLowMidFreqSlider) {
            std::cerr << "Freq: " << std::to_string(((FreqSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Freq after cast:" << std::to_string((int)((FreqSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQLowMidFreq((unsigned int)((FreqSlider*)slider)->getValue());
        }
        else if (slider == pHiMidFreqSlider) {
            std::cerr << "Freq: " << std::to_string(((FreqSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Freq after cast:" << std::to_string((int)((FreqSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQHiMidFreq((unsigned int)((FreqSlider*)slider)->getValue());
        }
        else if (slider == pHiFreqSlider) {
            std::cerr << "Freq: " << std::to_string(((FreqSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Freq after cast:" << std::to_string((int)((FreqSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQHiFreq((unsigned int)((FreqSlider*)slider)->getValue());
        }
        else if (slider == pLowMidQSlider) {
            std::cerr << "Q: " << std::to_string(((QSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Q after cast:" << std::to_string((float)((QSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQLowMidQ((float)((QSlider*)slider)->getValue());
        }
        else if (slider == pHiMidQSlider) {
            std::cerr << "Q: " << std::to_string(((QSlider*)slider)->getValue()) << std::endl;
            std::cerr << "Q after cast:" << std::to_string((float)((QSlider*)slider)->getValue()) << std::endl;
            pChannel->setEQHiMidQ((float)((QSlider*)slider)->getValue());
        }
        else if (slider == &lowGainSlider) {
            std::cout << "Low Gain Slider" << std::endl;
            pChannel->setEQLowGain(slider->getValue());
        }
        else if (slider == &lowMidGainSlider) {
            pChannel->setEQLowMidGain(slider->getValue());
        }
        else if (slider == &hiMidGainSlider) {
            pChannel->setEQHiMidGain(slider->getValue());
        }
        else if (slider == &hiGainSlider) {
            pChannel->setEQHiGain(slider->getValue());
        }
    }
    catch (const char *c) {
        std::cerr << "Error: " << c << std::endl;
    }
}

/**
* Assigns a channel strip to this EQ and reload its 
* parameters
*/
void ChannelEQ::setChannelStrip(CChannelStrip *pC) {
    pChannel = pC;
    reloadValues();
}


/**
* Reloads values from CChannelStrip object
*/
void ChannelEQ::reloadValues() {

    // Frequencies
    pLowFreqSlider->setValue(pChannel->getEQLowFreq());
    pLowMidFreqSlider->setValue(pChannel->getEQLowMidFreq());
    pHiMidFreqSlider->setValue(pChannel->getEQHiMidFreq());
    pHiFreqSlider->setValue(pChannel->getEQHiFreq());

    // Gains
    lowGainSlider.setValue(pChannel->getEQLowGain());
    lowMidGainSlider.setValue(pChannel->getEQLowMidGain());
    hiMidGainSlider.setValue(pChannel->getEQHiMidGain());
    hiGainSlider.setValue(pChannel->getEQHiGain());

    // Qs
    pLowMidQSlider->setValue(pChannel->getEQLowMidQ());
    pHiMidQSlider->setValue(pChannel->getEQHiMidQ());

    // Comp
    compThresholdSlider.setValue(pChannel->getCompThreshold());
    compAttackSlider.setValue(pChannel->getCompThreshold());
    compGainSlider.setValue(pChannel->getCompThreshold());
    compReleaseSlider.setValue(pChannel->getCompThreshold());
    pCompRatioSlider->setValue(pChannel->getCompRatio());
}
