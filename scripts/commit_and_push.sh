#!/usr/bin/env bash
set -euo pipefail
msg="${1:-chore: organize data structure lab repository}"

git status
git add -A
git commit -m "$msg"
git push origin master
