#ifndef RATIOSLIDER_H_INCLUDED
#define RATIOSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQSlider.h"
#include <vector>

/**
* Custom control for compressor ratio.
*/
class RatioSlider    : public EQSlider
{
public:
    RatioSlider(std::vector<float>);
    ~RatioSlider();

    void paint (Graphics&) override;
    void resized() override;
    double getValue();
    void setValue(float);
    String getTextFromValue(double value) override;

private:
    std::vector<float> ratioList;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RatioSlider)
};


#endif  // RATIOSLIDER_H_INCLUDED
