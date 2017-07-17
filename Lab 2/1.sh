#!/bin/bash
if [ $# -ne 1 ]
  then
  echo "Not Enough Arguments. 1 Expected."
  exit 1
fi
if [[ `expr $1 % 2` -ne 0 ]]
  then
  echo "Given Number is Odd"
else
  echo "Given Number is Even"
fi