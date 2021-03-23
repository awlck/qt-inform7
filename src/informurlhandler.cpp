//
// Created by awelc on 22.03.2021.
//

#include "informurlhandler.h"

#include <QtCore/QFile>
#include <QtWebEngineCore/QWebEngineUrlRequestJob>
#include <QtWebEngineCore/QWebEngineUrlScheme>

#include <QtCore/QDebug>

#include "config.h"

const QByteArray InformUrlHandler::schemeName = QByteArrayLiteral("inform");

InformUrlHandler::InformUrlHandler(const Config *conf, QObject *parent) : QWebEngineUrlSchemeHandler(parent), config(conf) { }

void InformUrlHandler::requestStarted(QWebEngineUrlRequestJob *job) {
    if (job->requestMethod() == QByteArrayLiteral("POST")) {
        job->fail(QWebEngineUrlRequestJob::RequestDenied);
    }
    qDebug() << "Attempting to load:" << job->requestUrl();
    // TODO: Figure out non-internal paths
    QString urlString(job->requestUrl().toString().remove("inform:"));
    QFile *fileToLoad = new QFile(config->dataDir + urlString, job);
    fileToLoad->open(QIODevice::ReadOnly);
    if (urlString.endsWith(".png"))
        job->reply(QByteArrayLiteral("image/png"), fileToLoad);
    else if (urlString.endsWith(".html"))
        job->reply(QByteArrayLiteral("text/html"), fileToLoad);
    else if (urlString.endsWith(".css"))
        job->reply(QByteArrayLiteral("text/css"), fileToLoad);
    else
        job->fail(QWebEngineUrlRequestJob::RequestDenied);
}

void InformUrlHandler::registerUrlScheme() {
    QWebEngineUrlScheme informScheme(schemeName);
    informScheme.setFlags(QWebEngineUrlScheme::SecureScheme | QWebEngineUrlScheme::LocalScheme | QWebEngineUrlScheme::LocalAccessAllowed);
    QWebEngineUrlScheme::registerScheme(informScheme);
}
