/*
 * Custom.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "Custom.h"
#include "Registry.h"
#include "../ISpellMechanics.h"

static const std::string EFFECT_NAME = "core:custom";

static const std::string EVENT_APPLICABLE_GENERAL = "applicable";
static const std::string EVENT_APPLICABLE_TARGET = "applicableTarget";

namespace spells
{
namespace effects
{

VCMI_REGISTER_SPELL_EFFECT(Custom, EFFECT_NAME);

Custom::Custom()
{

}

Custom::~Custom() = default;

void Custom::adjustTargetTypes(std::vector<TargetType> & types) const
{

}

void Custom::adjustAffectedHexes(std::set<BattleHex> & hexes, const Mechanics * m, const Target & spellTarget) const
{

}

bool Custom::applicable(Problem & problem, const Mechanics * m) const
{
	return false;
}

bool Custom::applicable(Problem & problem, const Mechanics * m, const EffectTarget & target) const
{
	return false;
}

void Custom::apply(BattleStateProxy * battleState, RNG & rng, const Mechanics * m, const EffectTarget & target) const
{

}

EffectTarget Custom::filterTarget(const Mechanics * m, const EffectTarget & target) const
{
	return EffectTarget(target);
}

EffectTarget Custom::transformTarget(const Mechanics * m, const Target & aimPoint, const Target & spellTarget) const
{
	return EffectTarget(spellTarget);
}

void Custom::serializeJsonEffect(JsonSerializeFormat & handler)
{

}


}
}
