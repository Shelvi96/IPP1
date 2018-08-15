#!/bin/bash

for f in *.in; do
  ./brute <${f} >${f%.in}.out 2>${f%.in}.err
done
