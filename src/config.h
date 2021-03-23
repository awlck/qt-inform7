//
// Created by Adrian Welcker on 2019-02-15.
//

#ifndef QT_INFORM7_CONFIG_H
#define QT_INFORM7_CONFIG_H

#include <QtCore/QString>

struct Config {
	Config();
	QString appDir;
	QString compilersDir;
	QString dataDir;
};

#endif //QT_INFORM7_CONFIG_H
