#!/bin/bash
if [ $# -ne 2 ]
then
    echo 'Not Enough Arguments. 2 Needed'
    exit 1
fi
add() {
  echo `expr $1 + $2`
}
add $1 $2