hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session names_weak -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\names_cn.txt C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt && del names_weak.restore & hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session weak_names -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt C:\Users\cdutboy\Dropbox\hashcat_only\names_cn.txt && del weak_names.restore & hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session top3000names_weak -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\top3000names.txt C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt && del top3000names_weak.restore & hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session weak_top3000names -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt C:\Users\cdutboy\Dropbox\hashcat_only\top3000names.txt && del weak_top3000names.restore & hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session familynames_weak -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\family_names.txt C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt && del familynames_weak.restore & hashcat64.exe -D 1,2 -w 4 -m 2500 #HL# --session weak_family_names -a 1 C:\Users\cdutboy\Dropbox\hashcat_only\wordlist.txt C:\Users\cdutboy\Dropbox\hashcat_only\family_names.txt && del weak_family_names.restore
