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

	JsonNode expected;
	expected.Vector().push_back(JsonUtils::intNode(1));

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

	JsonNode expected;
	expected.Vector().push_back(JsonUtils::intNode(0));

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);

}

}
