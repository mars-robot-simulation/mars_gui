#pragma once

//#include <QtGui>
#include <main_gui/BaseWidget.h>
#include <main_gui/PropertyDialog.h>
#include <mars_interfaces/sim/ControlCenter.h>
#include <mars_interfaces/graphics/GraphicsEventClient.h>
#include <mars_interfaces/core_objects_exchange.h>

#include <QTreeWidget>

namespace mars
{
    namespace gui
    {

        class NodeSelectionTree : public main_gui::BaseWidget,
                                  public main_gui::PropertyCallback,
                                  public interfaces::GraphicsEventClient
        {
            Q_OBJECT

        public:
            NodeSelectionTree(interfaces::ControlCenter *c, QWidget *parent = NULL);
            ~NodeSelectionTree();

            main_gui::PropertyDialog *pDialog;

            virtual void selectEvent(unsigned long int id, bool mode);

            // returns the ids of the selected nodes
            std::vector<unsigned long> selectedNodes(void);

        private:
            interfaces::ControlCenter *control;
            bool filled, select_allowed;
            QtVariantProperty *node_view_mode, *node_selection_mode, *root ;

            std::vector<interfaces::core_objects_exchange> simNodes;
            std::vector<unsigned long> present;

            QTreeWidget *treeWidget;

            void closeEvent(QCloseEvent* event);
            void fill(unsigned long id, QTreeWidgetItem *current = NULL);
            void selectRecursively(QTreeWidgetItem *current, bool mode);
            QTreeWidgetItem* findByNodeId(unsigned long id, QTreeWidgetItem *parent = NULL);
            void reset(void);
            void createTree(unsigned long root);
            void createList(void);

        signals:
            void closeSignal(void* widget);
            void itemSelectionChanged();

        private slots:
            virtual void valueChanged(QtProperty *property, const QVariant &value);
            void selectNodes(void);

        };

    } // end of namespace gui
} // end of namespace mars
