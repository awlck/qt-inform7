//
// Created by awelc on 22.03.2021.
//

#pragma once

#ifndef QT_INFORM7_INFORMURLHANDLER_H
#define QT_INFORM7_INFORMURLHANDLER_H

#include <QWebEngineUrlSchemeHandler>
struct Config;

class InformUrlHandler : public QWebEngineUrlSchemeHandler
{
Q_OBJECT
public:
    InformUrlHandler(const Config *conf, QObject *parent = nullptr);

    void requestStarted(QWebEngineUrlRequestJob *job) override;

    static void registerUrlScheme();

private:
    const Config *config;
    const static QByteArray schemeName;
};

#endif //QT_INFORM7_INFORMURLHANDLER_H
