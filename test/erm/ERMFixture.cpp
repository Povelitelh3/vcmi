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

ERMFixture::BattleFake::BattleFake()
	: CBattleInfoCallback(),
	BattleStateMock()
{
}

void ERMFixture::BattleFake::setUp()
{
	CBattleInfoCallback::setBattle(this);
}


ERMFixture::ERMFixture()
{
	//ctor
}

ERMFixture::~ERMFixture() = default;

void ERMFixture::loadScript(const JsonNode & scriptConfig)
{
	subject.reset(VLC->scriptHandler->loadFromJson(scriptConfig));

	context = subject->createIsolatedContext();

	context->init(&infoMock, battleFake.get());
}


void ERMFixture::setUp()
{
	battleFake = std::make_shared<BattleFake>();
	battleFake->setUp();
}


}
