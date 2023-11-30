#!/usr/bin/env bash

ls -rtl *.cpp |
	cut -d" " -f9 |
	tail -1 |
	sed 's/ex-\([0-9]\+\).cpp/\1/' |
	while read n; do printf "cp ex-%02d.cpp ex-%02d.cpp\n" "$n" "$((n + 1))"; done |
	sh
