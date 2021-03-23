/*
 * i7project.h: I7 project creation - header file
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

#ifndef QT_INFORM7_I7PROJECT_H
#define QT_INFORM7_I7PROJECT_H

#include <QtCore/QDir>
#include <QtCore/QObject>
#include <QtCore/QString>
class QWidget;

class Config;

class I7Project : QObject {
Q_OBJECT
public:
    static I7Project *create(QString path);
    static I7Project *open(QString path);
    enum CompileStep {
        NI_RUNNING,
        I6_RUNNING,
        CBLORB_RUNNING
    };
    enum CompileResult {
        SUCCESS,
        PROBLEM,
        NI_CRASH,
        I6_CRASH,
        CBLORB_PROBLEM
    };
    const QDir &getPath() const;
    QString getSourceFile() const;
public slots:
    void compile(const Config &cfg);
    void refreshIndex(const Config &cfg);
signals:
    void compileStatus(int progress, CompileStep step, QString consoleOutput);
    void compileFinished(CompileResult result);
protected:
    I7Project() = default;
    QDir path;
};

#endif //QT_INFORM7_I7PROJECT_H
