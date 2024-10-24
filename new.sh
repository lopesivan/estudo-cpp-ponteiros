#!/usr/bin/env bash

prefix=ex-

ls ${prefix}*.cpp | sort -n -t'-' -k 2 |
	tail -1 |
	sed -e "s/${prefix}\([0-9]\+\).cpp/\1/" -e 's/^0//' |
	while read n; do printf "cp ${prefix}%02d.cpp ${prefix}%02d.cpp\n" "$n" "$((n + 1))"; done
