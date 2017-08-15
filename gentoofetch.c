#include<string.h> /* strchr */
#include<stdio.h> /* printf, fopen, fclose */
#include<stdlib.h> /* getenv */
#include<sys/sysinfo.h> /* uptime,freeram,totalram,procsg */
#include<sys/utsname.h> /* uname, kernel, cpu, hostname (nodename) */
#include<glob.h> /* packages */
#include<unistd.h> /* readlink */
#include<sys/stat.h> /* stat */
int main(void){
static FILE *file;
static int prof1,prof2;
static char gcc[23],
resolution[10],
clib[40],
clibv[34],
alsa[36],
prof[64],
release[13],
cpul[60],
ge[12],
root[16],
*cpu;
static struct stat sock;
static struct sysinfo sys;
static struct utsname kernel;
static  glob_t packages;
glob("/var/db/pkg/*/*",GLOB_NOSORT|GLOB_NOESCAPE,NULL,&packages);
sysinfo(&sys);
uname(&kernel);

/* CPU */
 file=fopen("/proc/cpuinfo","r");
 fgets(cpul,20,file);
 fgets(cpul,20,file);
 fgets(cpul,20,file);
 fgets(cpul,20,file);
 fgets(cpul,20,file);
 fgets(cpul,60,file); /*jump to 5th line */
 fclose(file);
 cpu=&cpul[13];

/* gcc */
 file=popen("gcc --version","r");
 fgets(gcc,23,file);
 pclose(file);

/* root */
 file=popen("df -hTx devtmpfs -x tmpfs|awk 'FNR==2{print$4\"/\"$3\" \"$2}'","r");
 fgets(root,16,file);

/* clib */
 file=popen("gcc -dumpmachine","r");
 fgets(clib,18,file);
 pclose(file);
 switch (clib[strlen(clib)-1]) {
  case 'g':
   strcpy(clib,"glibc ");
   file=popen("/lib/libc-*","r");
   fgets(clibv,33,file);
   pclose(file);
   strcpy(&clib[6],&clibv[15]);
  break;
  case 'u':
   strcpy(clib,"ucblibc");
  break;
  case 'm':
   strcpy(clib,"musl");
  break;
 }

/* release */
 file=popen(". /etc/portage/make.conf;echo \"${ACCEPT_KEYWORDS}\"","r");
 fgets(release,8,file);
 pclose(file);
 switch (release[0]) {
 case '*':
  strcpy(release,"experimental");
 break;
 case '~':
  strcpy(release,"testing");
 break;
 default:
  strcpy(release,"stable");
 break;
 }

/* Resolution */
 file=fopen("/sys/devices/virtual/graphics/fbcon/subsystem/fb0/device/drm/card0/device/graphics/fb0/virtual_size","r");
 fgets(resolution,10,file);
 fclose(file);
 *strchr(resolution,',')='x';

/* sound card detection */
 file=popen("aplay -L","r");
 do
  fgets(alsa,18,file);
 while (alsa[0]!='d');
 fgets(alsa,36,file);
 pclose(file);

/* profile */
 readlink("/etc/portage/make.profile",prof,64);
 prof1 = strlen(prof);
 do
  --prof1;
 while (prof[prof1]!='/');
 ++prof1;
 prof2=prof1-7;
 while(prof[--prof2]!='/');
 while(prof[--prof2]!='/');
 while(prof[--prof2]!='/');
 ++prof2;

/* graphic environment */
 stat("/tmp/dmitry-runtime-dir/wayland-0",&sock);
 if (sock.st_mode==49645)
 strcpy(ge,"Wayland");
 else {
   stat("/tmp/.X11-unix/X0",&sock);
    if (sock.st_mode==49663)
     strcpy(ge,"X11");
    else
     strcpy(ge,"Framebuffer");
 }
 if(getenv("TERM")[0]=='l')
  strcpy(ge,"Framebuffer");

printf("[1;35m         -/oyddmdhs+:.[1;35m              %s[1;37m@[1;35m%s\n\
[1;35m     -o[1;37mdNMMMMMMMMNNmhy+[1;35m-`           OS:[m Gentoo %s\n\
[1;35m   -y[1;37mNMMMMMMMMMMMNNNmmdhyb[1;35m+-        Profile:[m %s %s\n\
[1;35m `o[1;37mmMMMMMMMMMMMMNmdmmmmddhhy[1;35m/`      Kernel:[m %s %s\n\
[1;35m om[1;37mMMMMMMMMMMMN[1;35mhhyyyo[1;37mhmdddhhhd[1;35mo`    Clib:[m %s\n\
[1;35m.y[1;37mdMMMMMMMMMMd[1;35mhs++so/s[1;37mmdddhhhhdm[1;35m+`  GCC:[m %s\n\
[1;35m oy[1;37mhdmNMMMMMMMN[1;35mdyooy[1;37mdmddddhhhhyhN[1;35md. Graphic Environment:[m %s\n\
[1;35m  :o[1;37myhhdNNMMMMMMMNNNmmdddhhhhhyym[1;35mMh Terminal:[m %s\n\
[1;35m    .:[1;37m+sydNMMMMMNNNmmmdddhhhhhhmM[1;35mmy Shell:[m %s\n\
[1;35m       /m[1;37mMMMMMMNNNmmmdddhhhhhmMNh[1;35ms: Packages:[m %lu\n\
[1;35m    `o[1;37mNMMMMMMMNNNmmmddddhhdmMNhs[1;35m+`  Root:[m %s\
[1;35m  `s[1;37mNMMMMMMMMNNNmmmdddddmNMmhs[1;35m/.    Uptime:[m %lud,%luh,%lum\n\
[1;35m /N[1;37mMMMMMMMMNNNNmmmdddmNMNdso[1;35m:`      Processes:[m %u\n\
[1;35m+M[1;37mMMMMMMNNNNNmmmmdmNMNdso[1;35m/-         RAM:[m %luMiB/%luMiB\n\
[1;35myM[1;37mMNNNNNNNmmmmmNNMmhs+/[1;35m-`           CPU:[m %s\
[1;35m/h[1;37mMMNNNNNNNNMNdhs++/[1;35m-`              GPU:[m Intel HD Graphics 4600\n\
[1;35m`/[1;37mohdmmddhys+++/:[1;35m.`                 Resolution:[m %s\n\
[1;35m  `-//////:--.                      Sound Card:[m %s\n",
getenv("USER"),kernel.nodename,
release,
(prof[prof2]=='d')?"default":"hardened",&prof[prof1],
kernel.sysname,kernel.release,
clib,
&gcc[5],
ge,
getenv("TMUX_PANE")?"tmux":getenv("TERM"),
getenv("SHELL"),
packages.gl_pathc,
root,
sys.uptime/86400,sys.uptime/3600%24,sys.uptime/60%60,
sys.procs,
(sys.totalram-sys.freeram)/1048576,sys.totalram/1048576,
cpu,
resolution,
&alsa[4]);

return 0;
}
