/*
  ==============================================================================

    EQSlider.cpp
    Created: 10 Jul 2016 12:59:20am
    Author:  rajan

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "EQSlider.h"

//==============================================================================
EQSlider::EQSlider() : Slider(RotaryVerticalDrag, TextBoxRight)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(80,50);
    setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colour(0xffafafaf));
    setColour(Slider::ColourIds::textBoxBackgroundColourId, Colour(0xff262626));
    setColour(Slider::ColourIds::textBoxTextColourId, Colour(0xffdadada));
    setColour(Slider::ColourIds::rotarySliderFillColourId, Colour(0xffb9b7b4));

}

EQSlider::~EQSlider()
{
}

void EQSlider::paint (Graphics& g)
{
    Slider::paint(g);

}

void EQSlider::resized()
{
    Slider::resized();
    // This method is where you should set the bounds of any child
    // components that your component contains..

}