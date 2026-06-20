#!/usr/bin/env bash
set -euo pipefail

ensure_dir() { mkdir -p "$1"; }

move_repo_item() {
  local src="$1"
  local dst="$2"
  [[ -e "$src" ]] || return 0
  if [[ -e "$dst" ]]; then
    echo "Skip: '$dst' already exists. '$src' was not moved."
    return 0
  fi
  mkdir -p "$(dirname "$dst")"
  if [[ -d .git ]]; then
    git mv "$src" "$dst" 2>/dev/null || mv "$src" "$dst"
  else
    mv "$src" "$dst"
  fi
  echo "Moved: $src -> $dst"
}

for f in Lec01 Lec02 Lec04 Lec05 Lec09 Lec10 HW HW/HW2 Project Project/AirlineBooking; do
  ensure_dir "$f"
done

move_repo_item "HelloWorld"          "Lec01/HelloWorld"
move_repo_item "pointer"             "Lec02/pointer"
move_repo_item "poi"                 "Lec02/poi"
move_repo_item "ComplexTest"         "Lec04/ComplexTest"
move_repo_item "ComplexV4"           "Lec04/ComplexV4"
move_repo_item "Lec04_Class_Example" "Lec04/Lec04_Class_Example"
move_repo_item "ArrayStack"          "Lec05/ArrayStack"
move_repo_item "Binary_Heap"         "Lec09/Binary_Heap"
move_repo_item "Lec09_Trees.ipynb"   "Lec09/Lec09_Trees.ipynb"
move_repo_item "DFS_BFS"             "Lec10/DFS_BFS"
move_repo_item "Lec10_Graph"         "Lec10/Lec10_Graph"
move_repo_item "WgraphMST"           "Lec10/WgraphMST"
move_repo_item "Word.txt"            "Lec10/Word.txt"

if [[ -z "$(find HW/HW2 -mindepth 1 -maxdepth 1 2>/dev/null)" ]]; then
  touch HW/HW2/.gitkeep
fi

if [[ -e .vs ]]; then
  [[ -d .git ]] && git rm -r --cached .vs 2>/dev/null || true
  rm -rf .vs
fi
if [[ -e .vscode && -d .git ]]; then
  git rm -r --cached .vscode 2>/dev/null || true
fi

echo
echo "Repository structure cleanup is complete. Run: git status"
