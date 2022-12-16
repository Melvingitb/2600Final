#!/bin/bash
INPUT=""
while true
do
     | while read -r payload
    do
        if [[ "$payload" == "1" ]]; then
            echo "Input detected"
            ./auto.sh
        fi
    done
    
done