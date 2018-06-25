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
#include "../../ScriptingService.h"
#include "../../serializer/JsonSerializeFormat.h"

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
	std::shared_ptr<scripting::Context> context = resolveScript(m);
	if(!context)
		return false;

	setContextVariables(m, context);

	JsonNode response = context->callGlobal(EVENT_APPLICABLE_GENERAL, JsonNode());

	if(response.Vector().size() != 1)
	{
		logMod->error("Invalid API response from script %s.", scriptName);
		logMod->debug(response.toJson(true));
		return false;
	}
	return response.Vector().at(0).Integer() == 1;
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
	handler.serializeString("script", scriptName);
}

std::shared_ptr<scripting::Context> Custom::resolveScript(const Mechanics * m) const
{
	auto script = m->scriptingService()->resolveScript(scriptName);

	if(!script)
		return std::shared_ptr<scripting::Context>();

	std::shared_ptr<scripting::Context> context = script->createIsolatedContext();
	context->init(m->game(), m->battle());
	return context;
}

void Custom::setContextVariables(const Mechanics * m, std::shared_ptr<scripting::Context> context) const
{
	context->setGlobal("effect-level", m->getEffectLevel());
}


}
}
