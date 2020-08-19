10. Write a script that receives program/process names as command line arguments.
 The script will monitor all the processes in the system,
 and whenever a program with one of those names is run, 
the script will kill it and display a message. (see commands ps, kill, killall)

#!/bin/bash

command=$1
if [ -z "$command" ]; then
    echo "Invalid command" >&2
    exit 1
fi

while true; do
        process_id=`ps -ef | grep -i "$1"| grep -v "$$" | awk '{print $2}'`
        while read line; do
                pid=$$
               if [[ "$pid" !=  "$linie" ]]; then
                        echo $pid
                        echo $line
                        result=`kill -KILL "$line"`
                sleep 4
                fi
        done <<< "$process_id"
                sleep 1
done
