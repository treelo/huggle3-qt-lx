//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef SPEEDYFORM_H
#define SPEEDYFORM_H

#include "definitions.hpp"
// now we need to ensure that python is included first, because it simply suck :P
#ifdef PYTHONENGINE
#include <Python.h>
#endif

#include <QTimer>
#include <QDialog>
#include "apiquery.hpp"
#include "collectable_smartptr.hpp"
#include "editquery.hpp"
#include "wikiedit.hpp"

namespace Ui
{
    class SpeedyForm;
}

namespace Huggle
{
    class WikiEdit;
    class WikiUser;
    class ApiQuery;
    class EditQuery;

    /*!
     * \brief The window that is used to report a page for deletion
     */
    class SpeedyForm : public QDialog
    {
            Q_OBJECT
        public:
            explicit SpeedyForm(QWidget *parent = nullptr);
            ~SpeedyForm();
            void Init(WikiEdit *edit_);
            Collectable_SmartPtr<WikiEdit> edit;
            QString Text;
            QString Header;

        private slots:
            void OnTick();
            void on_pushButton_2_clicked();
            void on_pushButton_clicked();

        private:
            void Fail(QString reason);
            void processTags();
            Collectable_SmartPtr<EditQuery> Template;
            Collectable_SmartPtr<ApiQuery> qObtainText;
            QString base;
            QString warning;
            QTimer *timer;
            Ui::SpeedyForm *ui;
    };
}
#endif // SPEEDYFORM_H


