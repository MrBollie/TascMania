#include "../JuceLibraryCode/JuceHeader.h"
#include "RatioSlider.h"

/**
* Standard constructor.
*/
RatioSlider::RatioSlider(std::vector<float> r) : EQSlider()
{
    ratioList = r;
    setRange(0, ratioList.size()-1, 1);
}

RatioSlider::~RatioSlider()
{
}

void RatioSlider::paint (Graphics& g)
{
    Slider::paint(g);

}

void RatioSlider::resized()
{
    Slider::resized();
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

String RatioSlider::getTextFromValue(double value) {
    if (value < ratioList.size()) {
        double v = ratioList[(int)value];
        if (v == 0) return "inf";
        return String::formatted("%.2f", v);
    }
    return String("unk");
}

float RatioSlider::getValue() {
    int v = Slider::getValue();
    if( v < 0 || v > ratioList.size())
        return 0;
    
    return (float)ratioList[(int)v];
}

void RatioSlider::setValue(float v) {
    for (int i = 0 ; i < ratioList.size() ; i++) {
        if (ratioList[i] == v) {
            Slider::setValue(i);
            std::cerr << "Setting default value " << std::to_string(v) << std::endl;
            return;
        }    
    }
    Slider::setValue(0);
}
