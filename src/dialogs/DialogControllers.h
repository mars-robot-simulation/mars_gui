#pragma once

#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/graphics/GraphicsEventClient.h>
#include "ControllerHandler.h"

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {


        class DialogControllers : public main_gui::BaseWidget,
                                  public main_gui::PropertyCallback
        {
            Q_OBJECT

        public:
            DialogControllers(interfaces::ControlCenter *c,
                              main_gui::GuiInterface *gui);
            ~DialogControllers();

            main_gui::PropertyDialog *pDialog;

            void show(void) {pDialog->show();}
            void hide(void) {pDialog->hide();}
            bool isHidden(void) {return pDialog->isHidden();}
            void close(void) {pDialog->close();}

        private:
            virtual void topLevelItemChanged(QtProperty* current);
            virtual void valueChanged(QtProperty *property, const QVariant &value);

            QtProperty *oldFocus;
            bool filled;
            QPushButton *addButton;
            QPushButton *removeButton;
            std::vector<ControllerHandler*> allDialogs;
            std::vector<ControllerHandler*> newDialogs;
            std::vector<QtProperty*> allControllers_p;
            std::vector<QtProperty*> newControllers_p;
            std::vector<interfaces::core_objects_exchange> allControllers;
            interfaces::ControlCenter* control;
            main_gui::GuiInterface *mainGui;

        private slots:
            void on_new_controller();
            void on_remove_controller();
            void on_add_controller();
            // selection of objects for the focused controller
            void on_nodes_selection();
            void on_sensors_selection();
            void on_motors_selection();
            void closeDialog();
        };

    } // end of namespace gui
} // end of namespace mars
