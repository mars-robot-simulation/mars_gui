#pragma once

#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include "NodeSelectionTree.h"

#include <QListWidget>

namespace mars
{
    namespace gui
    {

        /**
         * \brief Provides selection functionality displaying information about
         * distance between two objects. Changing the distance is also possible along
         * the distance vector originating from the first object's position.
         */
        class DialogDistance : public main_gui::BaseWidget,
                               public main_gui::PropertyCallback
        {

            Q_OBJECT

        public:
            /**\brief creates the dialog */
            DialogDistance(interfaces::ControlCenter *c);
            ~DialogDistance();

            main_gui::PropertyDialog *pDialog;

        private:
            std::vector<interfaces::core_objects_exchange> simNodes;
            std::vector<interfaces::core_objects_exchange> simJoints;

            std::vector<unsigned long> selectedNodes;
            std::vector<unsigned long> selectedJoints;
            utils::Vector direction, origin;
            interfaces::core_objects_exchange first, second;
            double original_distance;

            QListWidget *objectList;
            interfaces::ControlCenter* control;
            bool filled;

            QtVariantProperty* viewNodes, *viewJoints, *selection, *distance, *ap1, *ap2, *rp1, *rp2;

            void closeEvent(QCloseEvent *event);
            void updateProperties(void);
            void changeDistance(double new_dist);

        signals:
            void closeSignal(void*);

        private slots:
            virtual void valueChanged(QtProperty *property, const QVariant &value);
            void selectObjects();
        };

    } // end of namespace gui
} // end of namespace mars
