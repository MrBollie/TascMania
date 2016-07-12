/*
  ==============================================================================

    RouteComponent.h
    Created: 8 Jul 2016 12:40:42pm
    Author:  rajan

  ==============================================================================
*/

#ifndef ROUTECOMPONENT_H_INCLUDED
#define ROUTECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CRouting.h"

//==============================================================================
/*
*/
class RouteComponent    : public Component,
                            public ComboBox::Listener
{
public:
    RouteComponent(CRouting*);
    ~RouteComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;

private:
    CRouting *pRouting;
    ComboBox outCombos[8];
    Label outLabels[8];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RouteComponent)
};


#endif  // ROUTECOMPONENT_H_INCLUDED
