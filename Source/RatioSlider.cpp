#include "../JuceLibraryCode/JuceHeader.h"
#include "QSlider.h"

/**
* Standard constructor.
*/
QSlider::QSlider(std::vector<float> q) : EQSlider()
{
    qList = q;
    setRange(0, qList.size()-1, 1);
}

QSlider::~QSlider()
{
}

void QSlider::paint (Graphics& g)
{
    Slider::paint(g);

}

void QSlider::resized()
{
    Slider::resized();
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

String QSlider::getTextFromValue(double value) {
    if (value < qList.size()) {
        double v = qList[(int)value];
        return String::formatted("%.2f", v);
    }
    return String("unk");
}

double QSlider::getValue() {
    double v = Slider::getValue();
    if( v < 0 || v > qList.size())
        return 0;
    
    return (double)qList[(int)v];
}

void QSlider::setValue(float v) {
    for (int i = 0 ; i < qList.size() ; i++) {
        if (qList[i] == v) {
            Slider::setValue(i);
            std::cerr << "Setting default value " << std::to_string(v) << std::endl;
            return;
        }    
    }
    Slider::setValue(0);
}
