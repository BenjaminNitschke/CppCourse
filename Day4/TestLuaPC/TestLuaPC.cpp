// TestLuaPC.cpp: Simple test of the LuaSupport library for the PC
// Made by BenjaminNitschke.com (c) 2009 - feel free to use this code.
#include "stdafx.h"

// Global variable for the Lua interpreter
lua_State* Lua;

#pragma region lua_print
/// <summary>
/// Lua_print helper method to forward Lua prints to our console!
/// </summary>
int lua_print(lua_State *L)
{
	int n=lua_gettop(L);
	int i;
	for (i=1; i<=n; i++)
	{
		if (i>1)
			printf("\t");
		if (lua_isstring(L,i))
			printf(lua_tostring(L,i));
		else if (lua_isnil(L,i))
			printf("nil");
		else if (lua_isboolean(L,i))
			printf(lua_toboolean(L,i) ? "true" : "false");
		else
		{
			printf(luaL_typename(L,i));
			printf(":%s", lua_topointer(L,i));
		} // else
	} // for (i)
	printf("\n");
	return 0;
} // lua_print()
#pragma endregion

#pragma region main
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Initialize Lua\n");

	Lua = lua_open();
	luaL_openlibs(Lua);
	lua_register(Lua, "print", lua_print);

	// Simple print test from Lua:
	luaL_dostring(Lua, "print(\"Hi from Lua\")");

	// Now load a Lua file, which also loads another Lua file (LuaUnit.lua)
	if (luaL_dofile(Lua, "SomeClass.lua") != 0)
	{
		printf("Error: Unable to execute Lua file %s: %s\n", "SomeClass.lua",
			lua_tostring(Lua, 1));
	} // if (luaL_dofile)

	/*and this is how you would call a SomeClass.SomeMethod method!
	lua_getglobal(Lua, "SomeClass");
	lua_getfield(Lua, -1, "SomeMethod");
	lua_pcall(Lua, 0, 0, 0);
	lua_pop(Lua, 1);
	*/

	// Stop the Lua engine and cleanup
	printf("Closing Lua\n");
	lua_close(Lua);
	Lua = NULL;

	// Keep command window for debug mode (ctrl+f5 does not have this issue)
	char input[100];
	gets_s(input);

	return 0;
} // _tmain
#pragma endregion
