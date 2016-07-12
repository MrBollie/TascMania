/*
  ==============================================================================

    ChannelStrip.h
    Created: 8 Jul 2016 10:32:08am
    Author:  rajan

  ==============================================================================
*/

#ifndef CHANNELSTRIP_H_INCLUDED
#define CHANNELSTRIP_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CChannelStrip.h"

//==============================================================================
/*
*/
class ChannelStrip    : public Component,
                        public Slider::Listener,
                        public Button::Listener
{
public:

    ChannelStrip(CChannelStrip*);
    ~ChannelStrip();

    class Listener {
        public:
            virtual ~Listener() {}
            virtual void eqRequested(ChannelStrip*) {}
            virtual void compRequested(ChannelStrip*) = 0;
    };

    void addListener(Listener*);
    void removeListener(Listener*);

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button*) override;
    CChannelStrip* getCChannelStrip();

private:
    ListenerList<Listener> channelStripListeners;
    CChannelStrip *pChannel;

    Component *pMain;
    
    Slider volumeSlider;
    Slider panSlider;

    TextButton selToggle; 
    TextButton phaseToggle;    
    TextButton compToggle;
    TextButton eqToggle;
    TextButton muteToggle;
    TextButton soloToggle;
    
    Label stripLabel;

    void sendEQRequest();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStrip)
};


#endif  // CHANNELSTRIP_H_INCLUDED
