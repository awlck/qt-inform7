//
// Created by awelc on 22.03.2021.
//

#include "informbrowser.h"

#include <QtCore/QFile>
#include <QtWebChannel/QWebChannel>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineView>

#include <QtCore/qdebug.h>

#include "config.h"
#include "informurlhandler.h"
#include "projectwindow.h"

InformBrowser::InformBrowser(QString title, QUrl start, ProjectWindow* parent) : QDockWidget(title, parent, Qt::Dialog), paths(new Config), mainWindow(parent) {
    hide();
    QFile webChannel(":/qtwebchannel/qwebchannel.js");
    webChannel.open(QFile::ReadOnly);
    jsTweaks = webChannel.readAll();
    jsTweaks += "new QWebChannel(qt.webChannelTransport, function(channel){"
                    "console.log('lel');"
                    "console.log(channel.ProjectWindow);"
                    "window.Project = channel.objects.ProjectWindow;"
                "});";

    profile = new QWebEngineProfile(this);
    urlHandler = new InformUrlHandler(paths, this);
    profile->installUrlSchemeHandler(QByteArrayLiteral("inform"), urlHandler);
    view = new QWebEngineView(this);
    connect(view, &QWebEngineView::loadFinished, this, &InformBrowser::loadFinished);
    auto *page = new QWebEnginePage(profile, view);
    channel = new QWebChannel(page);
    page->setWebChannel(channel);
    channel->registerObject("ProjectWindow", parent);
    page->load(start);
    view->setPage(page);
    view->show();
    this->setWidget(view);
}

InformBrowser::~InformBrowser() {
    delete paths;
}

void InformBrowser::loadFinished(bool) {
    qDebug() << jsTweaks;
    view->page()->runJavaScript(jsTweaks, [](const QVariant& v) { qDebug() << v.toString(); });
}

void InformBrowser::prepareClose() {
    channel->deregisterObject(mainWindow);
}
