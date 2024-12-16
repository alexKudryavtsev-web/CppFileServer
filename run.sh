#!/bin/bash
set -e # Exit on any error

./test_main

if [ $? -ne 0 ]; then
  echo "Tests failed. Exiting."
  exit 1
fi

./main
