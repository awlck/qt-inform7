//
// Created by awelc on 22.03.2021.
//
#pragma once

#ifndef QT_INFORM7_DOCSBROWSER_H
#define QT_INFORM7_DOCSBROWSER_H

#include <QtWidgets/QDockWidget>

class QWebChannel;
class QWebEngineProfile;
class QWebEngineView;

class Config;
class InformUrlHandler;
class ProjectWindow;

/* class JScomms_Docs : public QObject {
Q_OBJECT
public:
    explicit JScomms_Docs(QObject *parent = nullptr);
    Q_INVOKABLE void setCodeToPaste(const QString &code);

private:
    QString code;
    QString title;
}; */


class InformBrowser : public QDockWidget {
    Q_OBJECT
public:
    explicit InformBrowser(QString title, QUrl start, ProjectWindow *parent);
    ~InformBrowser();
    void prepareClose();

private slots:
    void loadFinished(bool);

private:
    QString jsTweaks;

    Config *paths;
    InformUrlHandler *urlHandler;
    // JScomms_Docs *comms;
    ProjectWindow* mainWindow;
    QWebChannel *channel;
    QWebEngineProfile *profile;
    QWebEngineView *view;
};

#endif //QT_INFORM7_DOCSBROWSER_H
