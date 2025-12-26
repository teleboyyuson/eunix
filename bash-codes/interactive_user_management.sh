#!/bin/bash

add_user() {
    read -p "Username: " user
    sudo useradd "$user" && echo "User added"
}

delete_user() {
    read -p "Username: " user
    sudo userdel "$user" && echo "User deleted"
}

while true; do
    echo "1) Add User"
    echo "2) Delete User"
    echo "3) Exit"
    read -p "Choice: " choice

    case $choice in
        1) add_user ;;
        2) delete_user ;;
        3) break ;;
        *) echo "Invalid option" ;;
    esac
done
