/*
 * ERMFixture.cpp, part of VCMI engine
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

ERMFixture::BattleFake::BattleFake(std::shared_ptr<PoolMock> pool_)
	: CBattleInfoCallback(),
	BattleStateMock(),
	pool(pool_)
{
}

void ERMFixture::BattleFake::setUp()
{
	CBattleInfoCallback::setBattle(this);
}

Pool * ERMFixture::BattleFake::getContextPool() const
{
	return pool.get();
}


ERMFixture::ERMFixture()
{
	//ctor
}

ERMFixture::~ERMFixture() = default;

void ERMFixture::loadScript(const JsonNode & scriptConfig)
{
	subject = VLC->scriptHandler->loadFromJson(scriptConfig, "test");

	context = subject->createContext();

	context->init(&infoMock, battleFake.get());

	EXPECT_CALL(*pool, getContext(_)).WillRepeatedly(Return(context));
}

void ERMFixture::setUp()
{
	pool = std::make_shared<PoolMock>();

	battleFake = std::make_shared<BattleFake>(pool);
	battleFake->setUp();
}


}
