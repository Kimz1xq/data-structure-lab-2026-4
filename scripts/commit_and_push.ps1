param(
    [string]$CommitMessage = "chore: organize data structure lab repository"
)

$ErrorActionPreference = "Stop"

git status
git add -A
git commit -m $CommitMessage
git push origin master
