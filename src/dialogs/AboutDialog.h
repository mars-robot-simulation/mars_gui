#pragma once

#include <QDialog>

namespace mars
{
    namespace gui
    {

        class AboutDialog : public QDialog
        {
            Q_OBJECT

        public:
            AboutDialog(QWidget *parent = 0);
            ~AboutDialog();


        };

    } // end of namespace gui
} // end of namespace mars
