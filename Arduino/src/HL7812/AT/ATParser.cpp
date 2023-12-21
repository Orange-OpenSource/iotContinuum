/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/


#include "Arduino.h"
#include "ATParser.h"

ATParser::ATParser() :
	mFrame(""),
	mCurrentPos(0) {
}

ATParser::~ATParser(void) {
	flush();
	
}

void ATParser::flush() {
	for (std::vector<ATLine*>::iterator it = mVectorLine.begin() ; it != mVectorLine.end(); ++it) {
		delete *it;
	}
	mVectorLine.clear();
}

void ATParser::begin(String frame) {
	flush();

	mFrame = frame;
	mCurrentPos = 0;

	int i = 1;
	while(mCurrentPos < mFrame.length())
	{
		String line = extractLine();
		ATLine* atLine = new ATLine(line);
		mVectorLine.push_back(atLine);		
		
		i++;
	}
}

String ATParser::extractLine() {
	int jumpPos = 2;
	String line;
	bool finish = false;
	int pos = 0;
	
	while(!finish) {
		pos = mFrame.indexOf("\r\n", mCurrentPos);
		if (pos == mCurrentPos) {
			mCurrentPos += 2;
		} else {
			finish = true;
		}
		
	}
	if(pos == -1) {
		pos = mFrame.indexOf("\n", mCurrentPos);
		if(pos == -1) 
			pos = mFrame.length();
		
		jumpPos = 1;
	}
	
	line = mFrame.substring(mCurrentPos, pos);
	mCurrentPos = pos + jumpPos;
	
	return line;
}

int ATParser::getCount() {
	return mVectorLine.size();
}

ATLine* ATParser::getLine(int index) {
	if(index >= mVectorLine.size()) return NULL;
		return mVectorLine.at(index);
}

ATLine* ATParser::getLineByKey(String key) {
	const int count = mVectorLine.size();
	bool found = false;

	int16_t i = count - 1;
	while((i >= 0) && (!found)) {
		ATLine* line = mVectorLine.at(i);
		if(line->getData().startsWith(key)) {
			return line;
		}
		else {
			i--;
		}
	}	
	return NULL;
}

String ATParser::toString() {
	String frame = "";

	const int count = mVectorLine.size();
	for(int i = 0; i < count; i++)
	{
		ATLine* line = mVectorLine.at(i);
		frame += line->getData() + String("\r\n");
	}
	return frame;
}

bool ATParser::isOk() {	
	bool isOk = false;
	const int count = mVectorLine.size();

	if(count > 0) {
		ATLine* line = mVectorLine.at(count - 1);
		return line->isOk();
	}
	
	return false;
}

bool ATParser::isSuccess() {
	const int count = mVectorLine.size();
	int i = 0;
	bool isSuccess = true;
	while((i < count) && (isSuccess)) {
		ATLine* line = mVectorLine.at(i);
		if(!line->isSuccess())
		{
			isSuccess = false;
		}
		else {
			i++;
		}
	}	
	return isSuccess;
}
