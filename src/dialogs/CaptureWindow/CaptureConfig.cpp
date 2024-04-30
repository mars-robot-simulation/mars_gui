#include "CaptureConfig.h"

#include <cstdio>

#include <QDateTime>
#include <QDir>

#include <mars_interfaces/graphics/GraphicsManagerInterface.h>

namespace mars
{
    namespace gui
    {

        CaptureConfig::CaptureConfig(interfaces::ControlCenter *c)
        {
            control = c;
            gw = 0;
            gc = 0;
            capturing = capture = false;
            frame_rate = 15;
            win_id = 0;
            imageProcess = 0;
        }

        CaptureConfig::~CaptureConfig()
        {
            if(capture) stopCapture();
            while(isRunning()) msleep(10);
        }
  
        void CaptureConfig::setWindowID(unsigned long id)
        {
            gw = control->graphics->get3DWindow(id);
  
            win_id = id;
        }

        void CaptureConfig::startCapture(void)
        {
            if(imageProcess == 0)
            {
                capture = true;
                this->start();
                capturing = true;
            }
        }

        void CaptureConfig::stopCapture(void)
        {
            capture = false;
        }

        QString CaptureConfig::getState(void)
        {
            QString r_state;
            int state;

            if(imageProcess)
            {
                state = imageProcess->getState();
                switch(state)
                {
                case 1:
                    r_state.append("is capturing");
                    break;
                case 2:
                    r_state.append("wait for finishing");
                    break;
                case 3:
                    r_state.setNum(imageProcess->getPercent());
                    r_state.append(" \% of post process");
                    break;
                };
            }
            return r_state;
        }

        void CaptureConfig::run(void)
        {

            // init capture
            QString logFolder, num;
            void *data;
            int width, height;
            myImage newImage;
  
            logFolder = QDateTime().currentDateTime().toString("yyyy_MM_dd_hh_mm");
            logFolder.append("_win_");
            num.setNum(win_id);
            logFolder.append(num);

            // create dir
            if(QDir().mkdir(logFolder))
            {
                fprintf(stderr, "created folder: %s\n",
                        qPrintable(logFolder));
                if(gw) gw->setGrabFrames(true);
                imageProcess = new ImageProcess(logFolder, frame_rate);
            } else
            {
                fprintf(stderr, "error while creating folder\n");
                capture = false;
            }

            // update capture
            while(capture)
            {
                if(gw)
                {
                    data = 0;
                    gw->getImageData(&data, width, height);
                    if(data)
                    {
                        newImage.data = data;
                        newImage.width = width;
                        newImage.height = height;
                        imageProcess->addImage(newImage);
                    }
                }
                msleep(1000/frame_rate);
            }

            // deinit capture
            if(gw) gw->setGrabFrames(false);
            delete imageProcess;
            imageProcess = 0;
            capturing = false;
        }

    } // end of namespace gui
} // end of namespace mars
