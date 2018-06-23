/*
 * CustomTest.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "EffectFixture.h"

#include "mock/mock_scripting_Context.h"
#include "mock/mock_scripting_Script.h"
#include "mock/mock_scripting_Service.h"

namespace test
{
using namespace ::spells;
using namespace ::spells::effects;
using namespace ::scripting;
using namespace ::testing;

class CustomTest : public Test, public EffectFixture
{
public:
	const std::string SCRIPT_NAME = "testScript";

	ServiceMock serviceMock;
	ScriptMock scriptMock;
	std::shared_ptr<ContextMock> contextMock;

	CustomTest()
		: EffectFixture("core:custom")
	{
		contextMock = std::make_shared<ContextMock>();
	}

protected:
	void SetUp() override
	{
		EffectFixture::setUp();
	}
};

TEST_F(CustomTest, ApplicableRedirected)
{

	EXPECT_CALL(serviceMock, resolveScript(Eq(SCRIPT_NAME))).WillOnce(Return(&scriptMock));
	//TODO: we should cache even isolated context in client|server objects
	EXPECT_CALL(scriptMock, createIsolatedContext()).WillOnce(Return(contextMock));

	JsonNode response(JsonNode::JsonType::DATA_VECTOR);
	response.Vector().push_back(JsonUtils::intNode(1));


	EXPECT_CALL(*contextMock, apiQuery(Eq("applicable"),_)).WillOnce(Return(response));//TODO: check call parameter
	//expect query 'applicable' from script

	JsonNode options(JsonNode::JsonType::DATA_STRUCT);
	options["script"].String() = SCRIPT_NAME;
	EffectFixture::setupEffect(options);

	EXPECT_TRUE(subject->applicable(problemMock, &mechanicsMock));
}


}

