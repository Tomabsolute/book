/**
 * @file main.cpp
 * @brief Conway生命游戏的主程序文件
 */

 #include <ncurses.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <string.h>
 #include "Conway.h"
 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_image_write.h" // 添加stb_image_write.h头文件
 
 /**
  * @brief 主函数，程序入口
  * 
  * 程序根据用户输入的参数初始化Conway生命游戏，并运行游戏循环直到用户输入'q'退出。
  * 
  * @param argc 命令行参数个数
  * @param argv 命令行参数数组，包含程序名称、游戏区域宽度、高度以及可选的RLE文件或'rand'字符串
  * @return int 返回状态码，0表示正常退出，1表示输入参数不足
  */
 int main(int argc, char *argv[])
 {
     // 检查命令行参数是否足够
     if (argc < 3)
     {
         printf("Usage: %s width height rle_file[|rand]\n", argv[0]);
         return 1;
     }
 
     // 设置边界条件
     boundary = 1;
 
     // 初始化ncurses库
     initscr();
 
     // 关闭输入回显
     noecho();
 
     // 隐藏光标
     curs_set(FALSE);
 
     // 禁止行缓冲，使得getch立即返回
     cbreak();
 
     // 设置非阻塞模式
     nodelay(stdscr, TRUE);
 
     // 根据命令行参数初始化细胞状态
     init_cells(atoi(argv[1]), atoi(argv[2]));
 
     // 如果未提供模式文件，默认设置随机细胞
     if (argc < 4)
         set_rand_cells();
     else
         load_pattern(10, 10, argv[3]);
 
     // 获取游戏区域的宽度和高度
     int width = world.width;
     int height = world.height;
 
     // 获取指向细胞状态数组的指针
     int **cell = world.cell;
 
     // 游戏主循环
     while (1)
     {
         // 清除屏幕
         clear();
 
         // 绘制细胞
         draw_cells();
 
         // 刷新屏幕以显示绘制的细胞
         refresh();
 
         // 睡眠一段时间以控制游戏速度
         usleep(10000);
 
         // 更新细胞状态
         update_cells();
 
         // 再次睡眠一段时间以控制游戏速度
         usleep(10000);
 
         // 检测用户输入，如果输入'q'，退出游戏循环
         int ch = getch();
         if (ch == 'q')
         {
             break;
         }
         else if (ch == 's')
         {
             // 保存当前图像为BMP格式
             unsigned char *data = (unsigned char *)malloc(width * height * 3);
             for (int y = 0; y < height; y++) {
                 for (int x = 0; x < width; x++) {
                     int index = (y * width + x) * 3;
                     if (cell[y][x]) {
                         data[index] = data[index + 1] = data[index + 2] = 255; // 白色
                     } else {
                         data[index] = data[index + 1] = data[index + 2] = 0; // 黑色
                     }
                 }
             }
             char filename[256];
             snprintf(filename, sizeof(filename), "conway_%d_%d.bmp", width, height);
             stbi_write_bmp(filename, width, height, 3, data);
             free(data);
             printf("Image saved as %s\n", filename);
         }
     }
 
     // 结束ncurses模式
     endwin();
 
     // 释放内存
     free_cells();
 
     // 返回0表示正常退出
     return 0;
 }
 