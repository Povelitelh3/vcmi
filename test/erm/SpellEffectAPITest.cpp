/*
 * SpellEffectAPITest.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ERMFixture.h"

namespace test
{

using namespace ::testing;
using namespace ::scripting;

class SpellEffectAPITest : public Test, public ERMFixture
{
public:


protected:
	void SetUp() override
	{
		ERMFixture::setUp();
	}
};

TEST_F(SpellEffectAPITest, ApplicableOnExpert)
{
	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);

	scriptConfig["source"].String() = "test/erm/SpellEffectAPITest.verm";

	loadScript(scriptConfig);

	context->setGlobal("effect-level", 3);

	JsonNode params;

	JsonNode ret = context->callGlobal("applicable", params);

	JsonNode expected = JsonUtils::intNode(1);

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);

}

TEST_F(SpellEffectAPITest, NotApplicableOnAdvanced)
{
	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);

	scriptConfig["source"].String() = "test/erm/SpellEffectAPITest.verm";
	loadScript(scriptConfig);

	context->setGlobal("effect-level", 2);

	JsonNode params;

	JsonNode ret = context->callGlobal("applicable", params);

	JsonNode expected = JsonUtils::intNode(0);

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);

}

TEST_F(SpellEffectAPITest, ApplicableOnLeftSideOfField)
{
	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);

	scriptConfig["source"].String() = "test/erm/SpellEffectAPITest.verm";
	loadScript(scriptConfig);

	context->setGlobal("effect-level", 1);

	JsonNode params;

	BattleHex hex(2,2);

	JsonNode first;
	first.Vector().push_back(JsonUtils::intNode(hex.hex));
	first.Vector().push_back(JsonNode());

	JsonNode targets;
	targets.Vector().push_back(first);

	params.Vector().push_back(targets);

	JsonNode ret = context->callGlobal("applicableTarget", params);

	JsonNode expected = JsonUtils::intNode(1);

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);
}

TEST_F(SpellEffectAPITest, NotApplicableOnRightSideOfField)
{
	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);

	scriptConfig["source"].String() = "test/erm/SpellEffectAPITest.verm";
	loadScript(scriptConfig);

	context->setGlobal("effect-level", 1);

	JsonNode params;

	BattleHex hex(11,2);

	JsonNode first;
	first.Vector().push_back(JsonUtils::intNode(hex.hex));
	first.Vector().push_back(JsonUtils::intNode(-1));

	JsonNode targets;
	targets.Vector().push_back(first);

	params.Vector().push_back(targets);

	JsonNode ret = context->callGlobal("applicableTarget", params);

	JsonNode expected = JsonUtils::intNode(0);

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);
}

}
