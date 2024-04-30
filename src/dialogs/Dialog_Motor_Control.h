#pragma once

#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/core_objects_exchange.h>
#include <main_gui/BaseWidget.h>

#include <QSlider>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace mars
{
    namespace gui
    {

        /**
         * \brief Dialog_Motor_Control is a widget that creates MotorSet widgets for each
         * available motor to change its values
         */
        class Dialog_Motor_Control : public main_gui::BaseWidget
        {

            Q_OBJECT

        public:
            /**\brief creates the dialog */
            Dialog_Motor_Control(interfaces::ControlCenter *c);
            ~Dialog_Motor_Control();

        private:
            std::vector<interfaces::core_objects_exchange> motors;
            std::vector<QDoubleSpinBox*> radspinboxes;
            std::vector<QDoubleSpinBox*> degspinboxes;
            std::vector<QSlider*> sliders;
            double scale;

            bool slideractive;
            bool radboxactive;
            bool degboxactive;

            QGridLayout* grLayout;
            QVBoxLayout* mainLayout;
            interfaces::ControlCenter* control;

            void closeEvent(QCloseEvent *event);

        signals:
            void closeSignal(void*);

        private slots:
            void zerobuttonclicked();
            void sliderValueChanged(int);
            void radspinboxValueChanged(double);
            void degspinboxValueChanged(double);
        };

    } // end of namespace gui
} // end of namespace mars
