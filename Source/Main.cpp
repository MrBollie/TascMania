#include <unistd.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "RouteWindow.h"
#include "CTascamUSB.h"
#include "CRouting.h"


/**
* This class is the root for our application. It sets up the main and the route
* window and initializes the USB communication.
**/
class TascManiaApplication  : public JUCEApplication
{
public:
    TascManiaApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return false; }

    /**
    * Set up windows and the usb communication.
    */
    void initialise (const String& commandLine) override
    {
        pUSB = new CTascamUSB();
        try {
            pUSB->init();
        }
        catch(const char *s) {
            std::cerr << "Error: " << s << std::endl;
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon,
                "Error", s); 
        }
        pRouting = new CRouting(pUSB);
        routeWindow = new RouteWindow (getApplicationName(), pRouting);
        mainWindow = new MainWindow(getApplicationName(), pUSB, routeWindow);
    }

    /**
    * This method takes care of cleanly shutting down the application.
    */
    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
        routeWindow = nullptr; // (deletes our route window)
        
        delete pRouting;
        delete pUSB;
    }

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

private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<RouteWindow> routeWindow;   
    CTascamUSB *pUSB;
    CRouting *pRouting;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (TascManiaApplication)
