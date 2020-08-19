#afisare index + continut pentru fiecare linie
#!/bin/awk
BEGIN {
    v=0
}

{
v++
print v, $0
}

END {
    }
