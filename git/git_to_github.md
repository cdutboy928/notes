# 用git在github上托管代码
1 在github上创建相应程序包的repository，如命名为herblabel。网址为 https://github.com/helixcn/herblabel
2 第一次使用本地版本的git时，需要设定用户名和联系方式。  
      git config --global user.name "Jinlong Zhang"  
      git config --global user.email "jinlongzhang01@gmail.com"
3 更改credential helper缓存密码的时间
    git config --global credential.helper 'cache --timeout=3600'
4 在本地/herblabel/文件夹中创建本地的repository。
    cd /home/jinlong/git_repositories/github_herblanel/
    git init
5 在/herblabel/文件夹下，将herblabel源代码记录到git库中。
    git add *
6 master版本，即最终发布版本，commit到本地的库中。
    git commit -m 'initial commit'
7 推送到github
    git remote add origin https://github.com/cdutboy928/notes
    git remote -v
    git push -u origin master
    git会提示输入github的用户名和密码，输入后，git会自动将master分支上传到服务器。
8 将master分支推送到github服务器后，每一次在本地进行修改时，如修整了软件按的一个bug，一般流程如下：
    (1) 新建一个分支，如herblabel_dev。命令如下：
    git checkout -b herblabel_dev
    (2) 修改代码，fix the bug
    (3) 回到master分支git checkout master
    (4) 将herblabel_dev所做的修改合并到master中：git merge herblabel_dev
    (5) 提交所做的修改git add *
    (6) 记录所做的修改git commit -m "xx bug fixed"
    (7) 提交所做的修改到github服务器 git push
