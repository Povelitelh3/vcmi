/*
 * LuaScriptModule.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../../lib/CScriptingModule.h"

namespace scripting
{

class LuaScriptModule : public Module
{
public:
	LuaScriptModule();
	virtual ~LuaScriptModule();

	std::shared_ptr<ContextBase> createContextFor(const Script * source, const IGameInfoCallback * gameCb, const CBattleInfoCallback * battleCb) const override;

	void registerSpellEffect(spells::effects::Registry * registry, const Script * source) const override;

private:
};

}