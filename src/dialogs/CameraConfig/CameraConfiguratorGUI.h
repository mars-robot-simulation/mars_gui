#pragma once

#include <QMutex>

#include "CameraConfig.h"
#include "main_gui/BaseWidget.h"
#include "main_gui/PropertyDialog.h"

namespace mars
{
    namespace gui
    {

        class CameraConfiguratorGUI : public main_gui::BaseWidget,
                                      public main_gui::PropertyCallback
        {
            Q_OBJECT

        public:
            CameraConfiguratorGUI(interfaces::ControlCenter* c);
            ~CameraConfiguratorGUI();

            main_gui::PropertyDialog *pDialog;

            void show(void) {if (pDialog) pDialog->show();}
            void hide(void) {if (pDialog) pDialog->hide();}
            bool isHidden(void) {if (pDialog) return pDialog->isHidden(); else return true;}
            void close(void) {if (pDialog) pDialog->close();}

            void addCamera(CameraConfig* camera);
            void removeCamera(CameraConfig* camera);

            void cameraSelected(int index);
            void checkStateChanged(bool checked);
            void checkRotationChanged(bool checked);
            void setOffsetPos(void);
            void setOffsetRot(void);
            void checkFrustumChanged(bool checked);
            void setFrustum(void);

        private:

            struct NodeElem {
                unsigned long id;
                std::string name;
                int index;
            };

            NodeElem *nodeElem;
            interfaces::ControlCenter *control;
            unsigned long frame;
            QMutex nodeMutex;
            QMutex boxmutex;
            unsigned long generic_id;
            unsigned int camera;
            bool take_events, first_camera, filled;
            bool set_frustum;

            QtVariantProperty *winIDCombo, *nodeIDCombo, *lockPos, *lockRot;
            QtVariantProperty *xPosBox, *yPosBox, *zPosBox, *xRotBox, *yRotBox, *zRotBox;
            QtVariantProperty *frustum, *frt_left, *frt_right, *frt_top, *frt_bottom, *frt_near, *frt_far;
            QtVariantProperty *save_config, *load_config, *state;

            std::vector<CameraConfig*> cameras;
            std::vector<NodeElem*> nodes;
            std::vector<double> frustumsettings;

            void updateFRTBoxes(std::vector<double> frustum);
            void updateGUI(void);

        protected slots:
            virtual void valueChanged(QtProperty *property, const QVariant &value);
            virtual void accept();
            virtual void reject();

            void saveConfig( );
            void loadConfig( );
            void timerEvent(QTimerEvent* event);

        };

    } // end of namespace gui
} // end of namespace mars
