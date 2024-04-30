#pragma once

#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {

        /**
         *Dialog for rescaling the environment
         * every node in the environment is rescaled (including its position)
         */

        class Dialog_Rescale_Environment: public main_gui::BaseWidget,
                                          public main_gui::PropertyCallback
        {
            Q_OBJECT
        public:
            /**\brief Creates the Dialog */
            Dialog_Rescale_Environment(interfaces::ControlCenter *c, main_gui::GuiInterface *gui);
            ~Dialog_Rescale_Environment();

            main_gui::PropertyDialog* pDialog;
            void show(void) {pDialog->show();}
            void hide(void) {pDialog->hide();}
            bool isHidden(void) {return pDialog->isHidden();}
            void close(void) {pDialog->close();}

        private slots:

            virtual void accept();
            virtual void reject();
            virtual void valueChanged(QtProperty* property, const QVariant& value);
            void closeDialog();

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;
            QtVariantProperty *x_factor, *y_factor, *z_factor;

        };

    } // end of namespace gui
} // end of namespace mars
