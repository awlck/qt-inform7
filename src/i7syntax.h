/*
 * i7syntax.h: I7 syntax hightlighting (header file)
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

#ifndef QT_INFORM7_I7SYNTAX_H
#define QT_INFORM7_I7SYNTAX_H

#include <QtCore/QRegularExpression>
#include <QtGui/QSyntaxHighlighter>
#include <QtGui/QTextCharFormat>

class QTextDocument;

class I7SyntaxHighlighter : public QSyntaxHighlighter {
	Q_OBJECT
public:
	explicit I7SyntaxHighlighter(QTextDocument *doc);
protected:
	void highlightBlock(const QString &text) override;
	QTextCharFormat headerFmt;
	QRegularExpression headerRule;
	QTextCharFormat commentFmt;
	QTextCharFormat stringFmt;
	QRegularExpression stringRule;
	QTextCharFormat substFmt;
};

#endif //QT_INFORM7_I7SYNTAX_H
