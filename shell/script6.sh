3. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.
#!/bin/bash

while [ $# -gt 0 ]; do
    file=$1
    word=$2
    if [ -f "$file" ]; then
        #alternativa:
        #wordCount=`sed "s/\<\|\>/\n/g" "$file" | grep -c "\<$word\>"`
        wordCount=`grep -o "\<$word\>" "$file" | grep -c "\<$word\>"`
        if [ $wordCount -ge 3 ]; then
            echo "$file contains $word $wordCount times"
        fi
    fi
    shift 2
done


v2:

#!/bin/bash

while [ $# -gt 0 ]; do
    file=$1
    word=$2
    if [ -f $1 ]; then
       number=`grep -c "\<$word\>" "$file"`
         if [ $number -ge 3 ]; then
            echo "Exista"
            echo "$number"
        else
            echo "Nu exista"
         fi
    else
       echo "nimic"
     fi

    shift 2
done
