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
	const int32_t EFFECT_LEVEL = 1456;
	const int32_t RANGE_LEVEL = 4561;
	const int32_t EFFECT_POWER = 4789;
	const int32_t EFFECT_DURATION = 42;

	const int32_t EFFECT_VALUE = 42000;//TODO: this should be 64 bit

	ServiceMock serviceMock;
	ScriptMock scriptMock;
	std::shared_ptr<ContextMock> contextMock;

	CustomTest()
		: EffectFixture("core:custom")
	{
		contextMock = std::make_shared<ContextMock>();
	}

	void expectSettingContextVariables()
	{
		EXPECT_CALL(mechanicsMock, getEffectLevel()).WillRepeatedly(Return(EFFECT_LEVEL));
		EXPECT_CALL(*contextMock, setGlobal(Eq("effect-level"), Matcher<int>(Eq(EFFECT_LEVEL))));

		EXPECT_CALL(mechanicsMock, getRangeLevel()).WillRepeatedly(Return(RANGE_LEVEL));
		EXPECT_CALL(*contextMock, setGlobal(Eq("effect-range-level"), Matcher<int>(Eq(RANGE_LEVEL))));

		EXPECT_CALL(mechanicsMock, getEffectPower()).WillRepeatedly(Return(EFFECT_POWER));
		EXPECT_CALL(*contextMock, setGlobal(Eq("effect-power"), Matcher<int>(Eq(EFFECT_POWER))));

		EXPECT_CALL(mechanicsMock, getEffectDuration()).WillRepeatedly(Return(EFFECT_DURATION));
		EXPECT_CALL(*contextMock, setGlobal(Eq("effect-duration"), Matcher<int>(Eq(EFFECT_DURATION))));

		EXPECT_CALL(mechanicsMock, getEffectValue()).WillRepeatedly(Return(EFFECT_VALUE));
		EXPECT_CALL(*contextMock, setGlobal(Eq("effect-value"), Matcher<int>(Eq(EFFECT_VALUE))));
	}

protected:
	void SetUp() override
	{
		EffectFixture::setUp();
	}
};

TEST_F(CustomTest, ApplicableRedirected)
{
	EXPECT_CALL(mechanicsMock, scriptingService()).WillRepeatedly(Return(&serviceMock));


	EXPECT_CALL(serviceMock, resolveScript(Eq(SCRIPT_NAME))).WillOnce(Return(&scriptMock));
	//TODO: we should cache even isolated context in client|server objects
	EXPECT_CALL(scriptMock, createIsolatedContext()).WillOnce(Return(contextMock));

	EXPECT_CALL(*contextMock, init(_,_)).Times(1);

	expectSettingContextVariables();

	JsonNode response = JsonUtils::intNode(1);

	EXPECT_CALL(*contextMock, callGlobal(Eq("applicable"),_)).WillOnce(Return(response));//TODO: check call parameter
	//expect query 'applicable' from script

	JsonNode options(JsonNode::JsonType::DATA_STRUCT);
	options["script"].String() = SCRIPT_NAME;
	EffectFixture::setupEffect(options);

	EXPECT_TRUE(subject->applicable(problemMock, &mechanicsMock));
}


}

