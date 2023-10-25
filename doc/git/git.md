# How to use git

1. Clone the repo
`git clone https://github.com/qburrke/HopHopEngine.git`

2. Set up your name and email for you git so you can push changes:

```bash
git config --global user.name "INSERT GITHUB USENAME"
git config --global user.email "INSERT YOUR EMAIL"
```

3. Set up your own branch. Ex. `git branch dev-caleb`

4. Switch to work in your branch
`git checkout dev-*NAME*`

5. Now you can make changes to the repo, please add your name to the `README.md`

6. To add this to the repo:
```bash
git add .
git commit -m "SOME COMMENT"
git push origin dev-*NAME*
```

7. The next step from here is adding you changes on your branch to the `dev` branch. The `dev` branch is where all features go to that aren't quite ready to go to `main`

```bash
git checkout dev-*NAME*
git branch dev           # If dev branch does not exist
git merge dev dev-*NAME* # if dev branch does exist
git push origin dev
```

8. To merge these changes to the `main` branch, login onto github in the browser, navigate to the repo and click the green `Compare and create pull request`

>**NOTE:** Indigo and I will have to review each pull request and once both of use approve only then will your branch be merged with the proteced main branch.

>**NOTE:** When you push for the first time, you will be prompted for a password, copy and paste the following token: see discord
