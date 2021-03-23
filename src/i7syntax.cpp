/*
 * i7syntax.h: I7 syntax hightlighting
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

#include "i7syntax.h"

enum class State {
	BASE,
	COMMENT,
	STRING,
	SUBST
};

I7SyntaxHighlighter::I7SyntaxHighlighter(QTextDocument *doc) : QSyntaxHighlighter(doc) {
	headerFmt.setFontWeight(QFont::Bold);
	headerRule.setPattern("^((Section)|(Chapter)|(Part)|(Book)|(Volume)) .*?$");

	commentFmt.setFontWeight(QFont::Light);
	commentFmt.setForeground(Qt::green);

	stringFmt.setFontWeight(QFont::Bold);
	stringFmt.setForeground(Qt::blue);
	// stringRule.setPattern("\".*?\"");

	substFmt.setForeground(Qt::blue);
}

void I7SyntaxHighlighter::highlightBlock(const QString &text) {
	QRegularExpressionMatch headerMatch = headerRule.match(text);
	if (headerMatch.hasMatch()) setFormat(headerMatch.capturedStart(), headerMatch.capturedEnd(), headerFmt);

	int i;
	int commentLevel = previousBlockState();
	commentLevel = commentLevel == -1 ? 0 : commentLevel;
	int commentBegin, commentLength;
	State state;
	if (commentLevel > 0) {
		commentBegin = 0;
		commentLength = 1;
		state = State::COMMENT;
	}
	else {
		commentBegin = -1;
		commentLength = -1;
		state = State::BASE;
	}
	int stringBegin = -1;
	int stringLength = -1;
	int substBegin = -1;
	int substLength = -1;
	for (i = 0; i < text.size(); i++) {
		const QChar c = text[i];
		switch (state) {
		case State::BASE:
			if (c == '[') {
				state = State::COMMENT;
				commentBegin = i;
				commentLength = 1;
				commentLevel++;
			}
			else if (c == '"') {
				state = State::STRING;
				stringBegin = i;
				stringLength = 1;
			}
			break;
		case State::COMMENT:
			commentLength++;
			if (c == '[') {
				commentLevel++;
			}
			else if (c == ']' && --commentLevel == 0) {
				setFormat(commentBegin, commentLength, commentFmt);
				commentBegin = -1;
				commentLength = -1;
				state = State::BASE;
			}
			break;
		case State::STRING:
			stringLength++;
			if (c == '"') {
				setFormat(stringBegin, stringLength, stringFmt);
				stringBegin = -1;
				stringLength = -1;
				state = State::BASE;
			}
			else if (c == '[') {
				setFormat(stringBegin, stringLength, stringFmt);
				state = State::SUBST;
				substBegin = i;
				substLength = 1;
			}
			break;
		case State::SUBST:
			substLength++;
			if (c == ']') {
				setFormat(substBegin, substLength, substFmt);
				substBegin = -1;
				substLength = -1;
				stringBegin = i + 1;
				stringLength = 1;
				state = State::STRING;
			}
			break;
		}
		if (commentBegin != -1) {
			setFormat(commentBegin, commentLength, commentFmt);
		}
		setCurrentBlockState(commentLevel);
	}
}
