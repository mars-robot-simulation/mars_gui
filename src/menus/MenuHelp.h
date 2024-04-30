#pragma once

#include "MainGUIDefs.h"
#include <mars_interfaces/sim/ControlCenter.h>
#include "AboutDialog.h"

#include <main_gui/MenuInterface.h>
#include <main_gui/GuiInterface.h>

#include <QtGui>

namespace mars
{
    namespace gui
    {

        /**
         * \brief MenuHelp is the part of the menu bar that manages the help dialogs
         * \todo provide meaningful about and help dialogs; not implemented yet
         */
        class MenuHelp :  public main_gui::MenuInterface
        {

        public:
            /** \brief The constructor adds the actions to the Remove menu */
            MenuHelp(interfaces::ControlCenter *c, main_gui::GuiInterface *gui);
            ~MenuHelp();

            virtual void menuAction(int action, bool checked = false);

        protected:
            // All these functions open the appropriate dialog
            void menu_about();
            void menu_aboutQt();

        private:
            AboutDialog *da;

        };

    } // end of namespace gui
} // end of namespace mars
