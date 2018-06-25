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

#include "../../lib/ScriptHandler.h"

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

TEST_F(SpellEffectAPITest, Applicable)
{
	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);

	scriptConfig["source"].String() = "test/erm/SpellEffectAPITest.verm";
//
//	{
//		JsonNode & bindingsJson = scriptConfig["bindings"];
//		JsonNode & bindingJson = bindingsJson["applicable"];
//
//	}

	std::shared_ptr<ScriptImpl> subject;

	subject.reset(VLC->scriptHandler->loadFromJson(scriptConfig));

	std::shared_ptr<Context> context = subject->createIsolatedContext();

	context->init(&infoMock, battleFake.get());

	JsonNode params;

	JsonNode ret = context->apiQuery("applicable", params);

	JsonNode expected;
	expected.Integer() = 1;

	JsonComparer cmp(false);
	cmp.compare("applicable result", ret, expected);

}

}
