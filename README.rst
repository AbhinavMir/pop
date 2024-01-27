The idea is to implement a simple git-like SCM using C++, and have it implement some very basic commands. Namely:
1. `init` - initialize a new repository
2. `add` - add a file to the staging area
3. `commit` - commit the staged files
4. `status` - show the status of the repository
5. `log` - show the commit history
6. `checkout`, `reset`, `branch`, `merge` 
7. `rebase` - rebase the current branch on top of another branch
8. `squash` - squash commits into one
9. `cherry-pick` - pick a commit from another branch and apply it to the current branch
10. `hash-object` - hash an object
11. `cat-file` - show the contents of an object

I'm not re-inventing the WHL, I'm just learning git and C++. 