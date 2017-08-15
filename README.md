# gentoofetch
Screenshot information tool for Gentoo GNU/Linux, written in C.
![gentoofetch](https://user-images.githubusercontent.com/18743742/29305657-601e6172-8189-11e7-951e-32e1a4a565c3.png)
gentoofetch is 170 lines long, 11kb in size if dynamically linked, 830kb if statically linked. It's written 
in ASCII characrers, so no Unicode required.
To dowload gentoofetch type in your terminal:
git clone -b master --depth 1 https://github.com/DmitryHetman/gentoofetch
GPU detection still doesn't work, you can just edit executable or source code to 
substitute Intel HD with your GPU model:
# $ sandy gentoofetch.c
To run gentoofetch you must compile and install it:
# $ make
# (root) # make install
