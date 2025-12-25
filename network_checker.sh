#!/bin/bash

hosts=("google.com" "github.com" "localhost")

for host in "${hosts[@]}"; do
    if ping -c 1 "$host" &>/dev/null; then
        echo "$host is UP"
    else
        echo "$host is DOWN"
    fi
done
