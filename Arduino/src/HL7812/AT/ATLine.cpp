/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

#include "ATLine.h"
#include "ATValue.h"

ATLine::ATLine(String line) {
	this->mLine = line;
	mCurrentPos = 0;
	
	if(!isOk())
	{		
		if(mLine.charAt(0) == '+')
		{
			mCurrentPos = mLine.indexOf(":", 0);
			
			if(mCurrentPos != -1)
			{	  			
				int i = 1;
				mCurrentPos += 2;
				while(mCurrentPos < mLine.length())
				{
					String value = extractValue();
					ATValue* atValue = new ATValue(value);  				
					mVectorValue.push_back(atValue);
					
					i++;
				}	
			}
		}
	}
}

bool ATLine::isData()
{
  return (!isOk() && !isCommand());
}

ATLine::~ATLine(void) {
	flush();
  	mVectorValue.clear();
}

void ATLine::flush()
{
	for (std::vector<ATValue*>::iterator it = mVectorValue.begin() ; it != mVectorValue.end(); ++it) {
		delete *it;
	}
	mVectorValue.clear();
}

bool ATLine::isOk()
{
	return (mLine.indexOf("OK", 0) == 0);
}

bool ATLine::isSuccess()
{
	return !(mLine.indexOf("ERROR", 0) == 0);
}

String ATLine::toString()
{
	return mLine;
}

bool ATLine::isCommand()
{
	return (mLine.indexOf("+", 0) == 0);
}

String ATLine::getCommand()
{
	int posStart = mLine.indexOf("+", 0);
	if(posStart != 0) return "";
	int posEnd = mLine.indexOf(":", 0);
	if(posEnd <= 0) return "";
	
	return mLine.substring(posStart, posEnd);		
}

String ATLine::extractValue()
{
	String value;
	int pos = mLine.indexOf(",", mCurrentPos);
	
	if(pos == -1)
		pos = mLine.length();
		
	value = mLine.substring(mCurrentPos, pos);
	mCurrentPos = pos + 1;
	
	return value;
}

int ATLine::getCount()
{
	return mVectorValue.size();
}

ATValue* ATLine::getValue(int index)
{
	if(index >= getCount()) return NULL;
	return mVectorValue.at(index);
}

String ATLine::getData()
{
  return mLine;
}
