##Prints/returns the ibytes/obytes of a network interface with a timestamp.

### CLI
`make install-cli`
Usage: `netspeed en0`

### Lua
`make install`
Usage:
```
❯ lua
Lua 5.2.4  Copyright (C) 1994-2015 Lua.org, PUC-Rio
> networking = require("mjolnir._asm.sys.networking")
> print(networking.getstats())
table: 0x7febc3e0a3f0
> print(networking.getstats().ibytes)
513867624
> print(networking.getstats().obytes)
19964834
> print(networking.getstats().time_sec)
1476994779
> print(networking.getstats().time_usec)
162524
>
```
