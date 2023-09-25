# How to use git

1. Clone the repo
`git clone https://github.com/qburrke/HopHopEngine.git`

2. Set up your name and email for you git so you can push changes:
`git config --global user.name "INSERT GITHUB USENAME"` 
`git config --global user.email "INSERT YOUR EMAIL"`

3. Set up your own branch
`git branch dev-*NAME*` Ex. `git branch dev-caleb`

4. Switch to work in your branch
`git checkout dev-*NAME*`

5. Now you can make changes to the repo, please add your name to the README.md

6. To add this change to the main, first stadge the change, commit it, and then push it
`git add .`
`git commit -m "SOME COMMENT"`
`git push`

**NOTE:** When you push for the first time, you will be prompted for a password, copy and paste the following token: see discord

7. At this point, your changes are only pushed to **your** branch, to merge these changes to the `main` branch, login onto github in the browser, navigate to the `HopHopEngine` repo and click the green `Compare and create pull request`. From there "create the pull request".

**NOTE:** Indigo and I will have to review each pull request and once both of use approve only then will your branch be merged with the proteced main branch.
