/*
 * launcherdialog.h: Launcher dialog header file
 *
 * Copyright 2019 Adrian Welcker
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifndef QT_INFORM7_LAUNCHERDIALOG_H
#define QT_INFORM7_LAUNCHERDIALOG_H

#include <QtWidgets/QDialog>
class I7Project;
class QDialogButtonBox;
class QGridLayout;

class LauncherDialog : public QDialog {
	Q_OBJECT
public:
	explicit LauncherDialog(QWidget *parent = nullptr);
protected:
	void openMainWindowForProject(I7Project *proj);
private slots:
	void new_clicked();
	void open_clicked();
	void reopen_clicked();
private:
	QDialogButtonBox *buttonBox;
	QGridLayout *layout;
	QPushButton *newButton, *openButton, *reopenButton;
};

#endif //QT_INFORM7_LAUNCHERDIALOG_H
