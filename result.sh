#!/bin/bash

for type in "C" "S"; do
	for i in 4 8 16 32 64 128 256 512 1024; do
		./bin/exec $i $type > result/$i$type.txt
	done
done
