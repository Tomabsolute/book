[yes]图像保存功能：按下某个按键将当前时间下的图像保存（如bmp格式）

使用方法、依赖关系等; 生成 Conway 生命游戏可视化界面的 .c 文件与 .h 文件。

目的：是为了生成生成 Conway 生命游戏可视化界面

功能：生成 Conway 生命游戏可视化界面，可以让用户输入参数，并在界面上显示生成的生命游戏。

使用方法：
1.make生成conway可执行文件，在终端输入./conway 40 40 1.rle即可运行，其中1.rle为我从网上找来的滑翔机模型,更多的模型在pattern文件夹中
2.make doc生成doxygen文档，在终端cd html,然后open index.html即可查看文档。(我的操作系统是macos，其他系统的打开指令可能不同)
3.make clean清除生成的文件。
按附加要求添加了截图功能，在运行文件后，按下s即可截图保存为bmp图片，此处依赖从github下载的stb_image_write.h文件。
按q退出程序。

依赖关系：
main.cpp依赖：ncurses.h,unistd.h,stdlib.h,string.h,Conway.h,stb_image_write.h
Conway.cpp依赖：stdlib.h,string.h,Conway.h,ncurses.h,unistd.h,ctyp.h
