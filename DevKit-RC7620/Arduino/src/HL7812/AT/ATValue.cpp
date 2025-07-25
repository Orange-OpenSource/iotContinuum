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

ATValue::ATValue(String value)
{
	this->value = value;
}

ATValue::~ATValue(void){
}

String ATValue::toString()
{
	return value;
}