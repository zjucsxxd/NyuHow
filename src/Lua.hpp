#pragma once

#include <lua.hpp>
#include <memory>

// Lua state object
class Lua{
	private:
		// Lua environment in C
		std::shared_ptr<lua_State> L;
	public:
		// Allocate Lua state
		Lua() : L(luaL_newstate(), [](lua_State* p){if(p)lua_close(p);}){}
		// Copy Lua state
		Lua(const Lua&) = default;
		const Lua& operator =(const Lua&) = default;
		// No Lua state move
		Lua(const Lua&&) = delete;
		Lua& operator =(const Lua&&) = delete;
		// Access Lua state
		operator lua_State*() const{
			return this->L.get();
		}
};

