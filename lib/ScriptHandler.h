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
class JsonSerializeFormat;
class CScriptingModule;

namespace scripting
{

class ScriptImpl;
class ScriptHandler;

using ModulePtr = std::shared_ptr<CScriptingModule>;
using ModulesMap = std::map<std::string, ModulePtr>;
using ScriptPtr = std::shared_ptr<ScriptImpl>;
using ScriptMap = std::map<std::string, ScriptPtr>;

class DLL_LINKAGE ScriptImpl : public Script
{
public:
	std::string identifier;
	std::string sourcePath;
	std::string sourceText;

	ModulePtr host;

	ScriptImpl(const ScriptHandler * owner_);
	virtual ~ScriptImpl();

	void serializeJson(JsonSerializeFormat & handler);
	void serializeJsonState(JsonSerializeFormat & handler);

	std::shared_ptr<Context> createContext() const override;
private:
	const ScriptHandler * owner;

	void resolveHost();
};

class DLL_LINKAGE ScriptHandler : public ::IHandlerBase, public Service
{
public:
	ScriptHandler();
	virtual ~ScriptHandler();

	const Script * resolveScript(const std::string & name) const override;

	std::vector<bool> getDefaultAllowed() const override;
	std::vector<JsonNode> loadLegacyData(size_t dataSize) override;

	ScriptPtr loadFromJson(const JsonNode & json, const std::string & identifier) const;

	void loadObject(std::string scope, std::string name, const JsonNode & data) override;
	void loadObject(std::string scope, std::string name, const JsonNode & data, size_t index) override;


	template <typename Handler> void serialize(Handler & h, const int version)
	{
        //TODO: serialize scripts
		JsonNode state;
		if(h.saving)
			saveState(state);

		h & state;

		if(!h.saving)
			loadState(state);
	}

protected:

private:

	friend class ScriptImpl;

	ModulesMap knownModules;
	ScriptMap objects;

	void loadState(const JsonNode & state);
	void saveState(JsonNode & state);
};

}
