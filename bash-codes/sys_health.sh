#!/bin/bash
cpu=$(ps -eo %cpu | awk '{sum+=$1} END {print sum}')
mem=$(free | awk '/Mem/ {printf "%.0f", $3/$2*100}')
[[ ${cpu%.*} -gt 80 || $mem -gt 80 ]] && echo -e "\e[31mHIGH USAGE\e[0m" || echo OK
