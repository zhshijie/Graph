//
//  main.cpp
//  Lua_Learn
//
//  Created by 张世杰 on 15/4/22.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#include <iostream>
#include "LuaUtil.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}






void EvaluateTheGuesses(std::string user_guess)
{
    std::cout<<"In [C ++] "<<user_guess;
}
int ccp_EvaluateTheGuesses(lua_State *pL)
{
    int n = lua_gettop(pL);
    
    if (n!=1) {
        std::cout<<"\n [C++]:Wrong number of argument for"<<" cpp_EvaluateTheGuesses";
        return 0;
    }
    
    if (!lua_isstring(pL, 1)) {
        std::cout<<"\n[C++]: ERROR(): Problem with lua"<<
               "script file!\n\n"<<std::endl;
    }
    
    std::string user_guess = lua_tostring(pL, 1);
    EvaluateTheGuesses(user_guess);
    return 2;
}
//
//#include <luabind/luabind.hpp>
int main(int argc, const char * argv[]) {
    // insert code here...
//    lua_State *pL;
//    pL = luaL_newstate();
//
//    luaopen_base(pL);
//    luaopen_string(pL);
//    luaopen_table(pL);
//    luaopen_math(pL);
//    luaopen_io(pL);
//
//
//    if (int error = luaL_dofile(pL, "hello.lua")!=0)
//    {
//        std::cout<<"\n[C++]: ERROR("<< error<<"): Problem with lua"<<
//        "script file!\n\n"<<std::endl;
//        return 0;
//    }
//
//    
//    lua_close(pL);
    
    
    lua_State *pL;
    pL = luaL_newstate();
    luaopen_base(pL);
    luaopen_string(pL);
    luaopen_table(pL);
    luaopen_math(pL);
    
    //在Lua中注册函数
    lua_register(pL, "ccp_EvaluateTheGuesses", ccp_EvaluateTheGuesses);

    if (int error = luaL_dofile(pL, "C:C++jk.lua")!=0)
    {
        std::cout<<"\n[C++]: ERROR("<< error<<"): Problem with lua"<<
        "script file!\n\n"<<std::endl;
        return 0;
    }
    

    
//    luabind::open(pL);
    
    //重置栈索引
    //获得lua中的变量
//    lua_settop(pL, 0);
//    
//    lua_getglobal(pL, "age");
//    lua_getglobal(pL, "name");
//    
//    if (!lua_isnumber(pL, 1)||!lua_isstring(pL, 2)) {
//        std::cout<<"\n[C++]:ERROR :Invalid type!";
//    }
//    
//    std::string name = lua_tostring(pL, 2);
//    int age = PopLuaNumber<int>(pL, "age");
//
//    printf("name : %s age : %d",name.c_str(),age);

    //获得lua中的表
    //重设栈索引
//    lua_settop(pL, 0);
//    //将表放到堆栈上
//    lua_getglobal(pL, "simple_table");
//    
//    if (!lua_istable(pL, 1)) {
//        std::cout<<"\n [C++] :ERROR: simple_table is not a valid table";
//    }
//    else{
//        lua_pushstring(pL, "name");
//        lua_gettable(pL, -2);
//        if (!lua_isstring(pL, -1)) {
//            std::cout<<"\n [C++]:ERROR invalid type";
//        }
//        else{
//            std::string name = lua_tostring(pL, -1);
//           std::cout<<"\n \n [C++]:name = "<<name;
//            lua_pop(pL, -1);
//        }
//    }
    
    
//＝＝＝＝＝＝＝＝＝＝＝＝＝从C+中获取Lua函数
//    lua_getglobal(pL, "add");
//    
//    if (!lua_isfunction(pL, -1)) {
//    std::cout<<"\n\n[C++]: Oops! The lua function 'add' has not been defined";
//    }
//    
//    lua_pushnumber(pL, 4);
//    lua_pushnumber(pL, 5);
//    lua_call(pL, 2, 1);
//    int result = lua_tonumber(pL, -1);
//    lua_pop(pL, 1);
//    
//    std::cout<<"\n a + b =  "<<result;
//    
//
    
    
    
    
    return 0;
}
