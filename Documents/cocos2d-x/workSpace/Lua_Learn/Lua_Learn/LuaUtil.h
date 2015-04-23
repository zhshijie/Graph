//
//  LuaUtil.h
//  Lua_Learn
//
//  Created by 张世杰 on 15/4/23.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#ifndef Lua_Learn_LuaUtil_h
#define Lua_Learn_LuaUtil_h

#include <stdio.h>
#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

template <class T>
inline T PopLuaNumber(lua_State* pL,const char* name)
{
    lua_settop(pL,0);
    lua_getglobal(pL,name);
    
    //检查变量类型是否正确
    if (!lua_isnumber(pL,1)) {
        std::cout<<"\n[C++]:ERROR :Invalid type!";
        
    }
    T val = (T)lua_tonumber(pL,1);
    
    lua_pop(pL,1);
    return val;
}
#endif
