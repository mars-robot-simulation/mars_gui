#include "config.h"
#include "MarsGui.h"

#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/sim/SimulatorInterface.h>

#include <main_gui/GuiInterface.h>
#include <main_gui/MainGUI.h>
#include <main_gui/MyQMainWindow.h>

#include "MenuFile.h"
#include "MenuAdd.h"
#include "MenuSimulation.h"
#include "MenuWindow.h"

using namespace std;

namespace mars
{
    namespace gui
    {

        MarsGui::MarsGui(lib_manager::LibManager *theManager) : MarsGuiInterface(theManager),
                                                                control(NULL), gui(NULL)
        {
            menuFile   = NULL;
            menuAdd    = NULL;
            menuSim    = NULL;
            menuWindow = NULL;
        }

        MarsGui::~MarsGui()
        {
            if(control)
            {
                libManager->releaseLibrary("mars_core");
            }

            if(gui)
            {
                libManager->releaseLibrary("main_gui");
            }
            if(menuFile) delete menuFile;
            if(menuAdd) delete menuAdd;
            if(menuSim) delete menuSim;
            if(menuWindow) delete menuWindow;
            fprintf(stderr, "Delete mars_gui\n");
        }


        void MarsGui::setupGui()
        {
            interfaces::SimulatorInterface *sim;
            sim =libManager->getLibraryAs<interfaces::SimulatorInterface>("mars_core");
            if(sim)
            {
                control = sim->getControlCenter();
            }

            gui = libManager->getLibraryAs<main_gui::GuiInterface>("main_gui");
            if(!gui)
            {
                fprintf(stderr, "No main_gui lib found!\n");
            }

            resourcesPath.propertyType = cfg_manager::stringProperty;
            resourcesPath.propertyIndex = 0;
            resourcesPath.sValue = MARS_GUI_DEFAULT_RESOURCES_PATH;

            if(control && gui)
            {
                if(control->cfg)
                {
                    configPath = control->cfg->getOrCreateProperty("Config", "config_path",
                                                                   string(MARS_GUI_DEFAULT_RESOURCES_PATH));

                    string loadFile = configPath.sValue;
                    loadFile.append("/mars_Gui.yaml");
                    control->cfg->loadConfig(loadFile.c_str());

                    resourcesPath = control->cfg->getOrCreateProperty("MarsGui", "resources_path",
                                                                      "");
                    if(resourcesPath.sValue == "")
                    {
                        resourcesPath.sValue = MARS_GUI_DEFAULT_RESOURCES_PATH;
                    }

                    main_gui::MainGUI *mainGui;
                    if((mainGui = dynamic_cast<main_gui::MainGUI*>(gui)))
                    {
                        mainGui->mainWindow_p()->setWindowIcon(QIcon(":/images/mars_icon.ico"));

                        mainGui->addGenericMenuAction("../File/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Edit/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Control/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../View/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Data/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Tools/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Plugins/", 0, NULL, 0, "", 0, 0);
                        mainGui->addGenericMenuAction("../Options/", 0, NULL, 0, "", 0, 0);
                    }

                    /*
                      if (marsStyle.bValue) {
                      qApp->setStyle(new MarsStyle(resourcesPath.sValue+"/styles"));
                      }
                    */
                }

                menuFile = new MenuFile(control, gui, resourcesPath.sValue, libManager);
                menuAdd = new MenuAdd(control, gui, resourcesPath.sValue, libManager);
                menuSim = new MenuSimulation(control, gui, resourcesPath.sValue);
                menuWindow = new MenuWindow(control, gui);
            }
        }

        void MarsGui::cfgUpdateProperty(cfg_manager::cfgPropertyStruct _property)
        {

            if(_property.paramId == marsStyle.paramId)
            {
                /*        if (_property.bValue)
                          QApplication::setStyle(new MarsStyle(resourcesPath.sValue+"/styles"));
                          else
                          QApplication::setStyle(new QPlastiqueStyle);
                */
                return;
            }
        }
    } // end of namespace gui
} // end of namespace mars

DESTROY_LIB(mars::gui::MarsGui);
CREATE_LIB(mars::gui::MarsGui);

