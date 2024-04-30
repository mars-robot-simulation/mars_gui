#pragma once

#include "MainGUIDefs.h"
#include <main_gui/MenuInterface.h>
#include <mars_interfaces/sim/ControlCenter.h>

#include "DialogControllers.h"

#include "DialogDistance.h"
#include "Dialog_Add_Force.h"
#include "Dialog_Add_Torque.h"
#include "Dialog_Rescale_Environment.h"
#include "Dialog_Motor_Control.h"

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
         * \brief Provides the Simulation and Control menu entries
         */
        class MenuSimulation :  public QObject, public main_gui::MenuInterface
        {
            Q_OBJECT

        public:
            MenuSimulation(interfaces::ControlCenter *c, main_gui::GuiInterface *gui,
                           std::string resPath);
            ~MenuSimulation();

            virtual void menuAction(int action, bool checked = false);

        protected:
            void menu_controllers(void);

            void menu_distance(void);
            void menu_selection(void);
            void menu_importMesh(void);
            void menu_applyForce(void);
            void menu_applyTorque(void);
            void menu_rescaleEnvironment();
            void menu_motorControl();

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;
            std::string resourcesPath;

            DialogControllers *dc;

            DialogDistance *dd;
            NodeSelectionTree *nst;
            Dialog_Add_Force *daf;
            Dialog_Add_Torque *dat;
            Dialog_Rescale_Environment *dre;
            Dialog_Motor_Control *dmc;

        private slots:
            void closeWidget(void* widget);
        };

    } // end of namespace gui
} // end of namespace mars
