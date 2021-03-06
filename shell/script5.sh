2. Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.
#!/bin/bash

while true; do
    read input
    if [ "$input" = "stop" ]; then
        echo "Terminating..."
        exit 0
    fi
    if [ -f "$input" ]; then
        isText=$(file -b "$input" | grep -ic "text")
        if [ $isText -eq 1 ]; then
            echo "$input: `head -1 \"$input\" | wc -w`"
        fi
    else
        echo "$input is not a file!"
    fi
done