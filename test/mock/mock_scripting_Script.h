/*
 * mock_scripting_Script.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../../../lib/ScriptingService.h"

namespace scripting
{

class ScriptMock : public Script
{
public:

	MOCK_CONST_METHOD0(createContext, std::shared_ptr<Context>());

};

}



