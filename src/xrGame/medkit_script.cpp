#include "pch_script.h"
#include "medkit.h"
#include "eatable_item.h"

using namespace luabind;

#pragma optimize("s", on)
void CMedkit::script_register(lua_State* L)
{
    module(L)[class_<CMedkit, CEatableItem>("CMedkit").def(constructor<>())];
}
