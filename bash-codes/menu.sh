#!/bin/bash

echo "Enter one number in this following options:"
echo "1) Show date"
echo "2) Show user"
echo "3) Show uptime"
read choice

case $choice in
    1) date ;;
    2) whoami ;;
    3) uptime ;;
    *) echo "Invalid option" ;;
esac
