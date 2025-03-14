/**
 * @file Conway.cpp
 * @brief 康威生命游戏的实现文件。
 * 
 * 该文件实现了康威生命游戏的核心逻辑。
 */

 #include "Conway.h"
 #include <ncurses.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <string.h>
 
 /// 这里兑现了承诺
 struct World world;  
 
 int boundary = 1;
 
 /**
  * @brief 初始化细胞世界。
  * @param _w 世界的宽度。
  * @param _h 世界的高度。
  */
 void init_cells(int _w, int _h)
 {
     world.cell = (int **)malloc(_w * sizeof(int *)); // 为行分配内存
     for (int i = 0; i < _w; i++)
         world.cell[i] = (int *)malloc(_h * sizeof(int)); // 为每一行分配列
     world.width = _w;
     world.height = _h;
     for (int i = 0; i < _w; i++)
     {
         for (int j = 0; j < _h; j++)
         {
             world.cell[i][j] = 0; // 初始的死世界
         }
     }
 }
 
 /**
  * @brief 随机设置细胞状态。
  */
 void set_rand_cells()
 {
     for (int i = 0; i < world.width; i++)
     {
         for (int j = 0; j < world.height; j++)
         {
             world.cell[i][j] = rand() % 2;
         }
     }
 }
 
 /**
  * @brief 从 RLE 文件加载模式到世界中的指定位置。
  * @param _x 模式的起始 x 坐标。
  * @param _y 模式的起始 y 坐标。
  * @param rle_file RLE 文件的路径。
  */
 void load_pattern(int _x, int _y, char *rle_file)
 {
     FILE *file = fopen(rle_file, "r");
     if (file == NULL)
     {
         exit(1);
     }
     int w, h;
     int k = 0;
     char pattern[1000];
     int width = world.width;
     int height = world.height;
     int **cell = world.cell;
     if (file != NULL)
     {
         char line[256];
         while (fgets(line, sizeof(line), file))
         {
             if (line[0] == '#')
             {
                 continue;
             }
             else if (line[0] == 'x')
             {
                 sscanf(line, "x = %d, y = %d", &w, &h);
             }
             else if (line[0] == 'b' ||
                      line[0] == 'o' ||
                      line[0] == '!' ||
                      line[0] == '$' ||
                      isdigit(line[0]))
             {
                 for (int i = 0; i < strlen(line); i++)
                 {
                     pattern[k] = line[i];
                     k++;
                 }
             }
         }
     }
     else
     {
         printf("File not found\n");
     }
     pattern[k] = '\0';
     int px = _x;
     int py = _y;
 
     for (int i = 0; i < strlen(pattern); i++)
     {
         int count = 0;
         if (isdigit(pattern[i]))
         {
             while (isdigit(pattern[i]))
             {
                 count = count * 10 + (pattern[i] - '0');
                 i++;
             }
         }
         if (pattern[i] == 'b')
         {
             if (count == 0)
                 count = 1;
             for (int j = 0; j < count; j++)
             {
                 cell[py][px] = 0; // cell[x][y]
                 py++;
             }
         }
         else if (pattern[i] == 'o')
         {
             if (count == 0)
                 count = 1;
             for (int j = 0; j < count; j++)
             {
                 cell[py][px] = 1; // cell[x][y]
                 py++;
             }
         }
         else if (pattern[i] == '$')
         {
             px++;
             py = _y;
         }
         else if (pattern[i] == '!')
         {
             break;
         }
     }
 
     fclose(file);
 }
 
 /**
  * @brief 绘制当前世界中的细胞状态。
  */
 void draw_cells()
 {
     for (int i = 0; i < world.width; i++)
     {
         for (int j = 0; j < world.height; j++)
         {
             mvaddch(j, i, world.cell[i][j] ? '*' : ' ');
         }
     }
 }
 
 /**
  * @brief 计算指定位置细胞的邻居数量。
  * @param x 细胞的 x 坐标。
  * @param y 细胞的 y 坐标。
  * @return 邻居数量。
  */
 int count_neighbors(int x, int y)
 {
     int count = 0;
     int width = world.width;
     int height = world.height;
     int **cell = world.cell;
 
     for (int i = -1; i <= 1; i++)
     {
         for (int j = -1; j <= 1; j++)
         {
             if (i == 0 && j == 0) continue; // 直接跳过自身
 
             if (boundary == 0) // 固定边界
             {
                 int nx = x + i;
                 int ny = y + j;
 
                 if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                 {
                     continue;
                 }
 
                 count += cell[nx][ny];  // 确保正确的索引顺序（行优先）
             }
             else if (boundary == 1) // 循环边界
             {
                 int nx = (x + i + width) % width;
                 int ny = (y + j + height) % height;
 
                 count += cell[nx][ny];  // 确保正确的索引顺序
             }
         }
     }
 
     return count;
 }
 
 /**
  * @brief 更新世界中的细胞状态，根据康威生命游戏规则。
  */
 void update_cells()
 {
     int **new_cell;
     int **cell = world.cell;
     int width = world.width;
     int height = world.height;
     new_cell = (int **)malloc(width * sizeof(int *)); // 为行分配内存
     for (int i = 0; i < width; i++)
         new_cell[i] = (int *)malloc(height * sizeof(int)); // 为每一行分配列
 
     for (int i = 0; i < width; i++)
     {
         for (int j = 0; j < height; j++)
         {
             int count = count_neighbors(i, j);
             if (count < 2 || count > 3)
             {
                 new_cell[i][j] = 0;
             }
             else if (count == 3)
             {
                 new_cell[i][j] = 1;
             }
             else
             {
                 new_cell[i][j] = cell[i][j];
             }
         }
     }
     for (int i = 0; i < width; i++)
     {
         for (int j = 0; j < height; j++)
         {
             cell[i][j] = new_cell[i][j];
         }
     }
     for (int i = 0; i < width; i++)
         free(new_cell[i]);
     free(new_cell);
 }
 
 /**
  * @brief 释放世界中细胞数组所占用的内存。
  */
 void free_cells()
 {
     for (int i = 0; i < world.width; i++)
     {
         free(world.cell[i]);
     }
     free(world.cell);
 }