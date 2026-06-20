# 적용 방법

이 묶음은 GitHub에 바로 push할 수 없을 때, 로컬에서 안전하게 적용하도록 만든 파일입니다.

## Windows PowerShell 기준

```powershell
git clone https://github.com/Kimz1xq/data-structure-lab-2026-4.git
cd data-structure-lab-2026-4
# 이 zip의 내용물을 현재 폴더에 덮어쓰기 방식으로 압축 해제
.\scripts\reorganize_repo.ps1
git status
git add -A
git commit -m "chore: organize coursework repository"
git push origin master
```

`git push`에서 로그인 창이 뜨면 GitHub 계정과 토큰을 사용하면 됩니다. 토큰을 명령어에 직접 적는 방식은 기록에 남을 수 있으므로 권장하지 않습니다.

## macOS / Linux / Git Bash 기준

```bash
git clone https://github.com/Kimz1xq/data-structure-lab-2026-4.git
cd data-structure-lab-2026-4
# 이 zip의 내용물을 현재 폴더에 덮어쓰기 방식으로 압축 해제
bash scripts/reorganize_repo.sh
git status
git add -A
git commit -m "chore: organize coursework repository"
git push origin master
```
