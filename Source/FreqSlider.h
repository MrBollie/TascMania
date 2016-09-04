#ifndef FREQSLIDER_H_INCLUDED
#define FREQSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQSlider.h"
#include <vector>

/**
* Custom Slider for the EQs frequencies ranges.
*/
class FreqSlider    : public EQSlider
{
public:
    FreqSlider(std::vector<unsigned int>);
    ~FreqSlider();

    void paint (Graphics&) override;
    void resized() override;
    double getValue();
    void setValue(unsigned int);
    String getTextFromValue(double value);

private:
    std::vector<unsigned int> freqList;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqSlider)
};


#endif  // FREQSLIDER_H_INCLUDED
