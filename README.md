# WhimsicalWizardry

:)

## Branch naming conventions
  - First and Last Name initials - and whatever you are working, feature, fixes.
  - e.g. CM-CharacterMovement

### Create new branch whenever you are working on something new.
New branches should be created from main, unless you are working off another branch. This in order to prevent many conflicts when syncing older branches. 
Small warning, Blueprints can be overwritten completely if multiple people are working on it.
### Steps to making a new branch using Git Commands
1. Clone the repo.(skip if you already cloned)
```
git clone URL
```
2. Update local repo from origin using fetch
```
git fetch origin
```
3. Create new branch
```
git checkout -b CM-BranchName
```

#### Git commands
Push
```
git push                      //works for current branch
git push origin BranchName  
```
Pull
```
git pull                      //Fetches and merges remote branch into current branch.
git pull origin BranchName    //Recieves files from another branch.
```
Status
```
git status
```
Adding files to commit
```
git add .                     //Adds all missing files.
git add FolderName/FileName   //Adding file from a folder.
git add FolderName/\*.txt     //Adding all files with same extension in the folder.
```
Commits
```
git commit -m "Message"
```
Branches
```
git branch                  //Shows all local branches
git branch                  //Shows all local and remote branchs
```
## Whenever you are done your branch, make a pull request.
  - Build Engineer will look over any changes, along with another Coder to help verify (if conflicts arise).
  - Later on the branches after merging will be deleted. Note: that branches deleted from the GitHub, are removed remotely. Locally is it still available on the PC if it is still on the system. Cautious: may be deleted if you fetch from origin.

### Steps to making a new pull request.
1. Once you think you are done with your branch. Commit and push to your branch.
2. Confirm your commit, by checking your branch on github.
3. On github, in your branch or view all branches, click the new pull request button.
	- in the branch click Contritube and then Open pull request.
