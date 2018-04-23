# Git Book
## 1. Getting Started
## 2. Git Basics
### Git Basics-Recording Changes to the Repository
#### Removing Files
To remove a file from Git, you have to remove it from your tracked files (more accurately, remove it from your staging area) and then commit it. The `git rm` command does that, and also removes the file from your working directory so you don't see it as untracked file the next time around.
If you simply remove the file from your working directory, it shows up under the "Changes not staged for commit" (that is, *unstaged*) area of your `git status` output:

        $ rm PROJECTS.md
        $ git status
        On branch master
        Your branch is up-to-date with 'origin/master'.
        Changes not staged for commit:
        (use "git add/rm <file>..." to update what will be committed)
        (use "git checkout -- <file>..." to discard changes in working directory)

                deleted:    PROJECTS.md
        no changes added to commit (use "git add" and/or "git commit -a")
Then, if you run `git rm`, it stages the file's removal:

        $ git rm PROJECTS.md
        rm 'PROJECTS.md'
        $ git status
        On branch master
        Your branch is up-to-date with 'origin/master'.
        Changes to be committed:
        (use "git reset HEAD <file>..." to unstage)

            deleted: PROJECTS.md
The next time you commit, the file will be gone and no longer tracked. If you modified the file and added it to the staging area already, you must force the removal with the `-f` option. This is a safety feature to prevent accidental removal of data that hasn't yet been recorded in a snapshot and that can't be recovered from Git.
Another useful thing you may want to do is to keep the file in your working tree but remove it from your staging area. In other words, you may want to keep the file on your hard drive but not have Git track it anymore. This is particulary useful if you forgot to add something to your `.gitignore` file and accidentally staged it, like a large log file or a bunch of `.a` compiled files. To do this, use the `--cached` option(similar with `git update-index --remove` or `git update-index --force-remove`):

        $ git rm --cached README
You can pass files, directories, and file-glob patterns to the `git rm` command. That means you can do things such as:

        $ git rm log/\*.log
Note the backslash in front of the `*`. This is necessary because Git does its own filename expansion in addition to your shell's filename expansion. This command removes all files that have the `.log` extension in the `log/` directory. Or, you can do something like this:

        $ git rm \*~
This command removes all files whose names end with a `~`.
#### Moving Files
Unlike many other VCS systems, Git doesn't explicitly track file movement. If you rename a file in Git, no metadata is stored in Git that tells it you renamed the file. However, Git is pretty smart about figuring that out after the fact-we'll deal with detecting file movement a bit later.
Thus it's a bit confusing that Git has a `mv` command. If you want to rename a file in Git, you can runn something like this:

        $ git mv file_from file_to
and it works fine. In fact, if you run something like this and look at the status, you'll see that Git considers it a renamed file:

        $ git mv README.md README
        $ gi status
        On branch master
        Your branch is up-to-date with 'origin/master'.
        Changes to be committed:
            (use "git reset HEAD <file>..." to unstage)

            renamed: README.md -> REAME
However, this is equivalent to running something like this:

        $ mv README.md README
        $ git rm README.md
        $ git add README
Git figures out that it's a rename implicitly, so it doesn't matter if you rename a file that way or with the `mv` command. The only difference is that `git mv` is one command instead of three-it's a convenience function. More importantly, you can use any tool you like to rename a file, and address tha add/rm later, before you commit.
Summary:for untracked files, use `rm`;
        for tracked files and staged files: `git rm --cached` to delete from stage area and the file will become untracked; `git rm --f` to delete both from stage area and working directory.
### 2.3 Git Basics-Viewing the Commit History
#### Viewing the Commit History
After you have created several commits, or if you have cloned a repository with an existing commit history, you'll probaly want to look back to see what has happened. The most basic and powerful tool to do this is the `git log` command.
These examples use a very simple project called "simplegit". To get the project, run

        $ git clone https://github.com/schacon/simplegit-progit
When you run `git log` in this project, you should get output that looks something like this:

        $ git log
        commit ca82a6dff817ec66f44342007202690a93763949
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Mar 17 21:52:11 2008 -0700

            changed the version number

        commit 085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Sat Mar 15 16:40:33 2008 -0700

            removed unnecessary test

        commit a11bef06a3f659402fe7563abf99ad00de2209e6
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Sat Mar 15 10:31:28 2008 -0700

            first commit
By default, with no arguments, `git log` lists the commits made in that repository in reverse chronological order-that is, the most recent commits show up first. As you can see, this command lists each commit with its SHA-1 checksum, the author's name and email, the date written, and the commit message.
A huge number ana variety of options to the `git log` command are available to show you exactly what you're looking for. Here, we'll show you some of the most popular.
One of the more helpful options is `-p` or `--patch`, which shows the difference (the *patch* output) introduced in each commit. You can also limit the number of log entries displayed, such as using `-2` to show only the last two entries.

        $ git log -p -2
        commit ca82a6dff817ec66f44342007202690a93763949
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Mar 17 21:52:11 2008 -0700

            changed the version number

        diff --git a/Rakefile b/Rakefile
        index a874b73..8f94139 100644
        --- a/Rakefile
        +++ b/Rakefile
        @@ -5,7 +5,7 @@ require 'rake/gempackagetask'
         spec = Gem::Specification.new do |s|
            s.platform = Gem::Platform::RUBY
            s.name     = "simplegit"
        -   s.version  = "0.1.0"
        +   s.version  = "0.1.1"
            s.author   = "Scott Chacon"
            s.email    = "schacon@gee-mail.com
            s.summary  = "A simple gem for using Git in Ruby code."

        commit 085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Sat Mar 15 16:40:33 2008 -0700

            removed unnecessary test

        diff --git a/lib/simplegit.rb b/lib/simplegit.rb
        index a0a60ae..47c6340 100644
        --- a/lib/simplegit.rb
        +++ b/lib/simplegit.rb
        @@ -18,8 +18,3 @@ class SimpleGit
            end

        end
        -
        -if $0 == __FILE__
        -  git = SimpleGit.new
        -  puts git.show
        -end
This option displays the same information but with a diff directly following each entry. This is very helpful for code review or to quickly browse what happened during a series of commits that a collaborator has added. You can also use a series of summarizing options with `git log`. For example, if you want to see some abbreviated stats for each commit, you can use the `--stat` option:

        $ git log --stat
        commit ca82a6dff817ec66f44342007202690a93763949
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Mar 17 21:52:11 2008 -0700

            changed the version number

        Rakefile | 2 +-
        1 file changed, 1 insertion(+), 1 deletion(-)

        commit 085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Sat Mar 15 16:40:33 2008 -0700

            removed unnecessary test

        lib/simpelgit.rb | 5 -----
        1 file changed, 5 deletions(-)

        commit a11bef06a3f659402fe7563abf99ad00de2209e6
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Sat Mar 15 10:31:28 2008 -0700

            first commit

        README              |   6 ++++++
        Rakefile            |  23 +++++++++++++++++++++++
        lib/simplegit.rb    |  25 +++++++++++++++++++++++++
        3 files changed, 54 insertions(+)
As you can see, the `--stat` option prints below each commit entry a list of modified files, how many files were changed, and how many lines in those files were added and removed. It also puts a summary of the information at the end.
Another really useful option is `--pretty`. This option changes the log output to formats other than the default. A few prebuilt options are available for you to use. The `oneline` option prints each commit on a single line, which is useful if you're looking at a lot of commits. In addition, the `short`, `full`, and `fuller` options show the output in roughly the same format but with less or more information, respectively:

        $ git log --pretty=oneline
        ca82a6dff817ec66f44342007202690a93763949 changed the version number
        085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7 removed unnecessary test
        a11bef06a3f659402fe7563abf99ad00de2209e6 first commit
The most interesting option is `format`, which allows you to specify your own log output format. This is especially useful when you're generating output for machine parsing-because you specify the format explicitly, you know it won't change with updates to Git:

        $ git log --pretty=format:"%h - %an, %ar : %s"
        ca82a6d - Scott Chacon, 6 years ago : changed the version number
        085bb3b - Scott Chacon, 6 years ago : removed unnecessary test
        a11bef0 - Scott Chacon, 6 years ago : first commit
Useful options for `git log --pretty=format` lists some of the more useful options that `format` takes.

Table 1. Usefule options for `git log --pretty=format`

Option|Description of Output
--|--
%H|Commit hash
%h|Abbreviated commit hash
%T|Tree hash
%t|Abbreviated tree hash
%P|Parent hashes
%p|Abbreviated parent hashes
%an|Author name
%ae|Author email
%ad|Author Date(format respects the --date=option)
%ar|Author date, relative
%cn|Committer name
%ce|Committer email
%cd|Committer date
%cr|Committer date, relative
%s|Subject
You may be wondering what the difference is between _author_ and _committer_. The author is the person who originally wrote the work, whereas the committer is the person who last applied the work. So, if you send in a patch to a project and one of the core members applies the patch, both of you get credit-you as the author, and the core member as the committer. We'll cover this distinction a bit more in Distributed Git.
The `oneline` and `format` options are particularly usefule with another `log` option called `--graph`. This option adds a nice little ASCII graph showing your branch and merge history:

        $ git log --pretty=format:"%h %s" --graph
        * 2d3acf9 ignore errors from SIGCHLD on trap
        *  5e3ee11 Merge branch 'master` of git://github.com/dustin/grit
        |\
        | * 420eac9 Added a method for getting the current branch.
        * | 30e367c timeout code and tests
        * | 5a09431 add timeout protection to grit
        * | e1193f8 support for heads with slashes in them
        |/
        * d6016bc require time for xmlschema
        *  11d191e Merge branch 'defunkt' into local
This type of output will become more interesting as we go through branching and merging in the next chapter.
Those are only some simple output-formatting options to `git log`-there are many more. Common options to `git log` lists the options we've covered so far, as well as some othe common formatting options that may be useful, along with how they change the output of the long command.
Table 2. common options to `git log`

Option|Description
--|--
`-p`|Show the patch introduced with each commit.
`--stat`|Show statistics for files modified in each commit.
`--shortstat`|Display only the changed/insertions/deletions line from the --stat command.
`--name-only`|Show the list of files modified after the commit information.
`--name-status`|Show the list of files affected with added/modified/deleted information as well.
`--abbrev-commit`|Show only the first few characters of the SHA-1 checksum instead of all 40.
`--relative-date`|Display the date in a relative format (for example, "2 weeks ago") instead of using the full date format.
`--graph`|Display an ASCII graph of the branch and merge history beside the log output.
`--pretty`|Show commits in an alternate format. Options include oneline, short, full, fuller, and format (where you specify your own format).
`--oneline`|Shorhand for `--pretty=oneline --abbrev-commit` used together.
#### Limiting Log Output
In addition to output-formatting options, `git log` takes a number of useful limiting options-that is, options that let you show only a subset of commits. You've seen one such option already-the `-2` option, which display only the last two commits. In fact, you can do `-<n>`, where `n` is any integer to show the last `n` commits. In reality, you're unlikely to use that often, because Git by default pipes all output through a pager so you see only one page of log output at a time.
However, the time-limiting options such as `--since` and `--until` are very useful. For example, this command gets the list of commits made in the last two weeks:

        $ git log --since=2.weeks
This command works with lots of formats-you can specify a specific date like "`2008-01-15`", or a relative date such as "`2 years 1 day 3 minutes ago`".
You can also filter the list to commits that match some search criteria. The `--author` option allows you to filter on a specific author, and the `--grep` option lets you search for keywords in the commit messages.
_Note: You can specify more than one isntance of both the --auothr and --grep search criteria, which will limit the commit output to commits that match any of the --author patterns and any of the --grep patterns; however, adding the --all-match option further limits the output to just those commits that match all --grep patters._
Another really helpful filter is the `-S` option (colloquially referred to as Git's "pickaxe" option), which takes a string and shows only those commits that changed the number of occurrences of that string. For instance, if you wanted to find the last commit that added or removed a reference to a specific function, you could call:

        $ git log -S function_name
The last really useful option to pass to `git log` as filter is a path. If you specify a directory or file name, you can limit the log output to commits that introduced a change to those files. This is always the last option and is generally preceded by double dashes(`--`) to separate the paths from the options.
Table 3. Options to limit the output of `git log`

Option|Description
---|---
`-<n>`|Show only the last n commits
`--since, --after`|Limit the commits to those made after the specified date.
`--until, --before`|Limit the commits to those made before the specified date.
`--author`|Only show commits in which the author entry matches the specified string.
`--committer`|Only show commits in which the committer entry matches the specified string.
`--grep`|Only show commits with a commit message containing the string.
`-S`|Only show commits adding or removing code matching the string.
For example, if you want to see which commits modifying test files in the Git source code history were committed by Junio Hamano in the month of Octorber 2008 and are not merge commits, you can run something like this:

        $ git log --pretty="%h - %s" --author=gitster --since="2008-10-01"\
            --before="2008-11-01" --no-merges -- t/
        5610e3b - Fix testcase failure when extended attributes are in use
        acd3b9e - Enhance hold_lock_file_for_{update,append}() API
        f563754 - demonstrate breakage of detached checkout with symbolic link HEAD
        d1a43f2 - reset --hard/read-tree --reset -u: remove unmerged new paths
        51a94af - Fix "checkout --track -b newbranch" on detached HEAD
        b0ad11e - pull: allow "git pull origin $something:$current_branch" into an unborn branch
Of the nearly 40,000 commits in the Git source code history, this command shows the 6 that match those criteria.
_Tip:
Preventing the display of merge commits
Depending on the workflow used in your repository, it's possible that a sizable percentage of the commits in your log history are just merge commits, which typically aren't very informative. To prevent the display of merge commits cluttering up your log history, simply add the log option `--no-merges`._
### 2.4 Git Basics-Undoing things
#### Undoing Things
At any stage, you may want to undo something. Here, we'll review a few basic tools for undoing changes that you've made. Be careful, because you can't always undo some of these undos. This is one of the few areas in Git where you may lose some work if you do it wrong.
One of the common undos takes place when you commit too early and possibly forget to add some files, or you mess up your commit message. If you want to redo that commit, make the additional changes you forgot, stage them, and commit again using the `--amend` option:

        $ git commit --amend
This command takes your staging area and uses it for the commit. If you've made no changes since your last commit (for instance, you run this command immediately after your previous commit), then your snapshot will look exactly the same, and all you'll change is your commit message.
The same commit-message editor fires up, but it already contains the message of your previous commit. You can edit the message the same as always, but it overwrites your previous commit.
As an example, if you commit and then realize you forgot to stage the changes in a file you wanted to add to this commit, you can do something like this:

        $ git commit -m 'initial commit'
        $ git add forgotten_file
        $ git commit --amend
You end up with a single commit-the second commit replaces the results of the first.
_Note:
It's important to understand that when you're amending your last commit, you're not so much fixing it as replacing it entirely with a new, improved commit that pushes the old commit out of the way and puts the new commit in tis place. Effectively, it's as if the previous commit never happened, and it won't show up in your repository history.
The obvious value to amending commits is to make minor improvements to your last commit, without cluttering your repository history with commit messages of the form, "Oops, forgot to add a file" or "Darn, fixing a typo in last commit"._
#### Unstaging a staged file
The next two sections demonstrate how to work wih your staging area and working directory changes. The nice part is that the command you use to determine the stage of those two areas also reminds you how to undo changes to them. For example, let's say you've changed two files and want to commit them as two separate changes, but you accidently type `git add *` and stage them both. How can you unstage one of the two? The `git status` command reminds you:

        $ git add *
        $ git status
        On branch master
        Changes to be committed:
            (use "git reset HEAD <file>..." to unstage)

              renamed:  README.md -> README
              modified: CONTRIBUTING.md
Right below the "Changes to be committed" test, it says use `git reset HEAD <file>...` to unstage. So, let's use that advice to unstage the `CONTRIBUTING.md` file:

        $ git reset HEAD CONTRIBUTING.md
        Unstaged changes after reset:
        M CONTRIBUTING.md
        $ git status
        On branch master
        Changes to be committed:
            (use "git reset HEAD <file>..." to unstage)

                renamed:    README.md -> README

        Changes not staged for commit:
            (use "git add <file>..." to update what will be committed)
            (use "git checkout -- <file>..." to discard changes in working directory)
                modified:   CONTRIBUTING.md
The command is a bit strange, but it works. The `CONTRIBUTING.md` file is modified but once again unstaged.
_Note: It's true that `git reset` can be a dangerous command, especially if you provide the `--hard` flag. However, in the scenario described above, thefile in your working directory is not touched, so it's relatively safe._
For now this magic invocation is all you need to know about the `git reset` command. We'll go into much more detail about what `reset` does and how to master it to do really interesting things in Reset Demystifiled.
#### Unmodifying a Modified File
What if you realize that you don't want to keep your changes to the `CONTRIBUTING.md` file? How can you easily unmodify it-revert it back to what it looked like when you last committed (or initially cloned, or however you got it into your working directory)? Luckily, `git status` tells you how to do that, too. In the last example output, the unstaged area looks like this:

        Changes not staged for commit:
            (use "git add <file>..." to update that will be committed)
            (use "git checkout -- <file>..." to discard changes in working directory)
                
                modified: CONTRIBUTING.md
It tells your pretty explicitly how to discard the changes you've made. Let's do what it says:

        $ git checkout -- CONTRIBUTING.md
        $ git status
        On branch master
        Changes to be committed:
            (use "git reset HEAD <file>..." to unstage)

                renamed:    README.md -> README
You can see that the changes have been reverted.
_Important: It's important to understand the `git checkout -- <file>` is a dangerous command. Any changes you made to that file are gone-Git just copied another file over it. Don't ever use this command unless you absolutely know that you don't want the file._
If you would like to keep the changes you've made to that file but still need to get it out of the way for now, we'll go over stashing and branching in Git Branching;these are generally better ways to go.
Remember, anything that is _committed_ in Git can almost always be recovered. Even commits that were on branches that were deleted or commits that were overwritten with an `--amend` commit can be recoered (see Data Recovery for data recovery). However, anything you lose taht was never committed is likely never to be seen again.
### 2.5 Git Basics-Working with Remotes
#### Working with Remotes
To be able to collaborate on any Git project, you need to know how to manage your remote reporitories. Remote repositories are versions of your project that are hosted on the Internet or network somewhere. You can have several of them, each of which generally is either read-only or read/write for you. Collaborating with others involves managing these remote repositories and pushing and pulling data to and from them when you need to share work. Managjing remote repositories includes knowing how to add remote repositories, remove remotes that are no longer valid, manage various remote branches and define them as being tracked or not, and more. In this section, we'll cover some of these remote-management skills.
_Note: Remote repositories can be on your local machine. It is entirely possible that you can be working with a "remote" repository that is, in fact, on the same host you are. The word "remote" does not necessarily imply that the repository is somewhere else on the network or Internet, only that it is elsewhere. Working with such a remote repository would still involve all the standard pushing, pulling and fetching operations as with any other remote._
#### Showing Your Remotes
To see which remote servers you have configured, you can run the `git remote` command. It lists the shortnames of each remote handle you've specified. If you've cloned your repository, you should at least see `origin`-that is the default name Git gives to the server you cloned from:

        $ git clone https://github.com/schacon/ticgit
        Cloning into 'ticgit'...
        remote: Reusing existing pack: 1857, done.
        remote: Total 1857 (delta 0), reused 0 (delta 0)
        Receiving objects: 100% (1857/1857), 374.35 KiB | 268.00 KiB/s, done.
        Resolving deltas: 100% (772/772), done.
        Checking connectivity...done.
        $ cd ticgit
        $ git remote
        origin
You can also specify `-v`, which shows you the URLs that Git has stored for the shortname to be used when reading and writing to that remote:

        $ git remote -v
        origin https://github.com/schacon/ticgit (fetch)
        origin https://github.com/schacon/ticgit (push)
If you have more than one remote, the command lists them all. For example, a repository with multiple remotes for working with several collaborators might look something like this.

        $ cd grit
        $ git remote -v
        bakkdoor https://github.com/bakkdoor/grit (fetch)
        bakkdoor https://github.com/bakkdoor/grit (push)
        cho45    https://github.com/cho45/grit (fetch)
        cho45    https://github.com/cho45/grit (push)
        defunkt  https://github.com/defunkt/grit (fetch)
        defunkt  https://github.com/defunkt/grit (push)
        koke     git://github.com/koke/grit.git (fetch)
        koke     git://github.com/koke/grit.git (push)
        origin   git@github.com:mojombo/grit.git (fetch)
        origin   git@github.com:mojombo/grit.git (push)
This means that we can pull contributions from any of these users pretty easily. We may additionally have permissin to push to one or more of these, though we can't tell that here.
Notice that these remotes use a variety of protocols; we'll cover more about this in Getting Git on a server.
#### Adding Remote Repositories
We've mentioned and given some demonstrations of how the `git clone` command implicitly adds the `origin` remote for you. Here's how to add a new remote explicitly. To add a new remote Git repository as a shortname you can reference easily, run `git remote add <shortname> <url>`:

        $ git remote
        origin
        $ git remote add pb https://github.com/paulboone/ticgit
        $ git remtoe -v
        origin https://github.com/schacon/ticgit (fetch)
        origin https://github.com/schacon/ticgit (push)
        pb     https://github.com/paulboone/ticgit (fetch)
        pb     https://github.com/paulboone/ticgit (push)
Now you can use the string `pb` on the command line in lieu of the whole URL. For example, if you want to fetch all the information that Paul has but that you don't yet have in your repository, you can run `git fetch pb`:

        $ git fetch pb
        remote: Counting objects: 43, done.
        remote: Compressing objects: 100% (36/36), done.
        remote: Total 43 (delta 10), reused 31 (delta 5)
        Unpacking objects: 100% (43/43), done.
        From https://github.com/paulboone/ticgit
         * [new branch]     master      -> pb/master
         * [new branch]     ticgit      -> pb/ticgit
Paul's master branch is now accessible locally as `pb/master`-you can merge it into one of your branches, or you can check out a local branch at that point if you want to inspect it. (We'll go over what branches are and how to use them in much more detail in Git Branching.)
#### Fetching and Pulling from Your Remotes
As you just saw, to get data from your remote projects, you can run:

        $ git fetch <remote>
The command goes out to that remtoe project and pulls down all the data from that remote project that you don't have yet. After you do this, you should have references to all the branches from that remote, which you can merge in or inspect at any time.
If you clone a repository, the command automatically adds that remote repository under the name "origin". So, `git fetch origin` fetches any new work tht has been pushed to that server since you cloned (or last fetched from) it. It's important to note that the `git fetch` command only downloads the data to your local repository-it doesn't automatically merge it with any of your work or modify what you're currently working on. You have to merge it manually into your work when you're ready.
If your current branch is set up to track a remote branch (see the next sectin and Git Branching for more information), you can use the `git pull` command to automatically fetch and then merge that remtoe branch into your current branch. This is an easier or more comfortable workflow for you; and by default, the`git clone` command automatically sets up your local master branch to track the remote master branch (or whatever the default branch is called) on the server you cloned from. Running `git pull` generally fetches data from the serve you originally cloned from and automatically tries to merge it into the code you're currently working on.
#### Pushing to Your Remotes
When you have your project at a point that you want to share, you have to push it upstream. The command for this is simple: `git push <remote> <branch>`. If you want to push your master branch to your `origin` server (again, cloning generally sets up both of those names for you automatically), then you can run this to push any commits you've done back up to the server:

        $ git push origin master
This command works only if you cloned from a server to which you have write access and if noboly has pushed in the meantime. If you and someone else clone at the same time and they push upstream and then you push upstream, you push will rightly be rejected. You'll have to fetch their work first and incorporate it into yours before you'll be allowed to push. See Git Branching for more detailed information on how to push to remote servers.
#### Inspecting a Remote
If you want to see more information about a particular remote, you can use the `git remote show <remote>` command. If you run this command with a particular shortname, such as `origin`, you get something like this:

        $ git remote show origin
        * remote origin
          Fetch URL: https://github.com/schacon/ticgit
          Push  URL: https://github.com/schacon/ticgit
          HEAD branch: master
          Remote branches:
            master                              tracked
            dev-branch                          tracked
        Local branch configured for 'git pull':
            master merges with remote master
        Local ref configured for 'git push':
            master pushes to master (up to date)
It lists the URL for the remote repository as well as the tracking branch information. The command helpfully tells you that if you're on the master branch and you run `git pull`, it will automatically merge in the maste branch on the remote after it fetches all the remote references. It also lists all the remote references it has pulled down.
That is a simple example you're likely to encounter. When you're using Git more heavily, however, you may see more information from `git remtoe show`:
        
        $ git remote show origin
        * remote origin
          URL: https://github.com/my-org/complex-project
          Fetch URL: https://github.com/my-org/complex-project
          Push  URL: https://github.com/my-org/complex-project
          HEAD branch: master
          Remote branches:
            master                          tracked
            dev-branch                      tracked
            markdown-strip                  tracked
            issue-43                        new (next fetch will store in remotes/origin)
            issue-45                        new (next fetch will store in remotes/origin)
            refs/remotes/origin/issue-11    stale (use 'git remote prune' to remove)
          Local branches configured for 'git pull':
            dev-branch merges with remote  dev-branch
            master     merges with remote master
          Local refs configured for 'git push':
            dev-branch                      pushes to dev-branch        (up to date)
            markdown-strip                  pushes to markdown-strip    (up to date)
            master                          pushes to master            (up to date)
This command shows which branch is automatically pushed to when you run `git push` while on certain branches. It also shows you which remote branches on the server you don't yet have, which remote branches you have that have been removed from the server, and multiple local branches that are able to merge automatically with their remote-tracking branch when you run `git pull`.
#### Renaming and Removing Remotes
You can run `git remote rename` to change a remote's shortname. For instance, if you want to rename `pb` to `paul`, you can do so with `git remote rename`:

        $ git remote rename pb paul
        $ git remote
        origin
        paul
It's worth mentioning that this changes all your remote-tracking branch names, too. What used to be referenced at `pb/master` is now at `paul/master`.
If you want to remove a remote for some reason-you've moved the server or are no loner using a particular mirror, or perhaps a contributor isn't contributing anymore-you can either use `git remote remove` or `git remote rm`:

        $ git remote remove paul
        $ git remote
        origin
Once you delete the reference to a remote this way, all remote-tracking branches and configuration settings associated with that remote are also deleted.
### 2.6 Git Basics-Tagging
#### Tagging
Like most VCSs, Git has the ability to tag specific points in history as being important. Typically people use this functionality to mark release points (v1.0, and so on). In this section, you'll learn how to list the available tags, how to create new tags, and what the different types of tags are.
#### Listing Your Tags
Listing the available tags in Git is traightforward. Just type `git tag` (with optional `-l` or `--list`):

        $ git tag
        v0.1
        v1.3
This command lists the tags in alphabetical order; the order in which they appear has no real importance.
You can also search for tags that match a particular pattern. The Git source repo, for instance, contains more than 500 tags. If you're only interested in looking at the 1.8.5 series, you can run this:

        $ git log -l "v1.8.5*"
        v1.8.5
        v1.8.5-rc0
        v1.8.5-rc1
        v1.8.5-rc2
        v1.8.5-rc3
        v1.8.5.1
        v1.8.5.2
        v1.8.5.3
        v1.8.5.4
        v1.8.5.5
_Note: Listing tag wildcards requires `-l` or `--list` option.
       If you want just the entire list of tags, running the command `git tag` implicitly assumes you want a listing and provides one; the use of `-l` or `--list` in this case is optional.
       If, however, you're supplying a wildcard pattern to match tag names, the use o `-l` or `--list` is mandatory._
#### Creating Tags
Git supports two types of tags: *lightweight* and *annotated*.
A lightweight tag is very much like a branch that doesn't change-it's just a pointer to a specific commit.
Annotated tags, however, are stored as full objects in the Git database. They're checksummed; contain the tagger name, email. and date; have a tagging message; and can be signed and verified with GNU Privacy Guard (GPG). It's generally recommended that you create annotated tags so you can have all this information; but if you want a temporary tag or for some reason don't want to keep the other information, lightweight tags are available too.
#### Annotated Tags
Creating an annotated tag in Git is simple. The easiest way is to specify `-a` when you run the `tag` command:

        $ git tag -a v1.4 -m "my version 1.4"
        $ git tag
        v0.1
        v1.3
        v1.4
The `-m` specifies a tagging message, which is stored with the tag. If you don't specify a message for an annotated tag, Git launches your editor so you can type it in.
You can see the tag data along with the commit that was tagged by using the `gi show` command:

        $ git show v1.4
        tag v1.4
        Tagger: Ben Straub <ben@straub.cc>
        Date:   Sat May 3 20:19:12 2014 -0700

        my version 1.4

        commit ca82a6dff817ec66f44342007202690a93763949
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Mar 17 21:52:11 2008 -0700

            changed the version number
That shows the tagger information, the dte the commit was tagged, and the annotation message before showing the commit information.
#### Lightweight Tags
Another way to tag commits is with a lightweight tag. This is basically the commit checksum stored in a file-no other information is kept. To create a lightweight tag, don't supply any of the `-a`, `-s`, or `-m` options, just provide a tag name:

        $ git tag v1.4-lw
        $ git tag
        v0.1
        v1.3
        v1.4
        v1.4-lw
        v1.5
This time, if you run `git show` on the tag, you don't see the extra tag information. The command just shows the commit:

        $ git show v1.4-lw
        commit ca82a6dff817ec66f44342007202690a93763949
        Author: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Mar 17 21:52:11 2008 -0700

            changed the version number
Tagging Later
You can also tag commits after you've moved past them. Suppose your commit history looks like this:

        $ git log --pretty=oneline
        15027957951b64cf874c3557a0f3547bd83b3ff6 Merge branch 'experiment'
        a6b4c97498bd301d84096da251c98a07c7723e65 beginning write support
        0d52aaab4479697da7686c15f77a3d64d9165190 one more thing
        6d52a271eda8725415634dd79daabbc4d9b6008e Merge branch 'experiment'
        0b7434d86859cc7b8c3d5e1dddfed66ff742fcbc added a commit function
        4682c3261057305bdd616e23b64b0857d832627b added a todo file
        166ae0c4d3f420721acbb115cc33848dfcc2121a started write support
        9fceb02d0ae598e95dc970b74767f19372d61af8 updated rakefile
        964f16d36dfccde844893cac5b347e7b3d44abbc commit the todo
        8a5cbc430f1a9c3d00faaeffd07798508422908a updated readme
Now, suppose you forgot to tag the project at v1.2, which was the "updated rakefile" commit. You can add it after the fact. To tag that commit, you specify the commit checksum (or part of it) at the endd of the command:

        $ git tag -a v1.2 9fceb02
You can see that you've tagged the commit:

        $ git tag
        v0.1
        v1.2
        v1.3
        v1.4
        v1.4-lw
        v1.5

        $ git show v1.2
        tag v1.2
        Tagger: Scott Chacon <schacon@gee-mail.com>
        Date:   Mon Feb 9 15:32:16 2009 -0800

        version 1.2
        commit 9fceb02d0ae598e95dc970b74767f19372d61af8
        Author: Magnus Chacon <mchacon@gee-mail.com>
        Date:   Sun Apr 27 20:43:35 2008 -0700

            updated rakefile
        ...
#### Sharing Tags
By default, the `git push` command doesn't transfer tags to remote servers. You will have to explicitly push tags to a shared server after you ahve created them.This process is just like sharing remote branches-you can run `git push origin <tagname>`.

        $ git push origin v1.5
        Counting objects: 14,done.
        Delta compression using up to 8 threads.
        Compressing objects: 100% (12/12), done.
        Writing objects: 100% (14/14), 2.05 KiB | 0 bytes/s, done.
        Total 14 (delta 3), reused 0 (delta 0)
        To git@github.com:schacon/simplegit.git
         * [new tag] v.15 -> v1.5
If you have a lot of tags that you want to push up at once, you can also use the `--tags` option to the `git push` command. This will transfer all of your tags to the remote server that are not already there.

        $ git push origin --tags
        Counting objects: 1, done.
        Writing objects: 100% (1/1), 160 bytes | 0 bytes/s, done.
        Total 1 (delta 0), reused 0 (delta 0)
        To git@github.com:schacon/simplegit.git
         * [new tag]        v1.4 -> v1.4
         * [new tag]        v1.4-lw -> v1.4-lw
Now, when someone else clones or pulls from your repository, they will get all your tags as well.
__Note: the command `git push <remote> <tag_name>` and `git push --tags` can both push up only tags, not other refs. If you want to push up both tags and other refs, run `git push --follow-tags` or `git push --tags HEAD`.
`git push --follow-tags`: Push all the refs that would be pushed without this option, and also push annotated tags in refs/tags that are missing from the remote but are pointing at committish that are reachable from the refs being pushed.__
#### Checking out Tags
If you want to view the versions of files a tag is pointing to, you can do a git checkout, though this puts your repository in "detached HEAD" state, which has some ill side effects:

        $ git checkout 2.0.0
        Note: checking out '2.0.0'.

        You are in 'detached HEAD' state. You can look aroung, make experimental changes and commit them, and you can discard any commis you make in this state without impacting any branches by performing another checkout.
        If you want to create a new branch to retain commits you create, you may do so (now or later) by using -b with the checkout command again. Example:

            git checkout -b <new-branch>
        HEAD is now at 99ada87... Merge pull request #89 from schacon/appendix-final

        $ git checkout 2.0-beta-0.1
        Previous HEAD position was 99ada87... Merge pull request #89 from schacon/appendix-final
        HEAD is now at df3f601... add atlas.json and cover image
In "detached HEAD" state, if you make changes and then create a commit, the tag will stay the same but your new commit won't belong to any branch and will be unreachable, except by the exact commit hash. Thus, if you need to make changes-say you're fixing a bug on an older version, for instance-you will generally want to create a branch:

        $ git checkout -b version2 v2.0.0
        Switched to a new branch 'version2'
If you do this and make a commit, your `version2` branch will be slightly different than your `v2.0.0` tag since it will move forward with your new changes, so do be careful.
#### Deleting Tags
* Delete the tag locally
        git tag -d v1.0
* Delete the tag on GitHub (which removes its download link)
        git push origin :v1.0
### 2.7 Git Basics-Git Aliases
#### Git Aliases
Before we finish this chapter on basic Git, there's just one little tip that can make your Git experience simpler, easier, and more familiar: aliases. We won't refer to them or assume you've used them later in the book, but you should probably know how to use them.
Git doesn't automatically infer your command if you type it in partially. If you don't want to type the entire text of each of the Git commands, you can easily set up an alias for each command using `git config`. Here are a couple of examples you may want to set up:

        $ git config --global alias.co checkout
        $ git config --global alias.br branch
        $ git config --global alias.ci commit
        $ git config --global alias.st status
This means that,for example, instead of typing `git commit`, you just need to type `git ci`. As you go on using Git, you'll probably use other commands frequently as well; don't hesitate to create new aliases.
This technique can also be very useful in creating commands that you think should exist. For example, to correct the usability probem you encountered with unstaging a file, you can add your own unstage alias to Git:

        $ git config --global alias.unstage 'reset HEAD --'
This makes the following two commands equivalent:

        $ git unstage fileA
        $ git reset HEAD -- fileA
This seems a bit clearer. It's also common to add a `last` command, like this:

        $ git config --global alias.last 'log -1 HEAD'
This way, you can see the last commit easily:

        $ git last
        commit 66938dae3329c7aebe598c2246a8e6af90d04646
        Author: Josh Goebel <dreamer3@example.com>
        Date:   Tue Aug 26 19:48:51 2008 +0800

            test for current head

            Signed-off-by: Scott Chacon <schacon@example.com>
As you can tell, Git simply replaces the new command with whatever you alias it for.
However, maybe you want to run an external command, rather than a Git subcommand. In that case, you start the command with a `!` character. This is useful if you write your own tools that work with a Git repository. We can demonstrate by aliasing `git visual` to run `gitk`:

        $ gi config --global alias.visual '!gitk'
### 2.8 Git Basics-Summary
#### Summary
At this point,you can do all the basic local Git operations-creating or cloning a repository, making changes, staging and committing those changes, and viewing the history of all the changes the repository has been through. Next, we'll cover Git's killer feature: its branching model.
## 3. Git Branching
### 3.1 Git Branching - Branches in a Nutshell
Nearly every VCS has some form of branching support. Branching means you diverge from the main line of development and continue to do work without messing with that main line.
In many VCS tools, this is a somewhat expensive process, often requiring you to create a new copy of your source code directory, which can take a long time for large projects.
Some people refer to Git's branching model as its "killer feature", and it certainly sets Git apart in the VCS community. Why is it so special? The way Git branches is incredibly lightweight, making branching operations nearly instantaneous, and switching back and forth between branches generally just as fast. Unlike many other VCSs, Git encourages workflows that branch and merge often, even multiple times in a day. Understanding and mastering this feature gives you a powerful and unique tool and can entirely change the way that you develop.
#### Branches in a Nutshell
To really understand the way Git does branching, we need to take a step back and examine how Git stores its data.
As you may remember from Getting Started, Git doesn't store data as a series of changesets or differences, but instead as a series of snapshots.
When you make a commit, Git stores a commit object that contains a pointer to the snapshot of the content you staged. This object also contains the author's name and email, the message that you typed, and pointers to the commit or commits that directly came before this commit (it parent or parents): zero parents for the initial commit, one parent for a normal commit, and multiple parents for a commit that results from a merge of two or more branches.
To visualize this, let's assume that you have a directory containing three files, and you stage them all and commit. Staging the files computes a checksum for each one (the SHA-1 hash we mentioned in Getting Started), stores tha version of the file in the Git repository (Git refers to them as blobs), and adds that checksum to the staging area:

        $ git add README test.rb LICENSE
        $ git commit -m 'The initial commit of my project'
When you create the commit by running `git commit`, Git checksums each subdirectory (in this case, just the root project directory) and stores those tree objects in the Git repository. Git then creates a commit object that has the metadata and pointer to the root project tree so it can re-create that snapshot when needed.
Your Git repository now contains five objects: one blob for the contents of each of your three files, one tree tha lists the contents of the directory and specifies which file names are stored as which blobs, and one commit with the pointer to that root tree and all the commit metadata.
![commit,tree, and blobs](commit-and-tree.png)
Figure 9. A commit and its tree
If you make some changes and commit again, the next commit stores a pointer to the commit that came immediately before it.
![commits and there parents](commits-and-parents.png)
Figure 10. Commits and their parents
A branch in Git is simply a lightweight movable pointer to one of these commits. The default branch name in Git is `master`. As you start making commits, you're given a `master` branch that points to the last commit you made. **Every time you commit, it moves forward automatically.**
_Note: The "master" branch in Git is not a special branch. It is exactly like any other branch. The only reason nearly every repository has one is that the `git init` command creates it by default and most people don't bother to change it._
![branch and history](branch-and-history.png)
Figure 11. A branch and its commit history
#### Creating a New Branch
What happens when you create a new branch? Well, doing so creates a new pointer for you to move around. Let's say you create a new branch called testing. You do this with the `git branch` command:

        $ git branch testing
This creates a new pointer to the same commit you're currently on.
![creating a new branch](two-branches.png)
Figure 12. Two branches pointing into the same series of commits
How does Git know what branch you're currently on? It keeps a special pointer called `HEAD`. Note that this is a lot different than the concept of `HEAD` in other VCSs you may be used to, such as Subversion or VCS. In Git, this is a pointer to the local branch you're currently on. In this case, you're still on `master`. The `git branch` command only created a new branch-it didn't switch to that branch.
![HEAD pointing to the current branch](head-to-master.png)
Figure 13. HEAD pointing to the current branch
You can easily see this by running a simple `git log` command that shows you where the branch pointers are pointing. This option is called `--decorate`.

        $ git log --oneline --decorate
        f30ab (HEAD -> master, testing) add feature #32 - ability to add new formats to the central interface
        34ac2 Fixed bug #1328 - stack overflow under certain conditions
        98ca9 The initial commit of my project
You can see the "master" and "testing" branches that are right there next to the `f30ab` commit.
#### Switching Branches
To switch to an existing branch, you run the `git checkout` command. Let's switch to the new `testing` branch:

        $ git checkout testing
This moves `HEAD` to point to the `testing` branch.
![HEAD pointing to the current branch](head-to-testing.png)
Figure 14. HEAD points to the current branch
What is the significance of that? Well, let's do another commit:

        $ vim test.rb
        $ git commit -a -m 'made a change'
![advance testing](advance-testing.png)
Figure 15. The HEAD branch moves forward when a commit is made
This is interesting, because now your `testing` branch has moved forward, but your `master` branch still points to the commit you were on when you ran `git checkout` to switch branches. Let's switch back to the `master` branch:

        $ git checkout master
![HEAD moves when you checkout](checkout-master.png)
Figure 16. HEAD moves when you checkout
That command did two things. It moved the HEAD pointer back to point to the `master` branch, and it reverted the files in your working directory back to the snapshot that `master` points to. This also means the changes you make from this point forward will diverge from an older version of the project. It essentially rewinds the work you've done in your `testing` branch so you can go in a different direction.
_Note: Switching branches changes files in your working directory. It's important to note that when you switch branches in Git, files in your working directory will change. If you switch to an older branch, your working directory will be reverted to look like it did the last time you committed on that branch. If Git cannot do it cleanly, it will not let you switch at all._
Let's make a few changes and commit again:

        $ vim test.rb
        $ git commit -a -m 'made other changes'
Now your project history has dirverged (see Divergent history). You created and switched to a branch, did some work, and then switched back to your main branch and did other work. Both of those changes are isolated in separate branches: you can switch back and forth between the branches and merge them together when you're ready. And you did all that with simple `branch`, `checkout`, and `commit` commands.
![Divergent history](advance-master.png)
Figure 17. Divergent history
You can also see this easily with the `git log` command. If you run `git log --oneline --decorate --graph --all` it will print out the history of your commits, showing where your branch pointers are and how your history has diverged.

        $ git log --oneline --decorate --graph --all
        * c2b9e (HEAD, master) made other changes
        | *87ab2 (testing) made a change
        |/
        * f30ab add feature #32 - ability to add new formats to the
        * 34ac2 fixed bug #1328 - stack overflow under certain conditions
        * 98ca9 initial commit of my project
Because a branch in Git is actually a simple file that contains the 40 character SHA-1 checksum of the commit it points to, branches are cheap to create and destroy. Creating a new branch is as quick and simple as writing 41 bytes to a file (40 characters and a newline).
This is in sharp contrast to the way most older VCS tools branch, which involves copying all of the project's files into a second directory. This can take several seconds or even minutes, depending on the size of the project, whereas in Git the process is always instantaneous. Also, because we're recording the parents when we commit, finding a proper merge base for merging is automatically done for us and is generally very easy to do. These features help encourage developers to create and use branches often.
### Git Branching-Basic Branching and Merging
#### Basic Branching and Merging
Let's go through a simple example of branching and merging with a workflow that you might use in the real world. You'll follow these steps:
1. Do some work on a website.
2. Create a branch for a new story you're working on.
3. Do some work in that branch.
At this stage, you'll receive a call that another issue is critical and you need a hotfix. You'll do the following:
1. Switch to your production branch.
2. Create a branch to add the hotfix.
3. After it's tested, merge the hotfix branch, and push to production.
4. Switch back to your original story and continue working.
#### Basic Branching
First,let's say you're working on your project and have a couple of commits already on the `master` branch.
![A simple commit history](basic-branching-1.png)
Figure 18. A simple commit history
You've decided that you're going to work on issue #53 in whatever issue-tracking system your company uses. To create a new branch and switch to it at the same time, you can run the `git checkout` command with the `-b` switch:

        $ git checkout -b iss53
        Switched to a new branch "iss53"
## 10. Git Internals
### 10.3 Git References
#### Remotes

The third type of reference that you'll see is a remote reference. If you add a remote and push to it, Git stores the value you last pushed to that remote for each branch in the refs/remotes directory. For instance, you can add a remote called origin and push your master branch to it:

        $ git remote add origin git@github.com:schacon/simplegit-progit.git
        $ git push origin master
        Counting objects: 11, done.
        Compressing objects: 100% (5/5), done.
        Writing objects: 100% (7/7), 716 bytes, done.
        Total 7 (delta 2), reused 4 (delta 1)
        To git@github.com:schacon/simplegit-progit.git
          allbef0..ca82a6d master -> master
Then, you can see what the `master` branch on the `origin` remote was the last time you communicated with the server, by checking the refs/remotes/origin/master file:
        
        $ cat .git/refs/remotes/origin/master
        ca82a6dff817ec66f44342007202690a93763949
Remote references differ from branches (refs/heads references) mainly in that they're considered read-only. You can `git checkout` to one, but Git won't point HEAD at one, so you'll never update it with a `commit` command. Git manages them as bookmarks to the last known state of where those branches were on those servers.

### [10.4 Git Internals-Packfiles](https://git-scm.com/book/en/v2/Git-Internals-Packfiles)
**Packfiles**
If you followed all of the instructions in the example from the previous section, you should now have a test Git repository with 11 objects-four blobs, three trees, three commits, and one tag:

        $ find .git/objects -type f
        .git/objects/01/55eb4229851634a0f03eb265b69f5a2d56f341 # tree 2
        .git/objects/1a/410efbd13591db07496601ebc7a059dd55cfe9 # commit 3
        .git/objects/1f/7a7a472abf3dd9643fd615f6da379c4acb3e3a # test.txt v2
        .git/objects/3c/4e9cd789d88d8d89c1073707c3585e41b0e614 # tree 3
        .git/objects/83/baae61804e65cc73a7201a7252750c76066a30 # test.txt v1
        .git/objects/95/85191f37f7b0fb9444f35a9bf50de191beadc2 # tag
        .git/objects/ca/c0cab538b970a37ea1e769cbbde608743bc96d # commit 2
        .git/objects/d6/70460b4b4aece5915caf5c68d12f560a9fe3e4 # 'test content'
        .git/objects/d8/329fc1cc938780ffdd9f94e0d364e0ea74f579 # tree 1
        .git/objects/fa/49b077972391ad58037050f2a75f74e3671e92 # new.txt
        .git/objects/fd/f4fc3344e67ab068f836878b6c4951e3b15f3d # commit 1
Git compresses the contents of these files with zlib, and you're not storing much, so all these files collectively take up only 925 bytes. Now you'll add some more sizable content to the repository to demonstrate an interesting feature of Git. To demonstrate, we'll add the repo.rb file from the Grit library-this is about a 22K source code file:

        $ curl https://raw.githubusercontent.com/mojombo/grit/master/lib/grit/repo.rb > repo.rb
        $ git checkout master
        $ git add repo.rb
        $ git commit -m 'added repo.rb'
        [master 484a592] added repo.rb
         3 files changed, 709 insertions(+), 2 deletions(-)
         delete mode 100644 bak/test.txt
         create mode 100644 repo.rb
         rewrite test.txt (100%)
If you look at the resulting tree, you can see the SHA-1 value that was calculated for your new repo.rb blob object:

        $ git cat-file -p master^{tree}
        100644 blob fa49b077972391ad58037050f2a75f74e3671e92    new.txt
        100644 blob 033b4468fa6b2a9547a70d88d1bbe8bf3f9ed0d5    repo.rb
        100644 blob e3f094f522629ae358806b17daf78246c27c007b    test.txt
You can then use `git cat-file` to see how large that object is:

        $ git cat-file -s 033b4468fa6b2a9547a70d88d1bbe8bf3f9ed0d5
        22044
At this point, modify that file a little, and see what happens:

        $ echo '# testing' >> repo.rb
        $ git commit -am 'modified repo a bit'
        [master 2431da6] modified repo.rb a bit
        1 file changed, 1 insertion(+)
Check the tree createdd by that last commit, and you see something interesting:

        $ git cat-file -p master^{tree}
        100644 blob fa49b077972391ad58037050f2a75f74e3671e92    new.txt
        100644 blob b042a60ef7dff760008df33cee372b945b6e884e    repo.rb
        100644 blob e3f094f522629ae358806b17daf78246c27c007b    test.txt
The blob is now a different blob, which means that although you added only a single line to the end of a 400-line file, Git stored that new content as a completely new object:

        $ git cat-file -s b042a60ef7dff760008df33cee372b945b6e884e
        22054
You have two nearly identical 22K objects on your disk (each compressed to approximately 7K). Wouldn’t it be nice if Git could store one of them in full but then the second object only as the delta between it and the first?
It turns out that it can. The initial format in which Git saves objects on disk is called a “loose” object format. However, occasionally Git packs up several of these objects into a single binary file called a “packfile” in order to save space and be more efficient. Git does this if you have too many loose objects around, if you run the `git gc` command manually, or if you push to a remote server. To see what happens, you can manually ask Git to pack up the objects by calling the `git gc` command:

        $ git gc
        Counting objects: 18, done.
        Delta compression using up to 8 threads.
        Compressing objects: 100% (14/14), done.
        Writing objects: 100% (18/18), done.
        Total 18 (delta 3), reused 0 (delta 0)
If you look in your `objects` directory, you’ll find that most of your objects are gone, and a new pair of files has appeared:

        $ find .git/objects -type f
        .git/objects/bd/9dbf5aae1a3862dd1526723246b20206e5fc37
        .git/objects/d6/70460b4b4aece5915caf5c68d12f560a9fe3e4
        .git/objects/info/packs
        .git/objects/pack/pack-978e03944f5c581011e6998cd0e9e30000905586.idx
        .git/objects/pack/pack-978e03944f5c581011e6998cd0e9e30000905586.pack
The objects that remain are the blobs that aren’t pointed to by any commit — in this case, the “what is up, doc?” example and the “test content” example blobs you created earlier. Because you never added them to any commits, they’re considered dangling and aren’t packed up in your new packfile.
The other files are your new packfile and an index. The packfile is a single file containing the contents of all the objects that were removed from your filesystem. The index is a file that contains offsets into that packfile so you can quickly seek to a specific object. What is cool is that although the objects on disk before you ran the `gc` command were collectively about 15K in size, the new packfile is only 7K. You’ve cut your disk usage by half by packing your objects.
How does Git do this? When Git packs objects, it looks for files that are named and sized similarly, and stores just the deltas from one version of the file to the next. You can look into the packfile and see what Git did to save space. The `git verify-pack` plumbing command allows you to see what was packed up:

        $ git verify-pack -v .git/objects/pack/pack-978e03944f5c581011e6998cd0e9e30000905586.idx
        2431da676938450a4d72e260db3bf7b0f587bbc1 commit 223 155 12
        69bcdaff5328278ab1c0812ce0e07fa7d26a96d7 commit 214 152 167
        80d02664cb23ed55b226516648c7ad5d0a3deb90 commit 214 145 319
        43168a18b7613d1281e5560855a83eb8fde3d687 commit 213 146 464
        092917823486a802e94d727c820a9024e14a1fc2 commit 214 146 610
        702470739ce72005e2edff522fde85d52a65df9b commit 165 118 756
        d368d0ac0678cbe6cce505be58126d3526706e54 tag    130 122 874
        fe879577cb8cffcdf25441725141e310dd7d239b tree   136 136 996
        d8329fc1cc938780ffdd9f94e0d364e0ea74f579 tree   36 46 1132
        deef2e1b793907545e50a2ea2ddb5ba6c58c4506 tree   136 136 1178
        d982c7cb2c2a972ee391a85da481fc1f9127a01d tree   6 17 1314 1 \
          deef2e1b793907545e50a2ea2ddb5ba6c58c4506
        3c4e9cd789d88d8d89c1073707c3585e41b0e614 tree   8 19 1331 1 \
          deef2e1b793907545e50a2ea2ddb5ba6c58c4506
        0155eb4229851634a0f03eb265b69f5a2d56f341 tree   71 76 1350
        83baae61804e65cc73a7201a7252750c76066a30 blob   10 19 1426
        fa49b077972391ad58037050f2a75f74e3671e92 blob   9 18 1445
        b042a60ef7dff760008df33cee372b945b6e884e blob   22054 5799 1463
        033b4468fa6b2a9547a70d88d1bbe8bf3f9ed0d5 blob   9 20 7262 1 \
          b042a60ef7dff760008df33cee372b945b6e884e
        1f7a7a472abf3dd9643fd615f6da379c4acb3e3a blob   10 19 7282       22054
        non delta: 15 objects
        chain length = 1:3 objects
        .git/objects/pack/pack-978e03944f5c581011e6998cd0e9e30000905586.pack: ok
Here, the `033b4` blob, which if you remember was the first version of your `repo.rb` file, is referencing the `b042a` blob, which was the second version of the file. The third column in the output is the size of the object in the pack, so you can see that `b042a` takes up 22K of the file, but that `033b4` only takes up 9 bytes. What is also interesting is that the second version of the file is the one that is stored intact, whereas the original version is stored as a delta-this is because you're most likely to need faster access to the most recent version of the file.
The really nice thing about this is that it can be repacked at any time. Git will occasionally repack your database automatically, always trying to save more space, but you can also manualy repack at any time by running `git gc` by hand.

### [10.5 Git Internals- The Refspec](https://git-scm.com/book/en/v2/Git-Internals-The-Refspec)
#### The Refspec
Throughout this book, we've used simple mappings from remote branches to local references, but they can be more complex. Suppose you were following along with the last couple sections and had created a small local Git repository, and now wanted to add a remote to it:

        $ git remote add origin https://github.com/schacon/simplegit-progit
Running the command above adds a section to your repository's `.git/config` file, specifying the name of the remote(`origin`), the URL of the remote repository, and the *refspec* to be used for fetching:

        [remote "origin"]
                url = https://github.com/schacon/simplegit-progit
                fetch = +refs/heads/*:refs/remotes/origin/*
The format of the refspec is, first, an optional `+`, followed by `<src>:<dst>`, where `<src>` is the pattern for references on the remote side and `<dst>` is where those references will be tracked locally. The `+` tells Git to update the reference even if it isn't a fast-forward.
In the default case that is automatically written by a `git remote add` command, Git fetches all the references under `refs/heads/` on the server and writes them to `refs/remotes/origin/` locally. So, if there is a `master` branch on the server, you can access the log of that branch locally via any of the following:

        $ git log origin/master
        $ git log remotes/orgin/master
        $ git log refs/remotes/origin/master
They're all equivalent, because Git expands each of them to `refs/remotes/origin/master`.
If you want Git instead to pull down only the `master` branch each time, and not every other branch on the remote server, you can change the fetch line to refer to that branch only:

        fetch = +refs/heads/master:refs/remotes/origin/master
This is just the default refspec for `git fetch` for that remote. If you want to do a one-time only fetch, you can specify the specific refspec on the command line, too. To pull the `master` branch on the remote down to the `origin/mymaster` locally, you can run:

        $ git fetch origin master:refs/remotes/origin/mymaster
You can also specify multiple refspecs. One the command line, you can pull down several branches like so:

        $ git fetch origin master:refs/remotes/origin/mymaster \
                topic:refs/remotes/origin/topic
        From git@github.com:schacon/simplegit
        ! [rejected]        master      -> origin/mymaster      (non fast forward)
        * [new branch]      topic       ->origin/topic
In this case, the `master` branch pull was rejected because it wasn't listed as a fast-forward reference. You can override that by specifying the `+` in front of the refspec.
You can also specify multiple refspec for fetching in your configuration file. If you want to always fetch the `master` and `experiment` branches from the `origin` remote, add two lines:

        [remote "origin"]
                url = https://github.com/schacon/simplegit-progit
                fetch = +refs/heads/master:refs/remotes/origin/master
                fetch = +refs/heads/experiment:refs/remote/origin/experiment
You can't use partial globs in the pattern, so this would be invalid:

        fetch = +refs/heads/qa*:refs/remotes/origin/qa*
However, you can use namespaces (or directories) to accomplish something like that. If you have a QA team that pushes a series of branches, and you want to get the `mater` branch and any of the QA team's branches but nothing else, you can use a config like this:

        [remote "origin"]
                url = https://github.com/schacon/simplegit-progit
                fetch = +refs/heads/master:refs/remotes/origin/master
                fetch = +refs/heads/qa/*:refs/remotes/origin/qa/*
If you have a complex workflow process tha has a QA team pushing branches, developers pushing branches, and integration teams pushing and collaborating on remote branches, you can namespace them easily this way.
#### Pushing Refspecs
It's nice that you can fetch namespaced references that way, but how does the QA team get their branches into a `qa/` namespace in the first place? You accomplish that by using refspecs to push.
If the QA team wants to push their `master` branch to `qa/master` on the remote server, they can run:

        $ git push origin master:refs/heads/qa/master
If they want Git to do that automatically each time they run `git push origin`, they can add a `push` value to their config file:

        [remote "origin"]
                url = https://github.com/schacon/simplegit-progit
                fetch = +refs/heads/*:refs/remotes/origin/*
                push = refs/heads/master:refs/heads/qa/master
Again, this will cause `git push origin` to push the local `master` branch to the remote `qa/master` branch by default.
#### Deleting References
You can also use the refspec to delete references from the remote server by running something like this:

        $ git push origin :topic
Because the refspec is `<src>:<dst>`, by leaving off the `<src>` part, this basically says to make the `topic` branch on the remote nothing, which deletes it.
Or you can use the newer syntax (available since Git v1.7.0):

        $ git push origin --delete topic
### 10.6 Git Internals - Transfer Protocols
#### Transfer Protocols
Git can transfer data between two repositories in two major two ways: the "dumb" protocoal and the "smart" protocol. This section will quickly cover how these two main protocols operate.
#### The Dumb Protocol
If you're setting up a repository to be served read-only over HTTP, the dumb protocol is likely what will be used. This protocol is called "dumb" because it requires no Git-specific code on the server side during the transport process; the fetch process is series of HTTP `GET` requests, where the client can assume the layout of the Git repository on the server.
*Note: The dumb protocol is fairly rarely used these days. It's difficult to secure or make private, so most Git hosts (both cloud-based and on-premises) will refuse to use it. It's generally advised to use the smart protocol, which we describe a bit further on.*
Let's follow the `http-fetch` process for the simplegit library:

        $ git clone http://server/simplegit-progit.git
The first thing this command does is pull down the `info/refs` file. This file is written by the `update-server-info` command, which is why you need to enable that as a `post-receive` hook in order for the HTTP transport to work properly:

        => GET info/refs
        ca82a6dff817ec66f44342007202690a93763949        refs/heads/master
Now you have a list of the remote references and SHA-1s. Next, you look for what the HEAD reference is so you know what o check out when you're finished:

        => GET HEAD
        ref: refs/heads/master
You need to check out the `master` branch when you've completed the process. At this point, you're ready to start the walking process. Because your starting point is the `ca82a6` commit object you saw in the `ino/refs` file, you start by fetching that:

        => GET objects/ca/82a6dff817ec66f44342007202690a93763949
        (179 bytes of binary data)
You get an object back-that object is in loose format on the server, and youfetched it over a static HTTP GET request. You can zlib-uncompress it, strip off the header, and look at the commit content:

        $ git cat-file -p ca82a6dff817ec66f44342007202690a93763949
        tree cfda3bf379e4f8dba8717dee55aab78aef7f4daf
        parent 085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        author Scott Chacon <schacon$gmail.com> 1205815931 -0700
        commiter Scott Chacon <schacon@gmail.com> 1240030591 -0700

        change the version number

Next, you have two more objects to retrieve-`cfda3b`, which is the tree of content that the commit we just retrieved points to; and `085bb3`, which is the parent commit:

        Get objects/08/5bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        (179 bytes of data)
This gives you your next commit object. Grab the tree object:

        => GET objects/cf/da3bf379e4f8dba8717dee55aab78aef7f4daf
        (404 - Not Found)
Oops-it looks like that tree object isn't in loose format on the server, so you get a 404 reponse back. There are a couple of reasons for this-the object could be in an alternate repository, or it could be in a packfile in this repository. Git checks or any listed alternates first:

        GET objects/info/http-alternates
        (empty file)
If this comes back with a list of alternate URLs, Git checks for loose files and packfiles there-this is a nice mechanism for projects that are forks of one another to share objects on disk. However, because no alternates are listed in this case, your object must be in a packfile. To see what packfiles are available on this server, you need to get the `objects/info/packs` file, which contains a listing of them (also generated by `update-sever-info`):

        => GET objects/info/packs
        P pack-816a9b2334da9953e530f27bcac22082a9f5b835.pack
There is only one packfile on the server, so your object is obviously in there, but you'll check the index file to make sure. This is also useful if you have multiple packfiles on the server, so you can see which packfile contains the object you need:

        => GET objects/pack/pack-816a9b2334da9953e530f27bcac22082a9f5b835.idx
        (4k of bianry data)
Now that you have the packfile index, you can see if your object is in it-because the index lists the SHA-1s of the objects contained in the packfile and the offsets of those objects. Your object is there, so go ahead and get the whole packfile:

        => GET objects/pack/pack-816a9b2334da9953e530f27bcac22082a9f5b835.pack
        (13k of bianry data)
You have your tree object, so you continue walking your commits. They're all also within the packfile you just downloaded, so you don't have to do any more requests to your server. Git checks out a working copy of the `master` branch that was pointed to by the HEAD reference you downloaded at the beginning.

#### The Smart Protocol
The dumb protocol is simple but a bit inefficient, and it can't handle writing of data from the client to the server. The smart protocol is a more common method of transferring data, but it requires a process on the remote end that is intelligent about Git-it can read local data, figure out what the client has and needs, and generate a custom packfile for it. There are two sets of processes for transferring data: a pair for uploading data and a pair for downloading data.
##### Uploading Data
To upload data to a remote process, Git uses the `send-pack` and `receive-pack` processes. The `send-pack` process runs on the client and connects to a `receive-pack` process on the remote side.
* SSH
For example, say you run `git push origin master` in your project, and `origin` is defined as a URL that uses the SSH protocol. Git fires up tha `send-pack` process, which initiates a connection over SSH to your server. It tries to run a command on the remote sever via an SSH call that looks something like this:

        $ ssh -x git@server "git-receive-pack 'simplegit-progit.git'"
        00a5ca82a6dff817ec66f4437202690a93763949 refs/heads/master□report-status \
                delete-refs side-band-64k quiet ofs-delta \
                agent=git/2:2.1.1+github-607-gfba4028 delete-refs
        0000
The `git-receive-pack` command immediately responds with one lien for each reference it currently has-in this case, just the `master` branch and its SHA-1. The first line also has a list of the server's capabilities (here, `report-status`, `delete-refs`, and some others, including the client identifier).
Each line stats with a 4-character hex value specifying how lone the rest of the line is. Your first line starts with 00a5, which is hexadecimal for 165, meaning that 165 bytes remain on that line. The next line is 0000, meaning the sever is done with its references listing.
Now that it knows the servers's state, your `send-pack` process determines what commits it has that the server doesn't. For each reference that this push will update, the `send-pack` process telss the `receive-pack` process that information. For instance, if you're updating the `master` branch and adding an `experiment` branch, the `send-pack` response may look something like this:

        0076ca82a6dff817ec66f44342007202690a93763949 15027957951b64cf874c3557a0f3547bd83b3ff6 \
            refs/heads/master report-status
        006c0000000000000000000000000000000000000000 cdfdb42577e2506715f8cfeacdbabc092bf63e8d \
            refs/heads/experiment
Git sends a line for each reference you're updating with the line's length, the old SHA-1, the new SHA-1, and the reference that is being updated. The first line also has the client's capabilities. The SHA-1 value of all '0's means that nothing was there before-because you're adding the experiment reference. If you were deleting a reference, you would see the opposite: all '0's on the right side.
Next, the client sends a packfile of all the objects the server doesn't have yet. Finally, the server responds with a success (or failure) indication:

        000eunpack ok
* HTTP(S)
This process is mostly the same over HTTP, though the handshaking is a bit different. The connection is initiated with this request:

        => GET http://server/simplegit-progit.git/info/refs?service=git-receive-pack
        001f# service=git-receive-pack
        00ab6c5f0e45abd7832bf23074a333f739977c9e8188 refs/heads/master□report-status \
                delete-refs side-band-64k quiet ofs-delta \
                agent=git/2:2.1.1~vmg-bitmaps-bugaloo-608-g116744e
        0000
That's the end of the first client-server exchange. The client then makes another request, this time a `POST`, with the data that `send-pack` provides.

        => POST http://server/simplegit-progit.git/git-receive-pack
The `POST` request includes the `send-pack` output and the packfile as its payload. The server then indicates success or failure with its HTTP response.
##### Downloading Data
When you download data, the `fetch-pack` and `upload-pack` processes are involved. The client initiates a `fetch-pack` process that connects to an `upload-pack` process on the remote side to negotiate what data will be transferred down.
* SSH
If you're doing the fetch over SSH, `fetch-pack` runs something like this:

        $ ssh -x git@server "git-upload-pack 'simplegit-progit.git'"
After `fech-pack` connects, `upload-pack` sends back something like this:

        00dfca82a6dff817ec66f44342007202690a93763949 HEAD□multi_ack thin-pack \
                side-band side-band-64k ofs-delta shallow no-progress include-tag \
                multi_ack_detailed symref=HEAD:refs/heads/master \
                agent=git/2:2.1.1+github-607-gfba4028
        003fe2409a098dc3e53539a9028a94b6224db9d6a6b6 refs/heads/master
        0000
This is very similar to what `receive-pack` responds with, but the capabilities are different. In addition, it sends bach what HEAD points to (`symref=HEAD:refs/heads/master`) so the client knows what to check out if this is a clone.
At this point, the `fetch-pack` process looks at what objects it has and responds with the objects that it needs by sending "want" and then the SHA-1 it wants. It sends all the objects it already has with "have" and then the SHA-1. At the end of this list, it writes "done" to initiate the `upload-pack` process to begin sending the packfile of the data it needs:

        003cwant ca82a6dff817ec66f44342007202690a93763949 ofs-delta
        0032have 085bb3bcb608e1e8451d4b2432f8ecbe6306e7e7
        0009done
        0000
* HTTP(S)
The handshake for a fetch operation takes two HTTP requests. The first is a `GET` to the same endpoint used in the dumb protocol: 

        => GET $GIT_URL/info/refs?service=git-upload-pack
        001e# service=git-upload-pack
        00e7ca82a6dff817ec66f44342007202690a93763949 HEAD□multi_ack thin-pack \
                side-band side-band-64k ofs-delta shallow no-process include-tag \
                multi_ack_detailed no-done symref=HEAD:refs/heads/master \
                agent=git/2:2.2.1+github-607-gfba4028
        003fca82a6dff817ec66f44342007202690a93763949 refs/heads/master
        0000
This is very similar to invoking `git-upload-pack` over an SSH connection, but the second exchange is performed as a seperate request:

        => POST $GIT_URL/git-upload-pack HTTP/1.0
        0032want 0a53e9ddeaddad63ad106860237bbf53411d11a7
        0032have 441b40d833fdfa93eb2908e52742248faf0ee993
        0000
Again, this is the same format as above. The response to this request indicates success or failure, and includes the packfile.
#### Protocols Summary
This section contains a very basic overview of the transfer protocols. The protocol includes many other features, such as `multi_ack` or `side-band` capabilities, but covering them is outside the scope of this book. We've tried to give you a sense of the general back-and-forth between client and server; if you need more knowledge than this, you'll probaly want to take a look at the Git source code.
