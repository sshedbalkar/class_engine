#!/bin/bash

username=$(whoami)
limitsFile="/etc/security/limits.conf"
# pattern="^#<item>"
pattern="^$username"
entry1="$username hard core 1280"
entry2="$username soft core 1280"

echo "User: $username"

result=$(cat $limitsFile | grep $pattern)
len=${#result}
echo "Result: $result, len: $len"

if (( $len == 0 )); then 
    echo "No entry found"
    echo $entry1
else
    echo "Entry is already there"
fi
exit 0

# 1. Install coredumpctl
# 2. Make sure Output of: sysctl -n kernel.core_pattern
#       Is similar to: |/lib/systemd/systemd-coredump %P %u %g %s %t 9223372036854775808 %h

# Useful coredumpctl commands:
# $ coredumpctl // Lists all core dump files
# $ coredumpctl dump [PID|Name of the xecutable|Time of crash] // dumps core file
# $ coredumpctl debug [PID|Name of the xecutable|Time of crash] // debugs crash

# GDB commands:
# (gdb) bt                          // stack trace
# (gdb) bt full                     // Full stack trace
# (gdb) info threads                // info on running threads
# (gdb) thread apply all bt         // stack trace of all threads
# (gdb) thread apply all bt full    // full stack trace of all threads