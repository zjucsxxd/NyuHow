#pragma once

#include <lua.hpp>

// Lua state object
class Lua{
	private:
		// Lua environment in C
		lua_State* L;
		// Reference counter for cleaning
		unsigned int* ref_count;
	public:
		// Allocate Lua state
		Lua() : L(luaL_newstate()), ref_count(new unsigned int){
			*this->ref_count = 1;
		}
		// Free Lua state
		~Lua(){
			if(--*this->ref_count == 0){
				lua_close(this->L);
				delete this->ref_count;
			}
		}
		// Copy Lua state
		Lua(const Lua& o) : L(o.L), ref_count(o.ref_count){
			*this->ref_count += 1;
		}
		const Lua& operator =(const Lua& o){
			if(--*this->ref_count == 0){
				lua_close(this->L);
				delete this->ref_count;
			}
			this->L = o.L;
			this->ref_count = o.ref_count;
			*this->ref_count += 1;
			return *this;
		}
		// Access Lua state
		operator lua_State*() const{
			return this->L;
		}
};