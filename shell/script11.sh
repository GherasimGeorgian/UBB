8. Write a bash script that receives a folder name as argument. Find recursively in the folder the number of times each file name is repeated.
#!/bin/bash

# with arrays; not entirely cool
# change IFS to handle files with spaces
ifs_bkc=$IFS
IFS=$'\n'
if [ $# -ne 1 ]; then
    echo "Provide exactly one argument"
    exit 0
fi

if [ ! -d "$1" ]; then
    echo "$1 is not a directory"
fi

declare -A arr

for f in `find "$1" -type f`; do
    fname=`echo "$f" | awk -F'/' '{print $NF}'`
    arr[$fname]=$((arr[$fname]+1))
done

for f in ${!arr[@]}; do
    echo "${arr[$f]} $f"
done

IFS=$ifs_bkc

#one liner without arrays; entirely cool
find "$1" -type f | awk -F'/' '{print $NF}' | sort | uniq -c


V2:
#!/bin/bash

ifs_bkc=$IFS
IFS=$'\n'

if [ $# -ne 1 ]; then
        echo "Provide exactly one argument"
        exit 0
fi

if [ ! -d "$1" ]; then
        echo "$1 is not a directory"
fi

n=0

for something in `find "$1" -type f`; do
           a[$n]=`echo "$something" | awk -F'/' '{print $NF}'`
           n=$((n+1))
done
for ((i=0; i<${#a[@]}; i++)); do
     aux="$aux"$'\n'"${a[i]}"
done

echo "${aux:1}"|sort|uniq -c