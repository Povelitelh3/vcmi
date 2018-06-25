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
	persistenceType(PersistenceType::STATELESS),
	runOn(RunOn::SERVER),
	host()
{

}

ScriptImpl::~ScriptImpl() = default;

std::shared_ptr<Context> ScriptImpl::createIsolatedContext() const
{
	return host->createContextFor(this);
}

void ScriptImpl::serializeJson(JsonSerializeFormat & handler)
{
	handler.serializeString("source", sourcePath);

	if(!handler.saving)
		afterLoad();
}

void ScriptImpl::afterLoad()
{
	//TODO: adjust when new languages will be added

	ResourceID sourcePathId(sourcePath);

	auto rawData = CResourceHandler::get()->load(sourcePathId)->readAll();

	source = std::string((char *)rawData.first.get(), rawData.second);

	host = owner->knownModules.at("erm");
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
		return iter->second;
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

ScriptImpl * ScriptHandler::loadFromJson(const JsonNode & json) const
{
	ScriptImpl * ret = new ScriptImpl(this);

	JsonDeserializer handler(nullptr, json);
	ret->serializeJson(handler);
	return ret;
}


void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data)
{

}

void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data, size_t index)
{
	throw std::runtime_error("No legacy data load allowed for scripts");
}



}
