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
Thus it's a bit confusing that Git has a `mv` command. If you want to rename a file in Git, you can run something like this:

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
### 2.3 Git Basics-Viewing the Commit History <a name=gitlog> </a>
#### Viewing the Commit History
After you have created several commits, or if you have cloned a repository with an existing commit history, you'll probably want to look back to see what has happened. The most basic and powerful tool to do this is the `git log` command.
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

##### How to read the diff output

    diff --git a/builtin-http-fetch.c b/http-fetch.c
    similarity index 95%
    rename from builtin-http-fetch.c
    rename to http-fetch.c
    index f3e63d7..e8f44ba 100644
    --- a/builtin-http-fetch.c
    +++ b/http-fetch.c
    @@ -1,8 +1,9 @@
     #include "cache.h"
     #include "walker.h"
    
    -int cmd_http_fetch(int argc, const char **argv, const char *prefix)
    +int main(int argc, const char **argv)
     {
    +       const char *prefix;
            struct walker *walker;
            int commits_on_stdin = 0;
            int commits;
    @@ -18,6 +19,8 @@ int cmd_http_fetch(int argc, const char **argv, const char *prefix)
            int get_verbosely = 0;
            int get_recover = 0;
    
    +       prefix = setup_git_directory();
    +
            git_config(git_default_config, NULL);
    
            while (arg < argc && argv[arg][0] == '-') {
* The first line `diff --git a/builtin-http-fetch.c b/http-fetch.c` is a "git diff" header. The `a/` and `/b` filenames are the same unless rename/copy is involved.
* Next are one or more extended header lines. The first three

        similarity index 95%
        rename from builtin-http-fetch.c
        rename to http-fetch.c
    tell us that the file was renamed from `builtin-http-fetch.c` to `http-fetch.c` and that those two files are 95% identical (which was used to detect this rename).
    The last line in extended diff header, which is `index f3e63d7..e8f44ba 100644` tells us about the mode of the given file (`100644` means that it is ordinary file and not e.g. symlink, and that it doesn't have executable permission it).
* Next is two-line unified diff header

    ---a/builtin-http-fetch.c
    +++b/http-fetch.c
* Next come one or more hunks of differences; each hunk shows one area where the files differ. Unified format hunks starts with line like `@@ -1,8 +1,9 @@` or `@@ -18,6 +19,8 @@ int cmd_http_fetch(int argc, const char **argv, ...` It is in the format `@@ from-file-range to-file-range @@`. The `from-file-range` is in the form `-<start line>,<number of lines>`, and `to-file-range` is `+<start line>,<number of lines>`. If number-of-lines not shown it means that it is 0.
    * `-1,6` means that this piece of the first file starts at line 1 and shows a total of 6 lines. Therefore it shows lines 1 to 6. `-` means "old".
    * `+1,4` means that this piece of the second file starts at line 1 and shows a total of 4 lines. Therefore it shows lines 1 to 4. `+` means "new".
    The optional header shows that C function where each change occurs, if it is a C file (like `-p` option in GUN diff), or the equivalent, if any, for other types of files. Depending on your git version and configuration, you can also get a code line next to the `@@` line, e.g. the `func1() {` in `@@ -4,7 +4,6 @@ func1() {`. This an also be obtained with the `-p` flag of plain diff. This awesome feature often tells exactly to which function or class each hunk belongs, which is very useful to interpret the diff.
* Next comes the description of where files differ. The lines common to both files begin with a space character. The lines that actually differ between the two files have one of the following indicator characters in the left print column:
    * `+`: A line was added here to the first file.
    * `-`: A line was removed here from the first file.

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
Those are only some simple output-formatting options to `git log`-there are many more. Common options to `git log` lists the options we've covered so far, as well as some other common formatting options that may be useful, along with how they change the output of the long command.
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
_Note: You can specify more than one instance of both the --author and --grep search criteria, which will limit the commit output to commits that match any of the --author patterns and any of the --grep patterns; however, adding the --all-match option further limits the output to just those commits that match all --grep patters._
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
To be able to collaborate on any Git project, you need to know how to manage your remote repositories. Remote repositories are versions of your project that are hosted on the Internet or network somewhere. You can have several of them, each of which generally is either read-only or read/write for you. Collaborating with others involves managing these remote repositories and pushing and pulling data to and from them when you need to share work. Managing remote repositories includes knowing how to add remote repositories, remove remotes that are no longer valid, manage various remote branches and define them as being tracked or not, and more. In this section, we'll cover some of these remote-management skills.
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
This means that we can pull contributions from any of these users pretty easily. We may additionally have permission to push to one or more of these, though we can't tell that here.
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
It lists the URL for the remote repository as well as the tracking branch information. The command helpfully tells you that if you're on the master branch and you run `git pull`, it will automatically merge in the master branch on the remote after it fetches all the remote references. It also lists all the remote references it has pulled down.
That is a simple example you're likely to encounter. When you're using Git more heavily, however, you may see more information from `git remote show`:
        
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
##### man git-push
###### NAME
git-push: Update remote refs along with associated objects
###### SYNOPSIS
`git push [-all | --mirror | --tags] [--follow-tags] [-n | --dry-run] [--repo=<repository>] [-f | --force] [-d | --delete] [--prune] [-v | --verbose] [-u | --set-upstream] [--[no]-signed|--sign=(true|false|if-asked)] [--no-verify] [<repository> [<refspec>...]]`
###### Description
Updates remote refs using local refs, while sending objects necessary to complete the given refs.
You can make interesting things happen to a repository every time you push into it, by setting up *hooks* there. See documentation for `git-receive-pack`.
When the command line does not specify where to push with the `<repository>` argument, `branch.*.remote` configuration for the current branch is consulted to determine where to push. If the configuration is missing, it defaults to `origin`.
![configuration_variables](configuration_variables.png)
When the command line does not specify what to push with `<refspec>...` arguments or `--all`, `--mirror`, `--tags` options, the command finds the default `<refspec>` by consulting `remote.*.push` configuration, and if it is not found, honors `push.default` configuration to decide what to push (See git-config for the meaning of `push.default`)
When neither the command-line nor the configuration specify what to push, the default behavior is used, which corresponds to the `simple` value for `push.default`: the current branch is pushed to the corresponding upstream branch, but as a safety measure, the push is aborted if the upstream branch does not have the same name as the local one.
###### `push.default`
Defines the action `git push` should take if no refspec is explicitly given. Different values are well-suited for specific workflows; for instance, in a purely central workflow (i.e. the fetch source is equal to the push destination), `upstream` probably what you want. Possible values are: 
* `nothing`
do not push anything (error out) unless a refspec is explicitly given. This is primarily meant for people who want to avoid mistakes by always being explicit.
* `current`
push the current branch to update a branch with the same name on the receiving end. Works in both central and non-central workflows.
* `upstream`
push the current branch back to the branch whose changes usually integrated into the current branch (which is called `@{upstream}`). This mode only makes sense if you are pushing to the same repository you would normally pull from (i.e. central workflow)
* `tracking`
This is a deprecated synonym for `upstream`.
* `simple`
in centralized workflow, work like `upstream` with an added safety to refuse to push if the upstream branch's name is different from the local one.
When pushing to a remote that is different from the remote you normally pull from, work as `current`. This is the safest option and is suited for beginners.
This mode has become the default in Git 2.0.
* `matching`
push all branches having the same name on both ends. This makes the repository you are pushing to remember the set of branches that will be pushed out (e.g. if you always push *maint* and *master* there and no other branches, the repository you push to will have these two branches, and your local *maint* and *master* will be pushed there).
To use this mode effectively, you have to make sure *all* the branches you would push out are ready to be pushed out before running `git push`, as the whole point of this mode is to allow you to push all of the branches in one go. If you usually finish work on only one branch and push out the result, while other branches are unfinished, this mode is not for you. Also this mode is no suitable for pushing into a shared central repository, as other people may add new branches there, or update the tip of existing branches outside your control.
This used to be the default, but not since Git 2.0 (`simple` is the new default).
###### OPTIONS
####### `<repository>`
The "remote" repository that is destination of a push operation. This parameter can be either a URL (see the section [GIT URLS](GIT_URLS)) or the name of a remote (see the section [REMOTES](#REMOTES))
####### `<refspec>...`
Specify what destination ref to update with what source object. The format of a `<refspec>` parameter is an optional plus `+`, followed by the source object `<src>`, followed by a colon `:`, followed by the destination ref `<dst>`.
The `<src>` if often the name of the branch you would want to push, but it can be any arbitrary "SHA-1 expression", such as `master~4` or `HEAD` (see [gitrevisions]).

#### Tracking Branches <a name=TrackingBranches> </a>
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
#### Fetching
##### NAME
git-fetch - Download objects and refs from another repository.
##### Synopsis

    git fetch [<options>] [<repository> [<refspec>...]]
    git fetch [<options>] <group>
    git fetch --multiple [<options>] [(<repository> | <group>)...]
    git fetch --all [<options>]
##### Description
**Fetch branches and/or tags (collectively, "refs") from one or more other repositories, along with the objects necessary to complete their histories. Remote-tracking branches are updated** (see description of <refspec> below for ways to control this behavior).
By default, any tag that points into the histories being fetched is also fetched; the effect is to fetch tags that point at branches that you are interested in. The default behavior can be changed by using the `--tags` or `--no-tags` options or by configuring `remote.<name>.tagOpt`. By using a refspec that fetches tags explicitly, you can fetch tags that do not point into branches you are interested in as well.
`git fetch` can fetch from either a single repository or URL, or from several repositories at once if `<group>` is given and there is `remotes.<group>` entry in the configuration file. (See `git-config`)
**When no remote is specified, by default the `origin` remote will be used, unless there's an upstream branch configured for the current branch.**
The names of refs that are fetched, together with the object names they point at, are written to `.git/FETCH_HEAD`. This information may be used by scripts or other git commands, such as `git-pull`.
##### Options
* `--all`
Fetch all remotes.
* `-a`, `--append`
Append ref names and object names of fetched refs to the existing contents of `.git/FETCG_HEAD`. Without this option old data in `.git/FETCH_HEAD` will be overwritten.
* `--dry-run`
Show what would be done, without making any changes.
* `-f`, `--force`
When `git fetch` is used with `<rbranch>:<lbranch>` refspec, it refuses to update the local branch `<lbranch>` unless the remote branch `<rbranch>` it fetches is a descendant of `<lbranch>`. This option overrides that check.
* `--multiple`
Allow several `<repository>` and `<group>` arguments to be specified. No `<refspec>`s may be specified.
* `-p`, `--prune`
After fetching, remove any remote-tracking references that no long exist on the remote. Tags are not subject to pruning if they are fetched only because of the default tag auto-following or due to a `--tags` option. However, if the tags are fetched due to an explicit refspec (either on the command line or in the remote configuration, for example if the remote was cloned with the `--mirror` option), then they are also subject to pruning.
* `-n`, `--no-tags`
By default, tags that point at objects that are downloaded from the remote repository are fetched and stored locally. This option disables this automatic tag following. The default behavior for a remote may be specified with the `remote.<name>tagOpt` setting. See `git-config`.
* `-t`, `--tags`
Fetch all tags from the remote (i.e., fetch remote tags `refs/tags/*` into local tags with the same name), in addition to whatever else would otherwise be fetched. Using this option alone does not subject tags to pruning, even if `--prune` is used (though tags may be pruned anyway if they are also the destination of an explicit refspec; see `--prune`).
* `-v`, `--verbose`
Be verbose.
* `<repository>`
The "remote" repository that is the source of a fetch or pull operation. This parameter can be either a URL (see the section *GIT URLS* below) or the name of a remote (see the section *REMOTES* below).
* `<group>`
A name referring to a list of repositories as the value of `remotes.<group>` in the configuration file. (See `git-config`)
* `<refspec>`
Specifies which refs to fetch and which local refs to update. **When no <refspec>s appear on the command line, the refs to fetch are read from `remote.<repository>.fetch` variables instead** (See CONFIGURED REMOTE-TRACKING BRANCHES below).
The format of a `<refspec>` is an optional plus `+`, followed by the source ref `<src>`, followed by a colon `:`, followed by the destination ref `<dst>`. The colon can be omitted when `<dst>` is empty.
`tag <tag>` means the same as `refs/tags/<tag>:refs/tags/<tag>`; it requests fetching everything up to the given tag.
**The remote ref that matches `<src>` if fetched, and if `<dst>` is not empty string, the local ref that matches it is fast-forwarded using `<src>`. If the optional plus `+` is used, the local ref is updated even if it does not result in a fast-forward update.**
Note: When the remote branch you want to fetch is known to be rewound and rebased regularly, it is expected that its new tip will not be descendant of its previous tip (as stored in your remote-tracking branch the last time you fetched). You would want to use the `+` sign to indicate non-fast-forward updates will be needed for such branches. ???There is no way to determine or declare that a branch will be made available in a repository with this behavior; the pulling user simply must know this is the expected usage pattern for a branch.???
##### GIT URLS <a name=GIT_URLS> </a>
In general, URLs contain information about **the transport protocol, the address of the remote server, and the path o the repository.** Depending on the transport protocol, some of this information many be absent.
Git support ssh, git, http, and https protocols (in addition, ftp, and ftps can be used for fetching, but this is inefficient and deprecated; do not use it).
The native transport (i.e. git:// URL) does no authentication and should be used with caution on unsecured networks.
The following syntaxes may be used with them:
* `ssh://[user@]host.xz[:port]/path/to/repo.git/`
* `git://host.xz[:port]/path/to/repo.git/`
* `http[s]://host.xz[:port]/path/to/repo.git/`
* `ftp[s]://host.xz[:port]/path/to/repo.git/`
An alternative scp-like syntax may also be used with the ssh protocol:
* `[user@]host.xz:path/to/repo.git/`
This syntax is only recognized if there are no slashes before the first colon. This helps differentiate a local path that contains a colon. For example the local path `foo:bar` could be specified as an absolute path or `./foo:bar` to avoid being misinterpreted as an ssh url.
The ssh and git protocols additionally support `~` username expansion:
* `ssh://[user@]host.xz[:port]/~[user]/path/to/repo.git/`
* `git://host.xz[:port]/~[user]/path/to/repo.git/`
* `[user@]host.xz:/~[user]/path/to/repo.git/`
For local repositories, also supported by Git natively, the following syntaxes may be used:
* `path/to/repo.git/`
* `file:///path/to/repo.git/`
These two syntaxes are mostly equivalent, except when cloning, when the former implies `--local` option. See `git-clone` for details.
If there are a large number of similar-named remote repositories and you want to use a different format for them (such that the URLs you use will be rewritten into URLs that work), you can create a configuration section of the form:

    [url "<acutual url base>"
            insteadof = <other url base>
For example, with this:

    [url "git://git.host.xz/"]
            insteadof = hsot.xz:/path/to/
            insteadof = work:
a URL like `work:repo.git` or like `host.xz:/path/to/repo.git` will be rewritten in any context that takes a URL to be `git://git.host.xz/repo.git`.
If you want to rewrite URLs for push only, you can create a configuration section of the form:

    [url "<actual url base>"]
            pushInsteadof = <other url base>
For example, with this:

    [url "ssh://example.org/"]
            pushInsteadof = git://example.org/
a URL like `git://example.org/path/to/repo.git` will be rewritten to `ssh://example.org/path/to/repo.git` for pushes, but pulls will still use the original URL.

##### REMOTES <a name=REMOTES> </a>
The name of one of the following can e used instead of a URL as `<repository>` argument:
* a remote in the Git configuration file: `$GIT_DIR/config`,
* a file in the `$GIT_DIR/remotes` directory, or
* a file in the `$GIT_DIR/branches` directory.
All of these also allow you to omit the refspec from the command line because they each contain a refspec which git will use by default.

###### Named remote in configuration file
You can choose to provide the name of a remote which you had previously configured using `git-remote`, `git-config` or even by a manual edit to the `$GIT_DIR/config` file. The URL of this remote will be used to access the repository. The refspec of this remote will be used by default when you do not provide a refspec on the command line. The entry in the `config` file would appear like this:

    [remote "<name>"]
            url = <url>
            pushurl = <pushurl>
            push = <refspec>
            fetch = <refspec>
The `<pushurl>` is used for pushes only. It is optional and defaults to `<url>`.

###### Named file in `$GIT_DIR/remotes`
You can choose to provide the name of a file in `GIT_DIR/remotes`. The URL in this file will be used to access the repository. The refspec in this file will be used as default when you do not provide a refspec on the command line. This file should have the following format:

    URL: one of the above URL format
    Push: <refspec>
    Pull: <refspec>
`Push:` lines are used by `git push` and `Pull:` lines are used by `git pull` and `git fetch`. Multiple `Push:` and `Pull` lines may be specified for additional branch mappings.

###### Named file in `$GIT_DIR/branches`
You can choose to provide the name of a file in `$GIT_DIR/branches`. The URL in this file will be used to access the repository. This file should have the following format:
    `<url>#<head>`
`<url>` is required; `#<head>` is optional.
Depending on the operation, git will use one of the following refspecs, if you don't provide one on the command line. `<branch>` is the name of this file in `$GIT_DIR/branches` and `<head>` defaults to `master`.
git fetch uses:
    `refs/heads/<head>:refs/heads/<branch>` ??? <a name=head_vs_branch></a>
git push uses:
    `HEAD:refs/heads/<head>`

##### CONFIGURED REMOTE-TRACKING BRANCHES
You often interact with the same remote repository by regularly and repeatedly fetching from it. In order to keep track of the progress of such a remote repository, `git fetch` allows you to configure `remote.<repository>.fetch` configuration variables.
Typically such a variable may look like this:

    [remote "origin"]
            fetch = +refs/heads/*:refs/remotes/origin/*
![configuration_variables](configuration_variables.png)
This configuration is used in two ways:
* When `git fetch` is run without specifying what branches and/or tags to fetch on the command line, e.g. `git fetch origin` or `git fetch`, `remote.<repository>.fetch` values are used as the refspecs-they specify which refs to fetch and which local refs to update. The example above will fetch all branches that exist in the `origin` (i.e., any ref that matches the left-hand side of the value, `refs/head/*`) and update the corresponding remote-tracking branches in the `refs/remotes/origin/*` hierarchy.
* When `git fetch` is run with explicit branches and/or tags to fetch on the command line, e.g. `git fetch origin master`, the <refspec>s given on the command line to determine what are to be fetched (e.g. `master` in the example, which is a short-hand for `master:`, which in turn means "fetch the `master` branch but I do not explicitly say what remote-tracking branch to update with it from the command line"), and the example command will fetch only the `master` branch. The `remote.<repository>.fetch` values determine which remote-tracking branch, if any, is updated. When used in this way, the `remote.<repository>.fetch` values do not have any effect in deciding what gets fetched (i.e. the values are not used as refspecs when the command-line lists refspecs); they are only used to decide where the refs that are fetched are stored by acting as a mapping.
The latter use of the `remote.<repository>.fetch` values can be overridden by giving the `--refmap=<refspec>` parameter(s) on the command line.
##### EXAMPLES
* Update the remote-tracking branches
`git fetch origin`
The above command copies all branches from the remote `refs/heads/` namespace and stores them to the local `refs/remotes/origin/` namespace, unless the `branch.<name>.fetch` option is used to specify a non-default refspec.
* Using refspecs explicitly:
`git fetch origin +pu:pu maint:tmp`
This updates (or creates, as necessary) branches `pu` and `tmp` in the local repository by fetching from the branches (respectively) `pu` and `maint` from the remote repository.
The `pu` branch will be updated even if it is not fast-forward, because it is prefixed with a plug sign; `tmp` will not be.
* Peek at a remote's branch, without configuring the remote in your local repository:
`$ git fetch git://git.kernel.org/pub/scm/git/git.git maint`
` git log FETCH_HEAD`
The first command fetches the `maint` branch from the repository at `git://git/kernel.org/pub/scm/git/git.git` and the second command uses `FETCH_HEAD` to examine the branch with `git-log`. The fetched objects will eventually be remove by git's built-in housekeeping (see `git-gc`).

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
If the server does not respond with a Git HTTP smart service, the Git client will try to fall back to the simpler _Dumb_ HTTP protocol. The Dumb protocol expects the bare Git repository to be served like normal files from the web server. The beauty of Dumb HTTP is the simplicity of setting it up. Basically, all you have to do is put a bare Git repository under your HTTP document root and set up a specific `post-udpate` hook, and you're done ([See Git Hooks](#Git_Hooks)). At that point, anyone who can access the web server under which you put the repository can also clone your repository. To allow read access to your repository over HTTP, do something like this:

        $ cd /var/www/htdocs/
        $ git clone --bare /path/to/git_project gitproject.git
        $ cd gitproject.git
        $ mv hooks/post-update.sample hooks/post-update
        $ chmod a+x hooks/post-update
That's all. The `post-update` hook that comes with Git by default runs the appropriate command (`git update-server-info`) to make HTTP fetching and cloning work properly. This command is run when you push to this repository (over SSH perhaps); then, other people can clone via something like

        $ git clone https://example.com/gitproject.git
In this particular case, we're using the `/var/www/htdocs` path that is common for Apache setups, but you can use any static web server-just put the bare repository in its path. The Git data is served as basic static files (see the Git Internals chapter for details about exactly how it's served).
Generally you would either choose to run a read/write Smart HTTP server or simply have the files accessible as read-only in the Dumb manner. It's rare to run a mix of the two services.
##### The Pros
We'll concentrate on the pros of the Smart version of the HTTP protocol.
The simplicity of having a single URL for all types of access and have the server prompt only when authentication is needed makes things very easy for the end user. Being able to authenticate with a username and password is also a big advantage over SSH, since users don't have to generate SSH keys locally and upload their public key to the server before being able to interact with it. For less sophisticated users, or users on systems where SSH is less common, this is a major advantage in usability. It is also a very fast and efficient protocol, similar to the SSH one.
You can also serve you repositories read-only over HTTPS, which means you can encrypt the content transfer; or you can go so far as to make the clients use specific signed SSL certificates.
Another nice thing is that HTTPS are such commonly used protocols that corporate firewalls are often set up to allow traffic through these ports.
##### The Cons
Git over HTTPS can be a little more tricky to set up compared to SSH on some servers. Other than that, there is very little advantage that other protocols have over Smart HTTP for serving Git content.
If you're using HTTP for authentication pushing, providing your credentials is sometimes more complicated than using keys over SSH. There are, however, several credential caching tools you can use, including Keychain access on macOS and Credential Manager on Windows, to make this pretty painless. Read [Credential Storage](https://git-scm.com/book/en/v2/ch00/_credential_caching) to see how to set up secure HTTP password caching on your system.
#### The SSH Protocol
A common transport protocol for Git when self-hosting is over SSH. This is because SSH access to servers is already set up in most places-and if it isn't, it's easy to do. SSH is also an authenticated network protocol and, because it's ubiquitous, it's generally easy to set up and use.
To clone a Git repository over SSH, you can specify an `ssh://` URL like this:

        $ git clone ssh://[user@]server/project.git
Or you can use the shorter scp-like syntax for the SSH protocol:

        $ git clone [user@]server:project.git
In both cases above, if you don't specify the optional username, Git assumes the user you're currently logged in as.
##### The Pros
The pros of using SSH are many. First, SSH is relatively easy to set up-SSH daemons are commonplace, many network admins have experience with them, and many OS distributions are set up with them or have tools to manage them. Next, access over SSH is secure-all data transfer is encrypted and authenticated. Last, like the HTTPS, Git and Local protocols, SSH is efficient, making the data as compact as possible before transferring it.
##### The Cons
The negative aspect of SSH is that it doesn't support anonymous access to your Git repository. If you're using SSH, people _must_ have SSH access to your machine, even in a read-only capacity, which doesn't make SSH conducive to open source projects for which people might simply want to clone your repository to examine it. If you're using it only within your corporate network, SSH many be the only protocol you need to deal with. If you want to allow anonymous read-only access to your projects and also want to use SSH, you'll have to set up SSH for you to push over but something else for others to fetch from.
### The Git Protocol
Next is the Git protocol. This is a special daemon that comes packaged with Git; it listens on a dedicated port (9418) that provides a service similar to the SSH protocol, but with absolutely no authentication. In order for a repository to be served over the Git protocol, you must create a `git-daemon-export-ok` file-the daemon won't serve a repository without that file in it-but other than that there is no security. Either the Git repository is available for everyone to clone, or it isn't. This means that there is generally no pushing over this protocol. You can enable push access but, given the lack of authentication, anyone on the internet who finds your project's URL could push to that project. Suffice it to say that this is rare.
##### The Pros
The Git protocol is often the fastest network transfer protocol available. If you're serving a lot of traffic for a public project or serving a very large project that doesn't require user authentication for read access, it's likely that you'll want to set up a Git daemon to serve your project. It uses the same data-transfer mechanism as the SSH protocol but without the encryption and authentication overhead.
##### The Cons
The downside of the Git protocol is the lack of authentication. It's generally undesirable for the Git protocol to be the only access to your project. Generally, you'll pair it with SSH or HTTPS access for the few developers who have push (write) access and have everyone else use `git://` for read-only access. It's also probably the most difficult protocol to set up. It must run its own daemon, which requires `Xinetd` configuration or the like, which isn't always a walk in the park. It also requires firewall access to port 9418, which isn't a standard port that corporate firewalls always allow. Behind big corporate firewalls, this obscure port is commonly blocked.
### 4.2 Git on the server-Getting Git on a Server
#### Getting Git on a Server
Now we'll cover setting up a Git service running these protocols on your own server.
_Note: Here we'll be demonstrating the commands and steps needed to do basic, simplified installations on a Linux-based server, though it's also possible to run these services on Mac or Windows servers. Actually setting up a production server within your infrastructure will certainly entail differences in security measures or operating system tools, but hopefully this will give you the general idea of what's involved._
In order to initially set up any Git server, you have to export an existing repository into a new bare repository-a repository that doesn't contain a working directory. This is generally straightforward to so. In order to clone your repository to create a new bare repository, you run the clone command with the `--bare` option. By convention, bare repository directory names end with the suffix `.git`, like so:

        $ git clone --bare my_project my_project.git
        Cloning into bare repository 'my_project.git'...
        done.
You should now have a copy of the Git directory data in your `my_project.git` directory.
This is roughly equivalent to something like

        $ cp -Rf my_project/.git my_project.git
There are a couple of minor differences in the configuration file but, for your purpose, this is close to the same thing. It takes the Git repository by itself, without a working directory, and creates a directory specially for it alone.
#### Putting the Bare Repository on a Server
Now that you have a bare copy of your repository, all you need to do is put it on a server and set up your protocols. Let's say you've set up a server called `git.example.com` to which you have SSH access, and you want to store all your Git repositories under the `/srv/git` directory. Assuming that `/srv/git` exits on that server, you can set up your new repository by copying your bare repository over:

        $ scp -r my_project.git user@git.example.com:/srv/git
_Note: `scp` copies files between hosts on a network. It uses ssh for data transfer, and uses the same authentication and provides the same security as ssh. `scp` will ask for passwords or passphrases if they are needed for authentication._
At this point, other users who have SSH-based read access to the `/srv/git` directory on that server can clone your repository by running

        $ git clone user@git.example.com:/srv/git/my_project.git
If a user SSHs into a server and has write access to the `/srv/git/my_project.git` directory, they will also automatically have push access.
Git will automatically add group write permissions to a repository properly if you run the `git init` command with the `--shared` option.

        $ ssh user@git.example.com
        $ cd /srv/git/my_project.git
        $ git init --bare --shared
You see how easy it is to take a Git repository, create a bare version, and place it on a server to which you and your collaborators have SSH access. Now you're ready to collaborate on the same project.
It's important to note that this is literally all you need to do to run a useful Git server to which several people have access-just add SSH-able accounts on a server, and stick a bare repository somewhere that all those users have read and write access to. You're ready to go-nothing else needed.
In the next few sections, you'll see how to expand to more sophisticated setups. This discussion will include not having to create user accounts for each user, adding public read access to repositories, setting up web UIs and more. However, keep in mind that to collaborate with a couple of people on a private project, all you need is an SSH server and a bare repository.
#### Small Setups
If you're a small outfit or are just trying out Git in your organization and have only a few developers, things can be simple for you. One of the most complicated aspects of setting up a Git server is user management. If you want some repositories to be read-only for certain users and read/write for others, access and permissions can be a bit more difficult to arrange.
#### SSH Access
If you have a server to which all your developers already have SSH access, it's generally easiest to set up your first repository there, because you have to do almost no work (as we covered in the last section). If you want more complex access control type permissions on your repositories, you can handle them with the normal filesystem permissions of you server's operating system.
If you want to place your repositories on a server that doesn't have accounts for everyone on your team for whom you want to grant write access, then you must set up SSH access for them. We assume that if you have a server with which to do this, you already have an SSH server installed, and that's how you're accessing the server.
There are a few ways you can give access to everyone on your team. The first is to set up accounts for everybody, which is straightforward but can be cumbersome. You may not want to run `adduser` and set temporary passwords for every user.
A second method is to create a single _git_ user account on the machine, ask every user who is to have write access to send you an SSH public key, and add that key to the `~/.ssh/authorized_keys` file of that new account. At that point, everyone will be able to access that machine via the _git_ account. This doesn't affect the commit data in any way-the SSH user you connect as doesn't affect the commits you've recorded.
Another way to do it is to have your SSH server authenticate from an LDAP sever or some other centralized authentication source that you may already have set up. As long as each user can get shell access on the machine, any SSH authentication mechanism you can think of should work.
### 4.3 Git on the Server-Generating Your SSH Public Key
#### Generating Your SSH Public Key
Many Git servers authenticate using SSH public keys. In order to provide a public key, each user in your system must generate one if they don't already have one. This process is similar across all operating systems. First, you should check to make sure you don't already have a key. By default, a user's SSH keys are stored in that user's `~/.ssh` directory. You can easily check to see if you have a key already by going to that directory and listing the contents:

        $ cd ~/.ssh
        $ ls
        authorized_keys2    id_dsa      known_hosts
        config              id_dsa.pub
You're looking for a pair of files named something like `id_dsa` or `id_rsa` and a matching file with a `.pub` extension. The `.pub` file is your public key, and the other is your private key. If you don't have these files (or you don't even have a `.ssh` directory), you can create them by running a program called `ssh-keygen`, which is provided with the SSH package on Linux/Mac systems and comes with Git for Windows:

        $ ssh-keygen
        Generating public/private rsa key pair.
        Enter file in which to save the key (/home/schacon/.ssh/id_rsa):
        Created directory '/home/schacon/.ssh'.
        Enter passphrase (empty for no passphrase):
        Enter same passphrase again:
        Your identification has been saved in /home/schacon/.ssh/id_rsa.
        Your public key has been saved in /home/schacon/.ssh/id_rsa.pub.
        The key fingerprint is:
        d0:82:24:8e:d7:f1:bb:9b:33:53:96:93:49:da:9b:e3 schacon@mylaptop.local
First it confirms where you want to save the key (`.ssh/id_rsa`), and then it asks twice for a passphrase, which you can leave empty if you don't want to type a password when you use the key.
Now, each user that does this has to send their public key to you or whoever is administrating the Git server (assuming you're using an SSH server setup that requires public keys). All they have to do is copy the contents of the `.pub` file and email it. The public keys look something like this:

        $ cat ~/.ssh/id_rsa.pub
        ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAklOUpkDHrfHY17SbrmTIpNLTGK9Tjom/BWDSU
        GPl+nafzlHDTYW7hdI4yZ5ew18JH4JW9jbhUFrviQzM7xlELEVf4h9lFX5QVkbPppSwg0cda3
        Pbv7kOdJ/MTyBlWXFCR+HAo3FXRitBqxiX1nKhXpHAZsMciLq8V6RjsNAQwdsdMFvSlVK/7XA
        t3FaoJoAsncM1Q9x5+3V0Ww68/eIFmb1zuUFljQJKprrX88XypNDvjYNby6vw/Pb0rwert/En
        mZ+AW4OZPnTPI89ZPmVMLuayrD2cE86Z/il8b+gw3r3+1nKatmIkjn2so1d01QraTlMqVSsbx
        NrRFi9wrf+M7Q== schacon@mylaptop.local
### 4.4 Git on the Server-Setting up the Server
#### Setting Up the Server
Let's walk through setting up SSH access on the server side. In this example, you'll use the `autorized_keys` method for authenticating your users. We also assume you're running a standard Linux distribution like Ubuntu.
_Note: A good deal of what is described where can be automated by using the `ssh-copy-id' command, rather than manually copying and installing public keys._
First, you create a `git` user and a `.ssh` directory for that user.

        $ sudo adduser git
        $ su git
        $ cd
        $ mkdir .ssh && chmod 700 .ssh
        $ touch .ssh/authorized_keys && chmod 600 .ssh/authorized_keys
Next, you need to add some developer SSH public keys to the `authorized_keys` file for the `git` user. Let's assume you have some trusted public keys and have saved them to temporary files. Again, the public keys look something like this:

        $ cat /tmp/id_rsa.john.pub
        ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCB007n/ww+ouN4gSLKssMxXnBOvf9LGt4L
        ojG6rs6hPB09j9R/T17/x4lhJA0F3FR1rP6kYBRsWj2aThGw6HXLm9/5zytK6Ztg3RPKK+4k
        Yjh6541NYsnEAZuXz0jTTyAUfrtU3Z5E003C4oxOj6H0rfIF1kKI9MAQLMdpGW1GYEIgS9Ez
        Sdfd8AcCIicTDWbqLAcU4UpkaX8KyGlLwsNuuGztobF8m72ALC/nLF6JLtPofwFBlgc+myiv
        O7TCUSBdLQlgMVOFq1I2uPWQOkOWQAHukEOmfjy2jctxSDBQ220ymjaNsHT4kgtZg2AYYgPq
        dAv8JggJICUvax2T9va5 gsg-keypair
You just append them to the `git` user's `authorized_keys` file in its `.ssh` directory:

        $ cat /tmp/id_rsa.john.pub >> ~/.ssh/authorized_keys
        $ cat /tmp/id_rsa.josie.pub >> ~/.ssh/authorized_keys
        $ cat /tmp/id_rsa.jessica.pub >> ~/.ssh/authorized_keys
Now, you can set up an empty repository for them by running `git init` with the `--bare` option, which initializes the repository without a working directory:

        $ cd /srv/git
        $ mkdir project.git
        $ cd project.git
        $ git init --bare
        Initialized empty Git repostiroy in /srv/git/project.git/
Then, John, Josie, or Jessica can push the first version of their project into that repository by adding it as a remote and pushing up a branch. Note that someone must shell onto the machine and create a bare repository every time you want to add a project. Let's use `gitserver` as the hostname of the server on which you've set up your `git` user and repository. If you're running it internally, and you set up DNS for `gitserver` to point to that server, then you can use the commands pretty much as is (assuming that `myproject` is an existing project with files in it):

        # On John's computer
        $ cd myproject
        $ git init
        $ git add .
        $ git commit -m 'initial commit'
        $ git remtoe add origin git@gitserver:/srv/git/project.git
        $ git push origin master
At this point, the others can clone it down and push changes back up just as easily:

        $ git clone git@gitserver:/srv/git/project.git
        $ cd project
        $ vim README
        $ git commit -am 'fix for the README file'
        $ git push origin master
With this method, you can quickly get a read/write Git server up and running for a handful of developers.
You should note that currently all these users can also log into the server and get a shell as the `git` user. If you want to restrict that, you will have to change the shell to something else in the `passwd` file.
You can easily restrict the `git` user to only doing Git activities with a limited shell toll called `git-shell` that comes with Git. If you set this as your `git` user's login shell, then the `git` user can't have normal shell access to your server. To use this, specify `git-shell` instead of bash or csh for your user's login shell. To do so, you must first add `git-shell` to `/etc/shells` if it's not already there:

        $ cat /etc/shells # see if `igt-shell` is already in there. If not...
        $ which git-shell # make sure git-shell is installed on your system
        $ sudo vim /etc/shells # and add the path to git-shell from last command
Now you can edit the shell for a user using `chsh <username> -S <shell>`:

        $ sudo chsh git -S $(which git-shell)
Now, the `git` user can only use the SSH connection to push and pull Git repositories and can't shell onto the machine. If you try, you'll see a login rejection like this:

        $ ssh git@gitserver
        fatal: Interactive git shell is not enabled.
        hint: ~/git-shell-commands should exist and have read and execute access.
        Connection to gitserver closed.
Now Git network commands will still work just fine but the users won't be able to get a shell. As the output states, you can also set up a directory in the `git` user's home directory that customizes the `git-shell` command a bit. For instance, you an restrict the Git commands that the server will accept or you can customize the message that users see if they try to SSH in like that. Run `git help shell` for more information on customizing the shell.
### 4.5 Git on the Server-Git Daemon
#### Git Daemon
Next we'll set up a daemon serving repositories using the "Git" protocol. This is a common choice for fast, unauthenticated access to your Git data. Remember that since this is not an authenticated service, anything you serve over this protocol is public within its network.
If you're running on server outside your firewall, it should be used only for projects that are publicly visible to the world. If the server you're running it on is inside your firewall, you might use it for projects that a large number of people or computers (continuous integration or build servers) have read-only access to, when you don't want to add an SSH key for each.
In any case, the Git protocol is relatively easy to set up. Basically, you need to run this command in a daemonized manner:

        $ git daemon --reuseaddr --base-path=/srv/git/ /srv/git/
The `--reuseaddr` option allows the server to restart without waiting for old connections to time out, while the `--base-path` option allows people to clone projects without specifying the entire path, and the path at the end tells the Git daemon where to look for repositories to export. If you're running a firewall, you'll also need to punch a hole in it at port 9418 on the box you're setting this up on.
You can daemonize this process a number of ways, depending on the operating system you're running.
Since `systemd` is the most common init system among modern Linux distributions, you can use it for that purpose. Simply place a file in `/etc/systemd/system/git-daemon.service` with these contents:

        [Unit]
        Description=Start Git Daemon

        [Service]
        ExecStart=/usr/bin/git daemon --reuseaddr --base-path=/srv/git/ /srv/git/
        Restart=always
        Restart=500ms

        StandardOutput=syslog
        StandardError=syslog
        SyslogIdentifier=git-daemon

        User=git
        Group=git

        [Install]
        WantedBy=multi-user.target
You might have noticed that Git daemon is started here with `git` as both group and user. Modify it to fit your needs and make sure the provided user exists on the system. Also, check that the Git binary is indeed located at `/usr/bin/git` and change the path if necessary.
Finally, you'll run `systemctl enable git-daemon` to automatically start the service on boot, and can start and stop the service with, respectively, `systemctl start git-daemon` and `systemctl stop git-daemon`.
Until LTS 14.04, Ubuntu used upstart service unit configuration. Therefore, on Ubuntu before 14.04 you can use an Upstart script. So, in the following file

        /etc/init/locoal-git-daemon.conf
you put this script:

        start on startup
        stop on shutdown
        exec /usr/bin/git daemon \
            --user=git --group=git \
            --reuseaddr \
            --base-path=/srv/git/ \
            /srv/git/
        respawn
For security reasons, it is strongly encouraged to have this daemon run as a user with read-only permissions to the repositories-you can easily do this by creating a new user *git-ro* and running the daemon as them. For the sake of simplicity we'll simply run ti as the same *git* user that `git-shell` is running as.
When you restart your machine, your Git daemon will start automatically and respawn if it goes down. To get it running without having to reboot, you can run this:

        $ initctl start local-git-daemon
On other systems, you may want to use `Xinetd`, a script in your `sysvinit` system, or something else-as long as you get that command daemonized and watched somehow.
Next, you have to tell Git which repositories to allow unauthenticated Git server-based access to. You can do this in each repository by creating a file named `git-daemon-export-ok`.

        $ cd /path/to/project.git
        $ touch git-daemon-export-ok

### 4.6 Git on the Server-Smart HTTP
#### Smart HTTP
We now have authenticated access through SSH and unauthenticated access through `git://`, but there is also a protocol that can do both at the same time. Setting up Smart HTTP is basically just enabling a CGI script that is provided with Git called `git-http-backend` on the server. This CGI will read the path and headers sent by a `git fetch` or `git push` to an HTTP URL and determine if the client can communicate over HTTP (which is true for any client since version 1.6.6). If the CGI sees that the client is smart, it will communicate smartly with it; otherwise it will fall back to the dumb behavior (so it is backward compatible for reads with older clients).
Let's walk through a very basic setup. We'll set this up with Apache as the CGI server. If you don't have Apache setup, you can do so on a Linux box with something like this:

        $ sudo apt-get install apache2 apache2-utils
        $ a2enmod cgi alias env
This also enables the `mod_cgi`, `mod_alias`, and `mod_env` modules, which are all needed for this to work properly.
You'll also need to set the Unix user group of the `/srv/git` directories to `WWW-data` so your web server can read-and-write access the repositories, because the Apache instance running the CGI script will (by default) be running as that user:

        $ chgrp -R WWW-data /srv/git
Next we need to add some things to the Apache configuration to run the `git-http-backend` as the handler for anything coming into the `/git` path of your web server.

        SetEnv GIT_PROJECT_ROOT /srv/git
        SetEnv GIT_HTTP_EXPORT_ALL
        ScriptAlias /git/ /usr/lib/git-core/git-http-backend/
If you leave out `GIT_HTTP_EXPORT_ALL` environment variable, then Git will only serve to unauthenticated clients the repositories with the `git-daemon-export-ok` file in them, just like the Git daemon did.
Finally you'll want to tell Apache to allow requests to `git-http-backend` and make writes be authenticated somehow, possibly with an Auth block like this:

        <Files "git-http-backend">
            AuthType Basic
            AuthName "Git Access"
            AuthUserFile /srv/git/.htpasswd
            Require expr !(%{QUERY_STRING} -strmatch '*service=git-receive-pack*' || %{REQUEST_URI} =~ m#/git-receive-pack$#)
            Require valid-user
        </Files>
That will require you to create a `.htpasswd` file containing the passwords of all the valid users. Here is an example of adding a "schacon" user to the file:

        $ htpasswd -c /srv/git/.htpasswd schacon

There are a tons of ways to have Apache authenticate users, you'll have to choose and implement one of them. This is just the simplest example we could come up with. You'll also almost certainly want to set this up over SSL so all this data is encrypted.
We don't want to go too far down the rabbit hole of Apache configuration specifics, since you could well be using a different server or have different authentication needs. The idea is that Git comes with CGI called `git-http-backend` that when invoked will do all the negotiation to send and receive data over HTTP. It does not implement any authentication itself, but that can easily be controlled at the layer of the web server that invokes it. You can do this with nearly any CGI-capable web server, so go with the one that you know best.
_Note: For more information on configuring authentication in Apache, check out the Apache docs here:http://httpd.apache.org/docs/current/howto/auth.html_

### 4.7 Git on the Server-GitWeb
#### GitWeb
Now that you have basic read/write and read-only access to your project, you may want to set up a simple web-based visualizer. Git comes with a CGI script called GitWeb that is sometimes used for this.
![GitWeb web-based user interface](git-instaweb .png)
Figure 49. The GitWeb web-based user interface.
If you want to check out what GitWeb would look like for your project, Git comes with a command to fire up a temporary instance if you have a lightweight web server on your system like `lighttpd` or `webrick`. On Linux machines, `lighttpd` is often installed, so you may be able to get it to run by typing `git instaweb` in your project directory. If you're running a Mac, Leopard comes preinstalled with Ruby, so `webrick` may be your best bet. To start `instaweb` with a non-lighttpd handler, you can run it with the `--httpd` option.

        $ git instaweb --httpd=webrick
        [2009-02-21 10:02:21] INFO WEBrick 1.3.1
        [2009-02-21 10:02:21] INFO ruby 1.8.6 (2008-03-03) [universal-darwin9.0]
That starts up an HTTPD server on port 1234 and then automatically starts a web browser that opens on that page. It's pretty easy on your part. When you're done and want to shut down the server, you can run the same command with the `--stop` option:

        $ git instaweb --http=webric --stop
If you want to run the web interface on a server all the time for your team for for an open source project you're hosting, you'll need to set up the CGI script to be served by your normal web server. Some Linux distributions have `gitweb` package that you may be able to install via `apt` or `dnf`, so you may want to try that first. We'll walk through installing GitWeb manually very quickly. First, you need to get the Git source code, which GitWeb comes with, and generate the custom CGI script:

        $ git clone git://git.kernel.org/pub/scm/git/git.git
        $ cd git/
        $ make GITWEB_PROJECTROOT="/srv/git" prefix=/usr gitweb
            SUBDIR gitweb
            SUBDIR ../
        make[2]: 'GIT-VERSION-FILE' is up to date.
            GEN gitweb.cgi
            GEN static/gitweb.js
        $ sudo cp -Rf gitweb /var/www/
Notice that you have to tell the command where to find your Git repositories with the `GITWEB_PROJECTROOT` variable. Now, you need to make Apache use CGI for that script, for which you can add a VirtualHost:

        <VirtualHost *:80>
            ServerName gitserver
            DocumentRoot /var/WWW/gitweb
            <Directory /var/WWW/gitweb>
                Options +ExecCGI +FollowSymLinks +SymLinksIfOwnerMatch
                AllowOverride All
                order allow, deny
                Allow from all
                AddHandler cgi-script cgi
                DirectoryIndex gitweb.cgi
            </Directory>
        </VirtualHost>

Again, GitWeb can be served with any CGI or Perl capable web server; if you prefer to use something else, it shouldn't be difficult to set up. At this point, you should be able to visit `http://gitserver/` to view your repositories online.

### 4.8 Git on the Server-GitLab
#### GitLab
GitWeb is pretty simplistic though. If you're looking for a more modern, fully featured Git server, there are some several open source solutions out there that you can install instead. As GitLab is one of the more popular ones, we'll cover installing and using it as an example. This is a bit more complex than the GitWeb option and likely requires more maintenance, but it is a much more fully featured option.
#### Installation
GitLab is a database-backed web application, so its installation is a bit more involved than some other Git servers. Fortunately, this process is very well-documented and supported.
There are a few methods you can pursue to install GitLab. To get something up and running quickly, you can download a virtual machine image or a one-click installer from https://bitnami.com/stack/gitlab, and tweak the configuration to match your particular environment. One nice touch Bitnami has included is the login screen (accessed by typing alt+→); it tells you the IP address and defaul username and password for the installed GitLab.
![the Bitnami GitLab virtual machine login screen](bitnami.png)
Figure 50. The Bitnami GitLab virtual machine login screen.
For anything else, follow the guidance in hte GitLab Community Edition readme, which can be found at https://gitlab.com/gitlab-org/gitlab-ce/tree/master. There you'll find assistance for installing GitLab using Chef recipes, a virtual machine on Digital Ocean, and RPM and DEB packages (which, as of this writing, are in beta). There's also "unofficial" guidance on getting GitLab running with non-standard operating systems and databases, a fully-maunal installation script, and many other topics.
#### Administration
GitLab's administration interface is accessed over the web. Simply point your browser to the hostname or IP address where GitLab is installed, and log in as an admin user. The default username is `admin@local.hos`, and the default password is `5iveL!fe` (which you will be prompted to change as soon as you enter it). Once logged in, click the `Admin area` icon in the menu at the top right.
![the GitLab menu](gitlab-menu.png)
Figure 51. The "Admin area" item in the GitLab menu.
#### Users
Users in GitLab are accounts that correspond to people. User accounts don't have a lot of complexity; mainly it's a collection of personal information attached to login data. Each user account comes with a **namespace**, which is a logical grouping of projects that belong to that user. If the user `jane` had a project named `project`, that project's url would be http://server/jane/project.
![the GitLab user administration screen](gitlab-users.png)
Figure 52. The GitLab user administration screen.
Removing a user can be done in two ways. "Blocking" a user prevents them from logging into the GitLab instance, but all of the data under that user's namespace will be preserved, and commits signed with that user's email address will still link back to their profile.
"Destroying" a user, on the other hand, completely removes them from the database and filesystem. All projects and data in their namespace is removed, and any groups they own will also be removed. This is obviously a much more permanent and destructive action, and its uses are rare.
#### Groups
A GitLab group is an assemblage of projects, along with data about how users can access those projects. Each group has a project namespace (the same way that users do), so if the group `training` has a project `materials`, its url would be http://server/training/materials.
![The GitLab group administration screen](gitlab-groups.png)
Figure 53. The GitLab group administration screen.
Each group is associated with a number of users, each of which has a level of permissions for the group's projects and the group itself. These range from "Guest" (issues and chat only) to "Owner" (full control of the group, its members, and its projects). The types of permissions are too numerous to list here, but GitLab has a helpful link on the administration screen.
#### Projects
A GitLab project roughly corresponds to a single Git repository. Every project belongs to a single namespace, either a user or a group. If the project belongs to a user, the owner of the project has direct control over who has access to the project; if the project belongs to a group, the group's user-level permissions will also take effect.
Every project has a visibility level, which controls who has read access to that project's pages and repository. If a project is *Private*, the project's owner must explicitly gran access to specific users. An *Internal* project is visible to any logged-in user, and a *Public* project is visible to anyone. Note that this controls both `git fetch` access as well as access to the web UI for that project.
#### Hooks
GitLab includes support for hooks, both at a project or system level. For either of these, the GitLab server will perform an HTTP POST with some descriptive JSON whenever relevant events occur. This is a great way to connect your Git repositories and GitLab instance to the rest of your development automation, such as CI server, chat room, or deployment tools.
#### Basic Usage
The first thing you'll want to do with GitLab is create a new project. This is accomplished by clicking the "+" icon on the toolbar. You'll be asked for the project's name, which namespace it should belong to, and what its visibility level should be. Most of what you specify here isn't permanent, and can be re-adjusted later through the settings interface. Click "Create Project", and you're done.
Once the project exists, you'll probably want to connect it with a local Git repository. Each project is accessible over HTTPS or SSH, either of which can be used to configure a Git remote. The URLs are visible at the top of the project's home page. For an existing local repository, this command will create a remote named `gitlab` to the hosted location:

        $ git remote add gitlab https://server/namespace/project.git
If you don't have a local copy of the repository, you can simply do this:

        $ git clone https://server/namespace/project.git
The web UI provides access to several useful views of the repository itself. Each project's home page shows recent activity, and links along the top will lead you to views of the project's files and commit log.
#### Working Together
The simplest way of working together on a GitLab project is by giving another user direct push access to the Git repository. You can add a user to a project by going to the "Members" section of that project's settings, and associating the new user with an access level (the different access levels are discussed a bit in Groups). By giving a user an access level of "Developer" or above, that user can push commits and branches directly to the repository with impunity.
Another, more decoupled way of collaboration is by using merge requests. This feature enables any user that can see a project to contribute to it in a controlled way. Users with direct access can simply create a branch, push commits to it, and open a merge request from their branch into `master` or any other branch. Users who don't have push permissions for a repository can "fork" it (create their own copy), push commits to *that* copy, and open a merge request from their fork back to the main project. This model allows the owner to be in full control of what goes into the repository and when, while allowing contributions from untrusted users.
Merge requests and issues are the main units of long-lived discussion in GitLab. Each mere request allows a line-by-line discussion of the proposed change (which supports a lightweight kind of code review), as well as a general overall discussion thread. Both can be assigned to users, or organized into milestone.
This section is focused mainly on the Git-related features of GitLab, but as a mature project, it provides many other features to help your team work together, such as project wikis and system maintenance tools. One benefit to GitLab is that, once the server is set up and running, you'll rarely need to tweak a configuration file or access the server via SSH; most administration and general usage can be accomplished through the in-browser interface.
### 4.9 Git on the Server-Third Party Hosted Options
#### Third Party Hosted Options
If you don't want to go through all of the work involved in setting up your own Git server, you have several options for hosting your Git projects on an external dedicated hosting site. Doing so offers a number of advantages:a hosting site is generally quick to set up and easy to start projects on, and no server maintenance or monitoring is involved. Even if you set up and run your own server internally, you may still want to use a public hosting site for your open source code-it's generally easier for the open source community to find and help you with.
These days, you have a huge number of hosting options to choose from, each with different advantages and disadvantages. To see an up-to-date list, check out the GitHosting page on the main Git wiki at https://git.wiki.kernel.org/index.php/GitHosting
We'll cover using GitHub in detail in GitHub, as it is the largest Git host out there and you may need to interact with projects hosted on it in any case, but there are dozens more to chose from should you not want to set up your own Git server.
### 4.10 Git on the Sever-Summary
#### Summary
You have several options to get a remote Git repository up and running so that you can collaborate with others or share your work.
Running your own server gives you a lot of control and allows you to run the server within your own firewall, but such a server generally requires a fair amount of your time to set up and maintain. If you place your data on a hosted server, it's easy to set up and maintain; however, you have to be able to keep your code on someone else's servers, and some organizations don't allow that.
It should be fairly straightforward to determine which solution or combination of solutions is appropriate for you and your organization.
## 5. Distributed Git

### 5.1 Distributed Git-Distributed Workflows
Now that you have a remote Git repository set up as a focal point for all the developers to share their code, and you're familiar with basic Git commands in a local workflow, you'll look at how to utilize some of the distributed workflows that Git affords you.
In this chapter, you'll see how to work with Git in a distributed environment as a contributor and an integrator. That is, you'll learn how to contribute code successfully to a project and make it as easy on you and the project maintainer as possible, and also how to maintain a project successfully with a number of developers contributing.

#### Distributed Workflows
Unlike Centralized Version Control Systems (CVCSs), the distributed nature of Git allows you to be far more flexible in how developers collaborate on projects. In centralized systems, every developer is a node working ore or less equally on a central hub. In Git, however, every developer is potentially both a node and a hub-that is, every developer can both contribute code to other repositories and maintain a public repository on which others can base their work and which they can contribute to. This opens a vast range of workflow possibilities for your project and/or your team, so we'll cover a few common paradigms that take advantage of this flexibility. We'll go over the strengths and possible weaknesses of each design; you can choose a single one to use, or you can mix and match features from each.

##### Centralized Workflow
In centralized systems, there is generally a single collaboration model-the centralized workflow. One central hub, or repository, can accept code, and everyone synchronizes their work to it. A number of developers are nodes-consumers of that hub-and synchronize to that one place.
![Centralized Workflow](centralized_workflow.png)
This means that if two developers clone from the hub and both make changes, the first developer to push their changes back up can do so with no problems. The second developer must merge in the first one's work before pushing changes up, so as not to overwrite the first developer's changes. This concept is as true in Git as it is in Subversion (or any CVCS), and this model works perfectly well in Git.
If you are already comfortable with a centralized workflow in you company or team, you can easily continue using that workflow with Git. Simply set up a single repository, and give everyone on your team push access; Git won't let users overwrite each other. Say John and Jessica both start working at the same time. John finishes his change and pushes it to the server. Then Jessica tries to push her changes, but the server rejects them. She is told that she's trying to push non-fast-forward changes and that she won't be able to do so until she fetches and merges. This workflow is attractive to a lot of people because it's a paradigm that many are familiar and comfortable with.
This is also not limited to small teams. With Git's branching model, it's possible for hundreds of developers to successfully work on a single project through dozens of branches simultaneously.

##### Integration-Manager Workflow
Because Git allows you to have multiple remote repositories, it's possible to have a workflow where each developer has write access to their own public repository and read access to everyone else's. This scenario often includes a canonical repository that represents the "official" project. To contribute to that project, you create your own public cone of the project and push your changes to it. Then, you can send a request to the maintainer of the main project to pull in your changes. The maintainer can then add your repository as a remote, test your changes locally, merge them into their branch, and push back to their repository. The process works as follows
1. The project maintainer pushes to their public repository.
2. A contributor clones that repository and makes changes.
3. The contributor pushes to their own public copy.
4. The contributor sends the maintainer and email asking them to pull changes.
5. The maintainer adds the contributor's repository as a remote and merges locally.
6. The maintainer pushes merge changes to the main repository.
![Integration-manager workflow](integration-manager.png)
Figure 55. Integration-manager workflow.
This is a very common workflow with hub-based tools like GitHub or GitLab, where it's easy to fork a project and push your changes into your fork for everyone to see. One of the main advantages of this approach is that you can continue to work, and the maintainer of the main repository can pull in your changes at any time. Contributors don't have to wait for the project to incorporate their changes-each party can work at their own pace.
##### Dictator and Lieutenants Workflow
This is a variant of a multiple-repository workflow. It's generally used by huge projects with hundreds of collaborators; one famous example is the Linux kernel. Various integration managers are in charge of certain parts of the repository; they're called *lieutenants*. All the lieutenants have one integration manager known as the benevolent dictator. The benevolent dictator pushes from his directory to a reference repository from which all the collaborators need to pull. The process works like this:
1. Regular developers work on their topic branch and rebase their work on top of `master`. The `master` branch is that of the reference repository to which the dictator pushes.
2. Lieutenants merge the developers' topic branches into their `master` branch.
3. The dictator merges the lieutenant's `master` branches into the dictator's `master` branch.
4. Finally, the dictator pushes that `master` branch to the reference repository so the other developers can rebase on it.
![dictator and lieutenant workflow](benevolent-dictator.png)
Figure 56. Benevolent dictator workflow
This kind of workflow isn't common, but can be useful in very big projects, or in highly hierarchical environments. It allows the project leader (the dictator) to delegate much of the work and collect large subsets of code at multiple points before integrating them.
#### Workflows Summary
These are some commonly used workflows that are possible with a distributed system like Git, but you can see that many variations are possible t suit your particular real-world workflow. Now that you can (hopefully) determine which workflow combination may work for you, we'll cover some more specific examples of how to accomplish the main roles that make up the different flows. In the next section, you'll learn about a few common patterns for contributing to a project.


### 5.2 Distributed Git-Contributing to a Project
#### Contributing to a Project
The main difficulty with describing how to contribute to a project are the numerous variations on how to do that. Because Git is very flexible, people can do work together in many ways, and it's problematic to describe how you should contribute-every project is different. Some of the variables involved are active contributor count, chosen workflow, you commit access, and possibly the external contribution method.
The first variable is active contributor count-how many users are actively contributing code to this project, and how often? In many instances, you'll have two or three developers with a few commits a day, or possibly less for somewhat projects. For larger companies or projects, the number of developers could be in the thousands, with hundreds or thousands of commits coming in each day. This is important, because with more and more developers, you run into more issues with making sure you code applies cleanly or can be easily merged. Changes you submit may be rendered obsolete or severely broken by work that is merged in while you were working or while your changes were waiting to be approved or applied. How can you keep your code consistently up to date and your commits valid?
The next variable is the workflow in use for the project. Is it centralized, with each developer having equal write access to the main codeline? Does the project have a maintainer or integration manager who checks all the patches? Are all the patches peer-reviewed and approved? Are you involved in that process? Is a lieutenant system in place, and do you have to submit your work to them first?
The next variable is your commit access. The workflow required in order to contribute to a project is much different if you have write access to the project than id you don't. If you don't have write access, how does the project prefer to accept contributed work? Does it even have a policy? How much work are you contributing at a time? How often do you contribute?
All these questions can affect how you contribute effectively to a project and what workflows preferred or available to you. We'll cover aspects of each of these in a series of use cases, moving from simple to more complex; you should be able to construct the specific workflows you need in practice from these examples.
##### Commit Guidelines
Before we start looking at the specific use cases, here's a quick note about commit messages. Having a good guideline for creating commits and sticking to it makes working with Git and collaborating with others a lot easier. The Git project provides a document that lays out a number of good tips for creating commits from which to submit patches-you can read it in the Git source code in the `Documentation/SubmittingPatches` file.
First, your submissions should not contain any whitespace errors. Git provides an easy way to check for this-before you commit, run `git diff --check`, which identifies possible whitespace errors and lists them for you.
![git diff --check for whitespaces](git-diff-check.png)
Figure 57. Output of `git diff --check`
If you run that command before committing, you can tell if you're about to commit whitespace issues that may annoy other developers.
Next, try to make each commit a logically separate changeset. If you can, try to make your changes digestible-don't code for a whole weekend on five different issues and then submit them all as one massive commit on Monday. Even if you don't commit during the weekend, use the staging area on Monday to split your work into at least one commit per issue, with a useful message per commit. If some of the changes modify the same file, try to use `git add --patch` to partially stage files (covered in detail in Interactive Staging). The project snapshot at the tip of the branch is identical whether you do one commit or five, as long as all the changes are added at some point, so try to make things easier on your fellow developers when they have to review your changes.
This approach also makes it easier to pull out or revert one of the changesets if you need to later. [Rewriting History](https://git-scm.com/book/en/v2/ch00/_rewriting_history) describes a number of useful Git tricks for rewriting history and interactively staging files-use these tools to help craft a clean and understandable history before sending the work to someone else.
The last thing to keep in mind is the commit message. Getting in the habit of creating quality commit messages makes using and collaborating with Git a lot easier. As a general rule, you messages should start with a single line that's no more than about 50 characters and that describes the changeset concisely, followed by a blank line, followed by a more detailed explanation. The Git project requires that the more detailed explanation include your motivation for the change and contrast its implementation with previous behavior-this is a good guideline to follow. It's also a good idea to use the imperative present tense in these messages. In other words, use commands. Instead of "I added tests for" or "Adding tests for," use "Add tests for." Here is a template originally written by Tim Pope:

        Short (50 chars or less) summary of changes

        More detailed explanatory text, if necessary. Wrap it to about 72 characters or so. In some contexts, the first line is treated as the subject of an email and the rest of the text as the body. The blank line separating the summary from the body is critical (unless you omit the body entirely); tools like rebase can get confuseed if you run the two together.

        Further paragraphs comes after blank lines.

        - Bullet points are okay, too

        - Typically a hyphen or asterisk is used for the bullet, preceded by a single space, with blank lines in between, but conventions vary here.
If all your commit messages follow this model, things will be much easier for you and the developers with whom you collaborate. The Git project has well-formatted commit messages-try running `git log --no-merges` there to see what a nicely-formatted project-commit history looks like.
_Note:
Do as we say, not as we do.
For the sake of brevity, many of the examples in this book don't have nicely-formatted commit messages like this; instead, we simply use the `-m` option to `git commit`.
In short, do as we say, not as we do._
##### Private Small Team
The simplest setup you're likely t encounter is a private project with one or two other developers. "Private," in this context, means closed-source-not accessible to the outside world. You and other developers all have push access to the repository.
In this environment, you can follow a workflow similar to what you might do when using Subversion or another centralized system. You still get the advantages of things like offline committing and vastly simpler branching and merging, but the workflow can be very similar; the main difference is that merges happen client-side rather than on the server at commit time. Let's see what it might look like when two developers start to work together with a shared repository. The first developer, John, clones the repository, makes a change, and commits locally. (The protocol messages have been replaced with `...` in these examples to shorten them somewhat.)

        # John's Machine
        $ git clone john@githost:dimplegit.git
        Cloning into 'simplegit'...
        ...
        $ cd simplegit/
        $ vim lib/simplegit.rb
        $ git commit -am 'remove invalid default value'
        [master 738ee87] remove invalid default value
        1 files changed, 1 insertions(+), 1 deletions(-)
The second developer, Jessica, does the same thing-clones the repository and commits a change:

        # Jessica's Machine
        $ git clone jessica@githost:simplegit.git
        Cloning into 'simplegit'...
        ...
        $ cd simplegit/
        $ vim TODO
        $ git commit -am 'add reset task'
        [master fbff5bc] add reset task
        1 files changed, 1 insertions(+), 0 deletions(-)
Now, Jessica pushes her work to he server, which works just fine:

        # Jessica's Machine
        $ git push origin master
        ...
        To jessica@githost:simplegit.git
            1edee6b..fbff5bc master -> master
The last line of the output above shows a useful return message from the push operation. The basic format is `<oldref>..<newref> fromref -> toref`, where `oldref` means the old reference, `newref` means the new reference, `fromref` is the name of the local reference being pushed, and `toref` is the name of the remote reference being updated. You'll see similar output like this below in the discussions, so having a basic idea of the meaning will help in understanding the various state of the repositories. More details are available in the documentation for [git-push](https://git-scm.com/docs/git-push).
Continuing with this example, shortly afterwards, John makes some changes, commits them to his local repository, and tries to push them to the same server:

        # John's Machine
        $ git push origin master
        To john@githost:simplegit.git
            ! [rejected]        master  -> master (non-fast forward)
        error: failed to push some refs to 'john@githost:simplegit.git'
In this case, John's push fails because of Jessica's earlier push of *her* changes. This is especially important t understand if you're used to Subversion, because you'll notice that the two developers didn't edit the same file. Although Subversion automatically does such a merge on the server if different files are edited, with Git, you must *first* merge the commits locally. In other words, John must first fetch Jessica's upstream changes and merge then into his local repository before he will be allowed to push.
As a first step, John fetches Jessica's work (this only *fetches* Jessica's upstream work, it does not yet merge it into John's work):

        $ git fetch origin
        ...
        From john@githost:simplegit
            + 049d078...fbff5bc master      -> origin/master
At this point, John's local repository looks something like this:
![fetched history](small-team-1.png)
Figure 58. John's divergent history.
Now John can merge Jessica's work that he fetched into his own local work:

        $ git merge origin/master
        Merge made by the 'recursive' strategy.
            TODO |  1+
            1 fiels changed, 1 insertions(+), 0 deletions(-)
As long as that local merge goes smoothly, John's updated history will now look like this:
![repository after merging `origin/master`](small-team-2.png)
Figure 59. John's repository after merging `origin/master`.
At this point, John might want to test this new code to make sure none of Jessica's work affects any of this and, as long as everything seems fine, he can finally push the new merged work up to the server:

        $ git push origin master
        ...
        To john@githost:simplegit.git
            fbff5bc..72bbc59    master -> master
In the end, John's commit history will look like this:
![John's history after pushing to the `origin` server](small-team-3.png)
Figure 60. John's history after pushing to the `origin` server.
In the meantime, Jessica has created a new topic branch called `issue54`, and made three commits to that branch. She hasn't fetched John's changes yet, so her commit history looks like this:
![Jessica's topic branch](small-team-4.png)
Figure 61. Jessica's topic branch.
Suddenly, Jessica learns that John has pushed some new work to hte sever and she wants to take a look at it, so she can fetch all new content from the server that she does not yet have with:

        # Jessica's Machine
        $ git fetch origin
        ...
        From jessica@githost:simplegit
            fbff5bc..72bbc59 master     -> origin/master
That pulls down the work John has pushed up in the meantime. Jessica's history now looks like this:
![Jessica's history after fetching John's changes](small-team-5.png)
Figure 62. Jessica's history after fetching John's changes.
Jessica thinks her topic branch is ready, but she wants to know what part of John's fetched work she has to merge into her work so that she can push. She runs `git log` to find out:

        $ git log --no-merges issue54..origin/master
        commit 738ee872852dfaa9d6634e0dea7a324040193016
        Author: John Smith <jsmith@example.com>
        Date: Fri May 29 16:01:27 2009 -0700

            remove invalid default value
The `issue54..origin/master` syntax is log filter that asks Git to display only those commits that are on the latter branch (in this case `origin/master`) that are not on the first branch (in this case `issue54`). We'll go over this syntax in detail in [Commit Ranges](https://git-scm.com/book/en/v2/ch00/_commit_ranges).
From the above output, we can see that there is a single commit that John has made that Jessica has no merged into her local work. If she merges `origin/master`, that is the single commit that will modify her local work.
Now, Jessica can merge her topic work into her master branch, merge John's work (`origin/master`) into her `master` branch, and then push back to the server again.
First (having committed all of the work on her `issue54` topic branch), Jessica switches back to her master branch in preparation for integrating all this work:

        $ git checkout master
        Switched to branch 'master'
        Your branch is behind 'origin/master' by 2 commits, and can be fast-forwarded.
Jessica can merge either `origin/master` or `issue54` first-they're both upstream, so the order doesn't matter. The end snapshot should be identical no matter which order she chooses; only the history will be different. She chooses to merge the `issue54` branch first:

        $ git merge issue54
        Updating fbff5bc..4af4298
        Fast forward
            README      |   1+
            lib/simplegit.rb    |   6+++++-
            2 files changed, 6 insertions(+), 1 deletions(-)
No problems occur; as you can see it was a simple fast-forward merge. Jessica now completes the local merging process by merging John's earlier fetched work that is sitting in the `origin/master` branch:

        $ git merge origin/master
        Auto-merging lib/simpelgit.rb
        Merge made by the 'recursive' strategy.
            lib/simplegit.rb    |   2 +-
            1 files changed, 1 insertins(+), 1 deletions(-)
Everything merges cleanly, and Jessica's history now looks like this:
![Jessica's history after merging John's changes](small-team-6.png)
Figure 63. Jessica's history after merging John's changes.
Now `origin/master` is reachable from Jessica's `master` branch, so she should be able to successfully push (assuming John hasn't pushed even more changes in the meantime):

        $ git push origin master
        ...
        To jessica@githost:simplegit.git
            72bbc59..8059c15    master -> master
Each developer has committed a few times and merged each other's work successfully.
![Jessica's history after pushing all changes back to the server](small-team-7.png)
Figure 64. Jessica's history after pushing all changes back to the server.
That is one of the simplest workflows. You work for while (generally in a topic branch), and merge that work into your `master` branch when it's ready to be integrated. When you want to share that work, you fetch and merge your `master` from `origin/master` if it has changed, and finally push to the `master` branch on the server. The general sequence is something like this:
![General sequence of events for a simple multiple-developer Git workflow](small-team-flow.png)
Figure 65. General sequence of events for a simple multiple-developer Git workflow.
##### Private Managed Team
In this next scenario, you'll look at contributor roles in a larger private group. You'll learn how to work in an environment where small groups collaborate on features, after which those team-based contributions are integrated by another party.
Let's say that John and Jessica are working together on one feature (call this "featureA"), while Jessica and a third developer, Josie, are working on a second (say, "featureB"). In this case, the company is using a type of integration-manager workflow where the work of the individual groups is integrated only by certain engineers, and the `master` branch of the main repo can be updated only by those engineers. In this scenario, all work is done in team-based branches and pulled together by the integrators later.
Let's follow Jessica's workflow as she works on her two features, collaborating in parallel with two different developers in this environment. Assuming she already has her repository cloned, she decides to work on `featureA` first. She creates a new branch for the feature and does some work on it there:

        # Jessica's Machine
        $ git checkout -b featureA
        Switched to a new branch 'featureA'
        $ vim lib/simplegit.rb
        $ git commit -am 'add limit to log function'
        [featureA 3300904] add limit to log function
        1 files changed, 1 insertions(+), 1 deletions(-)
At this point, she needs to share her work with John, so she pushes her `featureA` branch commits up to the server. Jessica doesn't have push access to the `master` branch-only the integrators do-so she has to push to another branch in order to collaborate with John:

        $ git push -u origin featureA
        ...
        To jessica@githost:simplegit.git
         * [new branch]     featureA -> featureA

`git push -u` or `git push --set-upstream`: For every branch that is up to date or successfully pushed, add upstream (tracking) reference, used by argument-less `git pull` and other commands. This is used to configure the branches for easier pushing and pulling later.
Jessica emails John to tell him that she's pushed some work into a branch named `featureA` and he can look at it now. While she waits for feedback from John, Jessica decides to start working on `featureB` with Josie. To begin, she starts a new feature branch, basing it off the server's `master` branch:

        # Jessica's Machine
        $ git fetch origin
        $ git checkout -b featureB origin/master
        Switched to a new branch 'featureB'
Now Jessica makes a couple of commits on the `featureB` branch:

        $ vim lib/simlegit.rb
        $ git commit -am 'made the ls-tree function recursive'
        [featureB e5b0fdc] made the ls-tree function recursive
         1 files changed, 1 insertions(+), 1 deletions(-)
        $ vim lib/simplegit.rb
        $ git commit -am 'add ls-files'
        [featureB 8512791] add ls-files
         1 files changed, 5 insertions(+), 0 deletions(-)
Jessica's repository now looks like this:
![Jessica's initial commit history](managed-team-1.png)
Figure 66. Jessica's initial commit history
She's ready to push her work, but gets an email from Josie that a branch with some initial "featureB" work on it was already pushed to the server as the `featureBee` branch. Jessica needs to merge those changes with own before she can push her work to the server. Jessica first fetches Josie's changes with `git fetch`:

        $ git fetch origin
        ...
        From jessica@githost:simplegit
         * [new branch]     featureBee -> origin/featureBee
Assuming Jessica is still on her checked-out `featureB` branch, she can now merge Josie's work into that branch with `git merge`:

        $ gi merge origin/featureBee
        Auto-merging lib/simplegit.rb
        Merge made by the 'recursive' strategy.
         lib/simplegit.rb  |    4 ++++
         1 files changed, 4 insertions(+), 0 deletions(-)
At this point, Jessica wants to push all of this merged "featureB" work back to the server, but she doesn't want to simply push her one `featureB` branch. Rather, since Josie has already started an up stream `featureBee` branch, Jessica wants to push to *that* branch which she does with:

        $ git push -u origin featureB:featureBee
        ...
        To jessica@githost:simplegit.git
            fba9af8..cd685d1    featureB -> featureBee
This is called a *refspec*. See [The Refspec](#TheRefspec) for a more detailed discussion of Git refspecs and different things you can do with them.
[tracking branches](#TrackingBranches)
the default format meaning of `git push` and `git fetch`
`man git-fetch`
`man git-push`

## 8. Customizing Git
### 8.3 Git Hooks <a name=Git_Hooks></a>
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

#### gitrevisions <a name=gitrevisions> </a>

##### NAME
gitrevisions-specifying revisions and ranges for Git

##### SYNOPSIS
gitrevisions

##### DESCRIPTION
Many Git commands take revision parameters as arguments. Depending on the command, they denote a specific commit or, for commands which walk the revision graph (such as [git-log](#gitlog)), all commits which are reachable from that commit. For commands that walk the revision graph one can also specify a range of revisions explicitly.
In addition, some Git commands (such as `git show`) also take revision parameters which denote other objects than commits, e.g. blobs ("files") or trees ("directories of files").

##### Specifying Revisions
A revision parameter `<rev>` typically, but not necessarily, names a commit object. It uses what is called an *extended SHA-1* syntax. Here are various ways to spell object names. The ones listed near the end of this list name trees and blobs contained in a commit.
* <sha1>, e.g. `dae86e1950b1277e545cee180551750029cfe735`, `dae86e`
    The full SHA-1 object name (40-byte hexadecimal string), or a leading substring that is unique within the repository. E.g. `dae86e1950b1277e545cee180551750029cfe735` and `dae86e` both name the same commit object if there is no other object in your repository whose object name starts with `dae86e`.
* <describeOutput>, e.g. `v1.7.4.2-679-g3bee7fb`
    Output from `git describe`; i.e. a closest tag, optionally followed by a dash and number of commits, followed by a dash, a `g`, and an abbreviated object name.
* <refname>, e.g. `master`, `heads/master`, `refs/heads/master`
    A symbolic ref name. E.g. `master` typically means the commit object referenced by `refs/heads/master`. If you happen to have both `heads/master` and `tags/master`, you can explicitly say `head/master` to tell Git which one you mean. When ambiguous, a <refname> is disambiguated by taking the first match in the following rules:
    1. If `$GIT_DIR/<refname>` exists, that is what you mean (this is usually useful only for `HEAD`, `FETCH_HEAD`, `ORIG_HEAD`, `MERGE_HEAD` and `CHERRY_PICK_HEAD`);
    2. otherwise, `refs/<refname>` if it exists;
    3. otherwise, `refs/tags/<refname>` if it exists;
    4. otherwise, `refs/heads/<refname>` if it exists;
    5. otherwise, `refs/remotes/<refname>` if it exists;
    6. otherwise, `refs/remotes/<refname>/HEAD` if it exists.
    `HEAD` names the commit on which you based the changes in the working tree. `FETCH_HEAD` records the branch which you fetched from a remote repository with your last `git fetch` invocation. `ORIG_HEAD` is created by commands that move your `HEAD` in a drastic way, to record the position of the `HEAD` before their operation, so that you can easily change the tip of the branch back to the state before you ran them. `MERGE_HEAD` records the commit(s) which you are merging into your branch when you run `git merge`. `CHERRY_PICK_HEAD` records the commit which you are cherry-picking when you run `git cherry-pick`.
    Note that any of the `refs/*` cases above may come either from the `$GIT_DIR/refs` directory or from the `$GIT_DIR/packed-refs` file. While the ref name encoding is unspecified, UTF-8 is preferred as some output processing may assume ref names in UTF-8.
* `@`
    `@` alone is a shortcut for `HEAD`.
* `<refname>@{<date>}`, e.g. `master@{yesterday}`, `HEAD@{5 minutes ago}`
    A ref followed by the suffix `@` with a date specification enclosed in a brace pair (e.g. `{yesterday}`, `{1 month 2 weeks 3 days 1 hour 1 second ago}` or `{1979-02-26 18:30:00}`) specifies the value of the ref at a prior point in time. This suffix may only be used immediately following a ref name and the ref must have an existing log (`$GIT_DIR/logs/<ref>`). Note that this looks up the state of your **local** ref at a given time; e.g., what was in your local `master` branch last week. If you want to look at commits made during certain times, see `--since` and `--until`.
* `<refname>@{<n>}`, e.g. `master@{1}`
    A ref followed by the suffix `@` with an ordinal specification enclosed in a brace pair (e.g. `{1}`, `{15}`) specifies the n-th prior value of that ref. For example `master@{1}` is the immediate prior value of `master` while `master@{15}` is the 15th prior value of `master`. This suffix may only be used immediately following a ref name and the ref must have an existing log (`$GIT_DIR/logs/<refname>`).
* `@{<n>}`, e.g. `@{1}`
    You can use the `@` construct with an empty ref part to get at a reflog entry of the current branch. For example, if you are on branch `blabla` then `@{1}` means the same as `blabla@{1}`.
* `@{<-n>}`, e.g. `@{-1}` ???
    The construct `@{-<n>}` means the `<n>`th branch/commit checked out before the current one.
* `<branchname>@{upstream}`, e.g. `master@{upstream}`, `@{u}`
    The suffix `@{upstream}` to a branchname (short form `<branchname>@{u}`) refers to the branch that the branch specified by branchname is set to build on top of (configured with `branch.<name>.remote` and `branch.<name>.merge`). A missing branch name defaults to the current one.
* `<branchname>@{push}`, e.g. `master@{push}`, `@{push}`
    The suffix `@{push}` reports the branch "where we would push to" if `git push` were run while `branchname` was checked out (or the current `HEAD` if no branchname is specified). Since our push destination is in a remote repository, of course, we report the local tracking branch that corresponds to that branch (i.e., something in `refs/remotes/`).
    Here's an example to make it more clear:

            $ git config push.default current
            $ git config remote.pushdefault myfork
            $ git checkout -b mybranch origin/master

            $ git rev-parse --symbolic-full-name @{upstream}
            refs/remotes/origin/master

            $ git rev-parse --symbolic-full-name @{push}
            refs/remotes/myfork/maybranch
    Note in the example that we set up a triangular workflow, where we pull from one location and push to another. In a non-triangular workflow, `@{push}` is the same as `@{upstream}`, and there is no need for it.
* `<rev>^`, e.g. `HEAD^`, `v1.5.1^0`
    A suffix `^` to a revision parameter means the first parent of that commit object. `^<n>` means the `<n>`th parent (i.e. `<rev>^` is equivalent to `<rev>^1`). As a special rule, `<rev>^0` means the commit itself and is used when `<rev>` is the object name of a tag object that refers to a commit object.
* `<rev>~<n>`, e.g. `master~3`
    A suffix `~<n>` to a revision parameter means the commit object that is the `<n>`th generation ancestor of the named commit object, following only the first parents. I.e. `<rev>~3` is equivalent to `<rev>^^^` which is equivalent to `<rev>^1^1^1`. See below for an illustration of the usage of this form.
* `<rev>^{type}`, e.g. `v0.99.8^{commit}`
    A suffix followed by an object type name enclosed in brace pair means dereference the object at `<rev>` recursively until an object of type `<type>` is found or the object cannot be dereferenced anymore (in which case, barf). For example, if `<rev>` is a commit-ish, `<rev>^{commit}` describes the corresponding commit object. Similarly, if `<rev>` is a tree-ish, `<rev>^{tree}` describes the corresponding tree object. `<rev>^0` is short-hand for `<rev>^{commit}`.
    `<rev>^{object}` can be used to make sure `<rev>` names an object that exists, without requiring `<rev>` to be a tag, and without dereferencing `<rev>`; because a tag is already an object, it does not have to be dereferenced even once to get to an object.
    `<rev>^{tag}` can be used to ensure that `<rev>` identifies an existing tag object.
* `<rev>^{}`, e.g. `v0.99.8^{}`
    A suffix `^` followed by an empty brace pair means the object could be a tag, and dereference the tag recursively until a non-tag object is found.
* `<rev>^{/<text>}`, e.g. `HEAD^{/fix nasty bug}`
    A suffix `^` to a revision parameter, followed by a brace pair that contains a text led by a slash, is the same as the `:/fix nasty bug` syntax below except that is returns the youngest matching commit which is reachable from the `<rev` before `^`.
* `:/<text`, e.g. `:/fix nasty bug`
    A colon, followed by a slash, followed by a text, names a commit whose commit message matches the specified regular expression. This name returns the youngest matching commit which is reachable from any ref. The regular expression can match any part of the commit message. To match messages starting with a string, one can use e.g. `:/^foo`. ???The special sequence `:/!` is reserved for modifiers to what is matched. `:/!-foo` performs a negative match, while `:/!!foo` matches a literal ! character, followed by `foo`. Any other sequence beginning with `:/!` is reserved for now.???
* `<rev>:<path>`, e.g. `HEAD:README`, `:README`, `master:./README`
    A suffix `:` followed by a path names the blob or tree at the given path in the tree-ish object named by the part before the colon. `:path` (with an empty art before the colon) is a special case of the syntax described next: content recorded in the index at the given path. A path starting with `./` or `../` is relative to the current working directory. The given path will be converted to be relative to the working tree's root directory. This is most useful to address a blob or tree from a commit or tree that has the same tree structure as the working tree.
* `:<n>:<path>`, e.g. `0:README`, `:README`
    A colon, optionally followed by a stage number (0 to 3) and a colon, followed by a path, names a blob object in the index at the given path. A missing stage number (and the colon that follows it) names a stage 0 entry. During a merge, stage 1 is the common ancestor, stage 2 is the target branch's version (typically the current branch), and stage 3 is the version from the branch which is being merged.
    Here is an illustration, by Jon Loeliger. Both commit nodes B and C are parents of commit node A. Parent commits are ordered left-to-right.

            G   H   I   J
             \ /     \ /
              D   E   F
               \  |  / \
                \ | /   |
                 \|/    |
                  B     C
                   \   /
                    \ /
                     A

        A =      = A^0
        B = A^   = A^1     = A~1
        C = A^2  = A^2
        D = A^^  = A^1^1   = A~2
        E = B^2  = A^^2
        F = B^3  = A^^3
        G = A^^^ = A^1^1^1 = A~3
        H = D^2  = B^^2    = A^^^2  = A~2^2
        I = F^   = B^3^    = A^^3^
        J = F^2  = B^3^2   = A^^3^2
![caretVStilde](caretVStilde.png)

Way to remember: `~` is "fuzzy" or "approximate" (i.e, you only get the first parent); while `^` is precise (so goes through every single commit).
One thing that is often unmentioned is *how* to know which is the first or second parent. You can use `git log` or `git show`. If it's a merged commit with multiple parents, the parents will be listed in order of first, second, etc.

##### Specifying Ranges
History traversing commands such as `git log` operate on a set of commits, not just a single commit.
For these commands, specifying a single revision, using the notation described in the previous section, means the set of commits `reachable` from the given commit.
A commit's reachable set is the commit itself and the commits in its ancestry chain.

###### Commit Exclusions
* `^<rev>` (caret) Notation
    To exclude commits reachable from a commit, a prefix `^` notation is used. E.g. `^r1 r2` means commits reachable from `r2` but exclude the ones reachable from `r1` (i.e. `r1` and its ancestors).

###### Dotted Range Notations
* The `..` (two-dot) Range Notation
    The `^r1 r2` set operation appears so often that there is a shorthand for it. When you have two commits `r1` and `r2` (named according to the syntax explained in Specifying Revisions above), you can ask for commits that are reachable from `r2` excluding those that are reachable from `r1` by `^r1 r2` and it can be written as `r1..r2`.
* The `...` (three dot) Symmetric Difference Notation
    A similar notation `r1...r2` is called symmetric difference of `r1` and `r2` and is defined as `r1 r2 --not $(git merge-base --all r1 r2`). It is the set of commits that are reachable from either one of `r1` (left side) or `r2` (right side) but not from both.
In these two shorthand notations, you can omit one end and let it default to `HEAD`. For example, `origin..` is a shorthand for `origin..HEAD` and asks "What did I do since I forked from the origin branch?" Similarly, `..origin` is a shorthand for `HEAD..origin` and asks "What did the origin do since I forked from them?" Note that `..` would mean `HEAD..HEAD` which is an empty range that is both reachable and unreachable from `HEAD`.

####### Other `<rev>^` Parent Shorthand Notations
Two other shorthands exist, particularly useful for merge commits, for naming a set that is formed by a commit and its parent commits.
The `r1^@` notation means all parents of `r1`.
The `r1^!` notation includes commit `r1` but excludes all of its parents. By itself, this notation denotes the single commit `r1`.
While `<rev>^<n>` was about specifying a single commit parent, these two notations consider all its parents. For example you can say `HEAD^2^@`, however you cannot say `HEAD^@^2`.

##### Revision Range Summary
* `<rev>`
    Include commits that are reachable from `<rev>` (i.e. `<rev>` and its ancestors).
* `^<rev>`
    Exclude commits that are reachable from `<rev>` (i.e. `<rev>` and its ancestors).
* `<rev1>..<rev2>`
    Include commits that are reachable from `<rev2>` but exclude those that are reachable from `<rev1>`. When either `<rev1>` or `<rev2>` is omitted, it defaults to `HEAD`.
* `<rev1>...<rev2>`
    Include commits that are reachable from either `<rev1>` or `<rev2>` but exclude those that are reachable from both. When either `<rev1>` or `<rev2>` is omitted, it defaults to `HEAD`.
* `<rev>^@`, e.g. `HEAD^@`
    A suffix `^` followed by an at sign is the same as listing all parents of `<rev>` (meaning, include anything reachable from its parents, but not the commit itself).
* `<rev>^!`, e.g. `HEAD^!`
    A suffix `^` followed by an exclamation mark is the same as giving commit `<rev>` and then all its parents prefixed with `^` to exclude them (and their ancestors).

Here are a handful of examples using the Loeliger illustration above, with each step in the notation's expansion and selection carefully spelt out:


            G   H   I   J
             \ /     \ /
              D   E   F
               \  |  / \
                \ | /   |
                 \|/    |
                  B     C
                   \   /
                    \ /
                     A

    Args   Expanded arguments    Selected commits

    D                            G H D
    D F                          G H I J D F
    ^G D                         H D
    ^D B                         E I J F B
    ^D B C                       E I J F B C
    C                            I J F C
    B..C   = ^B C                C
    B...C  = B ^F C              G H D E B C
    C^@    = C^1
    = F                   I J F
    B^@    = B^1 B^2 B^3
    = D E F               D G H E F I J
    C^!    = C ^C^@
    = C ^C^1
    = C ^F                C
    B^!    = B ^B^@
    = B ^B^1 ^B^2 ^B^3
    = B ^D ^E ^F          B
    F^! D  = F ^I ^J D           G H D F


#### `man git show-ref`
##### NAME
`git show-ref`: List references in a local repository.

##### Synopsis

        git show-ref [-q|--quiet] [--verify] [--head] [-d|--dereference] [-s|--hash[=<n>]] [--abbrev[=<n>]] [--tags] [--heads] [--] [<pattern>...]
        git show-ref --exclude-existing[=<pattern>]

##### Description
Displays references available in a local repository along with the associated commit IDs. Results can be filtered using a pattern and tags can be dereferenced into object IDs. Additionally, it can be used to test whether a particular ref exists.
By default, shows the tags, heads, and remote refs.
The `--exclude-existing` from is a filter that does the inverse. It reads refs from stdin, one ref per line, and shows those that don't exist in the local repository.
Use of this utility is encouraged in favor of directly accessing files under the `.git` directory.

##### Options
* `--head`
    Show the `HEAD` reference, even if it would normally be filtered out.
* `--tags`, `--heads`
    Limit to `refs/heads` and `refs/tags`, respectively. These options are not mutually exclusive; when given both, references stored in `refs/heads` and `refs/tags` are displayed.
* `-d`, `--dereference`
    Dereference tags into object IDs as well. They will be shown with `^{}` appended.
* `-s`, `--hash[=<n>]`
    Only show the SHA-1 hash, not the reference name. When combined with `--dereference` the dereferenced tag will still be shown after the SHA-1.
* `--abbrev[=<n>]`
    Abbreviate the object name. When using `--hash`, you do not have to say `--hash --abbrev`; `--hash=n` would do.
* `-q`, `--quiet`
    Do not print any results to stdout. When combined with `--verigy` this can be used to silently check if a reference exists.
* `<pattern>...`
    Show references matching one or more patterns. Patterns are matched from the end of the full name, and only complete parts are matched, e.g. `master` matches `refs/heads/master`, `refs/remotes/origin/master`, `refs/tags/jedi/master` but not `refs/heads/mymaster` or `refs/remotes/master/jedi`.

##### OUTPUT
The output is in the format:`<SHA-1 ID> <space> <reference name>`.

        $ git show-ref --head --dereference
        832e76a9899f560a90ffd62ae2ce83bbeff58f54 HEAD
        832e76a9899f560a90ffd62ae2ce83bbeff58f54 refs/heads/master
        832e76a9899f560a90ffd62ae2ce83bbeff58f54 refs/heads/origin
        3521017556c5de4159da4615a39fa4d5d2c279b5 refs/tags/v0.99.9c
        6ddc0964034342519a87fe013781abf31c6db6ad refs/tags/v0.99.9c^{}
        055e4ae3ae6eb344cbabf2a5256a49ea66040131 refs/tags/v1.0rc4
        423325a2d24638ddcc82ce47be5e40be550f4507 refs/tags/v1.0rc4^{}

When using `--hash` (and not `--dereference`) the output format is: `<SHA-1 ID>`

        $ git show-ref --heads --hash
        2e3ba0114a1f52b47df29743d6915d056be13278
        185008ae97960c8d551adcd9e23565194651b5d1
        03adf42c988195b50e1a1935ba5fcbc39b2b029b
        ...
##### Example
To show all references called `master`, whether tags or heads or anything else, and regardless of how deep in the reference naming hierarchy they are, use:
        `git show-ref master`
This will show `refs/heads/master` but also `refs/remote/other-repo/master`, if such references exist.
When using the `--verify` flag, the command requires an exact path:
        `git show-ref --verify refs/heads/master`
will only match the exact branch called `master`.
If nothing matches, `git show-ref` will return an error code of `1`, and in the case of verification, it will show an error message.
For scripting, you can ask it to be quiet with the `--quiet` flag, which allows you to do things like
        `git show-ref --quiet --verigy -- "refs/heads/$headname" || echo "$headname is not a valid branch"`
to check whether a particular branch exists or not (notice how we don't actually want to show any results, and we want to use the full refname for it in order to not trigger the problem with ambiguous partial matches).???
To show only tags, or only proper branch heads, use `--tags` and/or `--heads` respectively (using both means that it shows tags and heads, but not other random references under the `refs/` subdirectory).
To do automatic tag object dereferencing, use the `-d` or `--dereference` flag, so you can do
        `git show-ref --tags --dereference`
to get a listing of all tags together with what they dereference.

##### Files
`.git/refs/*`, `.git/packed-refs`

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
#### The Refspec <a name=TheRefspec></a>
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

##### Example
When you clone a repository sets up the default refspec, you can see it in `.git/config` in the repository:

        [core]
            repositoryformatversion = 0
            filemode = true
            bare = false
            logallrefupdates = true
        [remote "origin"]
            url = https://git.example.com/example.git
            fetch = +refs/heads/*:refs/remotes/origin/*
        [branch "master]
            remote = origin
            merge = refs/heads/master
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

## 11. Manuals

### 11.1 `man git rev-list`

#### NAME
git-rev-list: Lists commit objects in reverse chronological order.

#### Synopsis

#### Description
List commits that are reachable by following the `parent` links from the given commit(s), but exclude commits that are reachable from the one(s) given with a `^` in front of them. The output is given in reverse chronological order by default.
You can think of this as a set operation. Commits given on the command line form a set of commits that are reachable from any of them, and then commits reachable from any of the ones given with `^` in front are subtracted from that set. The remaining commits are what comes out in the command's output. Various other options and paths parameters can be used to further limit the result.
Thus, the following command:

        $ git rev-list foo bar ^baz
means "list all the commits which are reachable from `foo` or `bar`, but not from `baz`".
A special notation `<commit1>..<commit2>` can be used as a shorthand for `^<commit1> <commit2>`. For example, either of the following may be used interchangeably:

        $ git rev-list origin..HEAD
        $ git rev-list HEAD ^origin

Another special notation is `<commit1>...<commit2>` which is useful for merges. The resulting set of commits is the symmetric difference between the two operands. The following two commands are equivalent:

        $ git rev-list A B --not $(git merge-base --all A B)
        $ git rev-list A...B
`rev-lsit` is a very essential Git command, since it provides the ability to build and traverse commit ancestry graphs. For this reason, it has a lot of different options that enables it to be used by commands as different as `git bisect` and `gi repack`.

#### Options
##### Commit Limiting
Besides specifying a range of commits that should be listed using the special notations explained in the description, additional commit limiting may be applied.
Using more options generally further limits the output (e.g. `--since=<date1>` limits to commits newer than `<date1>`, and using it with `--grep=<pattern>` further limits to commits whose log message has a line that matches `<pattern>`), unless otherwise noted.
Note that these are applied before commit ordering and formatting options, such as `--reverse`.
* `-<number>`, `-n <number>`, `--max-count=<number>`
    Limit the number of commits to output.
* `--skip=<number>`
    Skip *number* commits before starting to show the commit output.
* `--since=<date>`,`--after=<date>`
    Show commits more recent than a specified date.
* `--until=<date>`, `--before=<date>`
    Show commits older than a specific date.
* `--max-age=<timestamp>`, `--min-age=<timestamp>`
    Limit the commits output to specified time range.
* `--author=<pattern>`, `--committer=<pattern>`
    Limit the commits output to ones with author/committer header lines that match the specified pattern (regular expression). With more than one `--author=<pattern>`, commits whose author matches any of the given patterns are chosen (similarly for multiple `--committer=<pattern>`).
* `--grep-reflog=<pattern>`
    Limit the commits output to ones with reflog entries that match the specified pattern (regular expression). With more than one `--grep-reflog`, commits whose reflog message matches any of the given patterns are chosen. It is an error to use this option unless `--walk-reflogs` is in use.
* `--grep=<pattern>`
    Limit the commits output to ones with log message that matches the specified pattern (regular expression). With more than one `--grep=<pattern>`, commits whose message matches any of the given patterns are chosen (but see `--all-match`).
* `--all-match`
    Limit the commits output to ones that match all given `--grep`, instead of ones that match at least one.
* `--invert-grep`
    Limit the commits output to ones with log message that do not match the pattern specified with `--grep=<pattern>`.
* `-i`, or `--regexp-ignore-case`
    Match the regular expression limiting patterns without regard to letter case.
* `--basic-regexp`
    Consider the limiting patterns to be basic regular expressions; this is the default.
* `-E`, or `--extended-regexp`
    Consider the limiting patterns to be extended regular expressions instead of the default basic regular expressions.
* `-F`, or `--fixed-strings`
    Consider the limiting patterns to be fixed strings (don't interpret pattern as a regular expression).
* `--remove-empty`
    Stop when a given path disappears from the tree.
* `--merges`
    Print only merge commits. This is exactly the same as `--min-parents=2`.
* `--no-merges`
    Do not print commits with more than one parent. This is exactly the same as `--max-parents=1`.
* `--min-parents=<number>`, `--max-parents=<number>`, `--no-min-parents`, `--no-max-parents`
    Show only commits which have at least (or at most) that many parent commits. In particular, `--max-parents=1` is the same as `--no-merges`, `--min-parents=2` is the same as `--merges`. `--max-parents=0` gives all root commits and `--min-parents=3` all octopus merges.
    `--no-min-parents` and `--no-max-parents` reset these limits (to no limit) again. Equivalent forms are `--min-parents=0` (any commit has 0 or more parents) and `--max-parents=-1` (negative numbers denote no upper limit).
* `--first-parent`
    Follow only the first parent commit upon seeing a merge commit. This option can give a better overview when viewing the evolution of a particular topic branch, because merges into a topic branch tend to be only about adjusting to updated upstream from time to time, and this option allows you to ignore the individual commits brought in to your history by such a merge. Cannot be combined with `--bisect`.
* `--not`
    Reverses the meaning of the `^` prefix (or lack thereof) for all following revision specifiers, up to the next `--not`.
* `--all`
    Pretend as if all the refs in `refss/`, along with `HEAD`, are listed on the command line as `<commit>`.
* `--branches[=<pattern>]`
    Pretend as if all the refs in `refs/heads` are listed on the command line as `<commit>`. If `<pattern>` is given, limit branches to ones matching given shell glob. If pattern lacks `?,` `*,` or `[,` `/*` at the end is implied.
* `--tags[=<pattern>]`
    Pretend as if all the refs in `refs/tags` are listed on the command line as `<commit>`. If `<pattern>` is given, limit tags to ones matching given shell glob. If pattern lacks `?`, `*`, or `[`, `/*` at the end is implied.
* `--remotes[=<pattern>]`
    Pretend as if all the refs in `refs/remotes` are listed on the command line as `<commit>`. If `<pattern>` is given, limit remote-tracking branches to ones matching given shell glob. If pattern lacks `?`, `*`, or `[`, `/*` at the end is implied.
* `--glob=<glob-pattern>`
    Pretend as if all the refs matching shell glob `<glob-pattern>` are listed on the command line as `<commit>`. Leading `refs/` is automatically prepended if missing. If pattern lacks `?`, `*`, or `[`, `/*` at the end is implied.
* `--exclude=<glob-pattern>`
    Do not include refs matching `<glob-pattern>` that the next `--all`, `--branches`, `--tags`, `--remtoes`, or `--glob` would otherwise consider.
    The patterns given should not begin with `refs/heads`, `refs/tags`, or `refs/remotes` when applied to `--branches`, `--tags`, or `--remotes`, respectively, and they must begin with `refs/` when applied to `--glob` or `--all`. If a trailing `/*` is intended, it must be given explicitly.
* `--reflog`
    Pretend as if all objects mentioned by reflogs are listed on the command line as `<commit>`.
* `--single-worktree`
    Be default, all working trees will be examined by the following options when there are more than one: `--all`, `--reflog` and `--indexed-bojects`. This option forces them to examine the current working tree only.
* `--ignore-missing`
    Upon seeing an invalid object name in the input, pretend as if the bad input was not given.
* `--stdin`
    In addition to the `<commit>` listed on the command line, read them from the standard input. If a `--` separator is seen, stop reading commits and start reading paths to limit the result.
* `--quiet`
    Don't print anything to standard output. This form is primarily meant to allow the caller to test the exit status to see if a range of objects is fully connected (or not). It is faster than redirecting stdout to `/dev/null` as the output does not have to be formatted.
* `--cherry-pick`
    Omit any commit that introduces the same change as another commit on the "other side" when the set of commits are limited with symmetric difference.
    For example, if you have two branches, `A` and `B`, a usual way to list all commits on only one side of them is with `--left-right` (see the example below in the description of the `--left-right` option). However, it shows the commits that were cherry-picked from the other branch (for example, `3rd on b` may be cherry-picked from branch `A`). With this option, such pairs of commits are excluded from the output. With this option, such pairs of commits are excluded from the output.
* `--cherry-mark`
    Like `--cherry-pick` (see above) but mark equivalent commits with `=` rather than omitting them, and inequivalent ones with `+`.
* `--left-only`, `--right-only`
    List only commits on the respective side of a symmetric difference, i.e only those which would be marked `<` resp. `>` by `--left-right`.
    For example, `--cherry-pick --right-only A...B` omits those commits from `B` which are in `A` or are patch-equivalent to a commit in `A`. In other words, this lists the `+` commits from `git cherry A B`. More precisely, `--cherry-pick --right-only --no-merges` gives the exact list.
* `--cherry`
    A synonym for `--right-only --cherry-mark --no-merges`; useful to limit the output to the commits on our side and mark those that have been applied to the other side of a forked history with `git log --cherry upstream...mybranch`, similar to `git cherry upstream mybranch`.



### 11.2 `man git rev-parse`
#### NAME
git-rev-parse: Pick out and message parameters

#### Synopsis
`git rev-parse [--option] <args>...`

#### Description

### 11.3 `man git reflog`

#### NAME
git-reflog: Manage reflog information.

#### Synopsis
`git reflog <subcommand> <options>`

#### Description
The command takes various subcommands, and different options depending on the subcommand:

        git reflog [show] [log-options] [<ref>]
        git reflog expire [--expire=<time>] [--expire-unreachable=<time>] [--rewrite] [--updateref] [--stale-fix] [--dry-run | -n] [--verbose] [--all | <refs>...]
        git reflog delete [--rewrite] [--updateref] [--dry-run | -n] [--verbose] ref@{specifier}...
        git reflog exsists <ref>
Reference logs, or "reflogs", record when the tips of branches and other references were updated in the local repository. Reflogs are useful in various Git commands, to specify the old value of a reference. For example, `HEAD@{2}` means "where HEAD used to be two moves ago", `master@{one.week.ago}` means "where master used to point to one week ago in this local repository", and so on. See [gitrevisions](#gitrevisions) for more details.
This command manages the information recorded in the reflogs.
The `show` subcommand (which is also the default, in the absence of any subcommands) shows the log of the reference provided in the command-line (or `HEAD`, by default). The reflog covers all recent actions, and in addition the `HEAD` reflog records branch switching. `git reflog show` is an alias for `git log -g --abbrev-commit --pretty=oneline`; see git-log for more information.
The `expire` subcommand prunes older reflog entries. Entries older than `expire` time, or entries older than `expire-unreachable` time and not reachable from the current tip, are removed from the reflog. This is typically not used directly by end users-instead, see git-gc.
The `delete` subcommand deletes single entries from the reflog. Its argument must be an *exact* entry (e.g. `git reflog delete master@{2}`). This subcommand is also typically not used directly by end users.
The `exist` subcommand checks whether a ref has a reflog. It exits with zero status if the reflog exists, and non-zero status if it does not.

#### Options
##### Options for `show`
`git reflog show` accepts any of the options accepted by `git log`.
![git reflog](reflog.png)
![git reflog --all](reflog-all.png)

##### Options for `expire`
* `--all`
    Process the reflogs of all references.
* `--expire=<time>`
    Prune entries older than the specified time. If this option is not specified, the expiration time is taken from the configuration setting `gc.reflogExpire`, which in turn defaults to 90 days. `--expire=all` prunes entries regardless of their age; `--expire=never` turns off pruning of reachable entries (but see `--expire-unreachable`).
* `--expire-unreachable=<time>`
    Prune entries older than `<time>` that are not reachable from the current tip of the branch. If this option is not specified, the expiration time is taken from the configuration setting `gc.reflogExpireUnreachable`, which in turn defaults to 30 days. `--expire-unreachable=all` prunes unreachable entries regardless of their age; `--expire-unreachable=never` turns off early pruning of unreachable entries (but see `--expire`).
* `--updateref`
    Update the reference to the value of the top reflog entry (i.e. `<ref>@{0}`) if the previous top entry was pruned. (This option is ignored for symbolic references.)
* `--rewrite`
    If a reflog entry's predecessor is pruned, adjust its "old" SHA-1 to be equal to the "new" SHA-1 field of the entry that now precedes it.
* `--stale-fix`
    Prune any reflog entries that point to "broken commits". A broken commit is a commit that is not reachable from any of the reference tips and that refers, directly or indirectly, to a missing commit, tree, or blob object.
    This computation involves traversing all the reachable objects, i.e. it has the same cost as `git prune`. It is primarily intended to fix corruption caused by garbage collection using older versions of Git, which didn't protect objects referred to by reflogs.
* `-n`, or `-dry-run`
    Do not actually prune any entries; just show what would have been pruned.
* `--verbose`
    Print extra information on screen.

##### Options for `delete`
`git reflog delete` accepts options `--updateref`, `--rewrite`, `-n`, `--dry-run`, and `--verbose`, with the same meaning as when they are used with `expire`.
### 11.4 `man git branch`
#### NAME
`git branch`: List, create, or delete branches.

#### Synopsis

        git branch [--color[=<when>] | --no-color] [-r | -a] [--list] [-v [--abbrev=<length> | --no-abbrev]] [--column[=<options>] | --no-column] [(--merged | --no-merged | --contains) [<commit>]] [--sort=<key>] [--points-at <object>] [<pattern>...]
        git branch [--set-upstream | --track | --no-track] [-l] [-f] <branchname> [<start-point>]
        git branch (--set-upstream-to=<upstream> | -u <upstream>) [<branchname>]
        git branch --unset-upstream [<branchname>]
        git branch (-m | -M) [<oldbranch>] <newbranch>
        git branch (-d | -D) [-r] <branchname>...
        git branch --edit-description [<branchname>]

#### Description
If `--list` is given, or if there are no non-option arguments, existing branches are listed; the current branch will be highlighted with an asterisk. Option `-r` causes the remote-tracking branches to be listed,and option `-a` shows both local and remote branches.
![git branch --list](git_branch_list.png)
If a `<pattern>` is given, it is used as a shell wildcard to restrict the output to matching branches. If multiple patterns are given, a branch is shown if it matches any of the patterns. Note that when providing a `<pattern>`, you must use `--list`; otherwise the command is interpreted as branch creation.
With `--contains`, shows only the branches that contain the named commit (in other words, the branches whose tip commits are descendants of the named commit). With `--merged`, only branches merged into the named commit (i.e. the branches whose tip commits are reachable from the named commit) will be listed. With `--no-merged` only branches not merged into the named commit will be listed. If the `<commit>` argument is missing it defaults to `HEAD` (i.e. the tip of the current branch).
The command's second form creates a new branch head named `<branchname>` which points to the current `HEAD`, or `<start-point>` if given.
Note that this will create the new branch, but it will not switch the working tree to it; use `git checkout <newbranch>` to switch to the new branch.
When a local branch is started off a remote-tracking branch, Git sets up the branch (specifically the `branch.<name>.remote` and `branch.<name>.merge` configuration entries) so that `git pull` will appropriately merge from the remote-tracking branch. [See branch refspecs](#branch_refspecs) This behavior may be changed via the global `branch.autoSetupMerge` configuration flag. That setting can be overridden by using the `--track` and `--no-track` options, and changed later using `git branch --set-upstream-to`.
With a `-m` or `-M` option, `<oldbranch>` will be renamed to `<newbranch>`. If `<oldbranch>` had a corresponding reflog, it is renamed to match `<newbranch>`, and a reflog entry is created to remember the branch renaming. If `<newbranch>` exists, `-M` must be used to force the rename to happen.
With `-d` or `-D` option, `<branchname>` will be deleted. You may specify more than one branch for deletion. If the branch currently has a reflog then the reflog will also be deleted.
Use `-r` together with `-d` to delete remote-tracking branches. Note, that it only makes sense to delete remote-tracking branches if they no longer exist in the remote repository or if `git fetch` was configured not to fetch them again. See also the `prune` subcommand of `git remote` for a way to clean up all obsolete remote-tracking branches.



#### Options
* `-d`, `--delete`
    Delete a branch. The branch must be fully merged in its upstream branch, or in `HEAD` if no upstream was set with `--track` or `--set-upstream`.
* `-D`
    Shortcut for `--delete --force`.
* `-l`, `--create-reflog`
    Create the branch's reflog. This activates recording of all changes made to the branch ref, enabling use of date based sha1 expressions such as `<branchname>@{yesterday}`. Note that in non-bare repositories, reflogs are usually enabled by default by the `core.logallrefupdates` comfig option.
* `-f`, `--force`
    Reset `<branchname>` to `<startpoint>` if `<branchname>` exists already. Without `-f` git branch refuses to change an existing branch. In combination with `-d` (or `--delete`), allow deleting the branch irrespective of its merged status. In combination with `-m` (or `--move`), allow renaming the branch even if the new branch name already exists.
* `-m`, `--move`
    Move/rename a branch and the corresponding reflog.
* `-M`
    Shortcut for `--move --force`.
* `--color[=<when>]`
    Color branches to highlight current, local, and remote-tracking branches. The value must be always (the default), never, or auto.
* `--no-color`
    Turn off branch colors, even when the configuration file gives the default to color output. Same as `--color=never`.
* `--column[=<options>]`, `--no-column`
    Display branch listing in columns. See configuration variable `column.branch` for option syntax. `--column` and `--no-column` without options are equivalent to `always` and `never` respectively.
    This option is only applicable in non-verbose mode.
* `-r`, `--remotes`
    List or delete (if used with `-d`) the remote-tracking branches.
* `-a`, `--all`
    List both remote-tracking branches and local branches.
* `--list`
    Active the list mode.`git branch <pattern>` would try to create a branch, use `git branch --list <pattern>` to list matching branches.
* `-v`, `-vv`, `--verbose`
    When in list mode, show sha1 and commit subject line for each head, along with relationship to upstream branch (if any). If given twice, print the name of the upstream branch, as well (see also `git remote show <remote>`).
* `-q`, `--quiet`
    Be more quiet when creating or deleting a branch, suppressing non-error messages.
* `--abbrev=<length>`
    Alter the sha1's minimum display length in the output listing. The default value is 7 and be overridden by the `core.abbrev` config option.
* `--no-abbrev`
    Display the full sha1s in the output listing rather than abbreviation them.
* `-t`, `--track`
    When creating a new branch, set up `branch.<name>.remote` and `branch.<name>.merge` configuration entries to mark the start-point branch as "upstream" from the new branch. This configuration will tell git to show the relationship between the two branches in `git status` and `git branch -v`. Furthermore, it directs `git pull` without arguments to pull from the upstream when the new branch is checked out.
    This behavior is the default when the start point is a remote-tracking branch. Set the `branch.autoSetupMerge` configuration variable to `false` if you want `git checkout` and `git branch` to always behave as if `--no-track` were given. Set it to `always` if you want this behavior when the start-point is either a local or remote-tracking branch.
* `--no-track`
    Do not set up "upstream" configuration, even if the `branch.autoSetupMerge` configuration variable is true.
* `--set-upstream`
    If specified branch does not exist yet or if `--force` has been given, acts exactly like `--track`. Otherwise  sets up configuration like `--track` would when creating the branch, except that where branch points to is not changed.
* `-u <upstream>`, `--set-upstream-to=<upstream>`
    Set up `<branchname>`'s tracking information, so `<upstream>` is considered `<branchname>`'s upstream branch. If no `<branchname>` is specified, then it defaults to the current branch.
* `--unset-upstream`
    Remove the upstream information for `<branchname>`. If no branch is specified it defaults to the current branch.
* `--edit-description`
    Open an editor and edit the text to explain what the branch is for, to be used by various other commands (e.g. `format-patch`, `request-pull`, and `merge` (if enabled)). Multi-line explanations may be used.
* `--contains [<commit>]`
    Only list branches which contain the specified commit (`HEAD` if not specified). Implies `--list`.
* `--merged [<commit>]`
    Only list branches whose tips are reachable from the specified commit (`HEAD` if not specified). Implies `--list`.
* `--no-merged [<commit>]`
    Only list branches whose tips are not reachable from the specified commit (`HEAD` if not specified). Implies `--list`.
* `<branchname>`
    The name of the branch to create or delete. The new branch name must pass all checks defined by `git-check-ref-format`. Some of these checks may restrict the characters allowed in a branch name.
* The new branch head will point to this head. It may be given as a branch name, a commit-id, or a tag. If this option is omitted, the current `HEAD` will be used instead.
* `<oldbranch>`
    The name of an existing branch to rename.
* `<newbranch>`
    The new name for an existing branch. The same restrictions as for `<branchname>` apply.
* `-sort=<key>`
    Sort based on the key given. Prefix `-` to sort in descending order of the value. You may use the `--sort=<key>` option multiple times, in which case the last key becomes the primary key. The keys supported are the same as those in `git for-each-ref`. Sort order defaults to sorting based on the full refname (including `ref/...` prefix). This lists detached `HEAD` (if present) first, then local branches and finally remote-tracking branches.
* `--points-at <object>`
    Only list branches of the given object.???

#### Examples
Start development from a known tag

        $ git clone git://git.kernel.org/pub/scm/.../linux-2.6 my2.6
        $ cd my2.6
        $ git branch my2.6.14 v2.6.14 (1)
        $ git checkout my2.6.14
1. This step and the next one could be combined into a single step with `checkout -b my2.6.14 v.2.6.14`.

Delete an unneeded branch

        $ git clone git://git.kernel.org/.../git.git my.git
        $ cd my.git
        $ git branch -d -r origin/todo origin/html origin/man   (1)
        $ git branch -D test
1. Delete the remote-tracking branches `todo`, `html` and `man`. The next `fetch` or `pull` will create them again unless you configure them not to. See `git fetch`.
2. Delete the `test` branch even if the `master` branch (or whichever branch is currently checked out) does not have all commits from the `test` branch.

#### Notes
If you are creating a branch that you want to checkout immediately, it is easier to use the `git checkout` command with its `-b` option to create a branch and check it out with a single command.
The options `--contains`, `--merged` and `--no-merged` serve three related but different purposes:
* `--contains <commit>` is used to find all branches which will need special attention if `<commit>` were to be rebased or amended, since those branches contain the specified `<commit>`.
* `--merged` is used to find all branches which can be safely deleted, since those branches are fully contained by `HEAD`.
* `--no-merged` is used to find branches which are candidates for merging into HEAD, since those branches are not fully contained by `HEAD`.

### 11.4 `man git log`
#### Name
`git log`: Show commit logs

#### Synopsis
`git log [<options>] [<resvision range>] [[--] <path>...]`

#### Description
Shows the commit logs.
The command takes options applicable to the `git rev-list` command to control what is shown and how, and options applicable to the `git diff-*` commands to control how the changes each commit introduces are shown.

#### Options
* `--follow`
    Continue listing the history of a file beyond renames (works only for a single file).
* `--no-decorate`, `--decorate[=short|full|auto|no]`
    Print out the ref names of any commits that are shown. If `short` is specified, the ref name prefixes `refs/heads/`, `refs/tags/` and `refs/remotes` will not be printed. If `full` is specified, the full ref name (including prefix) will be printed. If `auto` is specified, then if the output is going to terminal, the ref names are shown as if `short` were given, otherwise no ref names are shown. The default option is `short`.
* `--source`
    Print out the ref name given on the command line by which each commit was reached.
* `--use-mailmap`
    Use mailmap file to map author and committer names and email addresses to canonical real names and email addresses.
    The `.mailmap` feature is used to coalesce together commits by the same person in the shortlog, where their name and/or email address was spelled differently.
    If the file `.mailmap` exists at the toplevel of the repository, or at the location pointed to by the `mailmap.file` or `mailmap.blob` configuration options, it is used to map author and committer names and email addresses to canonical real names and email addresses.
    In the simple form, each line in the file consists of the canonical real name of an author, whitespace, and an email address used in the commit (enclosed by `<` and `>`) to map to the name. For example:
    `Proper Nmae <commit@email.xx>`
    The more complex forms are:
    `<proper@email.xx> <commit@email.xx>`
    which allows mailmap to replace only the email part of a commit, and:
    `Proper Name <propter@email.xx> <commit@email.xx>`
    which allows mailmap to replace both the name and the email of a commit matching the specified commit email address, and:
    `Proper Name <proper@email.xx> Commit Name <commit@email.xx>`
    which allows mailmap to replace both the name and the email of a commit matching both the specified commit name and email address.
    Example 1: Your history contains commits by two authors, Jane and Joe, whose names appear in the repository under several forms:
    `Joe Developer <joe@example.com>`
    `Joe R. Developer <joe@example.com>`
    `Jane Doe <jane@example.com>`
    `Jane Doe <jane@laptop.(none)>`
    `Jane D. <jane@desktop.(none)>`
    Now suppose that Joe wants his middle name initial used, and Jane prefers her family name fully spelled out. A proper `.mailmap` file would look like:
    `Jane Doe <jane@destop.(none)>`
    `Joe R. Developer <joe@example.com>`
    Note how there is no need or an entry for `<jane@laptop.(none)>`, because the real name of that author is already correct.
    Example 2: Your repository contains commits from the following authors:
    `nick1 <bug@company.xx>`
    `nick2 <bug@company.xx>`
    `nick2 <nick2@company.xx>`
    `santa <me@company.xx>`
    `claus <me@company.xx>`
    `CTO <cto@coompany.xx>`
    Then you might want a `.mailmap` file that looks like:
    `<cto@company.xx>       <cto@coompany.xx>`
    `Some Dude <some@dude.xx>       nick1 <bugs@company.xx>`
    `Other Author <other@author.xx>    nick2 <bugs@company.xx>`
    `Other Authorr <other@author.xx>    <nick2@company.xx>`
    `Santa Claus <santa.claus@northpole.xx> <me@company.xx>`
    Use hash `#` for comments that are either on their own line, or after the email address.
* `--full-diff`
    Without this flag, `git log -p <path>...` shows commits that touch the specified paths, and diff about the same specified paths. With this, the full diff is shown for commits that touch the specified paths; this means that `<path>...` limits only commits, and doesn't limit diff for those commits.
* `-L <start>,<end>:<file>`, `-L :<funcname>:<file>`
    Trace the evolution of the line range given by `<start>,<end>` (or the function name regex `<funcname>`) within the `<file>`. You may not give any pathspec limiters. This is currently limited to a walk starting from a single revision, i.e., you may only give zero or one positive revision arguments. You can specify this option more than once.
    * `<start>` or `<end>` is number, it specifies an absolute line number (lines count from 1).
    * `/regex/`
        This form will use the first line matching the given POSIX regex. If `<start>` is a regex, it will search from the end of the previous `-L` range, if any, otherwise from the start of file. If `<start>` is `^/regex/`, it will search from the start of file. If `<end>` is a regex, it will search starting at the lien given by `<start>`.
    * `+offset`, or `-offset`
        This is only valid for `<end>` and will specify a number of lines before or after the lien given by `<start>`.
    If `:<funcname>` is given in place of `<start>` and `<end>`, it is a regular expression that denotes the range form the first funcname line that matches `<funcname>`, up to the next funcname line.
    `:<funcname>` searches from the end of the previous `-L` range, if any, otherwise from the start of file. `^:<funcname>` searches from the start of file.
* `<revision range>`
    Show only commits in the specified revision range. When no `<revision range>` is specified, it defaults to `HEAD` (i.e. the whole history leading to the current commit). `origin..HEAD` specifies all the commits reachable from the current commit (i.e. `HEAD`), but not from `origin`. For a complete list of ways to spell `<revision range>`, see the *Specifying Ranges* section of `gitrevisions`.
* `[--] <path>...`
    Show only commits that are enough to explain how the files that match the specified paths came to be. See *History Simplification* below for details and other simplification modes.
    Paths may need to be prefixed with `--` to separate them from options or the revision range, when confusion arises.

#### Commit Limiting
Besides specifying a range of commits that should be listed using the special notations explained in the description, additional commit limiting may be applied.
Using more options generally further limits the output (e.g. `--since=<date1>` limits to commits newer than `<date1>`, and using it with `--grep=<pattern>` further limits to commits whose log message has a line that matches `<pattern>`), unless otherwise noted.
Note that these are applied before commit ordering and formatting options, such as `--reverse`.




### 11.5 `man git cherry-pick`
#### NAME
`git cherry-pick`: Apply the changes introduced by some existing commits.

#### Synopsis

        git cherry-pick [--edit] [-n] [-m parent-number] [-s] [-x] [--ff] [-S[<keyid>]] <commit>...
        git cherry-pick --continue
        git cherry-pick --quit
        git cherry-pick --abort

#### Description
Given one or more existing commits, apply the change each one introduces, recording a new commit for each. This requires your working tree to be clean (no modifications from the `HEAD` commit).
When it is no obvious how to apply a change, the following happens:
1. The current branch and `HEAD` pointer stay at the last commit successfully made.
2. The `CHERRY_PICK_HEAD` ref is set to point at the commit that introduced the change that is difficult to apply.
3. Paths in which the change applied cleanly are updated both in the index file and in your working tree.
4. For conflicting paths, the index file records up to three versions, as described in the "TRUE MERGE" section of git-merge. The working tree files will include a description of the conflict bracketed by the usual conflict markers `<<<<<<<` and `>>>>>>>`.
5. No other modifications are made.
See git-merge for some hints on resolving such conflicts.

### 11.5 `man git merge`
#### NAME
`git merge`: Join two or more development histories together.

#### Synopsis

        git merge [-n] [--stat] [--no-commit] [--squash] [--[no-]edit] [-s <strategy>] [-X <strategy-option>] [-S [<keyid>]] [--[no-]allow-unrelated-histories] [--[no-]rerere-autoupdate] [-m <msg>] [<commit>...]
        git merge <msg> HEAD <commit>...
        git merge --abort
        git merge --continue

#### Description
**Incorporates changes from the named commits (since the time their histories diverged from the current branch)** **into the current branch**. This command is used by `git pull` to incorporate changes from another repository and can be used by hand to merge changes from one branch into another.
Assume the following history exists and the current branch is `master`:


                     A---B---C topic
                    /
               D---E---F---G master
Then `git merge topic` will replay the changes made on the `topic` branch since it diverged from `master` (i.e., `E`) until its current commit (`C`) on top of `master`, **and record the result in a new commit along with the names of the two parent commits and a log message from the user describing the changes.**


                     A---B---C topic
                    /         \
               D---E---F---G---H master
The second syntax (`<msg> HEAD <commit>...`) is supported for historical reasons. Do not use it from the command line or in new scripts. It is the same as `git merge -m <msg> <commit>...`.
The third syntax (`git merge --abort`) **can only be run after the merge has resulted in conflicts.** `git merge --abort` **will abort the merge process and try to reconstruct the pre-merge state.** However, **if there were uncommitted changes when the merge started (and especially if those changes were further modified after the merge was started), `git merge --abort` will in some cases be unable to reconstruct the original (pre-merge) changes.** Therefore:
**Warning**: Running `git merge` with non-trivial uncommitted changes is discouraged: while possible, it may leave you in a state that is hard to back out of in the case of a conflict.

#### Options
* `--commit`, `--no-commit`
    Perform the merge and commit the result. This option can be used to override `--no-commit`.
    **With `--no-commit` perform the merge but pretend the merge failed and do not autocommit, to give the user a chance to inspect and further tweak the merge result before committing.**
* `--edit`, `-e`, `--no-edit`
    **Invoke an editor before committing successful mechanical merge to further edit the auto-generated merge message**, so that the user can explain and justify the merge. **The `--no-edit` option can be used to accept the auto-generated message** (this is generally discouraged). The `--edit` (or `-e`) option is still useful if you are giving a draft message with the `-m` option from the command line and want to edit it in the editor.
    Older scripts may depend on the historical behavior of not allowing the user to edit the merge log message. They will see an editor opened when they run `git merge`. To make it easier to adjust such scripts to the updated behavior, the environment variable `GIT_MERGE_AUTOEDIT` can be set to `no` at the beginning of them.
* `-ff`
    **When the merge resolves as a fast-forward**, only update the branch pointer, without creating a merge commit. This is the default behavior.
* `--no-ff`
    Create a merge commit even when the merge resolves as a fast-forward. This is the default behavior when merging an annotated (and possibly signed) tag.
* `--ff-only`
    **Refuse to merge and exit with a non-zero status unless the current `HEAD` is already up-to-date or the merge can be resolved as a fast-forward.**
* `--log[=<n>]`, `--no-log`
    **In addition to branch names, populate the log message with one-line descriptions from at most <n> actual commits that are being merged.** See also `git-fmt-merge-msg`.
    **With `--no-log` do not list one-line descriptions from the actual commits being merged**.
* `--stat`, `-n`, `--no-stat` ???
    **Show a diffstat at the end of the merge.** The diffstat is also controlled by the configuration option merge.stat.
    With `-n` or `--no-stat` do not show a diffstat at the end of the merge.
* `--squash`, `--no-squash`
    **Produce the working tree and index state as if a real merge happened (except for the merge information), but do not actually make a commit, move the `HEAD`, or record `$GIT_DIR/MERGE_HEAD` (to cause the next `git commit` command to create a merge commit).** This allows you to create a single single commit on top of the current branch whose effect is the same as merging another branch (or more in case of an octopus).
    **With `--no-squash` perform the merge and commit the result.** This option can be used to override `--squash`.
    This is a way to merge all changes from one branch into another, but squash to a single commit at the same time.
    A word of caution: this works, but the default commit message includes the log from the branch being merged. The problem is it looks similar to the format you normally see where the entire text shown does not actually become part of the commit message, but in this case it does. So if you don't want all that, you need manually remove all of it from your commit message. I should have tested this before using it.
* `-s <strategy>`, `--strategy=<strategy>`
    Use the given merge strategy; can be supplied more than once to specify them in the order they should be tried. **If there is no `-s` option, a built-in list of strategies is used instead (`git merge-recursive` when merging a single head, `git merge-octopus` otherwise)**.
* `-X <option>`, `--strategy-option=<option>`
    Pass merge strategy specific option through to the merge strategy.
    `git merge -s recursive -X ours` and `git merge -X ours` both are OK.
* `--summary`, `--no-summary`
    Synonyms to `--stat` and `--no-stat`; these are deprecated and will be remove in the future.
* `-q`, `--quiet`
    Operate quietly. Implies `--no-progress`.
* `-v`, `--verbose`
    Be verbose.
* `--progress`, `--no-progress`
    Turn progress on/off explicitly. If neither is specified, progress is shown if standard error is connected to a terminal. Note that not all merge strategies may support progress reporting.
* `--allow-unrelated-histories`
    By default, `git merge` command refuses to merge histories that do not share a common ancestor. This option can be used **to override this safety when merging histories of two projects that started their lives independently.** As that is a very rare occasion, no configuration variable to enable this be default exists and will not be added.
* `-S[<keyid>]`, `--gpg-sign[=<keyid>]`
    GPG-sign the resulting merge commit. The `<keyid>` argument is optional and defaults to the committer identity; if specified, it must be stuck to the option without a space.
* `-m <msg>`
    Set the commit message to be used for the merge commit (in case one is created).
    **If `--log` is specified, a shortlog of the commits being merged will be appended to the specified message.**
    The `git fmt-merge-msg` command can be used to give a good default for automated `git merge` invocations. The automated message can include the branch description.
* `--[no-]rerere-autoupdate`
    Allow the rerere mechanism to update the index with the result of auto-conflict resolution if possible.
    `git rerere`: Reuse recorded resolution of conflicted merges.
* `--abort`
    Abort the current conflict resolution process, and try to reconstruct the pre-merge state.
    If there were uncommitted worktree changes present when the merge started, `git merge --abort` will in some cases be unable to reconstruct these changes. **It is therefore recommended to always commit or stash your changes before running `git merge`.**
    **`git merge --abort` is equivalent to `git reset --merge` when `MERGE_HEAD`is present.**
* `<commit>...`
    Commits, usually other branch heads, to merge into our branch. Specifying more than one commit will create a merge with ore than two parents (affectionately called an Octopus merge).
    **If no commit is given from the command line, merge the remote-tracking branches that the current branch is configured to use as its upstream.** See also the configuration section of this manual page.
    **When `FETCH_HEAD` (and no other commit) is specified, the branches recorded in the `.git/FETCH_HEAD` file by the previous invocation of `git fetch` for merging are merged to the current branch.**

#### PRE-MERGE CHECKS
Before applying outside changes, you should **get your own work in good shape and committed locally**, so it will not be clobbered if there are conflicts. See also `git-stash`. `git pull` and `git merge` will stop without doing anything when local uncommitted changes overlap with files that `git pull`/`git merge` may need to update.
To avoid recording unrelated changes in the merge commit, `git pull` and `git merge` will also abort if there are any changes registered in the index relative to the `HEAD` commit. (One exception is when the changed index entries are in the state that would result from the merge already.)
**If all named commits are already ancestors of `HEAD`, `git merge` will exit early with the message "Already up-to-date."**

#### FAST-FORWARD MERGE
Often the current branch head is an ancestor of the named commit. This is the most common case especially when invoked from `git pull`: you are tracking an upstream repository, you have committed no local changes, and now you want to update to a newer upstream revision. In this case, a new commit is not needed to store the combined history; instead, **the `HEAD` (along with the index) is updated to point at the named commit, without creating an extra merge commit.**
This behavior **can be suppressed with the `--no-ff` option.**

#### TRUE MERGE
Except in a fast-forward merge (see above), the branches to be merged must be tied together by a merge commit that has both of them as its parents.
**A merged version reconciling the changes from all branches to be merged is committed, and your `HEAD`, index, and working tree are updated to it. It is possible to have modifications in the working tree as long as they do not overlap; the update will preserve them.**
When it is not obvious how to reconcile changes, for following happens:
**1. The `HEAD` pointer stays the same.**
**2. The `MERGE_HEAD` ref is set to point to the other branch head.**
**3. Paths that merged cleanly are updated both in the index file and in your working tree.**
**4. For conflicting paths, the index file records up to three versions: stage 1 stores the version from the common ancestor, stage 2 from `HEAD`, and stage 3 from `MERGE_HEAD` (you can inspect the stages with `git ls-files -u`). The working tree files contain the result of the "merge" program; i.e. 3-way merge results with familiar conflict markers `<<<===>>>`.**
**5. No other changes are made.** In particular, the local modifications you had before you started merge will stay the same and the index entries for them stay as they were, i.e. matching `HEAD`.
If you tried a merge which resulted in complex conflicts and want to start over, you can recover with `git merge --abort`.

#### MERGING TAG
**When merging an annotated (and possibly signed) tag, Git always creates a merge commit even if a fast-forward merge is possible, and the commit message template is prepared with the tag message.** Additionally, if the tag is signed, the signature check is reported as a comment in the message template. See also `git-tag`.
When you want to just integrate with the work leading to the commit that happens to be tagged, e.g. synchronizing with an upstream release point, you may not want to make an unnecessary merge commit.
In such a case, you can "unwrap" the tag yourself before feeding it to `git merge`, or pass `--ff-only` when you do not have any work on your own.
e.g.

        git fetch origin
        git merge v1.2.3^0
        git merge --ff-only v1.2.3

#### How conflicts are presented
**During a merge, the working tree files are updated to reflect the result of the merge.** Among the changes made to the common ancestor's version, non-overlapping ones (that is, you changed and area of the file while the other side left that area intact, or vice versa) are incorporated in the final result verbatim. When both sides made changes to the same area, however, Git cannot randomly pick one side over the other, and asks you to resolve it by leaving what both sides did to that area.
By default, Git uses the same style as the one used by the "merge" program from the RCS suit to present such conflicted hunk, like this:

        Here are lines that are either unchanged from the common ancestor, or cleanly resolved because only one side changed.
        <<<<<<< yours:sample.txt
        Conflict resolution is hard;
        let's go shopping.
        =======
        Git makes conflict resolution easy.
        >>>>>>> theirs:sample.txt
        And here is another line that is cleanly resolved or unmodified.
The area where a pair of conflicting changes happened is marked with markers `<<<<<<<`, `=======`, and `>>>>>>>`. The part before the `=======` is typically your side, and the part afterwards is typically their side.
The default format does not show what the original said in the conflicting area. You cannot tell how many lines are deleted and replaced with Barbie's remark on your side. The only thing that you can tell is that your side wants to say it is hard and you'd prefer to go shopping, while the other side wants to claim it is easy.
An alternative style can be used by setting the `merge.conflictStyle` configuration variable to `diff3`. In `diff3` style, the above conflict may look like this:

        Here are lines that are either unchanged from the common ancestor, or cleanly resolved because only one side changed.
        <<<<<<<< yours:sample.txt
        Conflict resolution is hard;
        let's go shopping.
        |||||||
        Conflict  resolution is hard.
        =========
        Git makes conflict resolution eay.
        >>>>>>> theirs: sample.txt
        And here is another line tht is cleanly resolved or unmodified.
In addition to the `<<<<<<<`, `========`, and `>>>>>>>` markers, **it uses another `|||||||` marker that is followed by the original text.** You can tell that the original just stated a fact, and your side simply gave in to that statement and gave up, while the other side tried to have a more positive attitude. You can sometimes come up with a better resolution by viewing the original.

#### How to resolve conflicts
After seeing a conflict, you can do two things: 
* Decide not to merge. The only clean-ups you need are to reset the index file to the `HEAD` commit to reverse 2. and to clean up working tree changes made by 2. and 3.; `git merge --abort` can be used for this.
* Resolve the conflicts. Git will mark the conflicts in the working tree. **Edit the files into the shape and `git add` them to the index. Use `git commit` to seal the deal.**
You can work through the conflict with a number of tools:
* **Use a mergetool. `git mergetool` to launch a graphical mergetool which will work you through the merge.**
* **Look at the diffs. `git diff` will show a three-way diff, highlighting changes from both the `HEAD` and `MERGE_HEAD` versions.**
* **Look at the diffs from each branch. `git log --merge -p <path>` will show diffs first for the `HEAD` version and then the `MERGE_HEAD` version.**
* **Look at the originals. `git show :1:filename` shows the common ancestor, `git show :2:filename` shows the `HEAD` version, and `git show :3:filename` shows the `MERGE_HEAD` version.**

#### Examples
* Merge branches `fixes` and `enhancements` on top of the current branch, making an octopus merge.
    `$ git merge fixes enhancements`
* Merge branch `obsolete` into the current branch, using `ours` merge strategy:
    `$ git merge -s ours obsolete`
* Merge branch `maint` into the current branch, but do not make a new commit automatically:
    `$ git merge --no-commit maint`
    This can be used when you want to include further changes to the merge, or want to write your own merge commit message.
    You should refrain from abusing this options to sneak substantial changes into a merge commit. Small fixups like bumping release/version name would be acceptable.

#### MERGE STRATEGIES
The merge mechanism (`git merge` and `git pull` commands) allows the backend *merge strategies* to be chosen with `-s` option. Some strategies can also take their own options, which can be passed by giving `-X <option>` arguments to `git merge` and/or `git pull`.
* `resolve`
    This can only resolve two heads (i.e. the current branch and another branch you pulled from) using a 3-way merge algorithm. **It tries to carefully detect criss-cross merge ambiguities and is considered generally safe and fast.**
* `recursive`
    This can only resolve two heads using a 3-way merge algorithm. When there is more than one common ancestor that can be used for 3-way merge, it creates a merged tree of the common ancestors and uses that as the reference tree for the 3-way merge. **This is has been reported to result in fewer merge conflicts without causing mismerges by tests done on actual merge commits taken from Linux 2.6 kernel development history. Additionally this can detect and handle merges involving renames. This is the default merge strategy when pulling or merging one branch.**
    The recursive strategy can take the following options:
    * `ours`
        **This option forces conflicting hunks to be auto-resolved cleanly by favoring *our* version.** **Changes from the other tree that do not conflict with our side are reflected to the merge result. For a binary file, the entire contents are taken from our side.**
        **This should not be confused with the `ours` merge strategy, which does not even look at what the other tree contains at all. It discards everything the other tree did, declaring *our* history contains all that happened in it.**
    * `theirs`
        This is the opposite of `ours`.
    * `patience`
        **With this option, `merge-recursive` spends a little extra time to avoid mismerges that sometimes occur due to unimportant matching lines (e.g., braces from distinct functions). Use this when the branches to be merged have diverged wildly**. See also `git-diff --patience`.
    * `diff-algorithm=[patience|minimal|histogram|myers]`
        Tells `merge-recursive` to use a different diff algorithm, which can help avoid mismerges that occur due to unimportant matching liens (such as braces from distinct functions). See also `git-diff --diff-algorithm`.
    * `ignore-space-change`, `ignore-all-space`, `ignore-space-at-eol`
        **Treats lines with indicated type of whitespace change as unchanged for the sake of a three-way merge. Whitespace changes mixed with other changes to a line are not ignored.** See also `git-diff -b -w` and `--ignore-space-at-eol`.
        * If *their* version only introduces whitespace changes to a line, *our* version is used.
        * If *our* version introduces whitespace changes but *their* version includes a substantial change, *their* version is used;
        * Otherwise, the merge proceeds in the usual way.
    * `no-renames`
        **Turn off rename detection.** See also `git-diff --no-renames`.
    * `find-renames[=<n>]`
        **Turn on rename detection**, optionally setting the similarity threshold. This is the default. See also `git-diff --find-renames`.
* `octopus`
    **This resolves cases with more than two heads, but refuses to do a complex merge that needs manual resolution. It is primarily meant to be used for bundling topic branch heads together. This is the default merge strategy when pulling or merging more than one branch.**
* `ours`
    This resolves any number of heads, but the resulting tree of the merge is always that of the current branch head, It is meant to be used to supersede old development history of side branches. Note that this is different from the `-Xours` option to the `recursive` merge strategy.
* `subtree`???
    This is a modified recursive strategy. When merging trees A and B, if B corresponds to a subtree of A, B is first adjusted to match the tree structure of A, instead of reading the trees at the same level. This adjustment is also done to the common ancestor tree.
With the strategies that use 3-way merge (including the default, *recursive*), if a changes is made on both branches, but later reverted on one of the branches, that change will be present in the merged result; some people find this behavior confusing. It occurs because only the heads and the merge base are considered when performing a merge, not the individual commits. The merge algorithm therefore considers the reverted change as no change at all , and substitutes the changed version instead.???

#### CONFIGURATION
* `merge.conflictStyle`
    Specify the style in which conflicted hunks are written out to working tree files upon merge. The default is `merge`, which shows a `<<<<<<<` conflict marker, changes made by one side, a `=======` marker, changes made by the other side, and then a `>>>>>>>` marker. An alternate style, `diff3`, adds a `||||||||` marker and the original text before the `=======` marker.
* `merge.defaultToUpstream`
    **If merge is called without any commit argument, merge the upstream branches configured for the current branch by using their last observed values stored in their remote-tracking branches.** **The values of the `branch.<current branch>.merge` that name the branches at the remote named by `branch.<current branch>.remote` are consulted, and then they are mapped via `remote.<remote>.fetch` to their corresponding remote-tracking branches, and the tips of these tracking branches are merged.** <a name=branch_refspecs></a>
* `merge.ff`
    **By default, Git does not create an extra merge commit when merging a commit that is a descendant of the current commit. Instead, the tip of the current branch is fast-forwarded. When set to `false`, this variable tells Git to create an extra merge commit in such a case (equivalent to giving the `--no-ff` option from the command line). When set to `only`, only such fast-forward merges are allowed (equivalent to giving the `--ff-only` option from the command line).**
* `merge.branchdesc`
    **In addition to branch names, populate the log message with the description text associated with them. Defaults to false.**
* `merge.log`
    **In addition to branch names, populate the log message with at most the specified number of one-line descriptions from the actual commits that are being merged. Defaults to false, and true is a synonym for 20.**
* `merge.renameLimit`
    **The number of files to consider when performing rename detection during a merge;** if not specified, defaults to the value of `diff.renameLimit`.
* `merge.stat`
    **Whether to print the diffstat between `ORIG_HEAD` and the merge result at the end of the merge. True by default.**
* `merge.tool`
    Controls which merge tool is used by `git mergetool`. The list below shows the valid built-in values. Any other value is treated as a custom merge tool and requires that a corresponding `mergetool.<tool>.cmd` variable is defined.
* `merge.verbosity`
    Controls the amount of output shown by the recursive merge strategy. **Level 0 outputs nothing except a final error message if conflicts were detected. Level 1 outputs only conflicts, 2 outputs conflicts and file changes. Level 5 and above outputs debugging information. The default is level 2.** Can be overridden by the `GIT_MERGE_VERBOSITY` environment variable.
* `branch.<name>.mergeOptions`
    **Sets default options for merging into branch `<name>`. The syntax and supported options are the same as those of `git merge`**, but option values containing whitespace characters are currently not supported.
### 11.6 `man git rebase`
## 12 Discussions
### 12.1 Visualize Merge History with `git log --graph`, `--first-parent`, and `--no-merges`
Git merges can be complicated, but these arcane parameters can help.
`git log` can display surprisingly confusing results when the history contains merges. In this post, I'll walk through a few parameters that can help clear things up.
I'll start by showing how the default "chronological" order of `git log` can mislead you when the history contains merge commits. Then I'll show how you can visualize Git merge history using `git log --graph`, and how to see the "true" history of a single branch using `--first-parent`. I'll end by giving an example where `--first-parent` doesn't do what you'd want. In those cases, `--no-merges` may yield better results.
By the time I'm done, I hope not only to teach you about a few useful parameters to `git log`, but to deepen your understanding of Git as a whole. In my experience at Redfin, developers frequently reach out to a local Git expert when they have a confusing experience with a Git merge. ("OMG I messed up my merge and now everything's broken!!!")
In troubled times like these, Git wizards can use advanced `git log` parameters to cast Magic Missile at the darkness.

#### Yes, I know what a rebase is:a defensive disclaimer
Before I continue, I should point out that Git makes it possible to **eliminate merge commits with `git rebase`**, and somebody's going to read this post and run to Hack News to say how stupid I am, because you should only use `git rebase` and you should never have merge commits.
Not you, dear reader, but I think we all know who it is I'm talking about.
OK, it might be you. If it is you, please try to hold your breath until the end of this section.
This post is long enough as it is, so I don't want to use space in this blog post to discuss when to rebase and when to merge. There are a million blog posts about that already. There are some smart people who say you should never have merge commits, and some other smart people who do lots of merge commits. For example, the Linux git repo has lots of interesting merges in its history.
IMO (In my opinion), the general consensus is that sometimes we should merge, and sometimes we should rebase, but there isn't always a good consensus on which cases are which. Participating effectively in this discussion requires a good understanding of how Git handles merges.
So, for the purpose of this post, I would like you to imagine, for the sake of discussion, that a group of developers might want to do a lot of merges, even though they know what rebasing means, and that sometimes they'd want to analyze some complex merge commits.

#### "Chronological" ordering: time is an illusion; long time, doubly so
Let's start with an [example repository](https://github.com/dfabulich/git-slightly-messy-merge/commits/master). You can generate a similar repo with [this script](https://gist.github.com/dfabulich/bdf255742fa79953f79486533204e23b).
The script creates a repository with just a few merges, like this:
1. We start by creating three branches off of the `master` branch: `branch1`, `branch2`, and `branch3`.
2. Make a commit directly on `master`.
3. Switch to `branch1`, and commit.
4. Switch to `branch2`, and commit.
5. Merge `branch2` back to the `master` branch.
6. Switch to `branc3` and commit.
7. Merge `branch1` to master.
8. Merge `branch3` to master last.
(We sleep for one second before each commit, so each commit gets a visibly different timestamp.)
Here's what we see when we run `git log --pretty="format:%h %ar %s` (that "pretty" argument says to show the commit hash, the relative timestamp, and the commit message, all on one line per commit; despite the name, it's not that pretty).

        8aec370 0 seconds ago Merge branch 'branch3'
        b7b4b7c 1 second ago Merge branch 'branch1'
        f88c7ba 2 seconds ago branch 3
        7b79ec5 3 seconds ago Merge branch 'branch2'
        accf1ce 4 seconds ago branch 2
        974b6d7 5 seconds ago branch 1
        a26aed9 6 seconds ago commit directly on master
        2d56476 7 seconds ago initial

![gitlogresult](gitlogresult.png)

As you can see, **`git log` prefers to show the commits in chronological order (`--date-order`). Those are the dates that the commits were created.**
**But, even though we're running `git log` on the `master` branch, this is not the chronological history of `master`. If these timestamps were days ago instead of seconds ago, you might mistakenly believe that the `branch1` commit `974b6d7` was in `master` five days ago, when in fact it only merged in yesterday. You might also think that the `branch1` commit `974b6d7` landed on `master` before the `branch2` commit `accf1ce`, but the reverse is true; `accf1c` merged to `master` before the `branch1` commit `974b6d7`.**

#### Merge commits: when one parent commit loves another parent commit very, very much
`git log` has a tool you can use to visualize all of this merging, `--graph`. The output looks like this:

        *   8aec370 0 seconds ago Merge branch 'branch3'
        |\
        | * f88c7ba 2 seconds ago branch 3
        * |   b7b4b7c 1 second ago Merge branch 'branch1'
        |\ \
        | * | 974b6d7 5 seconds ago branch 1
        | |/
        * |   7b79ec5 3 seconds ago Merge branch 'branch2'
        |\ \
        | * | accf1ce 4 seconds ago branch 2
        | |/
        * | a26aed9 6 seconds ago commit directly on master
        |/
        * 2d56476 7 seconds ago initial
**_Note: Look through the graph above from top down to bottom._**
This graph shows not only the commits (as asterisks `*`) but also their "parent" commits. **Most commits-"ordinary" commits-have only one parent: the last commit of the branch you were on when the commit was created.** In the above example, the initial commit `2d56476` is the only parent of the commit `a26aed9`.
The initial commit in a repository, the **"root commit"**, has no parents. It's possible for git repositories to have multiple root commits,typically due to errors rewriting Git history. The moral of this story is to avoid time travel whenever possible.
**When you merge two branches, you're creating a "merge" commit with two parents**: **the last commit of the branch you're on, and the last commit of the branch you're merging in.** In the graph above, `8aec370` is a merge commit with two parents: `b7b4b7c` (the last commit on `master` at the time) and `f88c7ba` (the last commit on `branch3`). See how **the merge commit `8aec370` has two lines sticking out of the bottom**, whereas `f88c7ba` has only one? No? Well, scroll up and look at the graph again. This is important!
It's also possible to perform **"octopus"** **merge** in git, which have two more parents. There's a commit in the Linux repo with 66 parents.
Note that **`git log --graph` does *not* show the commits in chronological order. The `git help` man pages cal it `--topo-order`, topological ordering. "Show no parents before all of its children are shown, and avoid showing commits on multiple lines of history intermixed."**
Did you know that "topological sorting" has essentially nothing to do with the modern mathematical definition of "topology"? I bet you do know that the definition of "topological sorting" has nothing to do with any Git problem you're trying to resolve. Git's help pages are full of technical jargon like this, terms that are technically correct but obscure the meaning of text rather than enlightening the reader.

#### Use `--graph` as little as possible
**Using `git log --graph` can help, if you know about parent commits and you know how to read it, but it's still not very easy to understand the visualization as a whole; it would be a completely illegible mess with just a few more merges in it.**
Don't even try to visualize the entire messy history of `master` when there are a bunch of merges on it. Visualization is powerful mental technique, but visual aids can only really represent a few dozen things before they become as complicated as the thing you were trying to understand in the first place.
And when analyzing messy merges, it's not just the commits we're trying to visualize, but the lines connecting the commits (the "edges" connecting the "nodes", in graph-theory terms). We can only visualize a few dozen of those, and that typically means we can visualize only a handful of merge commits at a time.
If you have a bunch of merges into the `master` branch, you'll find that the history of `master` isn't a straight line of history; it's more like one of those slashy fanfics in which the Amazing Spider-Man and Dr.Octopus have cybernetic octo-spider babies.
**Instead of trying to understand the entire graph, its' better to look at the history of `master` itself, in isolation.** That's what we'll do in the next section.

#### The "first parent" is the true lineage of master (usually)
In an ideal world, you'd be able to say to Git, **"Show me just the commits that were created on the `master` branch."** But for legacy reasons, **Git commits don't record the name of the branch on which commits are created. (In my example, I embedded that information in the commit message to make it easier to understand.)**
**From Git's perspective, by the time all of those merges are done, *all* of those commits are "on" the `master` branch.** That's why it has to show you all of them when you ask for the history of `master`.
But look at the graph again.

***   8aec370 0 seconds ago Merge branch 'branch3'**
|\
| * f88c7ba 2 seconds ago branch 3
*** |   b7b4b7c 1 second ago Merge branch 'branch1'**
|\ \
| * | 974b6d7 5 seconds ago branch 1
| |/
*** |   7b79ec5 3 seconds ago Merge branch 'branch2'**
|\ \
| * | accf1ce 4 seconds ago branch 2
| |/
*** | a26aed9 6 seconds ago commit directly on master**
|/
*** 2d56476 7 seconds ago initial**

See the commit asterisks that appear on the left-hand rail? (I've bolded those lines.) Those commits are the ones that were "really" on the `master` branch, aren't they? How did Git know to put those commits all in a straight line like that, if all of the commits are equal in the eyes of the `master` branch?
It turns out that, just like real children, Git doesn't treat a merge commit's two parents equally; merge commits have a "first parent" and a "second parent." **The "first parent" is the branch you were already on when you typed `git merge` (or `git pull` or whatever caused the merge). The "second parent" is the branch that you were pulling in.**
Here's what is says when you `git show 8aec370` in our example repository.

        commit 8aec37089204c7ec5d280779cdcfe5e378026c65
        Merge: b7b4b7c f88c7ba
        Author: Dan Fabulich <dan.fabulich@redfin.com>
        Date:   Wed Mar 15 22:37:25 2017 -0700

            Merge branch 'branch3'

See that "Merge" line? It's showing you the two parents of the merge commit, in order. The first parent was `b7b4b7c` and the second parent was `f88c7ba`.
Here's what we see when we `git log --first-parent`.

        8aec370 0 seconds ago Merge branch 'branch3'
        b7b4b7c 1 second ago Merge branch 'branch1'
        7b79ec5 3 seconds ago Merge branch 'branch2'
        a26aed9 6 seconds ago commit directly on master
        2d56476 7 seconds ago initial
**`--first-parent` instructs `git log` to log only the first parent of each commit, ignoring all other parents and their parents (their "ancestors"). Since the first parent is the parent that was already on `master` at the time the merge was performed, looking at the first parent can reveal the "true history" of the `master` branch.** The first-parent lineage shows you what you would have gotten if you'd peeked at the `master` branch at a particular point in time.
That's about as close as you can get to viewing the history of the `master` branch in isolation. (But, as we'll see in a moment, there are problems with using `--first-parent` this way.)

#### Beware: fast-forward merges can mix up parent order
Consider this sample script.

        git init --bare origin
        git clone origin clone1
        cd clone1

        echo 0 > file.txt
        git add file.txt
        git commit -am "initial commit"
        git push origin master
        git checkout -b branch1
        git push origin branch1

        cd ..
        git clone origin clone2

        cd clone1
        git checkout branch1
        echo 1 > file.txt
        git commit -am "1 (in clone1)"
        git push origin branch1

        cd ../clone2
        git checkout branch1
        echo 2 > file2.txt
        git add file2.txt
        git commit -m "2 (in clone2)"
        git pull --no-edit origin branch1
        git push origin branch1
In this sample, we create an `origin` repository and create two clones `clone1` and `clone2`. (**Imagine that these repositories each belonged to a different engineer.**)
In `clone1`, we create the initial commit and then an additional commit on `branch1` and push it to the `origin` repository. `clone2` only contains the initial commit, at first.
When we create a commit on `branch1` in `clone2`, we `pull` from the `origin` repository, creating a merge commit, and then immediately `push` our repository. (This is a very common approach for teams of engineers working directly on the same feature branch, aka topic branch.)
The `pull` creates a merge commit with a confusing message:

        Merge branch 'branch1` of /tmp/origin into branch1
Yes, we're merging `branch1` into `branch1`! Specially, we're merging `origin`'s `branch1` into `clone2`'s `branch1`.
The push from the local `maser` to the remote is a **"fast-forward" merge. In this type of merge, Git skips creating a merge commit, and instead moves `origin`'s `master` branch pointer to point directly to the latest commit from `clone2`.**
Now what happens when we `git log --first-parent`?

        $ git log --first-parent --oneline
        83ac7af Merge branch 'branch1` of /tmp/origin into branch1
        493e104 2 (in clone 2)
        8a5e558 initial commit
Uh oh! That's not the true history of `origin`'s `branch1`. Why not? Let's look at the `--graph` output:

        $ git log --graph --oneline
        *   83ac7af Merge branch 'branch1' of /tmp/origin into branch1
        |\
        | * 572edba 1 (in clone1)
        * | 493e104 2 (in clone2)
        |/
        * 8a5e558 initial commit
The first parent of the merge commit was `clone2`'s commit;`origin`'s `branch1`'s last commit is the *second* parent. That's not what we wanted.
Typically when this happens, `--graph` makes it pretty clear what's happening, if you can recognize it. (Any time I see a commit message about merging a branch into itself, e.g. `Merging branch X into X`, I remember "oh,yeah, that.")
When fast-forward merges result in mixed-up parents, `git log --graph` may be the simplest accurate view of the history. If the team is working on a small branch, the graph output should be pretty manageable.
Alternately, if the team working on your branch doesn't care about merges t o the branch, and especially if you don't care about the *order* of the commits, you might prefer to ignore merges completely with `git log --no-merges`.

        $ git log --no-merges --oneline
        493e104 2 (in clone2)
        572edba 1 (in clone1)
        8a5e558 initial commit
**It's in chronological order**, which obscures the "true" history of the branch, but if your team doesn't care about that, then neither do I!
In my experience, `--no-merges` works well only in small, shared branches. But what if your team shares `master` in this way, with lots of engineers regularly pulling and pushing directly to `master`?
As I understand it, the general consensus is that in that case, your history will be inherently hard to read, and so you should not use Git in that way. There are two better approaches, depending on whether you prefer to `merge` or `rebase`:
**1. In one approach, every change going into the `master` branch should use a pull requet, which creates a well-formed merge commit.**
**2. In anothe approach, engineers should pull with `git pull --rebase`.**

### 12.2 Check the difference between two branches
There are a couple of tricks that one can use for this particular case though. If you check the (extensive, albeit confusing) documentation for `git rev-list` you will find the options `--left-right`, `--left-only`, `--right-only`, `--cherry-mark`, `--cherry-pick`, and `--cherry`.
The `--left-right` option works with any symmetric difference, i.e., commits selected by `A...B`, which means "all commits that are on branch `A` or branch `B`, excluding any commits that are on *both* branches." This is how `git cherry` does the first part of its thing: it finds commits that are on the symmetric difference. However, `git cherry` goes on to *throw out*(meaning to remove, to get rid of) all the commits that are *"the same"* on both branches, then marks those on one side with `-` and those on the other with `+`. The `--left-right` option marks all commits as either `<` (left side) or `>` (right side).
Since `rev-list` is the Swiss Army Chainsaw command, it also has the ability to throw out commits that are the same. It has even more abilities too: it can throw out commits on one side entirely, same-or-different. This is what we want in this case: throw out "commits that are the same" (so that we keep only *different* ones); then throw out all "left side" commits (so that we keep only those that are in the right side but not the left side). We get the former with `--cherry-pick`: it keeps only commits that are considered *different*. Then we add `--right-only` to keep only those on the right side, i.e., when we say `firstbranch...secondbranch`, keep only those that are both different *and* in `secondbranch`, which is exactly what `git cherry` does.
Hence:
`git rev-list --right-only --cherry-pick firstbranch...secondbranch`
produces the same commit ID list as:
`git cherry firstbranch secondbranch`
(with the single difference being that instead of `+ face0ff...`, it prints `+face0ff`, i.e., no space after the `+` mark).
This seems pretty silly: instead of just the four words `git cherry` and two branch names, we need `git rev-list` and a bunch of options and two branch names and three periods. We've typed in lots more letters to get pretty much the same thing. So we could just use the shorter command and pipe it to `git log`, but now we get to the tricky bit.
Log options `--cherry-mark`, `--left-only`, `--right-only`, `--cherry` and `--cherry-pick` that show various selections of similar or dissimilar commits of a `...` (two-branch aka "symmetric difference") log. Also, `--left-right` shows for each commit whether its changes appear only on the left branch, right branch, or both.
`--cherry`: which is a synonym for `--right-only --cherry-mark --no-merges`. You can also use `--right-only --cherry-pick --no-merges`. The difference is that `--cherry-mark` *marks* the commits (as equivalent or not), while `--cherry-pick` *skips* the equivalent commits. The `git cherry` command is like similar, although I prefer the direct symmetric difference for instruction purposes: `git cherry` is what you use *after* you know all the above.
<hr>
The little-used command `git cherry` shows you the commits which haven't yet been cherry-picked. In short, you should just be able to do:
`git cherry next devel`
and see output a bit like this:

        + 492508acab7b454eee8b805f8ba906056eede0ff
        - 5ceb5a9077ddb9e78b1e8f24bfc70e674c627949
        + b4459544c000f4d51d1ec23f279d9cdb19c1d32b
        + b6ce3b78e938644a293b2dd2a15b2fecb1b54cd9
The commits that begin with `+` will be the ones that you *haven't yet* cherry-picked into `next`. In this case, I'd only cherry-picked one commit so far. You might want to add the `-v` parameter to the `git cherry` command, so that it also outputs the subject line of each commit.
And you wouldn't know of a way to get `cherry` to mark or exclude equivalent commits, would you? `cherry` seems like a plumbing command, but doesn't (appear to) offer many options. For what I'm currently in the middle of, `git cherry` gives me false positives, but `git log --chery-pick` correctly excludes the previously-picked/rebased commits.
<hr>

#### `git log` and `git rev-list` are very nearly the same command
In fact, they are built from the same source code, they just set some internal options differently (and `git log` will pretend you said `HEAD` if you don't name any other starting points). Since we're about to pipe the output of `git rev-list` to `git log --pretty='%h %ce'`, maybe we can just do the whole thing in `git log` directly.
Sure enough, we can. We need all those same options as with `git rev-list`, but now we can just run:
`git log --cherry-pick --right-only --pretty='%h %ce' firstbranch...secondbranch`
(you may want `--no-merges` here as well-I'm not sure offhand what `git cherry` does about merges!).



### 12.3 Why does git status show branch is up-to-date when changes exist upstream
#### Q
Changes exist upstream in a tracked branch, but when I type `git status`, it indicates that my local branch is up-to-date. Is this new behavior, did I change a config setting, or is something wrong?

#### A
What the status is telling you is that you're behind the ref called `origin/master`, which is a *local* ref in your *local* repo. In this case that ref happens to track a branch in some remote, called `origin`, but the status is not telling you anything about the branch on the remote. It's telling you about the ref, which is a commit ID stored on your local filesystem (in this case, it's typically in a file called `.git/refs/remotes/origin/master` in your local repo).
`git pull` does two operations: first it does a `git fetch` to get up to date with the commits in the remote repo (which updates the `origin/master` ref in your local repo), then it does a `git merge` to merge those commits into the current branch.
Until you do the `fetch` step (either on its own or via `git pull`) your local repo has no way to know that there are additional commits upstream, and `git status` only looks at your local `origin/master` ref.
When `git status` say up-to-date, it means "up-to-date with the branch that the current branch tracks", which in this case means "up-to-date with the local ref called `origin/master`". That only equates to "up-to-date with the upstream status that was retrieved last time we did a `fetch` which is not the same as "up-to-date with the latest live status of the upstream".
Why does it work this way? Well the `fetch` operation is a potentially slow and expensive network operation. The design of Git (and other distributed version control systems) is to avoid network operations when unnecessary, and is completely different model to the typical client-server system many people are used to. It's entirely to use Git offline, with no connection to centralized server, and the output of `git status` reflect this.
Creating and switching branches ( and checking their status) in Git is supposed to be lightweight, not something that performs a slow network operation to a centralized system.
