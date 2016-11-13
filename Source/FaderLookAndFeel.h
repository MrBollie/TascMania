#ifndef FADERLOOKANDFEEL_H_INCLUDED
#define FADERLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class FaderLookAndFeel : public LookAndFeel_V3 {
public:
    FaderLookAndFeel();
    virtual ~FaderLookAndFeel();

    void drawLinearSliderThumb (Graphics &, int x, int y, int width, int height, 
        float sliderPos, float minSliderPos, float maxSliderPos, 
        const Slider::SliderStyle, Slider &);


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaderLookAndFeel);
};

#endif  // FADERLOOKANDFEEL_H_INCLUDED
