/*
  ==============================================================================

    ChannelEQ.h
    Created: 8 Jul 2016 4:45:14pm
    Author:  rajan

  ==============================================================================
*/

#ifndef CHANNELEQ_H_INCLUDED
#define CHANNELEQ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQGraph.h"
#include "CChannelStrip.h"
#include "FreqSlider.h"
#include "RatioSlider.h"
#include "QSlider.h"

/**
* This class represents the EQ panel, that will will displayed in the top area
* of the control center main window. Channels can be assigned to it by pressing
* their sel buttons.
* \todo Add a LCF button
* \todo Add compressor to it
*/
class ChannelEQ    : public Component,
                    public Slider::Listener
{
public:
    ChannelEQ(CChannelStrip*);
    ~ChannelEQ();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void setChannelStrip(CChannelStrip*);

private:
    CChannelStrip *pChannel;

    EQGraph eqGraph;
    Label lowGainLabel;
    Label lowMidGainLabel;
    Label hiMidGainLabel;
    Label hiGainLabel;
    
    Label freqLabel; 
    Label gainLabel;

    EQSlider lowGainSlider;
    EQSlider lowMidGainSlider;
    EQSlider hiMidGainSlider;
    EQSlider hiGainSlider;
    
    FreqSlider *pLowFreqSlider;
    FreqSlider *pLowMidFreqSlider;
    FreqSlider *pHiMidFreqSlider;
    FreqSlider *pHiFreqSlider;
    
    Label lowMidQLabel;
    Label hiMidQLabel;

    QSlider *pLowMidQSlider;
    QSlider *pHiMidQSlider;

    TextButton lcfButton;

    // Compressor
    Label compThresholdLabel;
    Label compRatioLabel;
    Label compAttackLabel;
    Label compReleaseLabel;
    Label compGainLabel;

    EQSlider compThresholdSlider;
    RatioSlider *pCompRatioSlider;
    EQSlider compAttackSlider;
    EQSlider compReleaseSlider;
    EQSlider compGainSlider;

    void reloadValues();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelEQ)
};


#endif  // CHANNELEQ_H_INCLUDED
