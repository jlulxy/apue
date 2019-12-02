#!/bin/bash

for i in {1...1000}
do
	kill -USR1 $1 
	kill -USR2 $1
done

