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
It's important to understand that when you're amending your last commit, you're not so much fixing it as replacing it entirely with a new, improved commit that pushes the old commit out of the way and puts the new commit in this place. Effectively, it's as if the previous commit never happened, and it won't show up in your repository history.
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
This is shorthand for:

        $ git branch iss53
        $ git checkout iss53
![Creating a new branch pointer](basic-branching-2.png)
Figure 19. Creating a new branch pointer
You work on your website and do some commits. Doing so moves the `iss53` branch forward, because you have it checked out (that is, your `HEAD` is pointing to it):

        $ vim index.html
        $ git commit -a -m 'added a new footer [issue 53]'
![the branch has moved forward](basic-branching-3.png)
Figure 20. The `iss53` branch has moved forward with your work
Now you get the call that there is an issue with the website, and you need to fix it immediately. With Git, you don't have to deploy your fix along with the `iss53` changes you've made, and you don't have to put a lot of effort into reverting those changes before you can work on applying your fix to what is in production. All you have to do is switch back to your `master` branch.
However, before you do that, note that if your working directory or staging area has uncommitted changes that conflict with the branch you're checking out, Git won't let you switch branches. It's best to have a clean working state when you switch branches. There are ways to get around this (namely, stashing and commit amending) that we'll cover later on, in Stashing and Cleaning. For now, let's assume you've committed all your changes, so you can switch back to your `master` branch:

        $ git checkout master
        Switched to branch `master`
At this point, your project working directory is exactly the way it has before you started working on issue #53, and you can concentrate on your hotfix. This is an important point to remember: when you switch branches, Git resets your working directory to look like it did the last time you committed on that branch. It adds, removes, and modifies files automatically to make sure your working copy is what the branch looked like on your last commit to it.
Next, you have a hotfix to make. Let's create a `hotfix` branch on which to work until it's completed:

        $ git checkout -b hotfix
        Switched to a new branch 'hotfix'
        $ vim index.html
        $ git commit -a -m 'fixed the broken email address'
        [hotfix 1fb7853] fixed the broken email address
         1 file changed, 2 insertions(+)
![hotfix branch based on `master`](basic-branching-4.png)
Figure 21. Hotfix branch based on `master`
You can run your tests, make sure the hotfix is what you want, and finally merge the `hotfix` branch back into your `master` branch to deploy to production. You do this with the `git merge` command:

        $ git checkout master
        $ git merge hotfix
        Updating f42c576..3a0874c
        Fast-forward
         index.html | 2 ++
         1 file changed, 2 insertins(+)
You'll notice the phrase "fast-forward" in that merge. Because the commit `C4` pointed to by the branch `hotfix` you merged in was directly ahead of the commit `C2` you're on, Git simply moves the pointer forward. To phrase that another way, when you try to merge one commit with a commit that can be reached by following the first commit's history, Git simplifies things by moving the pointer forward because there is no divergent work to merge together-this is called a "fast-forward".
Your change is now in the snapshot of the commit pointed to by the `master` branch, and you can deploy the fix.
![master is fast-forwarded to `hotfix`](basic-branching-5.png)
Figure 22. `master` is fast-forwarded to `hotfix`
After your super-important fix is deployed, you're ready to switch back to the work you were doing before you were interrupted. However, first you'll delete the `hotfix` branch, because you no longer need it-the master branch points at the same place. You can delete it with the `-d` option to `git branch`:

        $ git branch -d hotfix
        Deleted branch hotfix (3a0874c).
Now you can switch back to your work-in-progress branch on issue #53 and continue working on it.

        $ git checkout iss53
        Switched to branch "iss53"
        $ vim index.html
        $ git commit -a -m 'finished the ne footer [issue 53]'
        [iss53 ad82d7a] finished the new footer [issue 53]
        1 file changed, 1 insertion(+)
![work continues on `iss53`](basic-branching-6.png)
Figure 23. Work continues on `iss53`
It's worth nothing here that the work you did in your `hotfix` branch is not contained in the files in your `iss53` branch. If you need to pull it in, you can merge your `master` branch into your `iss53` branch by running `git merge master`, or you can wait to integrate those changes until you decide to pull the `iss53` branch back into `master` later.
#### Basic Merging
Suppose you've decided that your issue #53 work is complete and ready to be merged into your `master` branch. In order to do that, you'll merge your `iss53` branch into `master`, much like you merged your `hotfix` branch earlier. All you have to do is check out the branch you wish to merge into and then run the `git merge` command:

        $ git checkout master
        Switched to branch 'master'
        $ git merge iss53
        Merge made by the 'recursive' strategy.
        index.html | 1 +
        1 file changed, 1 insertion(+)
This looks a bit different than the `hofix` merge you did earlier. In this case, your development history has diverged from some older point. Because the commit on the branch you're on isn't a direct ancestor of the  branch you're merging in, Git has to do some work. In this case, Git does a simple three-way merge, using the two snapshots pointed to by the branch tips and the common ancestor of the two.
![three snapshots used in a typical merge](basic-merging-1.png)
Figure 24. Three snapshots used in a typical merge
Instead of just moving the branch pointer forward, Git creates a new snapshot that results from this three-way merge and automatically creates a new commit that points to it. This is referred to as a merge commit, and is special in that it has more than one parent.
![a merge commit](basic-merging-2.png)
Figure 25. A merge commit
It's worth pointing out that Git determines the best common ancestor to use for its merge base; this is different than older tools like CVS or Subversion (before version 1.5), where the developer doing the merge had to figure out the best merge base for themselves. This makes merging a heck of a lot easier in Git than in these other systems.
Now that your work is merged in, you have no further need for the `iss53` branch. You can close the ticket in your ticket-tracking system, and delete the branch:

        $ git branch -d iss53
#### Basic Merge Conflicts
Occasionally, this process doesn't go smoothly. If you changed the same part of the same file differently in the two branches you're merging together, Git won't be able to merge them cleanly. If your fix for issue #53 modified the same part of a file as the `hotfix` branch, you'll get a merge conflict that looks something like this:

        $ git merge iss53
        Auto-merging index.html
        CONFLICT (content): Merge conflict in indext.html
        Automatic merge failed; fix conflicts and then commit the result.
Git hasn't automatically created a new merge commit. It has paused the process while you resolve the conflict. If you want to see which files are unmerged at any point after a merge conflict, you can run `git status`:

        $ git status
        On branch master
        You have unmerge paths.
            (fix conflicts and run "git commit")

        Unmeged paths:
            (use "git add <file>..." to mark resolution)

                both modified:      index.html

        no changes added to commit (use "git add" and/or "git commit -a")
Anything that has merge conflicts and hasn't been resolved is listed as unmerged. Git adds standard conflict-resolution markers to the files that have conflicts, so you can open them manually and resolve those conflicts. Your file contains a section that looks something like this:

        <<<<<<< HEAD:index.html
        <div id="footer">contact : email.support@github.com</div>
        =======
        <div id="footer">
            please contact us at support@github.com
        </div>
        >>>>>>> iss53:index.html
This means the version in `HEAD` (your `master` branch, because that was what you had checked out when you ran our merge command) is the top part of that block (everything above the `=======`), while the version in your `iss53` branch looks like everything in the bottom part. In order to resolve the conflict, you have to either choose one side or the other or merge the contents yourself. For instance, you might resolve this conflict by replacing the entire block with this:

        <div id="footer">
        please contact us at email.support@github.com
        </div>
This resolution has a little of each section, and the `<<<<<<<`,`======`, and `>>>>>>>` lines have been completely removed. After you've resolved each of these sections in each conflicted file, run `git add` on each file to mark it as resolved. Staging the file marks it as resolved in Git.
If you want to use a graphical tools to resolve these issues, you can run `git mergetool`, which fires up an appropriate visual merge tool and walks you through the conflicts:
        
        $ git mergetool

        This message is displayed because 'merge.tool' is not configured.
        See 'git mergetool --tool-help' or 'git help config' for more details.
        'git mergetool' will now attempt to use one of the following tools:
        opendiff kdiff3 tkdiff xxdiff meld toroisemerge gvimdiff diffuse diffmerge ecmege p4merge araxix bc3 codecomare vimdiff emerge
        Merging:
        index.html

        Normal merge conflict for 'index.html':
            {local}: modified file
            {remote}: modified file
        Hit return to start merge resolution tool (opendiff):
If you want to use a merge tool other than the default (Git chose `opendiff` in this case because the command was run on a Mac), you can see all the supported tools listed at the top after "one of the following tools." Just type the name of the tool you'd rather use.
_Note: If you need more advanced tools for resolving tricky merge conflict, we cover more on merging in Advanced Merging._
After you exit the merge tool, Git asks you if the merge was successful. If you tell the script that it was, it stages the file to mark it as resolved for you. You can run `git status` again to verify that all conflicts have been resolved:

        $ git status
        On branch master
        All conflicts fixed but you are still merging.
            (use "git commit" to conclude merge)

        Changes to be committed:

            modified:   index.html
If you're happy with that, and you verify that everything that had conflicts has been staged, you can type `git commit` to finalize the merge commit. The commit message by default looks something like this:

        Merge branch 'iss53'

        Conflicts:
            index.html
        #
        # It looks like you may be committing a merge.
        # If this is not correct, please remove the file
        #       .git/MERGE_HEAD
        # and try again


        # Please enter the commit message for your changes. Lines starting
        # with '#' will be ignored, and an empty message aborts the commit.
        # On branch master
        # All conflicts fixed but you are still merging.
        #
        # Changes to be committed:
        #       modified:   index.html
        #
If you think it would be helpful to others looking at this merge in the future, you can modify this commit message with details about how you resolved the merge and explain why you did the changes you made if these are not obvious.
### 3.3 Git Branching - Branch Management
#### Branch Management
Now that you've created, merged, and deleted some branches, let's look at some branch-management tools that will come in handy when you being using branches all the time.
The `git branch` command does more than just create and delete branches. If you run it with no arguments, you get a simple listing of your current branches:

        $ git branch
            iss53
        *   master
        *   testing
Notice the `*` character that prefixes the `master` branch: it indicates the branch that you currently have checked out (i.e., the branch that `HEAD` points to). This means that if you commit at this point, the `master` branch will be moved forward with your new work. To see the last commit on each branch, you can run `git branch -v`:

        $ git branch -v
            iss53 93b412c fix javascript issue
        *   master  7a98805 Merge branch 'iss53'
            testing 782fd34 add scott to the author list in the readmes
The useful `--merged` and `--no-merged` options can filter this list to branches that you have or have not yet merged into the branch you're currently on. To see which branches are already merged into the branch you're on, you can run `git branch --merged`:

        $ git branch --merged
            iss53
        *   master
Because you already merged in `iss53` earlier, you see it in your list. Branches on this list without the `*` in front of them are generally fine to delete with `git brand -d`; you've already incorporated their work into another branch, so you're not going to lose anything.
To see all the branches that contain work you haven't yet merged in, you can run `git branch --no-merged`:

        $ git branch --no-merged
            testing
This shows your other branch. Because it contains work that isn't merged in yet, trying to delete it with `git branch -d` will fail:

        $ git branch -d testing
        error: The branch 'testing' is not fully merged.
        If you are sure you want to delete it, run 'git branch -D testing'.
If you really do want to delete the branch and lose that work, you can force it with `-D`, as the helpful message points out.
_Tip: The options described above, `--merge` and `--no-merged` will, if not given a commit or branch name as an argument, show you what is, respectively, merged or not merged into your current branch.
You can always provide an additional argument to ask about the merge state with respect to some other branch without checking that other branch out first, as in, what is not merged into the `master` branch?

         $ git checkout testing
         $ git branch --no-merge master
             topicA
             featureB_
### 3.4 Git Branching - Branching Workflows
#### Branching Workflows
Now that you have the basics of branching and merging down, what can or should you do with them? In this section, we'll cover some common workflows that this lightweight branching makes possible, so you can decide if you would like to incorporate them into your own development cycle.
#### Long-Running Branches
Because Git uses a simple three-way merge, merging from one branch into another multiple times over a long period is generally easy to do. This means you can have several branches that are always open and that you use for different stages for your development cycle; you can merge regularly from some of them into others.
Many Git developers have a workflow that embraces this approach, such as having only code that is entirely stable inn their `master` branch-possibly only code that has been or will be released. They have another parallel branch named `develop` or `next` that they work from or use to test stability-it isn't necessarily always stable, but whenever it gets to a stable state, it can be merged into `master`. It's used to pull in topic branches (short-lived branches, like your earlier `iss53` branch) when they're ready, to make sure they pass all the tests and don't introduce bugs.
In reality, we're talking about pointers moving up the line of commits you're making. The stable branches are farther down the line in you commit history, and the bleeding-edge branches are farther up the history.
![A linear view of progressive-stability branching](lr-branches-1.png)
Figure 26. A linear view of progressive-stability branching
It's generally easier to think about them as work silos, where sets of commits graduate to a more stable silo when they're fully tested.
![A "silo" view of progressive-stability branching](lr-branches-2.png)
Figure 27. A "silo" view of progressive-stability branching
You can keep doing this for several levels of stability. Some larger projects also have a `proposed` or `pu` (proposed updates) branch that has integrated branches that may not be ready to go into the `next` or `master` branch. The idea is that your branches are at various levels of stability; when they reach a more stable level, they're merged into the branch above them. Again, having multiple long-running branches isn't necessary, but it's often helpful, especially when you're dealing with very large or complex projects.
#### Topic Branches
Topic branches, however, are useful in projects of any size. A topic branch is a short-lived branch that you create and use for a single particular feature or related work. This is something you've likely never done with a VCS before because it's generally to expensive to create and merge branches. But in Git it's common to create, work on, merge, and delete branches several times a day.
You saw this in the last section with the `iss53` and `hotfix` branches you created. You did a few commits on them and deleted them directly after merging them into your main branch. This technique allows you to context-switch quickly and completely-because your work is separated into silos where all the changes in that branch have to do with that topic, it's easier to see what has happened during code review and such. You can keep the changes there for minutes, days, or months, and merge them in when they're ready, regardless of the order in which they were created or worked on.
Consider an example of doing some work (on `master`), branching off for an issue (`iss91`), working on it for a bit, branching off the second branch to try another way of handling the same thing (`iss91v2`), going back to your `master` branch and working there for a while, and then branching off there to do some work that you're not sure is a good idea (`dumbidea` branch). Your commit history will look something like this:
![multiple topic branches](topic-branches-1.png)
Figure 28. Multiple topic branches
Now, let's say you decide you like the second solution to your issue best (`iss91v2`); and you showed the `dumbidea` branch to your coworkers, and it turns out to be genius. You can throw away the original `iss91` branch (losing commits `C5` and `C6`) and merge in the other two. Your history then looks like this:
![history of merging `dumbidea` and `iss91v2`](topic-branches-2.png)
Figure 29. History after merging `dumbidea` and `iss91v2`
We will go into more detail about the various possible workflows for your Git project in Distributed Git, so before you decide which branching scheme your next project will use, be sure to read that chapter.
It's important to remember when you're doing all this that these branches are completely local. When you're branching and merging, everything is being done only in your Git repository-no server communication is happening.
### 3.5 Git Branching - Remote Branches
#### Remote Branches
Remote references are references (pointers) in your remote repositories, including branches, tags, and so on. You can get a full list of remote references explicitly with `git ls-remote [remote]`, or `git remote show [remote]` for remote branches as well as more information. Nevertheless, a more common way is to take advantage of remote-tracking branches.
Remote-tracking branches are references to the state of remote branches. They're local references that you can't move; Git moves them for you whenever you do any network communication, to make sure they accurately represent the state of the remote repository. Think of them as bookmarks, to remind you where the branches in your remote repositories were the last time you connected to them.
Remote-tracking branches take the form `<remote>/<branch>`. For instance, if you wanted to see what the `master` branch on your `origin` remote looked like as of the last time you communicated with it, you would check the `origin/master` branch. If you were working on an issue with a partner and they pushed up an `iss53` branch, you might have your own local `iss53` branch, but the branch on the server would be represented by the remote-tracking branch `origin/iss53`.
This may be a bit confusing, so let's look at an example. Let's say you have a Git server on your network at `git.ourcompany.com`. If you clone from this, Git's `clone` command automatically names it `origin` for you, pulls down all its data, creates a pointer to where its `master` branch is, and names it `origin/master` locally. Git also gives you your own local `master` branch starting at the same place as origin's `master` branch, so you have something to work from.
_Note: "origin" is note special. Just like the branch name "master" does not have any special meaning in Git, neither does "origin". While "master" is the default name for a starting branch when you run `git init` which is the only reason it's widely used, "origin" is the default name for a remote when you run `git clone`. If you run `git clone -o booyah` instead, then you will have `booyah/master` as your default remote branch._
![server and local repositories after cloning](remote-branches-1.png)
Figure 30. Server and local repositories after cloning
If you do some work on your local `master` branch, and, in the meantime, someone else pushes to `git.ourcompany.com` and updates its `master` branch, then your histories move forward differently. Also, as long as you stay out of contact with your origin server, your `origin/master` pointer doesn't move.
![Local and remote work can diverge](remote-branches-2.png)
Figure 31. Local and remote work can diverge
To synchronize your work, you run a `git fetch origin` command. This command looks up which server "origin" is (in this case, it's `git.ourcompany.com`), fetches any data from it that you don't yet have, and updates your local database, moving your `origin/master` pointer to its new, more up-to-date position.
![`git fetch` updates your remote references](remote-branches-3.png)
Figure 32. `git fetch` updates your remote references
To demonstrate having multiple remote servers and what remote branches for those remote projects look like, let's assume you have another internal Git server that is used only for development by one of your sprint teams. This server is at `git.team1.ourcompany.com`. You can add it as a new remote reference to the project you're working on by running the `git remote add` command as we covered in Git Basics. Name this remote `teamone`, which will be your shortname for that whole URL.
![adding another server as a remote](remote-branches-4.png)
Figure 33. Adding another server as a remote
Now, you can run `git fetch teamone` to fetch everything the remote `teamone` server has that you don't have yet. Because that server has a subset of the data your `origin` server has right now, Git fetches no data but sets a remote-tracking branch called `teamone/master` to point to the commit that `teamone` has as its `master` branch.
![Remote tracking branch for `teamone/master`](remote-branches-5.png)
Figure 34. Remote tracking branch for `teamone/master`
#### Pushing
When you want to share a branch with the world, you need to push it up to a remote that you have write access to. Your local branches aren't automatically synchronized to the remotes you write to-you have to explicitly push the branches you want to share. That way, you can use private branches for work you don't want to share, and push up only the topic branches you want to collaborate on.
If you have a branch named `serverfix` that you want to work with others, you can push it up the same way you pushed your first branch. Run `git push <remote> <branch>`:

        $ git push origin serverfix
        Counting objects: 24, done.
        Delta compression using up to 8 threads.
        Compressing objects: 100% (15/15), done.
        Writing objects: 100% (24/24), 1.91 KiB | 0 bytes/s, done.
        Total 24 (delta 2), reused 0 (delta 0)
        To https://github.com/schacon/simplegit
         * [new branch]     serverfix -> serverfix
This is a bit of shortcut. Git automatically expands the `serverfix` branchname out to `refs/heads/serverfix:refs/heads/serverfix`, which means, "Take my serverfix local branch and push it to update the remote's serverfix branch." We'll go over the `refs/heads/` part in detail in Git Internals, but you can generally leave it off. You can also do `git push origin serverfix:serverfix`, which does the same thing-it says, "Take my serverfix and make it the remote's serverfix." You can use this format to push a local branch into a remote branch that is named differently. If you didn't want it to be called `serverfix` on the remote, you could instead run `git push origin serverfix:awesomebranch` to push your local `serverfix` branch to the `awesomebranch` branch on the remote project.
_Note: Don't type your password every time. 
If you're using an HTTPS URL to push over, the Git server will ask you for your username and password for authentication. By default it will prompt you on the terminal for this information so the server can tell if you're allowed to push.
If you don't want to type it every single time you push, you can set up a "credential cache". The simplest is just to keep it in memory for a few minites, which you can easily set up by running `git config --global credential.helper cache`.
For more information on the various credential caching options available, see Credential Storage._
The next time one of your collaborators fetches from the server, they will get a reference to where the server's version of `serverfix` is under the remote branch `origin/serverfix`:

        $ git fetch origin
        remote: Counting objects: 7, done.
        remote: Compressing objects: 100% (2/2), done.
        remote: Total 3 (delta 0), reused 3 (delta 0)
        Unpacking objects: 100% (3/3), done.
        From https://github.com/schacon/simplegit
         * [new branch]     serverfix       -> origin/serverfix
It's important to note that when you do a fetch that brings down new remote-tracking branches, you don't automatically have local, editable copies of them. In other words, in this case, you don't have a new `serverfix` branch-you only have an `origin/serverfix` pointer that you can't modify.
To merge this work into your current working branch, you can run `git merge origin/serverfix`. If you want your own `serverfix` branch that you can work on, you can base it off your remote-tracking branch:

        $ git checkout -b severfix origin/serverfix
        Branch serverfix set up tp track remtoe branch serverfix from origin
        Switched to a new branch 'serverfix'
This gives you a local branch that you can work on that starts where `origin/serverfix` is.
#### Tracking Branches
Checking out a local branch from a remote-tracking branch automatically creates what is called a "tracking branch" (and the branch it tracks is called an "upstream branch").
Tracking branches are local branches that have a direct relationship to a remote branch. If you're on a tracking branch and type `git pull`, Git automatically knows which server to fetch from and which branch to merge in.
When you clone a repository, it generally automatically creates a `master` branch that tracks `origin/master`. However, you can set up other tracking branches if you wish-ones that track branches on other remotes, or don't track the `master` branch. The simple case is the example you just saw, running `git checkout -b <branch> <remote>/<branch>`. This is a common enough operation that Git provides the `--track` shorthand:

        $ git checkout --track origin/serverfix
        Branch serverfix set up to track remote branch serverfix from origin.
        Switched to a new branch 'serverfix'.
In fact, this is so common that there's even a shortcut for that shortcut. If the branch name you're trying to checkout doesn't exist and exactly matches a name on only one remote, Git will create a tracking branch for you:

        $ git checkout serverfix
        Branch serverfix set up to track remote branch serverfix from origin.
        Switched to a new branch 'serverfix'
To set up a local branch with a different name than the remote branch, you can easily use the first version with a different local branch name:

        $ git checkout -b sf origin/serverfix
        Branch sf set up to track remote branch serverfix from origin.
        Switched to a new branch 'sf'
Now your local branch `sf` will automatically pull from `orgin/serverfix`.
If you already have a local branch and want to set it to a remote branch you just pulled, or want to change the upstream branch you're tracking, you can use the `-u` or `--set-upstream-to` option to `git branch` to explicitly set it at any time.

        $ git branch -u origin/serverfix
        Branch serverfix set up to track remote branch serverfix from origin.
_Note: Upstream shorthand.
When you have a tracking branch set up, you can reference its upstream branch with the `@{upstream}` or `@{u}` shorthand. So if you're on the `master`branch and it's tracking `origin/master`, you can say something like `git merge @{u}` instead of `git merge origin/master` if you wish._
If you want to see what tracking branches you have set up, you can use the `-vv` option to `git branch`. This will list out your local branches with more information including what each branch is tracking and if your local branch is ahead, behind or both.

        $ git branch -vv
            iss53 7e424c3 [origin/iss53: ahead 2] forgot the brackets
            master  1ae2a45 [origin/master] developing index fix
        *   serverfix f874d9 [teamone/server-fix-good: ahead 3, behiend 1] this should do it
            testing 5ea463a trying something new
So here we can see that our `iss53` branch is tracking `origin/iss53` and is "ahead" by two, meaning that we have two commits locally that are note pushed up the server. We can also see that our `master` branch is tracking `origin/master` and is up to date. Next we can see that our `serverfix` branch is tracking the `server-fix-googd` branch on our `teamone` server and is ahead by three and behind one, meaning that there is one commit on the server we haven't merged in yet and three commits locally that we haven't pushed. Finally we can see that our `testing` branch is not tracking any remote branch.
It's important to note that these numbers are only since the last time you fetched from each server. This command does not reach out to the servers, it's telling you about what it has cached from these servers locally. If you want totally up to date ahead and behind numbers, you'll need to fetch from all your remotes right before running this. You could do that like this:

        $ git fetch --all; git branch -vv
#### Pulling
While the `git fetch` command will fetch down all the changes on the server that you don't have yet, it will not modify your working directory at all. It will simply get the data for you and merge it yourself. However, there is a command called `git pull` which is essentially a `git fetch` immediately followed by a `git merge` in most cases. If you have a tracking branch set up as demonstrated in the last section, either by explicitly setting it or by having it created for you by the `clone` or `checkout` commands, `git pull` will look up what server and branch your current branch is tracking, fetch from that server and then try to merge in that remote branch.
Generally it's better to simply use the `fetch` and `merge` commands explicitly as the magic of `git pull` can often be confusing.
#### Deleting Remote Branches
Suppose you're done with a remote branch-say you and your collaborators are finished with a feature and have merged it into your remote's `master` branch (or whatever branch your stable codeline is in). You can delete a remote branch using the `--delete` option to `git push`. If you want to delete your `serverfix` branch from the server, you run the following:

        $ git push origin --delete serverfix
        To https://github.com/schacon/simplegit
         - [deleted]        serverfix
Basically all this done is to remove the pointer from the server. The Git server will generally keep the data there for a while until a garbage runs, so if it was accidentally deleted, it's often easy to recover.
### 3.6 Git Branching - Rebasing
#### Rebasing
In Git, there are two main ways to integrate changes from one branch into another: the `merge` and the `rebase`. In this section you'll learn what rebasing is, how to do it, why it's a pretty amazing tool, and in what cases you won't want to use it.
#### The Basic Rebase
If you go back to an earlier example from Basic Merging, you can see that you diverged your work and made commits on two different branches.
![simple divergent history](basic-rebase-1.png)
Figure 35. Simple divergent history
The easiest way to integrate the branches, as we've already covered, is the `merge` command. It performs a three-way merge between the two latest branch snapshots (`C3` and `C4`) and the most recent common ancestor of the two (`C2`), creating a new snapshot (and commit).
![merging to integrate diverged work history](basic-rebase-2.png)
Figure 36. Merging to integrate diverged work history
However, there is another way: you can take the patch of the change that was introduced in `C4` and reapply it on top of `C3`. In Git, this is called _rebasing_. With the `rebase` command, you can take all the changes that were committed on one branch and replay them on another one.
In this example, you'd run the following:

        $ git checkout experiment
        $ git rebase master
        Firtst, rewinding head to replay your work on top of it...
        Applying: added staged coommand
It works by going to the common ancestor of the two branches (the one you're on and the one you're rebasing onto), getting the diff introduced by each commit of the branch you're on, saving those diffs to temporary files, resetting the current branch to the same commit as the branch you are rebasing onto, and finally applying each change in turn.
![rebasing the change introduced in `C4` onto `C3`](basic-rebase-3.png)
Figure 37. Rebasing the change introduced in `C4` onto `C3`
At this point, you can go back to the `master` branch and do a fast-forward merge.

        $ git checkout master
        $ git mege experiment
![fast-forwarding the master branch](basic-rebase-4.png)
Figure 38. Fast-forwarding the master branch
Now, the snapshot pointed to by `C4'` is exactly the same as the one that was pointed to by `C5` in the merge example. There is no difference in the end product of the integration, but rebasing makes for a cleaner history. If you examine the log of a rebased branch, it looks like a linear history: it appears that all the work happened in series, even when it originally happened in parallel.
Often, you'll do this to make sure your commits apply cleanly on a remote branch-perhaps in a project to which you're trying to contribute but that you don't maintain. In this case, you'd do your work in a branch and then rebase your work onto `origin/master` when you were ready to submit your patches to the main project. That way, the maintainer doesn't have to do any integration work-just a fast-forward or a clean apply.
Note that the snapshot pointed by the final commit you end up with, whether it's the last of the rebased commits for a rebase or the final merge commit after a merge, is the same snapshot-it's only the history that is different. Rebasing replays changes from one line of work onto another in the order they were introduced, whereas merging takes the endpoints and merges them together.
#### More Interesting Rebases
You can also have your rebase replay on something other than the rebase target branch. Take a history like A history with a topic branch off another topic branch, for example. You branched off a topic branch (`server`) to add some server-side functionality to your project, and made a commit. Then, you branched off that to make the client-side changes (`client`) and committed a few times. Finally, you went back to your server branch and did a few more commits.
![a history with a topic branch off another topic branch](interesting-rebase-1.png)
Figure 39. A history wit a topic branch off another topic branch
Suppose you decide that you want to merge your client-side changes into your mainline for a rebase, but you want to hold off on the server-side changes until it's tested further. You can take the changes on client that aren't on server (`C8` and `C9`) and replay them on your `master` branch by using the `--onto` option of `git rebase`:

        $ git rebase --onto master server client
This basically says, "Take the `client` branch, figure out the patches since it diverged fro the `server` branch, and replay these patches in the `client` branch as if it was based directly off the `master` branch instead." It's a bit complex, but the result is pretty cool.
![rebasing a topic branch off another topic branch](interesting-rebase-2.png)
Figure 40. Rebasing a topic branch of another topic branch
Now you can fast-forward your `master` branch (see Fast-forwarding your master branch to include the client branch changes):

        $ git checkout master
        $ git merge client
![fast-forwarding your master branch to include the client branch changes](interesting-rebase-3.png)
Figure 41. Fast-forwarding your master branch to include the client branch changes
Let's say you decide to pull in your server branch as well. You can rebase the server branch onto the `master` branch without having to check it out first by running `git rebase <basebranch> <topicbranch>`-which checks out the topic branch (in this case, `server`) for you and replays it onto the base branch (`master`):

        $ git rebase master server
This replays your `server` work on top of your `master` work, as shown in Rebasing your server branch on top of your master branch.
![rebasing your server branch on top of your master branch](interesting-rebase-4.png)
Figure 42. Rebasing your server branch on top of your master branch
Then, you can fast-forward the base branch (`master`):

        $ git checkout master
        $ git merge server
You can remove the `client` and `server` branches because all the work is integrated and you don't need them anymore, leaving your history for this entire process looking like Final commit history:

        $ git branch -d client
        $ git branch -d server
![final commit history](interesting-rebase-5.png)
Figure 43. Final commit history
#### The Perils of Rebasing
Ahh, but the bliss of rebasing isn't without its drawbacks, which can be summed up in a single line:
**Do not rebase commits that exist outside your repository.**
If you follow that guide line, you'll be fine. If you don't, people will hate you, and you'll be scorned by friends and family.
When you rebase stuff, you're abandoning existing commits and creating new ones that are similar but different. If you push commits somewhere and others pull them down and base work on them, and then you rewrite those commits with `git rebase` and push them up again, your collaborators will have to re-merge their work and things will get messy when you try to pull their work back into yours.
Let's look at an example of how rebasing work that you've made public can cause problems. Suppose you clone from a central server and then do some work off that. Your commit history looks like this:
![clone a repository, and base some work on it](perils-of-rebasing-1.png)
Figure 44. Clone a repository, and base some work on it
Now, someone else does more work that includes a merge, and pushes that work to the central sever. You fetch it and merge the new remote branch into your work, making your history look like this:
![fetch more commits, and merge them into your work](perils-of-rebasing-2.png)
Figure 45. Fetch more commits, and merge them into your work
Next, the person who pushed the merged work decides to go back and rebase their work instead; they do a `git push --force` to overwrite the history on the server. You then fetch from that server, bringing down the new commits.
![someone pushes rebased commits, abandoning commits you've based your work on](perils-of-rebasing-3.png)
Figure 46. Someone pushes rebased commits, abandoning commits you've based your work on
Now you're both in a pickle. If you do a `git pull`, you'll create a merge commit which includes both lines of history, and your repository will look like this:
![you merge in the same work again into a new merge commit](perils-of-rebasing-4.png)
Figure 47. You merge in the same work again into a new merge commit
If you run a `git log` when your history looks like this, you'll see two commits that have the same author, date, and message, which will be confusing. Furthermore, if you push this history back up to the server, you'll reintroduce all those rebased commits to the central server, which can further confuse people. It's pretty safe to assume that the other developer doesn't want `C4` and `C6` to be in the history; that's why they rebased in the first place.
#### Rebase When You Rebase
If you **do** find yourself in a situation like this, Git has some further magic that might help you out. If someone on your team force pushes changes that overwrite work that you've based work on, your challenge is to figure out what is yours and what they've written.
It turns out that in addition to the commit SHA-1 checksum, Git also calculates a checksum that is based just on the patch introduced with the commit. This is called a "patch-id".
If you pull down work that was rewritten and rebase it on top of the new commits from your partner, Git can often successfully figure out what is uniquely yours and apply them back on top of the new branch.
For instance, in the previous scenario, if instead of doing a merge when we're at Someone pushes rebased commits, abandoning commits you've based your work on we run `git rebase teamone/master`, Git will:
* Determine what work is unique to our branch (C2, C3, C4, C6, C7)
* Determine which are not merge commits (C2, C3, C4)
* Determine which have not been rewritten into the target branch (just C2 and C3, since C4 is the same patch as C4')
* Apply those commits to the top of `teamone/master`
So instead of the result we see in You merge in the same work again into a new merge commit, we would end up with something more like Rebase on top of force-pushed rebase work.
![rebase on top of force-pushed rebase work](perils-of-rebasing-5.png)
Figure 48. Rebase on top of force-pushed rebase work
This only works if C4 and C4' that your partner made are almost exactly the same patch. Otherwise the rebase won' be able to tell that it's a duplicate and will add another C4-like patch (which will probably fail to apply cleanly, since the changes would already be at least somewhat there).
You can also simplify this by running a `git pull --rebase` instead of a normal `git pull`. Or you could do it manually with a `git ftch` followed by a `git rebase teamone/master` in this case.
If you are using `git pull` and want to make `--rebase` the default, you can set the `pull.rebase` config value with something like `git config --global pull.rebase true`.
If you treat rebasing as a way to clean up and work with commits before you push them, and if you only rebase commits that have never been available publicly, then you'll be fine. If you rebase commits that have already been pushed publicly, and people may have based work on those commits, then you may be in for some frustrating trouble, and the scorn of your teammates.
If you or a partner find it necessary at some point, make sure everyone knows to run `git pull --rebase` to try to make the pain after it happens a little bit simpler.
#### Rebase vs. Merge
Now that you've seen rebasing and merging in action, you may be wondering which one is better. Before we can answer this, let's step back a bit and talk about what history means.
One point of view on this is that your repository's commit history is a **record of what actually happened.** It's a historical document, valuable in its own right, and shouldn't be tampered with. From this angle, changing the commit history is almost blasphemous; you're lying about what actually transpired. So what if there was a messy series of merge commits? That's how it happened, and the repository should preserve that for posterity.
The opposing point of view is that the commit history is the **story of how your project was made.** You wouldn't publish the first draft of a book, and the manual for how to maintain your software deserves careful editing. This is the camp that uses tools like rebase and filter-branch to tell the story in the way that's best for future readers.
Now, to the question of whether merging or rebasing is better: hopefully you'll see that it's not that simple. Git is a powerful tool, and allows you to do many things to and with your history, but every team and every project is different. Now that you know how both of these things work, it's up to you to decide which one is best for your particular situation.
In general the way to get the best of both worlds is to rebase local changes you've made but haven't shared yet before you push them in order to clean up your story, but never rebase anything you've pushed somewhere.
### 3.7 Git Branching -Summary
#### Summary
We've covered basic branching and merging in Git. You should feel comfortable creating and switching to new branches, switching between branches and merging local branches together. You should also be able to share your branches by pushing them to a shared server, working with others on shared branches and rebasing your branches before they are shared. Next, we'll cover what you'll need to run your own Git repository-hosting server.
## 4. Git on the Server
### 4.1 Git on the Server - The Protocols
At this point, you should be able to do most of the day-to-day tasks for which you'll be using Git. However, in order to do any collaboration in Git, you'll need to have a remote Git repository. Although you can technically push changes and pull changes from individuals' repositories, doing so is discouraged because you can fairly easily confuse what they're working on if you're not careful. Furthermore, you want your collaborators to be able to access the repository even if your computer is offline-having a more reliable common repository if often useful. Therefore, the preferred method for collaborating with someone is to set up an intermediate repository that you both have access to, and push to and pull from that.
Running a Git server is fairly straightforward. First, you choose which protocols you want your server to communicate with. The first section of this chapter will cover the available protocols and the pros and cons of each. The next sections will explain some typical setups using those protocols and how to get your server running with them. Last, we'll go over a few hosted options, if you don't mind hosting your code on someone else's server and don't want to go through the hassle of setting up and maintaining your own server.
If you have no interest in running your own server, you can skip to the last section of the chapter to see some options for setting up a hosted account and then move on to the next chapter, where we discuss the various ins and outs of working in a distributed source control environment.
A remote history is generally a bare repository-a Git repository that has no working directory. Because the repository is only used as a collaboration point, there is no reason to have a snapshot checked out on disk; it's just the Git data. In the simplest terms, a bare repository is the contents of your project's `.git` directory and nothing else.
#### The Protocols
Git can use four distinct protocols to transfer data: Local, HTTP, Secure Shell (SSH) and Git. Here we'll discuss what they are and in what basic circumstances you would want (or not want) to use them.
#### Local Protocol
The most basic is the _Local protocol_, in which the remote repository is in another directory on the same host. This is often used if everyone on your team has access to a shared filesystem such as an NFS mount, or in the less likely case that everyone logs in to the same computer. The latter wouldn't be ideal, because all your code repository instances would reside on the same computer, making a catastrophic loss much more likely.
If you have a shared mounted filesystem, then you can clone, push to, and pull from a local file-based repository. To clone a repository like this, or to add one as a remote to an existing project, use the path to the repository as the URL. For example, to clone a local repository, you can run something like this:

        $ git clone /srv/git/project.git
Or you can do this:

        $ git clone file:///srv/git/project.git
Git operates slightly differently if you explicitly specify `file://` at the beginning of the URL. If you just specify the path, Git tries to use hardlinks or directly copy the files it needs. If you specify `file://`, Git fires up the processes that it normally uses to transfer data over a network, which is generally much less efficient. The main reason to specify the `file://` prefix is if you want a clean copy of the repository with extraneous references or objects left out-generally after an import from another VCS or something similar (see Git Internals for maintenance tasks). We'll use the normal path here because doing so is almost always faster.
To add a local repository to an existing Git project, you can run something like this:

        $ git remtoe add local_proj /srv/git/project.git
Then, you can push to and pull from that remote via your new remote name `local_proj` as though you were doing so over a network.
##### The Pros
The pros of file-based repositories are that they're simple and they use existing file permissions and network access. If you already have a shared filesystem to which your whole team has access, setting up a repository is very easy. You stick the bare repository copy somewhere everyone has shared access to and set the read/write permissions as you would for any other shared directory. We'll discuss how to export a bare repository copy for this purpose in Getting Git on a Server.
This is also a nice option for quickly grabbing work from someone else's working repository. If you and a co-worker are working on the same project and they want you to check something out, running a command like `git pull /home/john/project` is often easier than them pushing to a remote server and you subsequently fetching from it.
##### The Cons
The cons of this method are that shared access is generally more difficult to set up and reach from multiple locations than basic network access. If you want to push from your laptop when you're at home, you have to mount the remote disk, which can be difficult and slow compared to network-based access.
It's important to mention that this isn't necessarily the fastest option if you're using a shared mount of some kind. A local repository is fast only you have fast access to the data. A repository on NFS is often slower than the repository over SSH on the same server, allowing Git to run off local disks on each system.
Finally, this protocol does not protect repository against accidental damage. Every user has full shell access to the "remote" directory, and there is nothing preventing them from changing or removing internal Git files and corrupting the repository.
#### The HTTP Protocols
Git can communicate over HTTP using two different modes. Prior to Git 1.6.6, there was only one way it could do this which was very simple and generally read-only. In version 1.6.6, a new, smarter protocol was introduced that involved Git being able to intelligently negotiate data transfer in a manner similar to how it does over SSH. In the last few years, this new HTTP protocol has become very popular since it's simple for the user and smarter about how it communicates. The newer version is often referred to as the _Smart_ HTTP protocol and the older way as _Dumb_ HTTP. We'll cover the newer Smart HTTP protocol first.
##### Smart HTTP
Smart HTTP operates very similarly to the SSH or Git protocols but runs over standard HTTPS ports and can use various HTTP authentication mechanisms, meaning it's often easier on the user than something like SSH, since you can use things like username/password authentication rather than having to set up SSH keys.
It has probably become the most popular way to use Git now, since it can be set up to both serve anonymously like the `git://` protocol, and can also be pushed over with authentication and encryption like the SSH protocol. Instead of having to set up different URLs for these things, you can now use a single URL for both. If you try to push and the repository requires authentication (which it normally should), the server can prompt for a username and password. The same goes for read access.
In fact, for services like GitHub, the URL you use to view the repository online (for example, https://github.com/schacon/simplegit) is the same URL you can use to clone and, if you have access, push over.
##### Dumb HTTP
If the sever does not respond with a Git HTTP smart service, the Git client will try to fall back to the simpler _Dumb_ HTTP protocol. The Dumb protocol expects the bare Git repository to be served like normal files from the web server. The beauty of Dumb HTTP is the simplicity of setting it up. Basically, all you have to do is put a bare Git repository under your HTTP document root and set up a specific `post-udpate` hook, and you're done ([See Git Hooks](#8.3-Git-Hooks)). At that point, anyone who can access the web server under which you put the repository can also clone your repository. To allow read access to your repository over HTTP, do something like this:

        $ cd /var/www/htdocs/
        $ git clone --bare /path/to/git_project gitproject.git
        $ cd gitproject.git
        $ mv hooks/post-update.sample hooks/post-update
        $ chmod a+x hooks/post-update
That's all. The `post-update` hook that comes with Git by default runs the appropriate command (`git update-server-info`) to make HTTP fetching and cloning work properly. This command is run when you push to this repository (over SSH perhaps); then, other people can clone via something like

        $ git clone https://example.com/gitproject.git
In this particular case, we're using the `/var/www/htdocs` path that is common for Apache setups, but you can use any static web server-just put the bare repository in its path. The Git data is served as basic static files (see the Git Internals chapter for details about exactly how it's served).
Generally you would either choose to run a read/write Smart HTTP server or simply have the files accessible as read-only in the Dumb manner. It's rare to run a mix of the two services.



## 8. Customizing Git
### 8.3 Git Hooks
#### Git Hooks
Like many other Version Control Systems, Git has a way to fire off custom scripts when certain important actions occur. There are two groups of these hooks: client-side and server-side. Client-side hooks are triggered by operations such as committing and merging, while server-side hooks run on network operations such as receiving pushed commits. You can use these hooks for all sorts of reasons.
#### Installing a Hook
The hooks are all stored in the `hooks` subdirectory of the Git directory. In most projects, that's `.git/hooks`. When you initialize a new repository with `git init`, Git populates the hooks directory with a bunch of example scripts, many of which are useful by themselves; but they also document the input values of each script. All the examples are written as shell scripts, with some Perl thrown in, but any properly named executable scripts will work fine-you can write them in Ruby or Python or whatever language you are familiar with. If you want to use the bundled hook scripts, you'll have to rename them; their file names all end with `.sample`.
#### Client-Side Hooks
There are a lot of client-side hooks. This section splits them into committing-workflow hooks, email-workflow hooks scripts, and everything else.
_Note:
It's important to note that client-side hooks are not copied when you clone a repository. If you intent with these scripts is to enforce a policy, you'll probably want to do that on the server side; see the example in An Example Git-Enforced Policy._
##### Committing-Workflow Hooks
The first four hooks have to do with the committing process.
The `pre-commit` hook is run first, before you even type in a commit message. It's used to inspect the snapshot that's about to be committed, to see if you've forgotten something, to make sure tests run, or to examine whatever you need to inspect in the code. Exiting non-zero from this hook aborts the commit, although you can bypass it with `git commit --no-verify`. You can do things like check for code style (run `lint` or something equivalent), check for trailing whitespace (the default hook does exactly this), or check for appropriate documentation on new methods.
The `prepare-commit-msg` hook is run before the commit message editor is fire up but after the default message is created. It lets you edit the default message before the commit author sees it. This hook takes a few parameters: the path to the file that holds the commit message so far, the type of commit, and the commit SHA-1 if this is an amended commit. This hook generally isn't useful for normal commits; rather, it's good for commits where the default message is auto-generated, such as templated commit messages, merge commits, squashed commits, and amended commits. You may use it in conjunction with a commit template to programmatically insert information.
The `commit-msg` hook takes one parameter, which again is the path to a temporary file that contains the commit message written by the developer. If this script exits non-zero, Git aborts the commit process, so you can use it to validate your project state or commit message before allowing a commit to go through. In the last section of this chapter, We'll demonstrate using this hook to check that your commit message is conformant to a required pattern.
After the entire commit process is completed, the `post-commit` hook runs. It doesn't take any parameters, but you can easily get the last commit by running `git log -1 HEAD`. Generally, this script is used for notification or something similar.
##### Email Workflow Hooks
You can set p three client-side hooks for an email-based workflow. They're all invoked by the `git am` command, so if you aren't using that command in your workflow, you can safely skip to the next section. If you're taking patches over email prepared by `git format-patch`, then some of these may be helpful to you.
The first hook that is run is `applypatch-msg`. It takes a single argument: the name of the temporary file that contains the proposed commit message. Git aborts the patch if this script exits non-zero. You can use this to make sure a commit message is properly formatted, or to normalize the message by having the script edit it in place.
The next hook to run when applying patches via `git am` is `pre-applypatch`. Somewhat confusingly, it is run _after_ the patch is applied but before a commit is made, so you can use it to inspect the snapshot before making the commit. You can run tests or otherwise inspect the working tree with this script. If something is missing or the tests don't pass, exiting non-zero aborts the `git am` script without committing the patch.
The last hook to run during a `git am` operation is `post-applypatch`, which runs after the commit is made. You can use it to notify a group or the author of the patch you pulled in that you've done so. You can't stop the patching process with this script.
##### Other Client Hooks
The `pre-rebase` hook runs before you rebase anything and can halt the process by exiting non-zero. You can use this hook to disallow any commits that have already been pushed. The example `pre-rebase` hook that Git installs does this, although it makes some assumptions that may not match with your workflow.
The `post-rewrite` hook is run by commands that replace commits, such as `git commit --amend` and `git rebase` (although not by `git filter-branch`). Its single argument is which command triggered the rewrite, and it receives a list of rewrites on `stin`. This hook has many of the same uses as the `post-checkout` and `post-mege` hooks.
After you run a successful `git checkout`, the `post-checkout` hook runs; you can sue it to set up your working directory properly for your project environment. This may mean moving in large binary files that you don't want source controlled, auto-generating documentation, or something along those lines.
The `post-merge` hook runs after a successful `merge` command. You can use it to restore data in the working tree that Git can't track, such as permissions data. This hook can likewise validate the presence of files external to Git control that you may want copied in when the working tree changes.
The `pre-push` hook runs during `git push`, after the remote refs have been updated but before any objects have been transferred. It receives the name and location of the remote as parameters, and a list of to-be-updated refs through `stdin`. You can use it to validate a set of ref updates before a push occurs (a non-zero exit code will abort the push).
Git occasionally does garbage collection as part of its normal operation, by invoking `git gc --auto`. The `pre-auto-gc` hook is invoked just before the garbage collection takes place, and can be used to notify you that this is happening, or to abort the collection if now isn't a good time.
#### Server-Side Hooks
In addition to the client-side hooks, you can use a couple of important server-side hooks as a system administrator to enforce nearly any kind of policy for your project. These scripts run before and after pushes to the server. The pre hooks can exit non-zero at any time to reject the push as well as print an error message back to the client; you can set up a push policy that's as complex as you wish.
##### pre-receive
The first script to run when handling a push from a client is `pre-receive`. It takes a list of references that are being pushed from `stdin`; if it exits non-zero, none of them are accepted. You can use this hook to do things like make sure none of the updated references are non-fast-forward, or to do access control for all the refs and files they're modifying with the push.
##### update
The `update` script is very similar to the `pre-receive` script, except that it's run once for each branch the pusher is trying to update. If the pusher is trying to push to multiple branches, `pre-receive` runs only once, whereas update runs once per branch they're pushing to. Instead of reading from stdin, this script takes three arguments: the name of the reference (branch), the SHA-1 that reference pointed to before the push, and the SHA-1 the user is trying to push. If the update script exits non-zero, only that reference is rejected; other references can still be updated.
##### post-receive
The `post-receive` hook runs after the entire process is completed and can be used to update other services or notify users. It takes the same stdin data as the `pre-receive` hook. Examples include emailing a list, notifying a continuous integration server, or updating a ticket-tracking system-you can even parse the commit messages to  see if any tickets need to be opened, modified, or closed. This script can't stop the push process, but the client doesn't disconnect until it has completed, so be careful if you try to do anything that may take a long time.
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
