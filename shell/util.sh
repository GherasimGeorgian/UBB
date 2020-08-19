#!/bin/bash
while [ $# -gt 0 ]; do
    if [ -f "$1" ]; then
        a[$n]=`du -b "$1"`
        n=$((n+1))
    fi
    shift 1
done

Numarul de elemente din vector:
${#a[@]}

Elemente for intr-o linie
for ((i=0; i<${#a[@]}; i++)); do
     aux="$aux"$'\n'"${a[i]}"
done
Afisare elemente linie cu linie
echo "${aux:1}"
 

//////

#!/bin/bash

fisier=$1
if [ -z "$fisier" ]; then
    echo "Invalid command" >&2
    exit 1
fi

declare -A users

command=`awk -F' ' '{print $1}' $fisier`
while  read line; do
          users[$line]=$(($line))
        done <<< "$command"
for i in "${!users[@]}"; do
    echo "$i"
done

$0 linia curenta


Afisare primul argument

#!/bin/bash
echo $1


Afisare numar de argumente 

#!/bin/bash
echo $#



Numar infinit de argumente

#!/bin/bash

while [ $# -gt 0 ]; do
    file=$1
    word=$2
    echo "$1 $2"
    shift 2
done




Afisare int

#!/bin/bash
v=0
echo $v



fisier_text=$(file "$i"|grep -c ".txt")


dimensiune=$(wc -c "$i" |cut -d ' ' -f 1)


suma
sum=$((sum+dimensiune))


Testeaza daca numarul de argumente nu este egal cu 1 atunci mesaj
#!/bin/bash
if [ $# -ne 1 ]; then
   echo "Te rog introdu un singur argument!"
fi


 if [ $fisier_text -eq 1 ]; then

Afisare fisiere dintr-un folder
for i in `ls "$1"`; do
    echo $i
done


for i in "$1"/*; do
    if [ -f "$i" ]; then

extension file
find . -type f -name "*.txt"


echo "$input: `head -1 \"$input\" | wc -w`"