#ifndef _CONWAY_CRAZYFISH_
#define _CONWAY_CRAZYFISH_

/**
 * @file Conway.h
 * @brief 康威生命游戏的实现头文件。
 * 
 * 该文件定义了康威生命游戏的核心数据结构和函数声明。
 */

/**
 * @brief 世界结构体，表示细胞自动机的世界。
 */
struct World
{
    int width;  ///< 矩阵宽度
    int height; ///< 矩阵高度
    int **cell; ///< 二维数组，表示细胞状态（0 表示死，1 表示活）
};

/// 声明在外部文件会有一个 World 的实例 world 定义
extern struct World world;

/// 声明在外部文件会有一个 int 的实例 boundary 定义
extern int boundary;    ///< 用于控制世界的边界（0 表示世界外部是空白；1 表示世界是循环的）

/**
 * @brief 初始化世界中的细胞。
 * @param _w 世界的宽度。
 * @param _h 世界的高度。
 */
void init_cells(int _w, int _h);

/**
 * @brief 随机设置世界中的细胞状态。
 */
void set_rand_cells();

/**
 * @brief 从 RLE 文件加载模式到世界中的指定位置。
 * @param _x 模式的起始 x 坐标。
 * @param _y 模式的起始 y 坐标。
 * @param rle_file RLE 文件的路径。
 */
void load_pattern(int _x, int _y, char *rle_file);

/**
 * @brief 绘制当前世界中的细胞状态。
 */
void draw_cells();

/**
 * @brief 计算指定位置细胞的邻居数量。
 * @param x 细胞的 x 坐标。
 * @param y 细胞的 y 坐标。
 * @return 邻居数量。
 */
int count_neighbors(int x, int y);

/**
 * @brief 更新世界中的细胞状态，根据康威生命游戏规则。
 */
void update_cells();

/**
 * @brief 释放世界中细胞数组所占用的内存。
 */
void free_cells();

#endif