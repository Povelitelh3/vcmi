/*
 * LuaScriptModule.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "LuaScriptModule.h"
#include "LuaScriptingContext.h"

const char *g_cszAiName = "Lua interpreter";

extern "C" DLL_EXPORT void GetAiName(char * name)
{
	strcpy_s(name, strlen(g_cszAiName) + 1, g_cszAiName);
}

extern "C" DLL_EXPORT void GetNewModule(std::shared_ptr<scripting::Module> & out)
{
	out = std::make_shared<scripting::LuaScriptModule>();
}

namespace scripting
{

LuaScriptModule::LuaScriptModule() = default;
LuaScriptModule::~LuaScriptModule() = default;

std::shared_ptr<scripting::ContextBase> LuaScriptModule::createContextFor(const ScriptImpl * source) const
{
	auto ret = std::make_shared<scripting::LuaContext>();

	ret->loadScript(source);

	return ret;

}

}
