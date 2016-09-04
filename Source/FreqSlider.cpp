#include "../JuceLibraryCode/JuceHeader.h"
#include "FreqSlider.h"


/**
* Constructor accepting a vector of allowed frequencies.
* \param f Vector of permitted frequencies.
*/
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


/**
* Overriden method, that returns the string to be displayed on the little
* label besides the slider.
* It's being used to create a mapping.
* \param value Internal value of the slider.
*/
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


/**
* Overriden method to return the mapped value.
*/
double FreqSlider::getValue() {
    double v = Slider::getValue();
    if( v < 0 || v > freqList.size())
        return 0;
    
    return (double)freqList[(int)v];
}


/**
* Overriden method to set a mapped value.
* \param v mapped value
*/
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
