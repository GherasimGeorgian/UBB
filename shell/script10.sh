7. Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists (will return false if the target to which the link points does not exist)
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Provide exactly one argument"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "$1 is not a directory"
    exit 1
fi

for f in `find  "$1" -type l`; do
    if [ ! -e "$f" ]; then
        echo "$f"
    fi
done
