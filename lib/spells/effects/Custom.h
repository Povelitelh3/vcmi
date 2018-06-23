/*
 * Custom.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "Effect.h"

namespace scripting
{
	class Script;
	class Context;
}

namespace spells
{
namespace effects
{

class Custom : public Effect
{
public:
	Custom();
	virtual ~Custom();

	void adjustTargetTypes(std::vector<TargetType> & types) const override;

	void adjustAffectedHexes(std::set<BattleHex> & hexes, const Mechanics * m, const Target & spellTarget) const override;

	bool applicable(Problem & problem, const Mechanics * m) const;
	bool applicable(Problem & problem, const Mechanics * m, const EffectTarget & target) const;

	void apply(BattleStateProxy * battleState, RNG & rng, const Mechanics * m, const EffectTarget & target) const override;

	EffectTarget filterTarget(const Mechanics * m, const EffectTarget & target) const override;

	EffectTarget transformTarget(const Mechanics * m, const Target & aimPoint, const Target & spellTarget) const override;

protected:
	void serializeJsonEffect(JsonSerializeFormat & handler) override;

private:
	std::string scriptName;

	std::shared_ptr<scripting::Context> resolveScript(const Mechanics * m) const;
};

} // namespace effects
} // namespace spells
