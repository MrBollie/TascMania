/*
  ==============================================================================

    MasterStrip.h
    Created: 8 Jul 2016 5:14:56pm
    Author:  rajan

  ==============================================================================
*/

#ifndef MASTERSTRIP_H_INCLUDED
#define MASTERSTRIP_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MasterStrip    : public Component,
                        public Slider::Listener,
                        public Button::Listener
{
public:
    MasterStrip();
    ~MasterStrip();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button*) override;    

private:
    Slider volumeSlider;
    TextButton muteToggle;

    Label stripLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterStrip)
};


#endif  // MASTERSTRIP_H_INCLUDED
