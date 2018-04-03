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
