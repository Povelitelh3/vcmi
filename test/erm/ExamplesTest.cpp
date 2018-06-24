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

#include "ERMFixture.h"
#include "../../lib/VCMI_Lib.h"
#include "../../lib/ScriptHandler.h"
#include "../../lib/NetPacks.h"

#include "../mock/mock_IGameEventRealizer.h"
#include "../mock/mock_IGameInfoCallback.h"

///All unsorted ERM acceptance tests goes here

namespace test
{

using namespace ::testing;
using namespace ::scripting;

class ExamplesTest : public Test, public ERMFixture
{
public:
	StrictMock<IGameInfoCallbackMock> infoMock;
	StrictMock<IGameEventRealizerMock> applierMock;

	std::vector<std::string> actualTexts;

	ExamplesTest()
		: ERMFixture()
	{
	}

	void setDefaultExpectaions()
	{
		EXPECT_CALL(infoMock, getLocalPlayer()).WillRepeatedly(Return(PlayerColor(3)));
		EXPECT_CALL(applierMock, commitPackage(_)).Times(AtLeast(1)).WillRepeatedly(Invoke(this, &onCommit));
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
		ERMFixture::setUp();
	}
};

TEST_F(ExamplesTest, HelloWorld)
{
	setDefaultExpectaions();

	const std::string scriptPath = "test/erm/testy.erm";

	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);
	scriptConfig["source"].String() = scriptPath;

	ScriptImpl * subject = VLC->scriptHandler->loadFromJson(scriptConfig);

	GTEST_ASSERT_NE(subject, nullptr);

	std::shared_ptr<Context> ctx = subject->createIsolatedContext();
	ctx->giveActionCB(&applierMock);
	ctx->init(&infoMock);
}

TEST_F(ExamplesTest, HelloWorldVERM)
{
	setDefaultExpectaions();

	const std::string scriptPath = "test/erm/std.verm";

	JsonNode scriptConfig(JsonNode::JsonType::DATA_STRUCT);
	scriptConfig["source"].String() = scriptPath;

	ScriptImpl * subject = VLC->scriptHandler->loadFromJson(scriptConfig);

	GTEST_ASSERT_NE(subject, nullptr);

	std::shared_ptr<Context> ctx = subject->createIsolatedContext();
	ctx->giveActionCB(&applierMock);
	ctx->init(&infoMock);

	std::vector<std::string> expectedTexts =
	{
		"Hello world from macro def",
		"Hello world from macro usage",
		"Hello world from macro usage",
		"Hello world from macro usage",
		"Hello world from macro usage",
		"Hello world FN1",
		"Hello world FN2",
		"Hello world FN1",
		"Hello world FN2"
	};

	EXPECT_THAT(actualTexts, ContainerEq(expectedTexts));
}

}
