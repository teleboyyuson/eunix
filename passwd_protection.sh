#!/bin/bash

HASH="5e884898da28047151d0e56f8dc62927" # password: password

read -s -p "Enter password: " input
echo

input_hash=$(echo -n "$input" | md5sum | awk '{print $1}')

if [[ "$input_hash" == "$HASH" ]]; then
    echo "Access granted"
else
    echo "Access denied"
fi
