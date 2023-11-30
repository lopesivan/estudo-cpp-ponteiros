#!/usr/bin/env bash

ls -rtl *.cpp |
	cut -d" " -f9 |
	while read -r file; do
		cat <<EOF
# $file

\`\`\`cpp
$(cat "$file")
\`\`\`
---
EOF
	done
