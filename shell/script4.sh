1. Write a bash script that calculates the sum of the sizes of all text files in a given folder.

#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Please provide exactly one argument"
fi

sum=0
for i in "$1"/*; do
    if [ -f "$i" ]; then
        fisier_text=$(file "$i"|grep -c ".txt")
        if [ $fisier_text -eq 1 ]; then
           dimensiune=$(wc -c "$i" |cut -d ' ' -f 1)
           sum=$((sum+dimensiune))
        fi
    fi
done

echo "Total size: $sum"