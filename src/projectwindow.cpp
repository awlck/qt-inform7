/*
 * projectwindow.h - Main Window for Qt-Inform7
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

#include "projectwindow.h"

#include <QtCore/QTextStream>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QHBoxLayout>

#include "config.h"
#include "informbrowser.h"
#include "i7project.h"
#include "i7syntax.h"
#include "informurlhandler.h"

QString remapDocSource(QString& code);

ProjectWindow::ProjectWindow(I7Project *proj, QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
	setWindowTitle(tr("Qt-Inform7: %1").arg(proj->getPath().path()));
	this->proj = proj;
	conf = new Config;

	webEngineProfile = new QWebEngineProfile(this);
	urlHandler = new InformUrlHandler(conf, this);
	webEngineProfile->installUrlSchemeHandler(QByteArrayLiteral("inform"), urlHandler);
	// Set up the Documentation viewer
	docsBrowser = new InformBrowser(tr("Documentation"), QUrl("inform:/index.html"), this);
	// Set up the Index viewer
	/* indexBrowser = new QDockWidget(tr("Index"), this, Qt::Dialog);
	indexBrowser->hide();
	indexWebEngine = new QWebEngineView(indexBrowser);
	indexWebEngine->load(QUrl(proj->getPath().absolutePath() + "/Index/Welcome.html"));
	indexWebEngine->show();
    indexBrowser->setWidget(indexWebEngine); */
	indexBrowser = new InformBrowser(tr("Index"), QUrl(proj->getPath().absolutePath() + "/Index/Welcome.html"), this);
	setupButtons();
	setUnifiedTitleAndToolBarOnMac(true);
	sourcePanel = new QPlainTextEdit(this);
	sourceHightlighter = new I7SyntaxHighlighter(sourcePanel->document());
	QFile srcFile(proj->getSourceFile());
    if (srcFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&srcFile);
        sourcePanel->setPlainText(stream.readAll());
    }
    sourcePanel->setTabStopDistance(8 * QFontMetrics(sourcePanel->font()).horizontalAdvance(' '));
    setCentralWidget(sourcePanel);
}

void ProjectWindow::closeEvent(QCloseEvent* event) {
	docsBrowser->prepareClose();
	indexBrowser->prepareClose();
}

void ProjectWindow::setupButtons() {
	toolBar = addToolBar(tr("Launch"));
	toolBar->setAllowedAreas(Qt::TopToolBarArea);
	toolBar->setMovable(false);
	goAction = toolBar->addAction(tr("Go"));
	replayAction = toolBar->addAction(tr("Replay"));
	releaseAction = toolBar->addAction(tr("Release"));
	docsAction = docsBrowser->toggleViewAction();
	toolBar->addAction(docsAction);
	indexAction = indexBrowser->toggleViewAction();
	toolBar->addAction(indexAction);
}

void ProjectWindow::pasteCode(const QString &code) {
	QString theCode(code);
    sourcePanel->insertPlainText(remapDocSource(theCode));
}

void ProjectWindow::selectView(const QString &view) {
    sourcePanel->activateWindow();
    sourcePanel->setFocus();
}

QString remapDocSource(QString& code) {
	return code.replace(QStringLiteral("[=0x0022=]"), QStringLiteral("\""))
		.replace(QStringLiteral("[=0x000A=]"), QStringLiteral("\n"))
		.replace(QStringLiteral("[=0x0027=]"), QStringLiteral("'"))
		.replace(QStringLiteral("[=0x0009=]"), QStringLiteral("\t"));
}