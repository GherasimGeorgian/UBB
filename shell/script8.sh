5. Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file.
#!/bin/bash

while [ $# -gt 0 ]; do
    if [ -f "$1" ]; then
        isCFile=`file -b "$1" | grep -c "ASCII C program text"`
        if [ $isCFile -eq 1 ]; then
            libs="$libs"$'\n'"`grep "#include" $1`"
        fi
    fi
    shift 1
done
echo "$libs" | sort | uniq > libs




#!/bin/bash

while [ $# -gt 0 ]; do
      if [ -f "$1" ]; then
         isFileC=`file $1|grep -c "C source, ASCII text"`
                if [ $isFileC -ge 1 ]; then
                        librarii="$librarii"$'\n'"`grep "#include" $1`"
                fi
      fi
      shift 1
done
echo "$librarii"|sort| uniq >librarii.txt
