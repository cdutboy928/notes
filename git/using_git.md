# Use Git

## 用git在github上托管代码
    1. 在github上创建相应程序包的repository，如命名为herblabel。网址为 https://github.com/helixcn/herblabel
    2. 第一次使用本地版本的git时，需要设定用户名和联系方式。  
          git config --global user.name "Jinlong Zhang"  
          git config --global user.email "jinlongzhang01@gmail.com"
    3. 更改credential helper缓存密码的时间
        git config --global credential.helper 'cache --timeout=3600'
    4. 在本地/herblabel/文件夹中创建本地的repository。
        cd /home/jinlong/git_repositories/github_herblanel/
        git init
    5. 在/herblabel/文件夹下，将herblabel源代码记录到git库中。
        git add *
    6. master版本，即最终发布版本，commit到本地的库中。
        git commit -m 'initial commit'
    7. 推送到github
        git remote add origin https://github.com/cdutboy928/notes
        git remote -v
        git fetch
        git merge  *git pull 之前一定要git fetch & git merge!!!!，不然会覆盖远端内容*
        git push -u origin master
        git会提示输入github的用户名和密码，输入后，git会自动将master分支上传到服务器。
    8. 将master分支推送到github服务器后，每一次在本地进行修改时，如修整了软件按的一个bug，一般流程如下：
        (1) 新建一个分支，如herblabel_dev。命令如下：
            git checkout -b herblabel_dev
        (2) 修改代码，fix the bug
        (3) 回到master分支git checkout master
        (4) 将herblabel_dev所做的修改合并到master中：git merge herblabel_dev
        (5) 提交所做的修改git add *
        (6) 记录所做的修改git commit -m "xx bug fixed"
        (7)git fetch 
        (8)git merge  *git pull 之前一定要git fetch & git merge!!!!，不然后覆盖远端内容*
        (9) 提交所做的修改到github服务器 git push
    9. 如果远端有变化，如何获取最新状态。
        * git fetch
            git fetch <远端主机名> <远端分支名>:<本地分支名>
            git fetch <远程主机名> 将远程主机的更新，全部取回本地。
    
            git fetch origin master:brach2
            git fetch origin master:tmp
            git diff tmp
            git merge tmp "if there are conflicts
            git branch -d tmp
    
            If there are conflicts, resolve the conflicts mannually, git add and git commit
            The conflicts' format is as follows:
            <<<<< your part
           |||||
            original part
            \==========
            their part
            \>>>>>>
        * git pull
            git pull <远端主机名> <远端分支名>:<本地分支名>
            git pull 相当于 git fetch & git merge
            git pull 的弊端在于直接合并了，隐藏了细节。

## Git Basics
### Recording Changes to the Repository
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
Git figures out that it's a rename implicitly, so it doesn't matter if you rename a file that way or with the `mv` command. The only difference is that `git mv` is one command instead of three-it's a convenience function. More importantly, you can use any tool you like to rename a file, and address that add/rm later, before you commit.
Summary:for untracked files, use `rm`;
        for tracked files and staged files: `git rm --cached` to delete from stage area and the file will become untracked; `git rm --f` to delete both from stage area and working directory.

#### Viewing the commit history

