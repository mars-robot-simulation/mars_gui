#pragma once

#include <mars_interfaces/gui/MarsGuiInterface.h>
#include <cfg_manager/CFGManagerInterface.h>

namespace mars
{

    namespace interfaces
    {
        class ControlCenter;
    }

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {
        class MenuAdd;
        class MenuFile;
        class MenuSimulation;
        class MenuWindow;

        /**
         * \brief Sets up the main gui of the simulation and handles various generic gui options.
         */
        class MarsGui : public interfaces::MarsGuiInterface,
                        public cfg_manager::CFGClient
        {

        public:
            MarsGui(lib_manager::LibManager *theManager);
            virtual ~MarsGui();

            // LibInterface methods
            int getLibVersion() const {return 1;}
            const std::string getLibName() const {return std::string("mars_gui");}
            CREATE_MODULE_INFO();

            virtual void cfgUpdateProperty(cfg_manager::cfgPropertyStruct _property);

            void setupGui();

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *gui;
            cfg_manager::cfgPropertyStruct resourcesPath;
            cfg_manager::cfgPropertyStruct configPath;
            cfg_manager::cfgPropertyStruct cfgW_top, cfgW_left, cfgW_height, cfgW_width;
            cfg_manager::cfgPropertyStruct marsStyle;
            cfg_manager::cfgPropertyStruct dockStyle;
            cfg_manager::cfgPropertyStruct stateNamesProp, dockArea, dockFloat, dockLeft, dockTop, dockWidth, dockHeight;
            MenuAdd *menuAdd;
            MenuFile *menuFile;
            MenuSimulation *menuSim;
            MenuWindow *menuWindow;

        };

    } // end of namespace gui
} // end of namespace mars
