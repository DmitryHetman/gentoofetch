# gentoofetch
Screenshot information tool for Gentoo GNU/Linux, written in C.
![gentoofetch](https://raw.githubusercontent.com/DmitryHetman/gentoofetch/master/gentoofetch.png)
gentoofetch is 170 lines long, 11kb in size if dynamically linked, 830kb if statically linked. It's written 
in ASCII characrers, so no Unicode required.
GPU detection still doesn't work, you can just edit executable or source code to 
substitute Intel HD with your GPU model:
# $ sandy gentoofetch.c
To run gentoofetch you must compile and install it:
# $ make
# (root) # make install
