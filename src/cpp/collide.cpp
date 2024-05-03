/************************************************************************************
 * 程序：物理碰撞测试功能文件
 * 语言：C++
 * 编程人：呆呆兽（计科**班2021********）
 * 指导老师：钟凡
 * 创建时间：2022/4/10
 * 完成时间：2022/4/13
 *
 * 程序描述：    来不及写注释了，十一点多了要被公开处刑了啊啊啊啊啊啊啊
 *
 ************************************************************************************/
#include "collide.h"
#include "shape.h"
#include <cmath>
int ifCollideCar(const car& a, const car& b) {
	const point speed(a.speed.x - b.speed.x, a.speed.y - b.speed.y);//改变参考系，转b为静止
	const point& p0 = b.position;
	const point& p1 = a.position;//a的原位置
	const point p2(a.position.x + speed.x, a.position.y + speed.y);//a下一刻的位置

	bool yng = (p1.y - p2.y >= 0);//确保生成轨迹的次序由原位置开始
	bool xng = (p1.x - p2.x >= 0);
	
	for (int y = p1.y; yng ? (y >= p2.y) : (y <= p2.y); yng ? y-- : y++) {//更好的路径成为搜索，此处暴力遍历
		for (int x = p1.x; xng ? (x >= p2.x) : (x <= p2.x); xng ? x-- : x++) {
			if(4*((x-p1.x)*(p1.y-p2.y)-(y-p1.y)*(p1.x-p2.x))*((x-p1.x)*(p1.y-p2.y)-(y-p1.y)*(p1.x-p2.x))<=(p1.y-p2.y)*(p1.y-p2.y)+(p1.x-p2.x)*(p1.x-p2.x)){//符合要求的路径近似点
				//单格碰撞判断；
				bool coX = ((speed.x > 0 && x + 5 * a.size == p0.x) || (speed.x < 0 && x == p0.x + 5 * b.size)) && (y >= p0.y - 4 * b.size && p0.y >= y - 4 * a.size);
				bool coY = ((speed.y > 0 && y == p0.y - 4 * b.size) || (speed.y < 0 && y - 4 * a.size == p0.y)) && (x <= p0.x + 5 * b.size && p0.x <= x + 5 * a.size);
				if (coX && coY) return 3;
				else if (coY) return 2;
				else if (coX) return 1;
			}
		}
	}
	return 0;
}
void collideCar(car& a, car& b, int direction) {
	if (direction == 1||direction == 3) {//x方向
		int vx_a = ((a.mass - b.mass) * a.speed.x + 2 * b.mass * b.speed.x) / (a.mass + b.mass);
		int vx_b = ((b.mass - a.mass) * b.speed.x + 2 * a.mass * a.speed.x) / (a.mass + b.mass);
		a.speed.x = vx_a, b.speed.x = vx_b;
	}
	if(direction == 2||direction == 3) {//y方向
		int vy_a = ((a.mass - b.mass) * a.speed.y + 2 * b.mass * b.speed.y) / (a.mass + b.mass);
		int vy_b = ((b.mass - a.mass) * b.speed.y + 2 * a.mass * a.speed.y) / (a.mass + b.mass);
		a.speed.y = vy_a, b.speed.y = vy_b;
	}
}
int ifCollideWall(const car& a, const rectangle& wall) {
	const point& speed = a.speed;
	const point& p0 = wall.p1;
	const point& p1 = a.position;//a的原位置
	const point p2(a.position.x + speed.x, a.position.y + speed.y);//a下一刻的位置

	bool yng = (p1.y - p2.y >= 0);//确保生成轨迹的次序由原位置开始
	bool xng = (p1.x - p2.x >= 0);

	for (int y = p1.y; yng ? (y >= p2.y) : (y <= p2.y); yng ? y-- : y++) {//更好的路径成为搜索，此处暴力遍历
		for (int x = p1.x; xng ? (x >= p2.x) : (x <= p2.x); xng ? x-- : x++) {
			if (4 * ((x - p1.x) * (p1.y - p2.y) - (y - p1.y) * (p1.x - p2.x)) * ((x - p1.x) * (p1.y - p2.y) - (y - p1.y) * (p1.x - p2.x)) <= (p1.y - p2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x)) {//符合要求的路径近似点
				//单格碰撞判断；
				bool coX = ((speed.x > 0 && x + 5 * a.size == p0.x) || (speed.x < 0 && x == wall.p2.x)) && (y >= wall.p2.y && p0.y >= y - 4 * a.size);
				bool coY = ((speed.y > 0 && y == wall.p2.y) || (speed.y < 0 && y - 4 * a.size == p0.y)) && (x <= wall.p2.x && p0.x <= x + 5 * a.size);
				if (coX && coY) return 3;
				else if (coY) return 2;
				else if (coX) return 1;
			}
		}
	}
	return 0;
}
void collideWall(car& a, int direction) {
	direction == 1 ? a.speed.x *= -1 : 0;
	direction == 2 ? a.speed.y *= -1 : 0;
	direction == 3 ? a.speed.x *= -1, a.speed.y *= -1 : 0;
}

static int ifCollideCar_old(const car& a, const car& b) {
	int l1 = a.position.x, l2 = b.position.x;
	int r1 = l1 + 5 * a.size, r2 = l2 + 5 * b.size;
	int u1 = a.position.y, u2 = b.position.y;
	int d1 = u1 - 4 * a.size, d2 = u2 - 4 * b.size;
	if (((l1 - r2) == 1 || (l2 - r1) == 1 || (l1 - r2) == 0 || (l2 - r1) == 0) && (u1 >= d2 && u2 >= d1)) {
		return 1;
	}
	else if (((d2 - u1) == 1 || (d1 - u2) == 1 || (d2 - u1) == 0 || (d1 - u2) == 0) && (r1 >= l2 && r2 >= l1)) {
		return 2;
	}
	else if ((d2 - u1 == 1 || d1 - u2 == 1) && (l1 - r2 == 1 || l2 - r1 == 1)) {
		return 3;
	}
	else {
		return 0;
	}
}
static int ifCollideWall_old(const car& a, const rectangle& wall) {
	int l1 = a.position.x, l2 = wall.p1.x;
	int r1 = l1 + 5 * a.size, r2 = wall.p2.x;
	int u1 = a.position.y, u2 = wall.p1.y;
	int d1 = u1 - 4 * a.size, d2 = wall.p2.y;
	if ((abs(l1 - r2) == 1 || abs(l2 - r1) == 1) && (u1 >= d2 && u2 >= d1)) {
		return 1;
	}
	else if ((abs(u1 - d2) == 1 || abs(u2 - d1) == 1) && (r1 >= l2 && r2 >= l1)) {
		return 2;
	}
	else {
		return 0;
	}
}
