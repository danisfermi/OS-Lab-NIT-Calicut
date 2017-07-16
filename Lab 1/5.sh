#!/bin/bash
if [ $# -ne 3]
then
  echo "Not Enough Arguments, 3 Expected"
fi
sed -i "s/$1/$2/" "$3"