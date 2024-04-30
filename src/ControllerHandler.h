#pragma once

#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/core_objects_exchange.h>
#include <mars_interfaces/ControllerData.h>

#include "SelectionDialog.h"

namespace mars
{
    namespace gui
    {

        namespace ControllerTree
        {

            enum Mode {
                PreviewMode,
                EditMode
            };

        } // end of namespace ControllerTree

        /**
         * \brief handles one controller in the simulation providing gui options.
         * Editing controlllers is not supported.
         */
        class ControllerHandler : public QObject
        {
            Q_OBJECT;
        public:

            ControllerHandler(QtVariantProperty* property, unsigned long ind,
                              main_gui::PropertyDialog *pd,
                              interfaces::ControlCenter *c,
                              ControllerTree::Mode m);
            ~ControllerHandler();

            void valueChanged(QtProperty *property, const QVariant &value) {}
            void accept();

            ControllerTree::Mode mode;

            void nodes_selection();
            void motors_selection();
            void sensors_selection();

        public slots:
            void choose_nodes(QString list);
            void choose_sensors(QString list);
            void choose_motors(QString list);


        private:
            std::vector<interfaces::core_objects_exchange> mySensors;
            std::vector<interfaces::core_objects_exchange> myMotors;
            std::vector<interfaces::core_objects_exchange> myNodes;
            std::vector<interfaces::core_objects_exchange> chosenSensors;
            std::vector<interfaces::core_objects_exchange> chosenMotors;
            std::vector<interfaces::core_objects_exchange> chosenNodes;
            interfaces::ControlCenter* control;

            interfaces::ControllerData myController;
            bool filled;
            QtVariantProperty *filename, *sensors, *motors, *nodes, *rate;
            SelectionDialog* motorDialog, *sensorDialog, *nodeDialog;

            QtVariantProperty *topLevelController;

            std::vector<interfaces::core_objects_exchange> allControllers;
            std::string controllerName;
            std::string actualName;
            int myControllerIndex;
            main_gui::PropertyDialog *pDialog;
            QColor previewColor;
            QColor editColor;

            void fill();

        }; // end of class ControllerHandler

    } // end of namespace gui
} // end of namespace mars
