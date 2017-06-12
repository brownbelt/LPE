# LPE

EDIT: TO AVOID CONFUSION, THIS HAS ALREADY BEEN PATCHED AND HAS BEEN ASSIGNED CVE-2016-7292 ( https://technet.microsoft.com/library/security/ms16-149)

Important: This poc will only work on 64-bit out of the box. You need to change a few things for 32-bit, but i'll leave that up to the reader to figure out ;).


Place the files from the "for your downloads folder" in your c:\users\%username%\downloads folder and run lpe.exe 

This will remove windowstrustedrtproxy.sys from c:\windows\system32\drivers if not patched by the december 2016 patch.

(this is not a UAC-bypass, as this worked from a non-admin acc)
