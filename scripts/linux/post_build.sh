#!/bin/bash

fonts_dir=~/WorkWork/MyProjects/cpp/class_engine/src/lib/gui/imgui/misc/fonts

CreateSymlink () {
    symlink=$1
    dest=$2
    if [ -L ${symlink} ] ; then
       if [ ! -e ${symlink} ] ; then
          echo "[POST] Broken link, recreating: $symlink"
          rm $symlink
          ln -s $dest $symlink
       fi
    elif [ -e ${symlink} ] ; then
       echo "[POST] Not a link, recreating: $symlink"
       rm $symlink
       ln -s $dest $symlink
    else
       echo "[POST] Missing, creating new: $symlink"
       ln -s $dest $symlink
    fi
}

cd $1
CreateSymlink fonts $fonts_dir

exit 0