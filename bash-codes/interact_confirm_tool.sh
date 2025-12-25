#!/bin/bash

confirm() {
    read -p "$1 (y/n): " ans
    case "$ans" in
        y|Y) return 0 ;;
        *) return 1 ;;
    esac
}

echo "An update is now available..."

if confirm "Proceed with action?"; then
    echo "Confirmed"
else
    echo "Cancelled"
fi
