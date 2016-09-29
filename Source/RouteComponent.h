#ifndef ROUTECOMPONENT_H_INCLUDED
#define ROUTECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CRouting.h"

/**
* Component that holds the UI for output routing.
*/
class RouteComponent    : public Component,
                            public ComboBox::Listener
{
public:
    RouteComponent(CRouting*, ApplicationProperties*);
    ~RouteComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;

private:
    ApplicationProperties *pApplicationProperties;
    CRouting *pRouting;
    ComboBox outCombos[8];
    Label outLabels[8];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RouteComponent)
};


#endif  // ROUTECOMPONENT_H_INCLUDED
