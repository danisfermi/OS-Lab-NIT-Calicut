#!/bin/bash
if [ $# -ne 1 ]
  then
  echo "Not Enough Arguments. 1 Expected."
  exit 1
fi
find $1/ -size  0 -print0 |xargs -0 rm