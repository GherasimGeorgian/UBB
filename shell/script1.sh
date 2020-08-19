//afisare doar fisiere text dintr-un folder
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Please provide exactly one argument"
fi

sum=0
for i in "$1"/*; do
    if [ -f "$i" ]; then
        fisier_text=$(file "$i"|grep -c "text")
        if [ $fisier_text -eq 1 ]; then
           echo "$i"
        fi
    fi
done

echo "Total size: $sum"
