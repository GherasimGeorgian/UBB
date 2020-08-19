4. Sort all files given as command line arguments descending by size.
#!/bin/bash

while [ $# -gt 0 ]; do
    if [ -f "$1" ]; then
        a[$n]=`du -b "$1"`
        n=$((n+1))
    fi
    shift 1
done

n=$((n-1))
for i in $(seq 0 $n); do
    aux="$aux"$'\n'"${a[i]}"
done
aux="${aux:1}"
echo "$aux" | sort -rn

# shorter alternative
# printf '%s\n' "${a[@]}" | sort -nr

V2:

#!/bin/bash
while [ $# -gt 0 ]; do
    if [ -f "$1" ]; then
        a[$n]=`du -b "$1"`
        n=$((n+1))
    fi
    shift 1
done
n=$((n-1))
for i in $(seq 0 $n); do
    aux="$aux"$'\n'"${a[i]}"
done

echo "${aux:1}"|sort
