/*
 * EffectFixture.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../../../lib/spells/effects/Effect.h"

#include "../../mock/mock_spells_Mechanics.h"
#include "../../mock/mock_spells_Problem.h"
#include "../../mock/mock_spells_Spell.h"
#include "../../mock/mock_spells_SpellService.h"
#include "../../mock/mock_IGameInfoCallback.h"

#include "../../mock/mock_Creature.h"
#include "../../mock/mock_CreatureService.h"

#include "../../mock/mock_BonusBearer.h"
#include "../../mock/mock_battle_IBattleState.h"
#include "../../mock/mock_battle_Unit.h"
#include "../../mock/mock_vstd_RNG.h"
#include "../../mock/mock_scripting_Pool.h"


#include "../../../lib/JsonNode.h"
#include "../../../lib/NetPacksBase.h"
#include "../../../lib/battle/CBattleInfoCallback.h"

namespace battle
{
	bool operator== (const Destination & left, const Destination & right);
}

bool operator==(const Bonus & b1, const Bonus & b2);

namespace test
{

using namespace ::testing;
using namespace ::spells;
using namespace ::spells::effects;
using namespace ::scripting;

class EffectFixture
{
public:
	class UnitFake : public UnitMock
	{
	public:
		void addNewBonus(const std::shared_ptr<Bonus> & b);

		void makeAlive();
		void makeDead();

		void redirectBonusesToFake();

		void expectAnyBonusSystemCall();

	private:
		BonusBearerMock bonusFake;
	};

	class UnitsFake
	{
	public:
		std::vector<std::shared_ptr<UnitFake>> allUnits;

		UnitFake & add(ui8 side);

		battle::Units getUnitsIf(battle::UnitFilter predicate) const;

		void setDefaultBonusExpectations();
	};

	class BattleFake : public CBattleInfoCallback, public BattleStateMock
	{
		std::shared_ptr<PoolMock> pool;
	public:
		BattleFake(std::shared_ptr<PoolMock> pool_);

		void setUp();

		scripting::Pool * getContextPool() const override;
	};

	std::shared_ptr<Effect> subject;
	ProblemMock problemMock;
	StrictMock<MechanicsMock> mechanicsMock;
	StrictMock<CreatureServiceMock> creatureServiceMock;
	StrictMock<CreatureMock> creatureStub;
	StrictMock<SpellServiceMock> spellServiceMock;
	StrictMock<SpellMock> spellStub;
	StrictMock<IGameInfoCallbackMock> gameMock;
	vstd::RNGMock rngMock;

	UnitsFake unitsFake;

	std::shared_ptr<PoolMock> pool;
	std::shared_ptr<BattleFake> battleFake;

	std::shared_ptr<BattleStateProxy> battleProxy;

	std::string effectName;

	EffectFixture(std::string effectName_);
	virtual ~EffectFixture();

	void setupEffect(const JsonNode & effectConfig);

	void setupDefaultRNG();

	void setupEmptyBattlefield();

protected:
	void setUp();

private:
};

}
