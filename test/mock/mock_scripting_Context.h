/*
 * mock_scripting_Context.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../../../lib/JsonNode.h"
#include "../../../lib/ScriptingService.h"

namespace scripting
{

class ContextMock : public Context
{
public:
	MOCK_METHOD2(apiQuery, JsonNode(const std::string &, const JsonNode &));
	MOCK_METHOD2(init, void(const IGameInfoCallback *, const CBattleInfoCallback *));
	MOCK_METHOD1(giveActionCB, void(IGameEventRealizer *));
};

}
