#import <lauxlib.h>
#import "netspeed.c"

static int getstats(lua_State* L) {
    struct interface_stats stats = interface_bytes_transferred("en0"); // TODO
    lua_newtable(L);
    lua_pushnumber(L, stats.ibytes); lua_setfield(L, -2, "ibytes");
    lua_pushnumber(L, stats.obytes); lua_setfield(L, -2, "obytes");
    lua_pushnumber(L, stats.time_sec); lua_setfield(L, -2, "time_sec");
    lua_pushnumber(L, stats.time_usec); lua_setfield(L, -2, "time_usec");
    return 1;
}

static const luaL_Reg networkingLib[] = {
    {"getstats", getstats},
    {NULL, NULL}
};

int luaopen_mjolnir__asm_sys_networking_internal(lua_State* L) {
    luaL_newlib(L, networkingLib);
    return 1;
}
