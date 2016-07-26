/*
  ==============================================================================

    EQGraph.cpp
    Created: 9 Jul 2016 7:25:18pm
    Author:  rajan
    
    Just a stub for now, as I have no idea, how to do it. ;)

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EQGraph.h"

//==============================================================================
EQGraph::EQGraph()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 194);

}

EQGraph::~EQGraph()
{
}

void EQGraph::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

    g.setColour (Colours::white);
    g.drawRect (10, 5, 185, 120);   // draw an outline around the component

    // Gain Lines
    g.setColour (Colours::grey);
    g.drawLine(9, 35, 194, 35, 1);
    g.drawLine(9, 65, 194, 65, 1);
    g.drawLine(9, 95, 194, 95, 1);

    g.setColour (Colours::white);
    g.setFont (8.0f);
    g.drawText ("+12", 0, 0, 10, 10,
                Justification::right, true);   
    g.drawText ("+6", 0, 30, 10, 10,
                Justification::right, true);   
    g.drawText ("0", 0, 60, 10, 10,
                Justification::right, true);   
    g.drawText ("-6", 0, 90, 10, 10,
                Justification::right, true);   
    g.drawText ("-12", 0, 120, 10, 10,
                Justification::right, true);
}

void EQGraph::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
