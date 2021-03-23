/*
 * projectwindow.h - Main Window for Qt-Inform7 (header file)
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

#ifndef QT_INFORM7_PROJECTWINDOW_H
#define QT_INFORM7_PROJECTWINDOW_H

#include <QtWidgets/QMainWindow>

class QDockWidget;
// class QSplitter;
// class QTabWidget;
// class QTextBrowser;
class QToolBar;
class QPlainTextEdit;
class QWebEngineProfile;
class QWebEngineView;

class Config;
class InformBrowser;
class I7Project;
class I7SyntaxHighlighter;
class InformUrlHandler;

class ProjectWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit ProjectWindow(I7Project *proj, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
public:
    Q_INVOKABLE void pasteCode(const QString &code);
    Q_INVOKABLE void selectView(const QString &view);
protected:
	void closeEvent(QCloseEvent* event) override;
private slots:
    // void docsTriggered(bool checked);
private:
	// void setupSections();
	// void setupMenus();
	void setupButtons();
	// void setupStatusBar();

	Config *conf;
	I7Project *proj;
	InformBrowser *docsBrowser, *indexBrowser;
	InformUrlHandler *urlHandler;
	QAction *goAction, *replayAction, *releaseAction, *docsAction, *indexAction;
	//QDockWidget *docsBrowser, *indexBrowser;
	QPlainTextEdit *sourcePanel;
	/* QSplitter *splitter;
	QTabWidget *leftSide, *rightSide;
	QTextBrowser *docBrowserL, *docBrowserR; */
	QToolBar *toolBar;
	QWebEngineProfile *webEngineProfile;
	//QWebEngineView *docsWebEngine, *indexWebEngine;
	I7SyntaxHighlighter *sourceHightlighter;
};

#endif //QT_INFORM7_PROJECTWINDOW_H
