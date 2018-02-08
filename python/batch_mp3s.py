# -*- coding: UTF-8 -*-
import urllib
url_base="http://auto.tom61.com/down/mp3book/gscjx/"
url_pre= *
url_append= *
url=url_base+url_pre+'.mp3'+url_append
#url="http://auto.tom61.com/down/mp3book/gscjx/古诗精选-采葛（诗经-王风）.mp3?176013719797087x1517986929x176013721672955-77ca97c604691230b0bec04e98642197"
path="/home/cdutboy/唐诗/"+url_pre+".mp3"
data=urllib.urlopen(url).read()
f=file(path,"wb")
f.write(data)
f.close()
