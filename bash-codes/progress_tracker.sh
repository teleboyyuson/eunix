#!/bin/bash
for i in {1..20}; do
  printf "\rProgress: %d%%" $((i*5))
  sleep 0.1
done
echo
