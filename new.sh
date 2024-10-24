#!/usr/bin/env bash

ls -rtl *.cpp |
	cut -d" " -f9 |
	sort -n |
	tail -1 |
	sed -e 's/ex-\([0-9]\+\).cpp/\1/' -e 's/^0//' |
	while read n; do printf "cp ex-%02d.cpp ex-%02d.cpp\n" "$n" "$((n + 1))"; done
