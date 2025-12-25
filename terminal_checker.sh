#!/bin/bash

echo "Shell: $SHELL"
echo "PID: $$"

if [ -t 1 ]; then
    echo "Running in terminal"
else
    echo "Not a terminal"
fi
