/*
 * launcherdialog.cpp: Launcher dialog implementation
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

#include "launcherdialog.h"
#include "i7project.h"
#include "projectwindow.h"

#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>

LauncherDialog::LauncherDialog(QWidget *parent) : QDialog(parent) {
	setWindowTitle(tr("Welcome to Inform"));
	layout = new QGridLayout(this);
	buttonBox = new QDialogButtonBox(this);
	newButton = buttonBox->addButton(tr("Create a new project"), QDialogButtonBox::ActionRole);
	connect(newButton, &QPushButton::clicked, this, &LauncherDialog::new_clicked);
	openButton = buttonBox->addButton(tr("Open an existing project"), QDialogButtonBox::ActionRole);
	connect(openButton, &QPushButton::clicked, this, &LauncherDialog::open_clicked);
	reopenButton = buttonBox->addButton(tr("Reopen last project"), QDialogButtonBox::ActionRole);
	connect(reopenButton, &QPushButton::clicked, this, &LauncherDialog::reopen_clicked);
	reopenButton->setEnabled(false);
	buttonBox->setOrientation(Qt::Vertical);
	layout->addWidget(buttonBox, 1, 1);
}

void LauncherDialog::new_clicked() {
	QString which = QFileDialog::getSaveFileName(this, tr("Create Project"), QString(), tr("Inform Projects (*.inform)"));
	if (which != "") {
		I7Project *proj = I7Project::create(which);
		if (proj) {
			openMainWindowForProject(proj);
		} else {
			QMessageBox::warning(this, tr("Inform"), tr("Unable to create project."));
		}
	}
}

void LauncherDialog::open_clicked() {
	QString which =
#ifdef Q_OS_MACOS
		QFileDialog::getOpenFileName(this, tr("Open Project"), QString(), tr("Inform Projects (*.inform)"));
#else
		QFileDialog::getExistingDirectory(this, tr("Open Project"));
#endif
	if (which != "") {
		I7Project *proj = I7Project::open(which);
		if (proj) {
			openMainWindowForProject(proj);
		} else {
			QMessageBox::warning(this, tr("Inform"), tr("Not an Inform project."));
		}
	}
}

void LauncherDialog::reopen_clicked() {
	// TODO
}

void LauncherDialog::openMainWindowForProject(I7Project *proj) {
	ProjectWindow *window = new ProjectWindow(proj);
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->show();
	close();
}