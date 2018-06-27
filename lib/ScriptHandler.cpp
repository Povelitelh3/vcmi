/*
 * ScriptHandler.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ScriptHandler.h"

#include "CGameInterface.h"
#include "CScriptingModule.h"
#include "VCMIDirs.h"
#include "serializer/JsonDeserializer.h"
#include "serializer/JsonSerializer.h"
#include "filesystem/Filesystem.h"

namespace scripting
{

ScriptImpl::ScriptImpl(const ScriptHandler * owner_)
	:owner(owner_),
	host()
{

}

ScriptImpl::~ScriptImpl() = default;

std::shared_ptr<Context> ScriptImpl::createContext() const
{
	return host->createContextFor(this);
}

void ScriptImpl::serializeJson(JsonSerializeFormat & handler)
{
	handler.serializeString("source", sourcePath);

	if(!handler.saving)
	{
		resolveHost();

		ResourceID sourcePathId(sourcePath);

		auto rawData = CResourceHandler::get()->load(sourcePathId)->readAll();

		sourceText = std::string((char *)rawData.first.get(), rawData.second);
	}
}

void ScriptImpl::serializeJsonState(JsonSerializeFormat & handler)
{
	handler.serializeString("sourcePath", sourcePath);
	handler.serializeString("sourceText", sourcePath);

	if(!handler.saving)
	{
		resolveHost();
	}
}

void ScriptImpl::resolveHost()
{
	//TODO: adjust when new languages will be added
	host = owner->knownModules.at("erm");
}

std::shared_ptr<Context> PoolImpl::getContext(const Script * script)
{
	auto iter = cache.find(script);

	if(iter == cache.end())
	{
		auto context = script->createContext();
		cache[script] = context;
		return context;
	}
	else
	{
		return iter->second;
	}
}

ScriptHandler::ScriptHandler()
{
	//TODO: adjust when new languages will be added

	const boost::filesystem::path filePath = VCMIDirs::get().fullLibraryPath("scripting", "vcmiERM");

	auto module = CDynLibHandler::getNewScriptingModule(filePath);

	knownModules["erm"] = module;
}

ScriptHandler::~ScriptHandler() = default;

const Script * ScriptHandler::resolveScript(const std::string & name) const
{
	auto iter = objects.find(name);

	if(iter == objects.end())
	{
		logMod->error("Unknown script id '%s'", name);
		return nullptr;
	}
	else
	{
		return iter->second.get();
	}
}

std::vector<bool> ScriptHandler::getDefaultAllowed() const
{
	return std::vector<bool>();
}

std::vector<JsonNode> ScriptHandler::loadLegacyData(size_t dataSize)
{
	return std::vector<JsonNode>();
}

ScriptPtr ScriptHandler::loadFromJson(const JsonNode & json, const std::string & identifier) const
{
	ScriptPtr ret = std::make_shared<ScriptImpl>(this);

	JsonDeserializer handler(nullptr, json);
	ret->identifier = identifier;
	ret->serializeJson(handler);
	return ret;
}

void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data)
{
	auto object = loadFromJson(data, normalizeIdentifier(scope, "core", name));
	objects[object->identifier] = object;
}

void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data, size_t index)
{
	throw std::runtime_error("No legacy data load allowed for scripts");
}

void ScriptHandler::loadState(const JsonNode & state)
{
	objects.clear();

	const JsonNode & scriptsData = state["scripts"];

	for(auto & keyValue : scriptsData.Struct())
	{
		std::string name = keyValue.first;

		const JsonNode & scriptData = keyValue.second;

		ScriptPtr script = std::make_shared<ScriptImpl>(this);

		JsonDeserializer handler(nullptr, scriptData);
		script->serializeJsonState(handler);
		objects[name] = script;
	}
}

void ScriptHandler::saveState(JsonNode & state)
{
	JsonNode & scriptsData = state["scripts"];

	for(auto & keyValue : objects)
	{
		std::string name = keyValue.first;

		ScriptPtr script = keyValue.second;
		JsonNode scriptData;
		JsonSerializer handler(nullptr, scriptData);
		script->serializeJsonState(handler);

		scriptsData[name] = std::move(scriptData);
	}

}


}
