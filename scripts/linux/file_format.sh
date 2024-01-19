#!/bin/bash

filename=$(basename -- "$1")
extension="${filename##*.}"
filename="${filename%.*}"

#echo "Filename: $filename, ext: $extension"

cpp_files=( c cpp h hpp cc )

for item in "${cpp_files[@]}"; do
    if [[ $extension == "$item" ]]; then
        clang-format -i "$1"
        exit 0
    fi
done

exit 0