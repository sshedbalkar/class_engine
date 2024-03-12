#!/bin/bash

# Script to terminate a process
# $1 = name of the process
proc_name=$1

# Exclude everything but the process with TTY = pts/0
exclude_term_process_regex="^((?!pts\/[123456789])[\s\S])*$"
# echo $proc_name
processes=`/bin/ps -fu $USER| grep $proc_name | grep -P $exclude_term_process_regex`
# echo "Procs: $processes"
proc_ids_string=`awk '{print $2}' <<< "$processes"`
proc_ids=($proc_ids_string)

# echo PID: $proc_ids
if [ "${#proc_ids[@]}" -gt 0 ]; then
    echo "Killing: $proc_name with PID: ${proc_ids[@]}"
    kill -9 "${proc_ids[@]}"
fi

