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