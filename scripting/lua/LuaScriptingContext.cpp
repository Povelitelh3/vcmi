/*
 * LuaScriptingContext.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "LuaScriptingContext.h"

#include "../../lib/JsonNode.h"
#include "../../lib/NetPacks.h"

namespace scripting
{


LuaContext::LuaContext()
{
	L = luaL_newstate();
}

LuaContext::~LuaContext()
{
	lua_close(L);
}

void LuaContext::init(const IGameInfoCallback * cb, const CBattleInfoCallback * battleCb)
{
	icb = cb;
	bicb = battleCb;

	/*int ret = */ lua_pcall(L, 0, 0, 0);
}

void LuaContext::giveActionCB(IGameEventRealizer * cb)
{
	acb = cb;
}

void LuaContext::loadScript(const ScriptImpl * source)
{
	/*int ret = */luaL_loadbuffer(L, source->sourceText.c_str(), source->sourceText.size(), source->sourcePath.c_str());
}

JsonNode LuaContext::callGlobal(const std::string & name, const JsonNode & parameters)
{
	return JsonNode();
}

void LuaContext::setGlobal(const std::string & name, int value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	lua_setglobal(L, name.c_str());
}

void LuaContext::setGlobal(const std::string & name, const std::string & value)
{
	lua_pushlstring(L, value.c_str(), value.size());
	lua_setglobal(L, name.c_str());
}

void LuaContext::setGlobal(const std::string & name, double value)
{
	lua_pushnumber(L, value);
	lua_setglobal(L, name.c_str());
}

}
