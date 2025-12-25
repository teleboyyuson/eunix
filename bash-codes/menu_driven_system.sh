#!/bin/bash

if [ ! -t 1 ]; then
    echo "Must be run in a terminal"
    exit 1
fi

show_date() {
    date +"%Y-%m-%d %H:%M:%S"
}

disk_usage() {
    df -h | grep -E '^/dev'
}

memory_usage() {
    free -h
}

while true; do
    echo "==== System Utility ===="
    echo "1) Show date"
    echo "2) Disk usage"
    echo "3) Memory usage"
    echo "4) Exit"
    read -p "Choose: " choice

    case "$choice" in
        1) show_date ;;
        2) disk_usage ;;
        3) memory_usage ;;
        4) break ;;
        *) echo "Invalid option" ;;
    esac
done
