#!/bin/bash
if [ $# -ne 2 ]
  then
  echo "Not Enough Arguments. 2 Expected."
  exit 1
fi
cmp --silent $1 $2
if [[ $? -ne 0 ]]
  then 
  echo "The given files are different"
  else
  echo "The given files are same"
fi