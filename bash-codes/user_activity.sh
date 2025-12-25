#!/bin/bash

echo "Active users:"
who | awk '{print $1}' | sort | uniq | while read user; do
    sessions=$(who | grep "^$user " | wc -l)
    printf "%-10s %d session(s)\n" "$user" "$sessions"
done
