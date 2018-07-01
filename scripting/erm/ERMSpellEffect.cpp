/*
 * ERMSpellEffect.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ERMSpellEffect.h"

#include "../../lib/spells/effects/Registry.h"
#include "../../lib/spells/ISpellMechanics.h"

#include "../../lib/battle/Unit.h"
#include "../../lib/battle/CBattleInfoCallback.h"
#include "../../lib/ScriptingService.h"
#include "../../lib/serializer/JsonSerializeFormat.h"



static const std::string APPLICABLE_GENERAL = "applicable";
static const std::string APPLICABLE_TARGET = "applicableTarget";

namespace spells
{
namespace effects
{

ERMSpellEffectFactory::ERMSpellEffectFactory(const Script * script_)
	: script(script_)
{

}

ERMSpellEffectFactory::~ERMSpellEffectFactory() = default;

Effect * ERMSpellEffectFactory::create() const
{
	return new ERMSpellEffect(script);
}


ERMSpellEffect::ERMSpellEffect(const Script * script_)
	: script(script_)
{

}

ERMSpellEffect::~ERMSpellEffect() = default;

void ERMSpellEffect::adjustTargetTypes(std::vector<TargetType> & types) const
{

}

void ERMSpellEffect::adjustAffectedHexes(std::set<BattleHex> & hexes, const Mechanics * m, const Target & spellTarget) const
{

}

bool ERMSpellEffect::applicable(Problem & problem, const Mechanics * m) const
{
	std::shared_ptr<scripting::Context> context = resolveScript(m);
	if(!context)
		return false;

	setContextVariables(m, context);

	JsonNode response = context->callGlobal(APPLICABLE_GENERAL, JsonNode());

	if(response.getType() != JsonNode::JsonType::DATA_INTEGER)
	{
		logMod->error("Invalid API response from script %s.", script->getName());
		logMod->debug(response.toJson(true));
		return false;
	}
	return response.Integer() == 1;
}

bool ERMSpellEffect::applicable(Problem & problem, const Mechanics * m, const EffectTarget & target) const
{
	std::shared_ptr<scripting::Context> context = resolveScript(m);
	if(!context)
		return false;

	setContextVariables(m, context);

	JsonNode requestP;

	if(target.empty())
		return false;

	for(auto & dest : target)
	{
		JsonNode targetData;
		targetData.Vector().push_back(JsonUtils::intNode(dest.hexValue.hex));

		if(dest.unitValue)
			targetData.Vector().push_back(JsonUtils::intNode(dest.unitValue->unitId()));
		else
			targetData.Vector().push_back(JsonUtils::intNode(-1));

		requestP.Vector().push_back(targetData);
	}

	JsonNode request;
	request.Vector().push_back(requestP);

	JsonNode response = context->callGlobal(APPLICABLE_TARGET, request);

	if(response.getType() != JsonNode::JsonType::DATA_INTEGER)
	{
		logMod->error("Invalid API response from script %s.", script->getName());
		logMod->debug(response.toJson(true));
		return false;
	}
	return response.Integer() == 1;
}

void ERMSpellEffect::apply(BattleStateProxy * battleState, RNG & rng, const Mechanics * m, const EffectTarget & target) const
{

}

EffectTarget ERMSpellEffect::filterTarget(const Mechanics * m, const EffectTarget & target) const
{
	return EffectTarget(target);
}

EffectTarget ERMSpellEffect::transformTarget(const Mechanics * m, const Target & aimPoint, const Target & spellTarget) const
{
	return EffectTarget(spellTarget);
}

void ERMSpellEffect::serializeJsonEffect(JsonSerializeFormat & handler)
{
	//TODO: load everything and provide to script
}

std::shared_ptr<Context> ERMSpellEffect::resolveScript(const Mechanics * m) const
{
	auto context = m->battle()->getScriptingContext(script);
	context->init(m->game(), m->battle()); //???
	return context;
}

void ERMSpellEffect::setContextVariables(const Mechanics * m, std::shared_ptr<Context> context) const
{
	context->setGlobal("effect-level", m->getEffectLevel());
	context->setGlobal("effect-range-level", m->getRangeLevel());
	context->setGlobal("effect-power", m->getEffectPower());
	context->setGlobal("effect-duration", m->getEffectDuration());
	context->setGlobal("effect-value", static_cast<int32_t>(m->getEffectValue()));
}


}
}
