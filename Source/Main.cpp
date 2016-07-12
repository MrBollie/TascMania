/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/
#include <unistd.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "RouteWindow.h"
#include "CTascamUSB.h"
#include "CRouting.h"


//==============================================================================
class TascManiaApplication  : public JUCEApplication
{
public:
    //==============================================================================
    TascManiaApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        try {
            pUSB = new CTascamUSB();
            
            pRouting = new CRouting(pUSB);
            routeWindow = new RouteWindow (getApplicationName(), pRouting);
            mainWindow = new MainWindow(getApplicationName(), pUSB, routeWindow);

        }
        catch(const char *s) {
            std::cerr << "Faild USB init: " << s << std::endl;
        }
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
        routeWindow = nullptr; // (deletes our route window)
        
        delete pRouting;
        delete pUSB;
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */

private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<RouteWindow> routeWindow;   
    CTascamUSB *pUSB;
    CRouting *pRouting;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (TascManiaApplication)
