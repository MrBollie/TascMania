#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "CTascamUSB.h"
#include "RouteWindow.h"
#include "MainComponent.h"

/**
* This is the main window containing the mixer component
*/
class MainWindow    : public DocumentWindow
{
    public:
        MainWindow (String name, CTascamUSB *pUSB, RouteWindow *pR, 
            ApplicationProperties *pAppProperties);
        ~MainWindow();
        void closeButtonPressed() override;
        RouteWindow* getRouteWindow();

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        RouteWindow *pRouteWindow;
};
#endif  // MAIN_H_INCLUDED
