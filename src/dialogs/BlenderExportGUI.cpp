#include "config.h"
#include "BlenderExportGUI.h"

#include <main_gui/GuiInterface.h>

#include <mars_interfaces/sim/NodeManagerInterface.h>
#include <mars_interfaces/core_objects_exchange.h>

#include <QHBoxLayout>

namespace mars
{
    namespace gui
    {

        BlenderExportGUI::BlenderExportGUI(interfaces::ControlCenter* c,
                                           main_gui::GuiInterface* gui) :
            main_gui::BaseWidget(0, c->cfg, "BlenderExportGUI"),
            pDialog(new main_gui::PropertyDialog(NULL))
        {

            control = c;
            mainGui = gui;

            state = 0;
            frame = 0;
            fileHandle = 0;

            this->setWindowTitle(tr("Blender Export"));

            QHBoxLayout *hLayout = new QHBoxLayout;
            this->setLayout(hLayout);
            hLayout->addWidget(pDialog);

            pDialog->setPropCallback(this);
            pDialog->setViewButtonVisibility(false);

            filename = pDialog->addGenericProperty("../Export to", VariantManager::filePathTypeId(), "");
            filename->setAttribute(QString::fromStdString("filter"), "QDIR"); // for choosing a directory
            filename->setAttribute(QString::fromStdString("directory"), "."); // open in current directory

            status = pDialog->addGenericProperty("../State", QVariant::String, "No file selected!");
            status->setEnabled(false);

            pDialog->clearButtonBox();
            pDialog->addGenericButton("Reset", this, SLOT(resetButton()));
            pDialog->addGenericButton("Start", this, SLOT(startButton()));
            pDialog->addGenericButton("Stop", this, SLOT(stopButton()));

            rPath = control->cfg->getOrCreateProperty("MarsGui", "resources_path",
                                                      "").sValue;
            if(rPath == "")
            {
                rPath = MARS_GUI_DEFAULT_RESOURCES_PATH;
            }
        }


        BlenderExportGUI::~BlenderExportGUI(void)
        {
            control->dataBroker->unregisterTimedReceiver(this, "*", "*",
                                                         "mars_sim/simTimer");
            delete pDialog;
            if(fileHandle) fclose(fileHandle);
        }

        void BlenderExportGUI::valueChanged(QtProperty* property,
                                            const QVariant& value)
        {

            if(property != filename) return;
            if(value.toString().isEmpty()) return;

            status->setValue("File to export selected!");
            state = 1;
        }

        void BlenderExportGUI::startButton(void)
        {
            if(state == 1)
            {
                if(fileHandle) fclose(fileHandle);
                std::string path = filename->value().toString().toStdString();
                std::string filename_str = path +std::string("/export.dat");
                if((fileHandle = fopen(filename_str.data(), "w")) == 0)
                {
                    status->setValue("Cannot open file. Aborted.");
                    status = 0;
                }
                control->nodes->exportGraphicNodesByID(path);
                std::string cmd = "cp "+rPath+"/blender/export.blend " + path;
                system(cmd.c_str());
                state = 2;
            }
            if(state == 2)
            {
                state = 3;
                writeGenericData(0, NULL);
                status->setValue(tr("Exporting started..."));
                control->dataBroker->registerTimedReceiver(this, "mars_sim", "simTime",
                                                           "mars_sim/simTimer", 40);
            }
        }

        void BlenderExportGUI::stopButton(void)
        {
            if(state == 3)
            {
                state = 2;
                status->setValue(tr("Exporting stopped."));
                control->dataBroker->unregisterTimedReceiver(this, "*", "*",
                                                             "mars_sim/simTimer");
            }
        }

        void BlenderExportGUI::resetButton(void)
        {
            state = 0;
            status->setValue(tr("No file selected!"));
            filename->setValue("");
        }

        void BlenderExportGUI::receiveData(const data_broker::DataInfo &info,
                                           const data_broker::DataPackage &dataPackage,
                                           int callbackParam)
        {
            writeGenericData(0, 0);
        }

        void BlenderExportGUI::writeGenericData(unsigned long id,
                                                void* data) const
        {
            (void)id;
            (void)data;
            if(state == 3)
            {
                std::vector<interfaces::core_objects_exchange> objectList;
                std::vector<interfaces::core_objects_exchange>::iterator iter;
                interfaces::NodeData theNode;
                utils::Quaternion q;
                utils::Vector pos;
                control->nodes->getListNodes(&objectList);

                fprintf(fileHandle, "frame %lu\n", frame++);

                for(iter=objectList.begin(); iter!=objectList.end(); ++iter)
                {
                    theNode = control->nodes->getFullNode((*iter).index);
                    q = (*iter).rot * theNode.visual_offset_rot;

                    //pos = QVRotate((*iter).rot, theNode.visual_offset_pos);
                    pos = ((*iter).rot * theNode.visual_offset_pos);
                    pos += (*iter).pos;
                    fprintf(fileHandle, "node%lu %g %g %g %g %g %g %g\n",
                            (*iter).index, pos.x(), pos.y(),
                            pos.z(), q.w(), q.x(), q.y(), q.z());
                }
            }
        }

        void BlenderExportGUI::closeEvent(QCloseEvent *event)
        {
            (void)event;
            emit closeSignal(this);
        }

    } // end of namespace gui
} // end of namespace mars
