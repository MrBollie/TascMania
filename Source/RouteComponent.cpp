/*
  ==============================================================================

    RouteComponent.cpp
    Created: 8 Jul 2016 12:40:42pm
    Author:  rajan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "RouteComponent.h"

//==============================================================================
RouteComponent::RouteComponent(CRouting *pr)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    pRouting = pr;
    
    setSize(223,212);
    for (int i = 0 ; i < 8 ; i++) {
        
        // Labels
        Label *pl = &outLabels[i];
        addAndMakeVisible(pl);
        pl->setText(String("Output ") + std::to_string(i+1), 
            NotificationType::dontSendNotification);
        pl->setSize(68,25);
        pl->setTopLeftPosition(1,i*25+5);
        pl->setColour(Label::ColourIds::textColourId, Colours::white);
        
        // Output combos
        ComboBox *pc = &outCombos[i];
        addAndMakeVisible(pc);       
        pc->addListener(this);
        pc->setName(std::to_string(i+1));
        pc->addItem("Master L", 1);
        pc->addItem("Master R", 2);
        pc->addItem("Computer 1", 3);
        pc->addItem("Computer 2", 4);
        pc->addItem("Computer 3", 5);
        pc->addItem("Computer 4", 6);
        pc->addItem("Computer 5", 7);
        pc->addItem("Computer 6", 8);
        pc->addItem("Computer 7", 9);
        pc->addItem("Computer 8", 10);
        
        pc->setSize(150,25);
        pc->setTopLeftPosition(70,i*25+5);
    }

}

RouteComponent::~RouteComponent()
{
}

void RouteComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colour(0xff000000));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
}

void RouteComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void RouteComponent::comboBoxChanged(ComboBox* pComboBox) {
    try {
        pRouting->setOutput(pComboBox->getName().getIntValue(), 
            pComboBox->getText().toStdString());
    }
    catch(const char* s) {
        std::cerr << "Error: " << s << std::endl;
    }
}
