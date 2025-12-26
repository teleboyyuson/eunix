#!/bin/bash
file="notes_$(date +%F).txt"
read -p "Note: " n
echo "$n" >> "$file"
