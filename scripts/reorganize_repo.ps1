$ErrorActionPreference = "Stop"

function Ensure-Dir($path) {
    if (-not (Test-Path $path)) {
        New-Item -ItemType Directory -Force -Path $path | Out-Null
    }
}

function Move-RepoItem($src, $dst) {
    if (-not (Test-Path $src)) { return }
    if (Test-Path $dst) {
        Write-Host "Skip: '$dst' already exists. '$src' was not moved."
        return
    }

    $parent = Split-Path $dst -Parent
    if ($parent) { Ensure-Dir $parent }

    if (Test-Path ".git") {
        git mv $src $dst 2>$null
        if ($LASTEXITCODE -ne 0) {
            Move-Item $src $dst
        }
    } else {
        Move-Item $src $dst
    }
    Write-Host "Moved: $src -> $dst"
}

# Lecture / assignment / project root folders
$folders = @(
    "Lec01", "Lec02", "Lec04", "Lec05", "Lec09", "Lec10",
    "HW", "HW/HW2", "Project", "Project/AirlineBooking"
)
foreach ($f in $folders) { Ensure-Dir $f }

# Current repository cleanup: move existing root-level practice folders into lecture folders.
Move-RepoItem "HelloWorld"            "Lec01/HelloWorld"
Move-RepoItem "pointer"               "Lec02/pointer"
Move-RepoItem "poi"                   "Lec02/poi"
Move-RepoItem "ComplexTest"           "Lec04/ComplexTest"
Move-RepoItem "ComplexV4"             "Lec04/ComplexV4"
Move-RepoItem "Lec04_Class_Example"   "Lec04/Lec04_Class_Example"
Move-RepoItem "ArrayStack"            "Lec05/ArrayStack"
Move-RepoItem "Binary_Heap"           "Lec09/Binary_Heap"
Move-RepoItem "Lec09_Trees.ipynb"     "Lec09/Lec09_Trees.ipynb"
Move-RepoItem "DFS_BFS"               "Lec10/DFS_BFS"
Move-RepoItem "Lec10_Graph"           "Lec10/Lec10_Graph"
Move-RepoItem "WgraphMST"             "Lec10/WgraphMST"
Move-RepoItem "Word.txt"              "Lec10/Word.txt"

# Keep empty HW/HW2 visible in Git until actual HW2 code is added.
if (-not (Get-ChildItem "HW/HW2" -Force -ErrorAction SilentlyContinue)) {
    New-Item -ItemType File -Force -Path "HW/HW2/.gitkeep" | Out-Null
}

# Do not upload IDE/cache folders.
if (Test-Path ".vs") {
    if (Test-Path ".git") { git rm -r --cached .vs 2>$null | Out-Null }
    Remove-Item ".vs" -Recurse -Force -ErrorAction SilentlyContinue
}
if (Test-Path ".vscode") {
    if (Test-Path ".git") { git rm -r --cached .vscode 2>$null | Out-Null }
}

Write-Host ""
Write-Host "Repository structure cleanup is complete. Run: git status"
