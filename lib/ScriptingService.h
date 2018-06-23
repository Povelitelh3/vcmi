/*
 * ScriptingService.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

namespace scripting
{

class DLL_LINKAGE Context
{
public:
	virtual ~Context() = default;
};

class DLL_LINKAGE Script
{
public:
	virtual ~Script() = default;
};

class DLL_LINKAGE Service
{
public:
	virtual ~Service() = default;


};

}