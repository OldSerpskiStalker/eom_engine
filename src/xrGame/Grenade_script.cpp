#include "pch_script.h"
#include "Grenade.h"

using namespace luabind;

#pragma optimize("s", on)
void CGrenade::script_register(lua_State* L)
{
    module(L)[class_<CGrenade, CGameObject>("CGrenade").def(constructor<>())];
}
