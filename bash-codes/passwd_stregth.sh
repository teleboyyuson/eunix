#!/bin/bash

read -s -p "Enter password: " pass
echo

length=${#pass}

if [[ $length -ge 8 && "$pass" =~ [A-Z] && "$pass" =~ [0-9] ]]; then
    echo "Strong password"
else
    echo "Weak password"
fi
