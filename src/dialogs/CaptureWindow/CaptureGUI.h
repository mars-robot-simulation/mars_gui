#pragma once

#include "main_gui/BaseWidget.h"
#include "main_gui/PropertyDialog.h"
#include "CaptureConfig.h"

#include <QDoubleSpinBox>

namespace mars
{
    namespace gui
    {

        class CaptureGUI : public main_gui::BaseWidget,
                           public main_gui::PropertyCallback
        {
            Q_OBJECT

        public:
            CaptureGUI(interfaces::ControlCenter* c);
            ~CaptureGUI();

            main_gui::PropertyDialog *pDialog;

            void show(void) {if (pDialog) pDialog->show();}
            void hide(void) {if (pDialog) pDialog->hide();}
            bool isHidden(void) {if (pDialog) return pDialog->isHidden(); else return true;}
            void close(void) {if (pDialog!=NULL) pDialog->close();}

            void addCamera(CaptureConfig* camera);
            void removeCamera(CaptureConfig* camera);
            void cameraSelected(int index);
            void setFrameRate(double frameRate);
            void startCapture(void);
            void stopCapture(void);

        private:
            interfaces::ControlCenter *control;

            QtVariantProperty *status;
            QtVariantProperty *winIDCombo;
            QtVariantProperty *frameBox;
            QtVariantProperty *capture;
            unsigned int camera;
            bool take_events, first_camera, update_frame_box, filled;

            std::vector<CaptureConfig*> cameras;
            QPushButton* generatePushButton(QString objectName, QString text);
            QLayout* generateDoubleBox(QDoubleSpinBox *&theBox,
                                       QString objectName,
                                       QString text);
            void updateGUI(void);

        protected slots:
            void timerEvent(QTimerEvent* event);
            virtual void valueChanged(QtProperty *property, const QVariant &value);
            virtual void accept();
            virtual void reject();

        };

    } // end of namespace gui
} // end of namespace mars
