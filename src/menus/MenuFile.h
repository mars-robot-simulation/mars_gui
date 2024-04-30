#pragma once

#include "MainGUIDefs.h"

#include <main_gui/MenuInterface.h>

#include <string>

namespace lib_manager
{
    class LibManager;
}

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

        /**
         * \brief MenuFile creates the menus and menu items in the File menu of the simulation.
         */
        class MenuFile :  public main_gui::MenuInterface
        {

        public:

            /** \brief The constructor adds the actions to the File menu */
            MenuFile(interfaces::ControlCenter *c, main_gui::GuiInterface *gui,
                     std::string resPath, lib_manager::LibManager *theManager);
            ~MenuFile();

            /**
             * \brief Called whenever a menu item is selected.
             * \param action The action that is passed to the GuiInterface
             * via addGenericMenuAction function.
             * \param checked Indicates if the menu/menu item is checked or not.
             */
            virtual void menuAction(int action, bool checked = false);

        private:

            lib_manager::LibManager *libManager;
            main_gui::GuiInterface *mainGui;
            interfaces::ControlCenter *control;

            void menu_exportScene();
            void menu_openPlugin();
            void menu_openSceneFile();
            void menu_saveSceneFile();
            void menu_resetScene();
            void menu_newScene();
            void menu_saveGraph();

        };

    } // end of namespace gui
} // end of namespace mars
