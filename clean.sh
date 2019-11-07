#!/bin/bash

# rm all .out file
find . -name "*.out" | xargs rm
find . -name "*core" | xargs rm

