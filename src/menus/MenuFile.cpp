#include "MenuFile.h"

#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/sim/SimulatorInterface.h>
#include <main_gui/GuiInterface.h>
#include <lib_manager/LibManager.hpp>
#include <QtGui>

#include <QMessageBox>
#include <QFileDialog>

namespace mars
{
    namespace gui
    {

        /**
         * \brief MenuFile creates the menus and menu items in the File menu of the simulation.
         */
        MenuFile::MenuFile(interfaces::ControlCenter *c,
                           main_gui::GuiInterface *gui, std::string resPath,
                           lib_manager::LibManager *theManager)
            : libManager(theManager), mainGui(gui), control(c)
        {

            std::string tmp1;

            tmp1 = resPath + "/images";
            tmp1.append("/open_scene.png");
            mainGui->addGenericMenuAction("../File/Open", GUI_ACTION_OPEN_SCENE,
                                          (main_gui::MenuInterface*)this, 0, tmp1, true);

            tmp1 = resPath + "/images";
            tmp1.append("/new_scene.png");
            mainGui->addGenericMenuAction("../File/Clear Simulation", GUI_ACTION_NEW_SCENE,
                                          (main_gui::MenuInterface*)this, 0, tmp1, true);


            tmp1 = resPath + "/images";
            tmp1.append("/reset.png");
            mainGui->addGenericMenuAction("../File/Reset Simulation", GUI_ACTION_RESET_SCENE,
                                          (main_gui::MenuInterface*)this, 0, tmp1, true);

            tmp1 = resPath + "/images";
            tmp1.append("/save_scene.png");
            mainGui->addGenericMenuAction("../File/Export/MARS Scene", GUI_ACTION_SAVE_SCENE,
                                          (main_gui::MenuInterface*)this, 0, tmp1, true);

            mainGui->addGenericMenuAction("../File/Save Graph", GUI_ACTION_SAVE_GRAPH,
                                          (main_gui::MenuInterface*)this, 0, tmp1, true);


            // add separator
            mainGui->addGenericMenuAction("../File/", 0, NULL, 0, "", 0, -1);

            mainGui->addGenericMenuAction("../File/Export/OSG-OBJ Model", GUI_ACTION_EXPORT_SCENE,
                                          (main_gui::MenuInterface*)this, 0);

        }

        MenuFile::~MenuFile()
        {

        }

        void MenuFile::menuAction(int action, bool checked)
        {
            (void)checked;
            switch (action)
            {
            case GUI_ACTION_OPEN_SCENE: menu_openSceneFile(); break;
            case GUI_ACTION_SAVE_SCENE: menu_saveSceneFile(); break;
            case GUI_ACTION_RESET_SCENE: menu_resetScene(); break;
            case GUI_ACTION_NEW_SCENE: menu_newScene(); break;
            case GUI_ACTION_EXPORT_SCENE: menu_exportScene(); break;
            case GUI_ACTION_SAVE_GRAPH: menu_saveGraph(); break;
            }
        }

        void MenuFile::menu_exportScene(void)
        {
            control->sim->exportScene();
        }

        void MenuFile::menu_resetScene(void)
        {
            control->sim->resetSim();
        }

        void MenuFile::menu_newScene(void)
        {
            switch (QMessageBox::information( 0, "Simulation", "WARNING:\n"
                                              "All Objects will be deleted!",
                                              "OK", "Cancel", 0, // OK == button 0
                                              1) ) // Cancel == button 1
            {
            case 0: //OK clicked, delete all stuff
                //graphicsFactory->reset();
                control->sim->newWorld(true);
                break;
            case 1: // Cancel clicked, Alt-C or Escape pressed
                // don't exit
                break;
            }
        }


        /**
         * opens a saved file
         */
        void MenuFile::menu_openSceneFile()
        {
            const char *fileTypes =
                "All supported files (*.scn *.zip *.scene *.smurf *smurfs *.svg *.zsmurf *.zsmurfs *.urdf)"
                ";;MARS zipped scene files (*.scn *.zip)"
                ";;MARS scene files (*.scene)"
                ";;URDF files (*.urdf)"
                ";;SMURF files (*.smurf)"
                ";;zipped SMURF files (*.zsmurf)"
                ";;SMURF scene files (*.smurfs)"
                ";;SMURF svg scene (*.svg)"
                ";;zipped SMURF scene files (*.smurfs)"
                ";;YAML files (*.yaml *.yml)"
                ";;All files (*.*)";
            QString fileName = QFileDialog::getOpenFileName(0, "Open Scene", ".", fileTypes);

            if(fileName.isEmpty())
                return;
            bool wasrunning = false;
            if(control->sim->isSimRunning())
            {
                control->sim->startStopTrigger();
                wasrunning = true;
            }
            control->sim->loadScene(fileName.toStdString(), false);
            if(wasrunning) control->sim->startStopTrigger();
        }

        /**
         * saves a scene
         */
        void MenuFile::menu_saveSceneFile()
        {
            //graphicsFactory->saveScene("scene.obj");
            bool wasRunning = false;
            if(control->sim->isSimRunning())
            {
                control->sim->startStopTrigger();
                wasRunning = true;
            }

            QString fileName = QFileDialog::getSaveFileName(0, "Save File",
                                                            "../",
                                                            "MARS Scene Files (*.scn)");
            if(fileName.isEmpty())
            {
                std::cout << "File Save: no file selected" << std::endl;
            } else
            {
                control->sim->saveScene(fileName.toStdString(), wasRunning);
                if(wasRunning)
                {
                    control->sim->startStopTrigger();
                }
            }

        }

        void MenuFile::menu_saveGraph()
        {
            QString fileName = QFileDialog::getSaveFileName(0, "Save File",
                                                            "../",
                                                            "Dot graph Files (*.dot)");

            if(fileName.isEmpty())
            {
                std::cout << "File Save: no file selected" << std::endl;
            } else
            {
                control->sim->saveGraph(fileName.toStdString());
            }
        }

    } // end of namespace gui
} // end of namespace mars
