## Prints/returns the ibytes/obytes of a network interface with a timestamp.

### CLI
`make install-cli`

Usage:
```
netspeed en0
```

### Lua
`make install`

Usage:
```
❯ lua
Lua 5.2.4  Copyright (C) 1994-2015 Lua.org, PUC-Rio
> networking = require("mjolnir._asm.sys.networking")
> stats = networking.getstats("en0")
> print(stats)
table: 0x7ff8b8d01f30
> print(stats.obytes)
35755471
> print(stats.ibytes)
983379907
> print(stats.time_usec)
1.4770109435675e+15
>
```
