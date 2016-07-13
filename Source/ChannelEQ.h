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
#include "QSlider.h"

//==============================================================================
/*
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
    
    Label freqLabel[4]; 

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
    
    void formatSlider(Slider*);
    void reloadValues();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelEQ)
};


#endif  // CHANNELEQ_H_INCLUDED
