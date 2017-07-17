#!/bin/bash
if [ $# -ne 0 ]
  then
  echo "No Arguments Expected."
  exit 1
fi
read -p "Enter the Filename in which you wish to search for: " path
read -p "Enter the New Directory Name: " dirh
mkdir $dirh
mv -r $path/\.[^.]* $dirh/