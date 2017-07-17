#!/bin/bash
if [ $# -ne 3]
then
  echo "Not Enough Arguments, 3 Expected"
  exit 1
fi
sed -i "s/$1/$2/" "$3"