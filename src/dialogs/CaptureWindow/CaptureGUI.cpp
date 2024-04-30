#include "CaptureGUI.h"

namespace mars
{
    namespace gui
    {

        CaptureGUI::CaptureGUI(interfaces::ControlCenter* c)  :
            main_gui::BaseWidget(0, c->cfg, "CaptureGUI"),
            pDialog(new main_gui::PropertyDialog(NULL))
        {
            control = c;
            camera = 0;
            first_camera = true;
            take_events = false;
            filled = false;

            pDialog->setAttribute(Qt::WA_DeleteOnClose);
            pDialog->setWindowTitle(tr("Capture Window"));
            pDialog->setPropCallback(dynamic_cast<PropertyCallback*>(this));
            pDialog->setButtonBoxVisibility(false);

            QStringList enumNames;
            std::map<QString, QVariant> attr;
            attr.insert(std::pair<QString, QVariant>(QString::fromStdString("singleStep"), 1.0));
            attr.insert(std::pair<QString, QVariant>(QString::fromStdString("minimum"), 0.0));
 

            status = pDialog->addGenericProperty("../State", QVariant::String, "Not capturing!");
            status->setEnabled(false);  
            winIDCombo = pDialog->addGenericProperty("../Window", QtVariantPropertyManager::enumTypeId(),
                                                     QVariant(0), NULL, &enumNames);
            frameBox = pDialog->addGenericProperty("../Frame Rate", QVariant::Double, 0.0, &attr);
            capture = pDialog->addGenericProperty("../Capture", QVariant::Bool, false);

            startTimer(500);
            take_events = true;
            filled = true;
            update_frame_box = false;
        }

        CaptureGUI::~CaptureGUI(void)
        {
        }

        void CaptureGUI::accept() {}
        void CaptureGUI::reject() {}

        void CaptureGUI::valueChanged(QtProperty *property, const QVariant &value)
        {
            if(filled == false) return;
 
            if(property == winIDCombo)
                cameraSelected(value.toInt());
            else if(property == frameBox)
                setFrameRate(value.toDouble());
            else if(property == capture)
                (value.toBool()) ? startCapture() : stopCapture();
        }


        void CaptureGUI::cameraSelected(int index)
        {
            camera = index;
            update_frame_box = true;
            updateGUI();
        }

        void CaptureGUI::setFrameRate(double frameRate)
        {
            cameras[camera]->setFrameRate(frameRate);
        }

        void CaptureGUI::startCapture(void)
        {
            if(!cameras[camera]->isCapturing())
            {
                cameras[camera]->startCapture();
                update_frame_box = true;
                updateGUI();
            }
        }

        void CaptureGUI::stopCapture(void)
        {
            cameras[camera]->stopCapture();
            updateGUI();
        }

        void CaptureGUI::updateGUI(void)
        {
            if(camera < cameras.size() && take_events)
            {
                take_events = false;
                if(update_frame_box) frameBox->setValue(cameras[camera]->getFrameRate());
                update_frame_box = false;
                bool capturing = cameras[camera]->isCapturing();

                if(capturing)
                    status->setValue(cameras[camera]->getState());
                else 
                    status->setValue(tr("Not capturing"));
   
                take_events = true;
            }
        }

        void CaptureGUI::addCamera(CaptureConfig* camera)
        {
            QStringList enumNames = winIDCombo->attributeValue("enumNames").toStringList();
            char text[255];
            //generate name for label
            sprintf(text, "WinID: %lu", camera->getWindowID());
            // insert into select box
            enumNames << QString(text);
            winIDCombo->setAttribute("enumNames", enumNames);
            // and push_back to list
            cameras.push_back(camera);
            if(first_camera)
            {
                timerEvent(0);
                updateGUI();
                first_camera = false;
            }
        }

        void CaptureGUI::removeCamera(CaptureConfig* camera)
        {
            unsigned int i = 0;
            std::vector<CaptureConfig*>::iterator iter;
            QStringList enumNames = winIDCombo->attributeValue("enumNames").toStringList();
            bool found;

            // first find the correct index
            for(iter=cameras.begin(); iter!=cameras.end(); ++iter, ++i)
                if((*iter) == camera) break;

            if(iter!=cameras.end())
            {
                // we have the camera in the list and can remove it
                cameras.erase(iter);
                // select box remove i
                found = false;
                if(this->camera == i)
                {
                    found = true;
                    this->camera = 0;
                }
                enumNames.removeAt(i);
                winIDCombo->setAttribute("enumNames", enumNames);
                if(found) winIDCombo->setValue(this->camera);
            }
        }

        void CaptureGUI::timerEvent(QTimerEvent* event)
        {
            (void)event;
            updateGUI();
        }

    } // end of namespace gui
} // end of namespace mars
