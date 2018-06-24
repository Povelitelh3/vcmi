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

class JsonNode;
class IGameInfoCallback;
class IGameEventRealizer;
class CBattleInfoCallback;

namespace scripting
{

class DLL_LINKAGE Context
{
public:
	virtual ~Context() = default;

	virtual void init(const IGameInfoCallback * cb, const CBattleInfoCallback * battleCb) = 0;
	virtual void giveActionCB(IGameEventRealizer * cb) = 0;

	virtual JsonNode apiQuery(const std::string & name, const JsonNode & parameters) = 0;
};

class DLL_LINKAGE Script
{
public:
	virtual ~Script() = default;

	virtual std::shared_ptr<Context> createIsolatedContext() const = 0;
};

class DLL_LINKAGE Service
{
public:
	virtual ~Service() = default;

	virtual const Script * resolveScript(const std::string & name) const = 0;

};

}
