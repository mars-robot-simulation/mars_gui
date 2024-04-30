#pragma once

#include "MainGUIDefs.h"

#include <main_gui/MenuInterface.h>
#include <configmaps/ConfigData.h>

#include <string>
#include <QObject>

class QLineEdit;
class QWidget;
class QLabel;
class QComboBox;
class QVBoxLayout;
class QGridLayout;
class QPushButton;

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
         * \brief MenuAdd creates the menus and menu items in the File menu of the simulation.
         */
        class MenuAdd :  public QObject, public main_gui::MenuInterface
        {
            Q_OBJECT
        public:

            /** \brief The constructor adds the actions to the File menu */
            MenuAdd(interfaces::ControlCenter *c, main_gui::GuiInterface *gui,
                    std::string resPath, lib_manager::LibManager *theManager);
            ~MenuAdd();

            /**
             * \brief Called whenever a menu item is selected.
             * \param action The action that is passed to the GuiInterface
             * via addGenericMenuAction function.
             * \param checked Indicates if the menu/menu item is checked or not.
             */
            virtual void menuAction(int action, bool checked = false);

        private slots:
            void addObject();
            void selectFile();

        private:

            lib_manager::LibManager *libManager;
            main_gui::GuiInterface *mainGui;
            interfaces::ControlCenter *control;
            configmaps::ConfigMap material, defaultLight;
            QWidget *widgetAdd;
            QLabel *addLabel, *comboLabel1, *comboLabel2, *comboLabel3, *label3;
            QLineEdit *addLineEdit, *addLineEdit2;
            QPushButton *openFile;
            QGridLayout *gridLayout;
            QVBoxLayout *vLayout;
            QComboBox *combo1, *combo2, *combo3;
            int addType;

            void menu_addBox(const std::string &name);
            void menu_addSphere(const std::string &name);
            void menu_addPlane(const std::string &name);
            void menu_addMaterial(const std::string &name);
            void menu_addLight(const std::string &name);
            void menu_addMotor(const std::string &name);
            void menu_addJoint(const std::string &name);
            void menu_addMesh(const std::string &name);

        };

    } // end of namespace gui
} // end of namespace mars
