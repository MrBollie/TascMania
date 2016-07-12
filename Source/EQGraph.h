/*
  ==============================================================================

    EQGraph.h
    Created: 9 Jul 2016 7:25:18pm
    Author:  rajan

  ==============================================================================
*/

#ifndef EQGRAPH_H_INCLUDED
#define EQGRAPH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class EQGraph    : public Component
{
public:
    EQGraph();
    ~EQGraph();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQGraph)
};


#endif  // EQGRAPH_H_INCLUDED
