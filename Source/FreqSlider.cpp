/*
  ==============================================================================

    FreqSlider.cpp
    Created: 10 Jul 2016 12:06:45am
    Author:  rajan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FreqSlider.h"

//==============================================================================
FreqSlider::FreqSlider(std::vector<unsigned int> f) : EQSlider()
{
    freqList = f;
    setRange(0, freqList.size()-1, 1);
}

FreqSlider::~FreqSlider()
{
}

void FreqSlider::paint (Graphics& g)
{
    Slider::paint(g);

}

void FreqSlider::resized()
{
    Slider::resized();
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

String FreqSlider::getTextFromValue(double value) {
    if (value < freqList.size()) {
        double v = freqList[(int)value];
        if (v > 1000) {
            v = v / 1000;
            return String::formatted("%.1fk", v);
        }
        return String::formatted("%.0f", v);
    }
    return String("unk");
}

double FreqSlider::getValue() {
    double v = Slider::getValue();
    if( v < 0 || v > freqList.size())
        return 0;
    
    return (double)freqList[(int)v];
}

void FreqSlider::setValue(unsigned int v) {
    for (int i = 0 ; i < freqList.size() ; i++) {
        if (freqList[i] == v) {
            Slider::setValue(i);
            std::cerr << "Setting default value " << std::to_string(v) << std::endl;
            return;
        }    
    }
    //Slider::setValue(0);
}
