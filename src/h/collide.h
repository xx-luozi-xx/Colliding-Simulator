/************************************************************************************
 * 程序：物理碰撞测试头文件
 * 语言：C++
 * 编程人：呆呆兽（计科**班2021********）
 * 指导老师：钟凡
 * 创建时间：2022/4/10
 * 完成时间：2022/4/13
 *
 * 程序描述：    来不及写注释了，十一点多了要被公开处刑了啊啊啊啊啊啊啊
 *
 ************************************************************************************/
#pragma once
#include "shape.h"

int ifCollideCar(const car& a, const car& b);//返回1x方向碰，2y方向碰,3对角碰，0不碰；车的碰撞体积为包含车的最小矩形，下同
void collideCar(car& a, car& b, int direction);//direction为1x方向碰，2y方向碰；
int ifCollideWall(const car& a, const rectangle& wall);//返回1x方向碰，2y方向碰，0不碰；wall必须是规范矩形
void collideWall(car& a, int direction);//direction为1x方向碰，2y方向碰；