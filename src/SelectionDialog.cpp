#include "SelectionDialog.h"

#include <QVBoxLayout>

namespace mars
{
    namespace gui
    {

        SelectionDialog:: SelectionDialog(QWidget* parent) 
            : QWidget(parent) 
        {
            free = new QListWidget();
            chosen = new QListWidget();
            button_add = new QPushButton("-->");
            button_remove = new QPushButton("<--");
            button_up = new QPushButton("Up");
            button_down = new QPushButton("Down");
            QVBoxLayout *vLayout = new QVBoxLayout();
            vLayout->addWidget(button_add);
            vLayout->addWidget(button_remove);
            vLayout->addWidget(button_up);
            vLayout->addWidget(button_down);
            QHBoxLayout *hLayout = new QHBoxLayout();
            hLayout->addWidget(free);
            hLayout->addLayout(vLayout);
            hLayout->addWidget(chosen);
            setLayout(hLayout);
            connect(button_add, SIGNAL(clicked()), this, SLOT(entry_add()));
            connect(button_remove, SIGNAL(clicked()), this, SLOT(entry_remove()));
            connect(button_up, SIGNAL(clicked()), this, SLOT(entry_up()));
            connect(button_down, SIGNAL(clicked()), this, SLOT(entry_down()));
        }

        SelectionDialog::~SelectionDialog() 
        {
        }

        void SelectionDialog::reset(QStringList list)
        {
            free->clear();
            chosen->clear();
            if(!(list.isEmpty()))
                free->addItems(list);
            emit modified(getChosen());
        }

        void SelectionDialog::reset(QStringList freeList, QStringList chosenList)
        {
            free->clear();
            chosen->clear();
            if(!(freeList.isEmpty()))
                free->addItems(freeList);
            if(!(chosenList.isEmpty()))
                chosen->addItems(chosenList);
            emit modified(getChosen());
        }


        QString SelectionDialog::getChosen()
        {
            QStringList chosenEntries;
            for(unsigned int i=0; i<chosen->count(); i++)
                chosenEntries << chosen->item(i)->text();
            return chosenEntries.join(";");
        }

        void SelectionDialog::entry_up()
        {
            int row = chosen->currentRow();
            if(row == 0) return;
            QListWidgetItem *item = chosen->takeItem(row);
            chosen->insertItem(row-1, item);
            chosen->setCurrentItem(item);
            emit modified(getChosen());
        }

        void SelectionDialog::entry_down()
        {
            int row = chosen->currentRow();
            if(row == chosen->count()) return;
            QListWidgetItem *item = chosen->takeItem(row);
            chosen->insertItem(row+1, item);
            chosen->setCurrentItem(item);
            emit modified(getChosen());
        }

        void SelectionDialog::entry_add()
        {
            chosen->addItem(free->takeItem(free->currentRow()));
            emit modified(getChosen());
        }

        void SelectionDialog::entry_remove()
        {
            free->addItem(chosen->takeItem(chosen->currentRow()));
            emit modified(getChosen());
        }


    } // end of namespace gui
} // end of namespace mars
