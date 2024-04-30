#pragma once

#include <mars_interfaces/sim/ControlCenter.h>

#include <QThread>

#include "ImageProcess.h"

namespace mars
{

    namespace interfaces
    {
        class GraphicsCameraInterface;
        class GraphicsWindowInterface;
    }

    namespace gui
    {

        class CaptureConfig : public QThread
        {
            Q_OBJECT

        public:
            CaptureConfig(interfaces::ControlCenter *c);
            ~CaptureConfig();
  
            void setWindowID(unsigned long id);
            inline unsigned long getWindowID(void) {return win_id;}
            void setFrameRate(int frame_rate) {this->frame_rate = frame_rate;}
            inline int getFrameRate(void) {return frame_rate;}
            void startCapture(void);
            void stopCapture(void);
            bool isCapturing(void) {return capturing;}
            QString getState(void);

        protected:
            void run(void);

        private:
            interfaces::ControlCenter* control;
            interfaces::GraphicsWindowInterface *gw;
            interfaces::GraphicsCameraInterface* gc;
            ImageProcess *imageProcess;
            bool capture, capturing;
            int frame_rate;
            std::vector<myImage> imageList;

            unsigned long win_id;
        };

    } // end of namespace gui
} // end of namespace mars
