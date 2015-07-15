/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef UINT64METHODS_H
#define UINT64METHODS_H

/***
 * Lua can not represent uint64 values so we created support for it through our class system.
 *
 * Almost all metamethods including concat, tostring, comparing and math metamethods are implemented.
 * To convert an uint64 value back to a number you must call `tonumber(tostring(myuint64))` which returns nil if conversion failed.
 */
namespace Luauint64
{
    // Template by Mud from http://stackoverflow.com/questions/4484437/lua-integer-type/4485511#4485511
    int __add(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) + Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __sub(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) - Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __mul(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) * Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __div(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) / Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __mod(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) % Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __pow(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, static_cast<uint64>(powl(static_cast<long double>(*u), static_cast<long double>(Eluna::CHECKVAL<uint64>(L, 2)))));
        return 1;
    }
    int __eq(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) == Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __lt(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) < Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __le(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, (*u) <= Eluna::CHECKVAL<uint64>(L, 2));
        return 1;
    }
    int __tostring(Eluna* /*E*/, lua_State* L, uint64* u)
    {
        Eluna::Push(L, std::to_string(*u));
        return 1;
    }
};
#endif
