# Version Control
Our teams chosen version control will be done through Git, and hosted on Github. The current stable build of our engine we live in the `main` branch.

## Contributing
Those looking to contribute to the repo must create their own seperate branch off of main. This branch must have the following naming convention: `TYPE-NAME`. 

For example, Bob wants to contribute on the engine. So his branch would be: `dev-bob`. If bob wanted to contribute documentaion, his branch would be: `doc-bob`.

## Merging changes into production
The first step in merging changes onto the `main` branch is ensuring a contributer's branch is up to date with the current stable release(i.e `main`). Once up to date, a contributer must perform the following steps:

1. Merge contributor's branch into `dev` and resolve any merge conflicts.
2. Push `dev` onto remote (i.e github)
3. Create a pull request to initiate a review of the changes.
4. Make any necessary revisions based on feedback from the reviewers (See Pull Requests for more)
5. After approval from the reviewers, the changes on `dev` will be merged into the `main` branch with the contributors branch deleted

> If the `dev` branch currently does not exist, create it off of the `main` branch.

## Pull Requests
All contributions integrating into `main` must be done through a Github pull request. A pull request is a necessary step for the team to review changes before merged into the `main` branch. For a pull requests to be closed it must be accepted from all the reviewers.

## Reviewers
Caleb Burke
Indigo Stusek

## Standards
Contributors are expected to adhere to all our standards found in `doc/standards.md`.

## Reporting Issues
If you find any issues, please open an issue on Github providing a description of the issue and how to reproduce it.

