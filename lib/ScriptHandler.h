/*
 * ScriptHandler.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "ScriptingService.h"
#include "IHandlerBase.h"

class JsonNode;
class CScriptingModule;

namespace scripting
{

using ModulePtr = std::shared_ptr<CScriptingModule>;
using ModulesMap = std::map<std::string, ModulePtr>;

class Script
{
public:
	enum class PersistenceType
	{
		STATELESS,
		ISOLATED,
		SHARED
	};

	enum class RunOn
	{
		CLIENT,
		SERVER,
		BOTH
	};

	PersistenceType persistenceType;
	RunOn runOn;

	ModulePtr host;

	Script();
	virtual ~Script();
};

class ScriptHandler : public ::IHandlerBase, public Service
{
public:
	ScriptHandler();
	virtual ~ScriptHandler();

	std::vector<bool> getDefaultAllowed() const override;
	std::vector<JsonNode> loadLegacyData(size_t dataSize) override;

	void loadObject(std::string scope, std::string name, const JsonNode & data) override;
	void loadObject(std::string scope, std::string name, const JsonNode & data, size_t index) override;

	bool isInteractive() const override;


	template <typename Handler> void serialize(Handler & h, const int version)
	{
        //TODO: serialize scripts
	}

protected:

private:
	ModulesMap knownModules;

	ModulePtr interactiveModule; //may be null
};

}
