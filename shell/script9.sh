
6. Seminar problem: Write a script that monitors the state of a given folder and prints a message when something changed.
#!/bin/bash

D=$1
if [ -z "$D" ]; then
    echo "No directory provided" >&2
    exit 1
fi

if [ ! -d "$D"  ]; then
    echo "Directory $D does not exist" >&2
    exit 1
fi

OLD_STATE=""
while true; do
    STATE=""
    for P in `find $D`; do
        if [ -f $P ]; then
            props=`ls -l $P | sha1sum`
            content=`sha1sum $P`
        elif [ -d $P ]; then
            props=`ls -ld $P | sha1sum`
            content=`ls -l $P | sha1sum`
        fi
        STATE="$STATE"$'\n'"$props $content"
    done
    if [ -n "$OLD_STATE" ] && [ "$STATE" != "$OLD_STATE" ]; then
        echo "Directory state changed"
    fi
    OLD_STATE=$STATE
    sleep 1
done


V2:

#!/bin/bash
director=$1
if [ -z "$director" ]; then
   echo "Numele directorului este invalid" >&2
   exit 0
fi

if [ ! -d "$director" ]; then
   echo "Directorul $director nu exista" >&2
   exit 0
fi

stare_veche=""

while true; do
        stare_curenta=""
        for something in `find $director`; do
            if [ -f $something ]; then
               props=`ls -l $something | sha1sum`
               content=`sha1sum $something`
            elif [ -d $something ]; then
               props=`ls -ld $something | sha1sum`
               content=`ls -l $something | sha1sum`
            fi
            stare_curenta="$stare_curenta"$'\n'"$props $content"
        done
        if [ -n "$stare_veche" ] && [ "$stare_curenta" != "$stare_veche" ]; then
            echo "S-a produs o schimbare in director!"
        fi
        stare_veche=$stare_curenta
        sleep 1
done
