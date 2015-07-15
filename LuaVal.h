/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/
/*
Copyright (c) 2015 Rochet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef LUAVAL_H
#define LUAVAL_H

#include "LuaEngine.h"

// LuaVal borrowed from https://github.com/Rochet2/smallfolk_cpp

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <mutex>
#include <inttypes.h>

enum LuaTypeTag
{
    TNIL,
    TSTRING,
    TNUMBER,
    TTABLE,
    TBOOL,
    TINT,
    TUINT, // uint64 support
};

class LuaVal
{
public:
    // static nil value, same as LuaVal();
    static LuaVal const & nil()
    {
        static LuaVal const nil;
        return nil;
    }

    // returns the string representation of the value info similar to lua tostring
    std::string tostring() const
    {
        switch (tag)
        {
            case TBOOL:
                if (b)
                    return "true";
                else
                    return "false";
            case TNIL:
                return "nil";
            case TSTRING:
                return s;
            case TNUMBER:
                return tostring(d);
            case TTABLE:
                return tostring(tbl_ptr);
            case TINT:
                return tostring(i);
            case TUINT:
                return tostring(u);
            default:
                break;
        }
        ASSERT(false);
        return std::string();
    }

    static struct LuaValHasher
    {
        size_t operator()(LuaVal const & v) const
        {
            return std::hash<std::string>()(v.tostring());
        }
    };

    typedef std::unordered_map< LuaVal, LuaVal, LuaValHasher> LuaTable;
    typedef std::unique_ptr< LuaTable > TblPtr;

    LuaVal(const LuaTypeTag tag) : tag(tag), tbl_ptr(tag == TTABLE ? new LuaTable() : nullptr)
    {
        ASSERT(!istable() || tbl_ptr);
    }
    LuaVal() : tag(TNIL), tbl_ptr(nullptr)
    {
    }
    LuaVal(int8 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(int16 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(int32 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(uint8 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(uint16 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(uint32 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(int64 i) : tag(TINT), tbl_ptr(nullptr), i(i)
    {
    }
    LuaVal(uint64 u) : tag(TUINT), tbl_ptr(nullptr), u(u)
    {
    }
    LuaVal(lua_Number d) : tag(TNUMBER), tbl_ptr(nullptr), d(d)
    {
    }
    LuaVal(const std::string& s) : tag(TSTRING), tbl_ptr(nullptr), s(s)
    {
    }
    LuaVal(const char* s) : tag(TSTRING), tbl_ptr(nullptr), s(s)
    {
    }
    LuaVal(const bool b) : tag(TBOOL), tbl_ptr(nullptr), b(b)
    {
    }
    LuaVal(LuaTable const & luatable) : tag(TTABLE), tbl_ptr(new LuaTable(luatable))
    {
        ASSERT(tbl_ptr);
    }
    LuaVal(LuaVal const & val) : tag(val.tag), tbl_ptr(val.tag == TTABLE ? new LuaTable(*val.tbl_ptr.get()) : nullptr)
    {
        ASSERT(!istable() || tbl_ptr);
        if (isstring())
            s = val.s;
        if (isnumber())
            d = val.d;
        if (isbool())
            b = val.b;
        if (isint())
            i = val.i;
        if (isuint())
            u = val.u;
    }

    bool isstring() const { return tag == TSTRING; }
    bool isnumber() const { return tag == TNUMBER; }
    bool istable() const { return tag == TTABLE; }
    bool isbool() const { return tag == TBOOL; }
    bool isnil() const { return tag == TNIL; }
    bool isint() const { return tag == TINT; }
    bool isuint() const { return tag == TUINT; }

    // settable, return self
    LuaVal & set(LuaVal const & k, LuaVal const & v)
    {
        ASSERT(istable());
        if (k.isnil()) // on nil key do nothing
            return *this;
        LuaTable & tbl = (*tbl_ptr);
        if (v.isnil()) // on nil value erase key
            tbl.erase(k);
        else
            tbl[k] = v; // normally set pair
        return *this;
    }

    void Push(lua_State* L) const
    {
        switch (tag)
        {
            case TBOOL:
                Eluna::Push(L, b);
                break;
            case TNIL:
                Eluna::Push(L);
                break;
            case TSTRING:
                Eluna::Push(L, s);
                break;
            case TNUMBER:
                Eluna::Push(L, d);
                break;
            case TTABLE:
            {
                lua_newtable(L);
                int tbl = lua_gettop(L);
                uint32 i = 0;
                for (auto&& v : *tbl_ptr)
                {
                    v.first.Push(L);
                    v.second.Push(L);
                    lua_settable(L, tbl);
                }
                lua_settop(L, tbl);
                break;
            }
            case TINT:
                Eluna::Push(L, i);
                break;
            case TUINT:
                Eluna::Push(L, u);
                break;
            default:
                ASSERT(false);
                break;
        }
    }

    bool operator==(LuaVal const& rhs) const
    {
        if (tag != rhs.tag)
            return false;
        switch (tag)
        {
            case TBOOL:
                return b == rhs.b;
            case TNIL:
                return true;
            case TSTRING:
                return s == rhs.s;
            case TNUMBER:
                return d == rhs.d;
            case TTABLE:
                return tbl_ptr == rhs.tbl_ptr;
            case TINT:
                return i == i;
            case TUINT:
                return u == u;
        }
        return false;
    }

    bool operator!=(LuaVal const& rhs) const
    {
        return !(*this == rhs);
    }

    LuaVal& operator=(LuaVal const& val)
    {
        tag = val.tag;
        if (istable())
        {
            tbl_ptr = (std::make_unique<LuaTable>());
            *tbl_ptr = *val.tbl_ptr.get();
        }
        else
            tbl_ptr = std::make_unique<LuaTable>(val.tbl_ptr);
        if (isstring())
            s = val.s;
        if (isnumber())
            d = val.d;
        if (isbool())
            b = val.b;
        if (isint())
            i = val.i;
        if (isuint())
            u = val.u;
        return *this;
    }

private:
    LuaTypeTag tag;

    TblPtr tbl_ptr;
    std::string s;
    union
    {
        uint64 u;
        lua_Integer i;
        lua_Number d;
        bool b;
    };

    // sprintf is ~50% faster than other solutions
    static std::string tostring(const double d)
    {
        char arr[80];
        sprintf_s(arr, "%g", d);
        return arr;
    }
    static std::string tostring(const int64 i)
    {
        char arr[80];
        sprintf_s(arr, "%" PRId64, i);
        return arr;
    }
    static std::string tostring(const uint64 u)
    {
        char arr[80];
        sprintf_s(arr, "%" PRIu64, u);
        return arr;
    }
    static std::string tostring(TblPtr const & ptr)
    {
        char arr[80];
        sprintf_s(arr, "table: %p", ptr);
        return arr;
    }
};

class MsgQueue
{
public:
    void Add(lua_State *L, int minindex, int maxindex, std::string channel)
    {
        std::vector<LuaVal> store;
        for (int i = minindex; i <= maxindex; ++i)
            store.emplace_back(Check(L, i));

        WriteGuard guard(_lock);
        que[channel].emplace_back(store);
    }

    bool HasMessages(std::string channel)
    {
        WriteGuard guard(_lock);
        if (que.find(channel) == que.end())
            return false;
        return true;
    }

    // returns a copy or empty container
    std::vector< std::vector< LuaVal > > Get(std::string channel)
    {
        WriteGuard guard(_lock);
        auto it = que.find(channel);
        if (it == que.end())
            return it->second;
        return std::vector < std::vector< LuaVal > >();
    }

    void Clear(std::string channel)
    {
        que.erase(channel);
    }

    typedef std::unordered_map < std::string, std::vector< std::vector< LuaVal > > > Queue;
private:
    typedef std::vector<int> TableRefs;
    typedef std::mutex LockType;
    typedef std::lock_guard<LockType> WriteGuard;
    LockType _lock;

    Queue que;

    const LuaVal Check(lua_State* L, int index)
    {
        switch (lua_type(L, index))
        {
            case LUA_TBOOLEAN:
                return Eluna::CHECKVAL<bool>(L, index);
            case LUA_TNUMBER:
                if (lua_isinteger(L, index))
                    return Eluna::CHECKVAL<int>(L, index);
                else
                    return Eluna::CHECKVAL<double>(L, index);
            case LUA_TSTRING:
                return Eluna::CHECKVAL<std::string>(L, index);
            case LUA_TTABLE:
            {
                TableRefs refs;
                const LuaVal v = Check(L, index, refs);
                for (auto&& r : refs)
                    luaL_unref(L, LUA_REGISTRYINDEX, r);
                return v;
            }
            case LUA_TUSERDATA:
                // uint64 support
                if (uint64* u = Eluna::CHECKOBJ<uint64>(L, index, false))
                    return *u;
                break;
            case LUA_TNIL:
            case LUA_TNONE:
                return LuaVal::nil();
            default:
                break;
        }
        return LuaVal::nil();
    }

    const LuaVal Check(lua_State* L, int index, TableRefs& refs)
    {
        if (lua_type(L, index) != LUA_TTABLE)
            return Check(L, index);

        for (auto&& r : refs)
        {
            if (r == LUA_NOREF || r == LUA_REFNIL)
                continue;

            lua_rawgeti(L, LUA_REGISTRYINDEX, r);
            int equal = lua_compare(L, index, -1, LUA_OPEQ);
            lua_pop(L, 1);
            if (equal) // change table self references into nil
                return LuaVal::nil();
        }

        lua_pushvalue(L, index);
        refs.push_back(luaL_ref(L, -1));

        LuaVal table(TTABLE);

        lua_pushnil(L);
        while (lua_next(L, index) != 0)
        {
            table.set(Check(L, -2, refs), Check(L, -1, refs));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return table;
    }
};

#endif
