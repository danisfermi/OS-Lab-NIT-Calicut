#!/bin/bash
if [ $# -ne 1 ]
  then
  echo "1 Argument Expected. Please provide Directory Name"
  exit 1
fi
if [ -d "$1"]
  then
  echo "Directory Exists. Control Enters Directory."
else
  if [ -f "$1" ]  
    then 
    rm $1
    mkdir $1  
  else
    mkdir $1
  fi
fi