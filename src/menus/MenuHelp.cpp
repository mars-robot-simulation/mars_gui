#include "MenuHelp.h"

#include <QMessageBox>

namespace mars
{
    namespace gui
    {

        MenuHelp::MenuHelp(interfaces::ControlCenter* c, main_gui::GuiInterface *gui)
        {

            da = NULL;
            gui->addGenericMenuAction("../Help/About", GUI_ACTION_HELP_ABOUT,
                                      (main_gui::MenuInterface*)this, 0);
            gui->addGenericMenuAction("../Help/About Qt", GUI_ACTION_HELP_ABOUT_QT,
                                      (main_gui::MenuInterface*)this, 0);
        }

        MenuHelp::~MenuHelp()
        {
            if(da!=NULL)
            {
                da->close();
                delete da;
            }
        }

        void MenuHelp::menuAction(int action, bool checked) 
        {
            switch (action)
            {
            case GUI_ACTION_HELP_ABOUT: menu_about(); break;
            case GUI_ACTION_HELP_ABOUT_QT: menu_aboutQt(); break;
            }
        }

        void MenuHelp::menu_about() 
        {
            if(da!=NULL)
            {
                da->close();
                delete da;
            }
            da = new AboutDialog(0);
            da->show();
            da->exec();
        }


        void MenuHelp::menu_aboutQt()
        {
            QMessageBox::aboutQt(0, "About Qt");
        }

    } // end of namespace gui
} // end of namespace mars
