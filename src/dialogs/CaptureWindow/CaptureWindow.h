#pragma once

#include <QTimer>
#include <QMutex>

#include "CaptureGUI.h"
#include <main_gui/MenuInterface.h>
#include <mars_interfaces/graphics/GraphicsUpdateInterface.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {

        class CaptureWindow : public QTimer, main_gui::MenuInterface,
                              interfaces::GraphicsUpdateInterface
        {
            Q_OBJECT

        public:
            CaptureWindow(interfaces::ControlCenter* c, main_gui::GuiInterface *gui);
            ~CaptureWindow();

            virtual void menuAction(int action, bool checked = false);
            virtual void preGraphicsUpdate(void);

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;
            CaptureGUI* myWidget;
            std::vector<CaptureConfig*> cameras;
            QMutex myMutex;

            bool init;

        protected slots:
            void closeWidget(void);
            void timerEvent(QTimerEvent* event);

        };

    } // end of namespace gui
} // end of namespace mars
