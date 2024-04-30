#pragma once

#include "MainGUIDefs.h"
#include "BlenderExportGUI.h"
#include "ControllerConfigGUI.h"
#include <main_gui/MenuInterface.h>

#include <sstream>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {

        class CameraConfigurator;
        class CaptureWindow;

        /**
         * \brief MenuWindow creates the menus and menu items in the Window menu of the simulation.
         */
        class MenuWindow :  public QObject, public main_gui::MenuInterface,
                            public cfg_manager::CFGClient
        {

            Q_OBJECT

        public:

            /** \brief The constructor add the actions to the Window menu */
            MenuWindow(interfaces::ControlCenter *c, main_gui::GuiInterface *gui);
            ~MenuWindow();

            /**
             * \brief Called whenever a menu item is selected.
             * \param action The action that is passed to the GuiInterface
             * via addGenericMenuAction function.
             * \param checked Indicates if the menu/menu item is checked or not.
             */
            virtual void menuAction(int action, bool checked = false);

            // CFGClient methods
            virtual void cfgUpdateProperty(cfg_manager::cfgPropertyStruct _property);

        private:
            void menu_addWindow();
            void menu_dock(bool checked);
            void menu_blender();
            void menu_controller_config();

            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;

            BlenderExportGUI *blender;
            ControllerConfigGUI *cc;
            cfg_manager::cfgPropertyStruct cfgVisRep, cfgShowCoords, cfgShowGrid;
            cfg_manager::cfgPropertyStruct cfgShowContacts, cfgShowSelection;
            bool updateProp;
            CameraConfigurator *cameraConfigurator;
            CaptureWindow *captureWindow;

        private slots:
            void closeWidget(void* widget);

        };

    } // end of namespace gui
} // end of namespace mars
