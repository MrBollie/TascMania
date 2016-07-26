#ifndef CHANNELSTRIP_H_INCLUDED
#define CHANNELSTRIP_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CChannelStrip.h"

/**
* GUI class representing a channel strip.
* It contains various buttons and sliders, that 
* affect the channel.
*/
class ChannelStrip    : public Component,
                        public Slider::Listener,
                        public Button::Listener
{
public:

    ChannelStrip(CChannelStrip*);
    ~ChannelStrip();

    /**
    * Listener class for eqRequests
    */
    class Listener {
        public:
            virtual ~Listener() {}
            /**
            * Event handler for requests about 
            * showing a ChannelStrip's paraemters
            * on the ChannelEQ panel.
            * \param strip that requested the claim
            */
            virtual void eqRequested(ChannelStrip*) {}
            virtual void compRequested(ChannelStrip*) = 0;
    };

    void addListener(Listener*);
    void removeListener(Listener*);

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button*) override;
    void disengageSelButton();
    void engageSelButton();

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
