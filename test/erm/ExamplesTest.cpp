/*
 * ExamplesTest.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "../scripting/ScriptFixture.h"
#include "../../lib/VCMI_Lib.h"
#include "../../lib/ScriptHandler.h"
#include "../../lib/NetPacks.h"
#include "../JsonComparer.h"


///All unsorted ERM acceptance tests goes here

namespace test
{

using namespace ::testing;
using namespace ::scripting;

class ExamplesTest : public Test, public ScriptFixture
{
public:
	std::vector<std::string> actualTexts;

	ExamplesTest()
		: ScriptFixture()
	{
	}

	void setDefaultExpectaions()
	{
		EXPECT_CALL(infoMock, getLocalPlayer()).WillRepeatedly(Return(PlayerColor(3)));
		EXPECT_CALL(applierMock, commitPackage(_)).Times(AtLeast(1)).WillRepeatedly(Invoke(this, &ExamplesTest::onCommit));
	}

	void onCommit(CPackForClient * pack)
	{
		InfoWindow * iw = dynamic_cast<InfoWindow *>(pack);

		if(iw)
		{
			actualTexts.push_back(iw->text.toString());
		}
	}

protected:
	void SetUp() override
	{
		ScriptFixture::setUp();
	}
};

TEST_F(ExamplesTest, TESTY_ERM)
{
	setDefaultExpectaions();

	const std::string scriptPath = "test/erm/testy.erm";

	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);
	scriptConfig["source"].String() = scriptPath;

	ScriptPtr subject = VLC->scriptHandler->loadFromJson(scriptConfig, "test");

	GTEST_ASSERT_NE(subject, nullptr);

	std::shared_ptr<Context> ctx = subject->createContext(&infoMock, battleFake.get());
	ctx->giveActionCB(&applierMock);

	JsonNode ret = ctx->callGlobal("!!FU42", JsonNode());

	JsonNode expected;

	JsonComparer c(false);
	c.compare("!!FU42 ret", ret, expected);

	std::vector<std::string> expectedTexts =
	{
		"Hello world number 0! (2)",
		"Hello world number 1! (3)",
		"Hello world number 2! (2)",
		"Hello world number 3! (3)",
		"Hello world number 4! (1)",
		"Composed hello %world%, v2777=4, v2778=0!"
	};

	EXPECT_THAT(actualTexts, Eq(expectedTexts));
}

TEST_F(ExamplesTest, STD_VERM)
{
	setDefaultExpectaions();

	const std::string scriptPath = "test/erm/std.verm";

	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);
	scriptConfig["source"].String() = scriptPath;

	ScriptPtr subject = VLC->scriptHandler->loadFromJson(scriptConfig, "test");

	GTEST_ASSERT_NE(subject, nullptr);

	std::shared_ptr<Context> ctx = subject->createContext(&infoMock, battleFake.get());
	ctx->giveActionCB(&applierMock);

	JsonNode ret = ctx->callGlobal("!!FU42", JsonNode());

	JsonNode expected;

	JsonComparer c(false);
	c.compare("!!FU42 ret", ret, expected);

	std::vector<std::string> expectedTexts =
	{
		"Hello world from macro def",
		"Hello world from macro usage",
		"Hello world from macro usage",
		"Hello world from macro usage",
		"Hello world from macro usage"
	};

	EXPECT_THAT(actualTexts, Eq(expectedTexts));
}

}