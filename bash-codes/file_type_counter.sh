#!/bin/bash
declare -A c
for f in *.*; do ((c[${f##*.}]++)); done
for k in "${!c[@]}"; do echo "$k ${c[$k]}"; done
