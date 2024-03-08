# Class Engine
## _Simple and modular 2D Engine_

## Dependencies
Class Engine uses the following  dependencies
### Required
| Dependency | Version |Comment|
|-----------|----------|-------|
| Linux Kernel|6.2.0-39-generic|
|gcc|12.3.0|
|g++|12.3.0|
|build-essential|12.9ubuntu3|
|gdb|13.1|
|cmake|3.25.1|
|ninja-build|1.11.1|
|libsdl2-dev|2.26.3+dfsg-1|For rendering|
|libsdl2-ttf-dev|2.20.1+dfsg-2|
|pkg-config|1.8.1|
|valgrind|3.22.0|
|valgrind-devel|3.22.0|Download [valgrind-client-headers](ttps://rpmfind.net/linux/RPM/opensuse/15.6/noarch/valgrind-client-headers-3.22.0-150600.1.1.noarch.html), and [valgrind-devel](https://rpmfind.net/linux/RPM/opensuse/tumbleweed/x86_64/valgrind-devel-3.22.0-2.1.x86_64.html) (Requires `alien` for rpm installation on `ubuntu`)|

### Optional
| Dependency | Version |Comment|
|-----------|----------|-------|
|Ubuntu|Ubuntu 22.04|
|[coredumpctl](https://github.com/sshedbalkar/class_engine?tab=readme-ov-file#coredumpctl)|249.11-0ubuntu3.12|To analyze core dump files on `ubuntu`|
|snap|2.61.1|For installing `valgrind`|
|alien|8.95.5|For installing `rpm` packages on `ubuntu`|

## Tool specific info
### Coredumpctl
#### Installation
- Install 

    `coredumpctl`

- Make sure Output of the following command is similar
```sh
sysctl -n kernel.core_pattern
|/lib/systemd/systemd-coredump %P %u %g %s %t 9223372036854775808 %h
```
#### Useful commands
- List all core dump files

    `coredumpctl`

- Dump core file

    `coredumpctl dump [PID|Name of the xecutable|Time of crash]`

- Debug a crash

    `coredumpctl debug [PID|Name of the xecutable|Time of crash]`

### GDB
[Reference](docs/GDB_README.md)

### Useful Links
[Go to page](docs/LINKS_README.md)

