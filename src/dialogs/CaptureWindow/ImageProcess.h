#pragma once

#include <QThread>
#include <QMutex>
#include <vector>

namespace mars
{
    namespace gui
    {

        struct myImage
        {
            void *data;
            int width;
            int height;
        };

        class ImageProcess : public QThread
        {
        public:
            ImageProcess(QString folder, int framerate);
            ~ImageProcess();
            void addImage(myImage image);
            int getState(void) {return state;}
            int getPercent(void) {return percent;}

        protected:
            void run(void);
  
        private:
            QMutex listMutex;
            std::vector<myImage> imageList;
            bool processing;
            QString folder, file;
            int imageCount;
            int state;
            int percent;
            int file_count;
            int width, height;
            int framerate;
        };

    } // end of namespace gui
} // end of namespace mars
