#!/bin/bash
if [ $# -ne 3 ]
  then
  echo "Not Enough Arguments. 3 Expected."
  exit 1
fi
sed -n "$2,$3p" "$1"