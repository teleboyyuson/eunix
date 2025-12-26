#!/bin/bash
cut -d: -f1 /etc/passwd | while read u; do echo "User: $u"; done
