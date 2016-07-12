/*
  ==============================================================================

    EQSlider.h
    Created: 10 Jul 2016 12:59:20am
    Author:  rajan

  ==============================================================================
*/

#ifndef EQSLIDER_H_INCLUDED
#define EQSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class EQSlider    : public Slider
{
public:
    EQSlider();
    ~EQSlider();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQSlider)
};

#endif  // EQSLIDER_H_INCLUDED
