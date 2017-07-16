#!/bin/bash
hour=$(date +"%H")
if [ $hour -gt 12 ]
then
    echo "Good Afternoon"
else
    echo "Good Morning"
fi