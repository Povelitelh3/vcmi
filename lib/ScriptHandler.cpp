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

namespace scripting
{

ScriptHandler::ScriptHandler()
{
	//TODO: adjust when new languages will be added

	const boost::filesystem::path filePath = VCMIDirs::get().fullLibraryPath("scripting", "vcmiERM");

	auto module = CDynLibHandler::getNewScriptingModule(filePath);

//         module->giveActionCB(this);

//         module->giveInfoCB(this);

	knownModules["erm"] = module;
}

ScriptHandler::~ScriptHandler() = default;

std::vector<bool> ScriptHandler::getDefaultAllowed() const
{
	return std::vector<bool>();
}

std::vector<JsonNode> ScriptHandler::loadLegacyData(size_t dataSize)
{
	return std::vector<JsonNode>();
}

void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data)
{

}

void ScriptHandler::loadObject(std::string scope, std::string name, const JsonNode & data, size_t index)
{
	throw std::runtime_error("No legacy data load allowed for scripts");
}

bool ScriptHandler::isInteractive() const
{
	return (bool)interactiveModule;
}


}
