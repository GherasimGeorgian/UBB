#read from keyboard while stop
#!/bin/bash
while true; do
    read input
    if [ $input = "stop" ]; then
       echo "Finished...."
       exit 0
    fi
    if [ -f "$input" ]; then
       echo "$input"
    fi
done
