#pragma once

#include <QtGui>
#include <QListWidget>
#include <QPushButton>

namespace mars
{
    namespace gui
    {

        class SelectionDialog : public QWidget
        {
            Q_OBJECT
        public:
            SelectionDialog(QWidget* parent);
            ~SelectionDialog();

            void reset(QStringList freeList);
            void reset(QStringList freeList, QStringList chosenList);

        private:
            QListWidget *free, *chosen;
            QPushButton *button_up, *button_down, *button_add, *button_remove;
            QString getChosen();

        signals:
            void modified(QString);

        private slots:
            void entry_up();
            void entry_down();
            void entry_add();
            void entry_remove();

        };

    } // end of namespace gui
} // end of namespace mars
