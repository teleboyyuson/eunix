#!/bin/bash

sleep 100 &
PID=$!

echo "Job started with PID $PID"
sleep 5

kill "$PID"
echo "Job stopped"
