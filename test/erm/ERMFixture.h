/*
 * ERMFixture.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vstd/RNG.h>
#include "../../../lib/JsonNode.h"
#include "../../../lib/HeroBonus.h"
#include "../../../lib/ScriptingService.h"
#include "../../../lib/NetPacksBase.h"

#include "../mock/mock_battle_IBattleState.h"
#include "../../../lib/battle/CBattleInfoCallback.h"

namespace test
{

using namespace ::testing;
using namespace ::scripting;

class ERMFixture
{
public:
	class BattleFake : public CBattleInfoCallback, public BattleStateMock
	{
	public:
		BattleFake();

		void setUp();
	};

	std::shared_ptr<BattleFake> battleFake;

	ERMFixture();
	virtual ~ERMFixture();

protected:
	void setUp();

private:
};


}
