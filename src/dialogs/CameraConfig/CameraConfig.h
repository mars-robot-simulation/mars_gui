#pragma once

#include <mars_interfaces/sim/ControlCenter.h>
#include <data_broker/ReceiverInterface.h>
#include <data_broker/DataPackageMapping.h>

#include <mars_utils/Vector.h>
#include <mars_utils/Quaternion.h>
#include <QMutex>

namespace mars
{

    namespace interfaces
    {
        class GraphicsCameraInterface;
    }

    namespace gui
    {


        struct Frustum
        {
            double left;
            double right;
            double bottom;
            double top;
            double z_near;
            double z_far;
        };

        class CameraConfig : public data_broker::ReceiverInterface
        {

        public:
            CameraConfig(interfaces::ControlCenter *c);
            ~CameraConfig();

            void updateCamera(void);
            void setWindowID(unsigned long id);
            inline unsigned long getWindowID(void) {return win_id;}
            void setLockID(unsigned long node_id);
            inline unsigned long getLockID(void) {return node_id;}
            bool setLockCamera(bool option);
            inline bool getLockCamera(void) {return lock_camera;}
            void setLockRotation(bool option);
            inline bool getLockRotation(void) {return lock_rotation;}
            void saveConfig(std::string filename);
            void loadConfig(std::string filename);
            void setOffsetPos(utils::Vector pos);
            inline const utils::Vector* getOffsetPos(void) {return &offset_pos;}
            void setOffsetRot(utils::sRotation rot);
            inline const utils::sRotation* getOffsetRot(void) {return &offset_euler;}

            virtual void receiveData(const data_broker::DataInfo &info,
                                     const data_broker::DataPackage &package,
                                     int callbackParam);

            std::vector<double> getFrustumSettings(void);
            void setFrustum(std::vector<double> frustum);

        private:
            interfaces::ControlCenter* control;
            interfaces::GraphicsCameraInterface* gc;
            utils::Vector offset_pos;
            utils::Quaternion offset_rot;
            utils::sRotation offset_euler;
            utils::Vector node_pos;
            utils::Quaternion node_rot;
            QMutex dataMutex;
            Frustum frust;


            bool lock_camera, lock_rotation;
            unsigned int update_ticks;
            unsigned long node_id;
            unsigned long win_id;
            data_broker::DataPackageMapping dbMapping;
        };

    } // end of namespace gui
} // end of namespace mars
