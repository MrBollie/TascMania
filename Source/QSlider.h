/*
  ==============================================================================

    QSlider.h
    Created: 10 Jul 2016 12:06:45am
    Author:  rajan

  ==============================================================================
*/

#ifndef QSLIDER_H_INCLUDED
#define QSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQSlider.h"
#include <vector>

//==============================================================================
/*
*/
class QSlider    : public EQSlider
{
public:
    QSlider(std::vector<float>);
    ~QSlider();

    void paint (Graphics&) override;
    void resized() override;
    double getValue();
    void setValue(float);
    String getTextFromValue(double value) override;

private:
    std::vector<float> qList;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QSlider)
};


#endif  // QSLIDER_H_INCLUDED
