#pragma once

#include <QTimer>
#include <QMutex>

#include "CameraConfiguratorGUI.h"
#include <mars_interfaces/graphics/GraphicsUpdateInterface.h>


#include <main_gui/MenuInterface.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
        class MenuInterface;
    }

    namespace gui
    {

        class CameraConfigurator : public QTimer,
                                   public main_gui::MenuInterface,
                                   public interfaces::GraphicsUpdateInterface
        {
            Q_OBJECT

        public:
            CameraConfigurator(interfaces::ControlCenter* c,
                               main_gui::GuiInterface *mainGui);
            ~CameraConfigurator();

            virtual void menuAction(int action, bool checked = false);
            virtual void preGraphicsUpdate(void);

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;
            CameraConfiguratorGUI* myWidget;
            std::vector<CameraConfig*> cameras;
            QMutex myMutex;

            bool init;

        protected slots:
            void closeWidget(void);
            void timerEvent(QTimerEvent* event);

        };

    } // end of namespace gui
} // end of namespace mars
