/************************************************************************************
 * 程序：基础图形化头文件
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
#define BOARD_H 10000      //这两个参数是画板大小，可以通过这俩来控制碰撞过程的模拟速度（懒得加系统延迟暴力延迟）
#define BOARD_W 10000/4   

extern bool __board[BOARD_W][BOARD_H];

struct point;
struct rectangle;
struct circle;
class car;

void printBoard(int x = 0, int y = 0, int h = 20, int l = 40);
void printBoard(const point& xy, int h = 20, int l = 40);
void resetBoard();

struct point {
	int x, y;
	point();
	point(const point& p);
	point(int x, int y);	
	void set(const point& p);
	void set(int x, int y);
	void move(int x, int y);
	int draw();
};
struct rectangle {
	point p1, p2;
	rectangle();
	rectangle(const rectangle& rec);
	rectangle(const point& p1, const point& p2);
	rectangle(int x1, int y1, int x2, int y2);
	void set(const rectangle& rec);
	void set(const point& p1, const point& p2);
	void set(int x1, int y1, int x2, int y2);
	void format();
	void move(int x, int y);
	int draw(bool cover = 0);
};
struct circle {
	point p;
	int R;
	circle();
	circle(int x, int y, int R);
	circle(const point& p, int R);
	circle(const circle& circle);
	void set(int x, int y, int R);
	void set(const point& p, int R); 
	void set(const circle& circle);
	void move(int x, int y);
	int draw(bool cover = 0);
};
class car {
public:
	int size;
	int mass;
	point speed;
	point position;//左上角坐标
	car();
	car(const point& speed, const point& position, int size = 2, int mass = 1);
	car(const car& car);
	void set(const car& car);
	void setSpeed(int x, int y);
	void move(int x, int y);
	void move(int time);
	int draw(bool cover = 0);
private:
	rectangle _body;
	circle _wheel1, _wheel2;
};
