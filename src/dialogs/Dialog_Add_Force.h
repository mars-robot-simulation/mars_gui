#pragma once

#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/core_objects_exchange.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {


        /** \brief Adds a QDialog to set force to nodes */
        class Dialog_Add_Force : public main_gui::BaseWidget,
                                 public main_gui::PropertyCallback
        {
            Q_OBJECT

        public:
            /**\brief Creates the Dialog */
            Dialog_Add_Force(interfaces::ControlCenter* c, main_gui::GuiInterface *gui);
            ~Dialog_Add_Force();

            /** \brief return the address of the NodeList vector  */
            std::vector<interfaces::core_objects_exchange>* getNodeListPtr(void);

            main_gui::PropertyDialog* pDialog;
            void show(void) {pDialog->show();}
            void hide(void) {pDialog->hide();}
            bool isHidden(void) {return pDialog->isHidden();}
            void close(void) {pDialog->close();}

        private slots:

            /**\brief apply force to selected node */
            virtual void accept();
            virtual void reject();
            virtual void valueChanged(QtProperty*, const QVariant&) {}
            void closeDialog();

        private:
            std::vector<interfaces::core_objects_exchange> myNodes;
            interfaces::ControlCenter* control;
            main_gui::GuiInterface *mainGui;

            QtVariantProperty* vector_x;
            QtVariantProperty* vector_y;
            QtVariantProperty* vector_z;
            QtVariantProperty* magnitude;
            QtVariantProperty* node;

        };

    } // end of namespace gui
} // end of namespace mars
