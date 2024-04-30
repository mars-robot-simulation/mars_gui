#pragma once

#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include <data_broker/ReceiverInterface.h>

namespace mars
{

    namespace main_gui
    {
        class GuiInterface;
    }

    namespace gui
    {

        class BlenderExportGUI : public main_gui::BaseWidget,
                                 public main_gui::PropertyCallback,
                                 public data_broker::ReceiverInterface
        {
            Q_OBJECT

        public:
            BlenderExportGUI(interfaces::ControlCenter *c, main_gui::GuiInterface *gui);
            ~BlenderExportGUI();

            virtual void writeGenericData(unsigned long id, void *data) const;

            main_gui::PropertyDialog *pDialog;
            void receiveData(const mars::data_broker::DataInfo &info,
                             const mars::data_broker::DataPackage &data_package,
                             int callbackParam);

        public slots:
            void startButton(void);
            void stopButton(void);
            void resetButton(void);

        signals:
            void closeSignal(void* widget);

        private:
            interfaces::ControlCenter *control;
            main_gui::GuiInterface *mainGui;
            mutable unsigned long frame;
            int state;
            FILE *fileHandle;
            unsigned long generic_id;
            std::string rPath;

            QtVariantProperty *status;

            QtVariantProperty *filename;

            void closeEvent(QCloseEvent *event);

        protected slots:
            virtual void valueChanged(QtProperty *property, const QVariant &value);
        };

    } // end of namespace gui
} // end of namespace mars
