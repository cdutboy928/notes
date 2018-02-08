import urllib2
def getLeagalUrl(i):
    base_url="http://auto.tom61.com/down/mp3book/gscjx/"
    url_preletter='*'
    url_append='*'
    url=base_url+url_preletter+'.mp3'+url_append
    f=urllib2.urlopen(url)
    return url
#    except urllib2.URLError:
#        continue
    return ""

def download(url,i)
    f=urllib2.urlopen(url)
    data=f.read()
    with open(url_preletter+'.mp3','wb') as file:
        file.write(data)

if __name__ == '__main__':
    for i in range(0,600):
        url=getLegalUrl(i)
        if url == "":
            with open("download.log",'a') as log:
                log.write(str(i)+'not found\n')
        else:
            download(url,i)
