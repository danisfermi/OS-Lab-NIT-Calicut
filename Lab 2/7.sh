#!/bin/bash
i=1
while [ `find $1 -mindepth $i -maxdepth $i -type d | wc -l` -gt 0 ]
  do
  find "$1" -mindepth $i -maxdepth $i -type d
  let i++
done