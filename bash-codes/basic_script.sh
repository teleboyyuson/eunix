#!/bin/bash

# Basic Debian Bash Script
# Author: Your Name
# Date: YYYY-MM-DD

echo "Starting system check..."
echo

echo "User:"
whoami
echo

echo "System uptime:"
uptime
echo

echo "Updating package list (Debian-based)..."
sudo apt update
echo

echo "Disk usage:"
df -h
echo

echo "Script finished successfully."
