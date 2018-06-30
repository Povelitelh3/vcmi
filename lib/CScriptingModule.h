/*
 * CScriptingModule.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once

#include "IGameEventsReceiver.h"
#include "ScriptHandler.h"

namespace scripting
{

class DLL_LINKAGE ContextBase : public Context
{
public:
	ContextBase();
	virtual ~ContextBase();
};

class DLL_LINKAGE Module
{
public:
	Module();
	virtual ~Module();

    virtual std::shared_ptr<ContextBase> createContextFor(const ScriptImpl * source) const = 0;
};

}
