/*
 * i7project.cpp: I7 project creation and verification
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

#include "i7project.h"

#include <QtCore/QFile>
#include <QtCore/QUuid>

I7Project *I7Project::create(QString path) {
    QDir proj(path);
    QString _path = path;
    if (!proj.mkpath(path)) return nullptr;
    if (!proj.mkdir("Build")) return nullptr;
    if (!proj.mkdir("Index")) return nullptr;
    if (!proj.mkdir("Source")) return nullptr;
    QUuid uuid = QUuid::createUuid();
    QString id = uuid.toString(QUuid::WithoutBraces);
    QFile uuidFile(proj.absoluteFilePath("uuid.txt"));
    if (!uuidFile.open(QIODevice::WriteOnly)) return nullptr;
    uuidFile.write(id.toLocal8Bit());
    uuidFile.close();
    QFile notesFile(proj.absoluteFilePath("notes.rtf"));
    if (!notesFile.open(QIODevice::WriteOnly)) return nullptr;
    notesFile.close();
    QFile skeinFile(proj.absoluteFilePath("Skein.skein"));
    if (!skeinFile.open(QIODevice::WriteOnly)) return nullptr;
    // TODO: Create skein base
    skeinFile.close();

    QString projectName = proj.dirName();
    projectName.remove(QRegExp(".inform"));
    proj.cd("Source");
    QFile sourceFile(proj.absoluteFilePath("story.ni"));
    if (!sourceFile.open(QIODevice::WriteOnly)) return nullptr;
    QString content = "\"" + projectName + "\"\n\nExample Location is a room.";
    sourceFile.write(content.toUtf8());
    sourceFile.close();
    path.replace(".inform", ".materials");
    QDir materials(path);
    if (materials.mkpath(path)) return open(_path);
    return nullptr;
}

I7Project *I7Project::open(QString path) {
    QDir proj(path);
    QString _path = path;
    if (!proj.exists()) return nullptr;
    if (!QFileInfo(proj, "Settings.plist").exists()) return nullptr;
    if (!QFileInfo(proj, "uuid.txt").exists()) return nullptr;
    if (!proj.cd("Source")) return nullptr;

    // a  b  c  .  i  n  f  o  r  m
    // ........ -7 -6 -5 -4 -3 -2 -1
    path.remove(path.size()-7, 7);
    path.append(".materials");
    QDir materials(path);
    if (materials.exists()) {
        I7Project *result = new I7Project;
        result->path = _path;
        return result;
    }
    return nullptr;
}

const QDir &I7Project::getPath() const {
    return path;
}

QString I7Project::getSourceFile() const {
    QDir srcdir = path;
    srcdir.cd("Source");
    return srcdir.absoluteFilePath("story.ni");
}

void I7Project::compile(const Config &cfg) {
    // TODO
}

void I7Project::refreshIndex(const Config &cfg) {
    // TODO
}
