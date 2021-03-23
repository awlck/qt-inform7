//
// Created by Adrian Welcker on 2019-02-15.
//

#include "config.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>

Config::Config() {
	appDir = QCoreApplication::applicationDirPath();
	{
		QDir dir(appDir);
#ifdef Q_OS_WIN
		if (QFile(dir.absoluteFilePath("ni.exe")).exists()) compilersDir = appDir;
		else if (dir.cd("Compilers") && QFile(dir.absoluteFilePath("ni.exe")).exists()) compilersDir = dir.absolutePath();
		else compilersDir = "COMPILERS_NOTFOUND";
#else
		if (QFile(dir.absoluteFilePath("ni")).exists()) compilersDir = appDir;
		else if (dir.cd("Compilers") && QFile(dir.absoluteFilePath("ni")).exists()) compilersDir = dir.absolutePath();
		else compilersDir = "COMPILERS_NOTFOUND";
#endif
	}
	{
		// QDir dir(appDir);
		QDir dir("C:/Program Files/Inform 7");
		if (dir.cd("Documentation")) dataDir = dir.absolutePath();
		else dataDir = "DATA_NOTFOUND";
	}
}
