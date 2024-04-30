#pragma once

#include <mars_interfaces/sim/ControlCenter.h>
#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {

        class ControllerConfigGUI : public main_gui::BaseWidget,
                                    public main_gui::PropertyCallback
        {
            Q_OBJECT

        public:
            ControllerConfigGUI(interfaces::ControlCenter* c, main_gui::GuiInterface* gui);
            ~ControllerConfigGUI();

            main_gui::PropertyDialog *pDialog;

        signals:
            void closeSignal(void* widget);

        public slots:
            void disconnectController(void);
            void connectController(void);
            void setControllerIP(void);
            void setControllerPort(void);
            void toggleControllerAutoMode(bool checked);

        private:
            main_gui::GuiInterface *mainGui;

            struct ControllerElem {
                unsigned long id;
                std::string name;
                int index;
            };

            ControllerElem *controllerElem;
            interfaces::ControlCenter *control;
            unsigned long frame;
            bool take_events, filled;

            QtVariantProperty *controllerIDCombo;
            QtVariantProperty *autoModeCheck, *state;
            QtVariantProperty *ip_edit, *port_edit;

            std::vector<ControllerElem*> controllers;
            void updateGUI(void);
            void closeEvent(QCloseEvent *event);

        protected slots:
            virtual void valueChanged(QtProperty *property, const QVariant &value);
            void timerEvent(QTimerEvent* event);

        };

    } // end of namespace gui
} // end of namespace mars
