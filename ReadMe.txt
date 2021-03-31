1: 64位ubuntu 无法执行arm-linux-gcc 
sudo apt install lsb-core  

sudo apt install ia32-libs*  #命令如果已被ubuntu新版本替代，则执行下面一条命令
sudo apt install lib32ncurses5 lib32z1 lib32z1-dev

sudo apt install libmpfr4:i386

#mpfr gmp的版本号(x.x.x)按实际情况填写
sudo ln -s /usr/lib/i386-linux-gnu/libmpfr.so.x.x.x /lib/libmpfr.so.1
sudo ln -s /usr/lib/i386-linux-gnu/libgmp.so.x.x.x /lib/libgmp.so.3

2: 解压文件	
./run_me_first.sh

3: 
在某些liunx系统下解压失败，则手动使用bsdtar解压

4: git log 乱码
git config --global i18n.commitencoding utf-8
git config --global i18n.logoutputencoding utf-8
//添加下面 ~/.bashrc
export LESSCHARSET=utf-8

5: linux终端无法输入汉字
//添加下面 ~/.bashrc
export LANG="zh_CN.utf-8"
export LANGUAGE="zh_CN:zh:en_US:en"
export LC_ALL="zh_CN.utf-8"

