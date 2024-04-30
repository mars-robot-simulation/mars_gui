#include "config.h"
#include "MenuSimulation.h"

#include <main_gui/GuiInterface.h>

#include <mars_interfaces/sim/SimulatorInterface.h>
#include <mars_interfaces/sim/MotorManagerInterface.h>
#include <mars_interfaces/sim/NodeManagerInterface.h>

#include <QMessageBox>

namespace mars
{
    namespace gui
    {

        MenuSimulation::MenuSimulation(interfaces::ControlCenter* c,
                                       main_gui::GuiInterface *gui,
                                       std::string resPath) : control(c),
                                                              mainGui(gui)
        {

            dc = NULL; // controllers

            daf = NULL; // dialog add force
            dat = NULL; // dialog apply torque

            dd = NULL; // distance
            nst = NULL; // selection
            dmc = NULL; // motor control

            dre = NULL; // dialog rescale environment


            std::string tmp1;

            tmp1 = resPath + "/images";
            tmp1.append("/play_button.png");
            mainGui->addGenericMenuAction("../Control/Start", GUI_ACTION_SIM_START,
                                          (main_gui::MenuInterface*)this,
                                          'R', tmp1, true);

            tmp1 = resPath + "/images";
            tmp1.append("/pause_button.png");
            mainGui->addGenericMenuAction("../Control/Pause", GUI_ACTION_SIM_PAUSE,
                                          (main_gui::MenuInterface*)this,
                                          'P', tmp1, true);

            tmp1 = resPath + "/images";
            tmp1.append("/step_button.png");
            mainGui->addGenericMenuAction("../Control/Single Step",
                                          GUI_ACTION_SIM_STEP,
                                          (main_gui::MenuInterface*)this,
                                          'T', tmp1, true);

            // add separator
            mainGui->addGenericMenuAction("../Control/", 0, NULL, 0, "", 0, -1);
            mainGui->addGenericMenuAction("../Control/Motor Control",
                                          GUI_ACTION_MOTOR_CONTROL,
                                          (main_gui::MenuInterface*)this, 0);
            mainGui->addGenericMenuAction("../Control/", 0, NULL, 0, "", 0, -1);


            //mainGui->addGenericMenuAction("../Simulation/", 0, NULL, 0, "", 0, -1); // separator
            mainGui->addGenericMenuAction("../Control/Apply Force",
                                          GUI_ACTION_APPLY_FORCE,
                                          (main_gui::MenuInterface*)this, 0);
            mainGui->addGenericMenuAction("../Control/Apply Torque",
                                          GUI_ACTION_APPLY_TORQUE,
                                          (main_gui::MenuInterface*)this, 0);
            mainGui->addGenericMenuAction("../Tools/Rescale Environment",
                                          GUI_ACTION_RESCALE_ENV,
                                          (main_gui::MenuInterface*) this, 0);

            tmp1 = resPath + "/images";
            tmp1.append("/mesh.png");

            if(control->cfg)
            {
                resourcesPath = control->cfg->getOrCreateProperty("MarsGui", "resources_path",
                                                                  "").sValue;
                if(resourcesPath == "")
                {
                    resourcesPath = MARS_GUI_DEFAULT_RESOURCES_PATH;
                }
            }

            mainGui->addGenericMenuAction("../Deprecated/Controllers",
                                          GUI_ACTION_CONTROLLER_TREE,
                                          (main_gui::MenuInterface*)this,
                                          QKeySequence("CTRL+O")[0]);

            mainGui->addGenericMenuAction("../Tools/Object Distance",
                                          GUI_ACTION_DISTANCE,
                                          (main_gui::MenuInterface*)this, 0);
            resourcesPath.append("/images");
        }


        MenuSimulation::~MenuSimulation()
        {
        }

        void MenuSimulation::menuAction(int action, bool checked)
        {
            (void)checked;

            switch (action)
            {
            case GUI_ACTION_CONTROLLER_TREE: menu_controllers(); break;
            case GUI_ACTION_DISTANCE: menu_distance(); break;
            case GUI_ACTION_MOTOR_CONTROL:  menu_motorControl(); break;
            case GUI_ACTION_APPLY_FORCE: menu_applyForce(); break;
            case GUI_ACTION_APPLY_TORQUE: menu_applyTorque(); break;
            case GUI_ACTION_RESCALE_ENV: menu_rescaleEnvironment(); break;
            case GUI_ACTION_SIM_START:
                control->sim->StartSimulation();
                /*
                  if(!(control->sim->isSimRunning()))
                  control->sim->startStopTrigger();
                */
                break;
            case GUI_ACTION_SIM_PAUSE:
                control->sim->StopSimulation();
                /*
                  if(control->sim->isSimRunning())
                  control->sim->startStopTrigger();
                */
                break;
            case GUI_ACTION_SIM_STEP:
                if(!(control->sim->isSimRunning()))
                    control->sim->singleStep();
                break;
            default: break;
            }
        }

        void MenuSimulation::menu_controllers()
        {
            if(dc != NULL)
            {
                if(dc->pDialog)
                    dc->pDialog->close();
                delete dc;
                dc = NULL;
            }
            dc = new DialogControllers(control, mainGui);
            //mainGui->addDockWidget(dc->pDialog);
            dc->show();
        }

        void MenuSimulation::menu_rescaleEnvironment()
        {
            //if dialog already exists close it and delete its memory
            if(dre != NULL)
            {
                if(dre->pDialog)
                    dre->pDialog->close();
                delete dre;
                dre = NULL;
            }
            if(control->nodes->getNodeCount() > 0)
            {
                //create new dialog and show it
                dre = new Dialog_Rescale_Environment(control, mainGui);
                //mainGui->addDockWidget((void*)dre->pDialog);
                dre->show();
            } else
            {
                QMessageBox::information( 0, "Simulation",
                                          "Please create a node before starting the environment rescaling",
                                          "OK", 0); // ok == button 0
            }

        }

        void MenuSimulation::menu_motorControl()
        {
            if(dmc != NULL)
            {
                dmc->close();
            } else
            {
                if(control->motors->getMotorCount() <= 0)
                {
                    QMessageBox::information(0, "Simulation",
                                             "Create a motor first!", "OK", 0);
                    return;
                }

                dmc = new Dialog_Motor_Control(control);
                //mainGui->addDockWidget((void*)dmc);
                connect(dmc, SIGNAL(closeSignal(void*)),
                        this, SLOT(closeWidget(void*)));
                dmc->show();
            }
        }

        void MenuSimulation::menu_distance()
        {
            if(dd != NULL)
            {
                dd->close();
            } else
            {
                dd = new DialogDistance(control);
                //mainGui->addDockWidget(dd);
                connect(dd, SIGNAL(closeSignal(void*)),
                        this, SLOT(closeWidget(void*)));
                dd->show();
            }
        }

        void MenuSimulation::menu_applyForce()
        {
            //close and delete existing dialog
            if(daf != NULL)
            {
                if(daf->pDialog)
                    daf->pDialog->close();
                delete daf;
                daf = NULL;
            }
            if(control->nodes->getNodeCount() > 0)
            {
                // create new dialog
                daf = new Dialog_Add_Force(control, mainGui);
                //mainGui->addDockWidget((void*)daf->pDialog);
                daf->show();
            } else
            {
                QMessageBox::information(0, "Simulation", "Please create a node first",
                                         "OK", 0); // ok == button 0
            }
        }


        void MenuSimulation::menu_applyTorque()
        {
            //close and delete existing dialog
            if(dat != NULL)
            {
                if(dat->pDialog)
                    dat->pDialog->close();
                delete dat;
                dat = NULL;
            }
            if(control->nodes->getNodeCount() > 0)
            {
                // create new dialog
                dat = new Dialog_Add_Torque(control, mainGui);
                //mainGui->addDockWidget((void*)dat->pDialog);
                dat->show();
            } else
            {
                QMessageBox::information(0, "Simulation", "Please create a node first",
                                         "OK", 0); // ok == button 0
            }
        }

        void MenuSimulation::closeWidget(void* widget)
        {
            void **toClose = NULL;

            if(widget == dd) toClose = (void**)&dd;
            else if(widget == nst) toClose = (void**)&nst;
            else if(widget == dmc) toClose = (void**)&dmc;

            if(toClose && *toClose)
            {
                mainGui->removeDockWidget(*toClose);
                if(*toClose)
                {
                    delete (QObject*)*toClose;
                    *toClose = NULL;
                }
            }

        }

    } // end of namespace gui
} // end of namespace mars
