/************************************************************************************
 * 程序：基础图形化功能实现文件
 * 语言：C++
 * 编程人：呆呆兽（计科**班2021********）
 * 指导老师：钟凡
 * 创建时间：2022/4/10
 * 完成时间：2022/4/13
 *
 * 程序描述：    来不及写注释了，十一点多了要被公开处刑了啊啊啊啊啊啊啊
 *
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "shape.h"

bool __board[BOARD_W][BOARD_H] = { 0 };
void resetBoard() {
	for(int i=0;i<BOARD_W;i++)
		for (int j = 0; j < BOARD_H; j++) {
			__board[i][j] = 0;
		}
}
void printBoard(int x, int y, int h, int l) {
	system("cls");
	for (int i = 0; i <= l; i++) {
		printf("--");
	}
	printf("\n");
	for (int i = y + BOARD_H / 2 + h ; i >= y + BOARD_H / 2; i--) {
		for (int j = x + BOARD_W /2; j <= x + BOARD_W / 2 + l; j++) {
			printf("%c ", __board[j][i]?'@':' ');
		}
		printf("\n");
	}
	for (int i = 0; i <= l; i++) {
		printf("--");
	}
	printf("\n");
}
void printBoard(const point& xy, int h, int l) {
	system("cls");
	for (int i = 0; i <= l; i++) {
		printf("--");
	}
	printf("\n");
	for (int i = xy.y + BOARD_H / 2 + h; i >= xy.y + BOARD_H / 2; i--) {
		for (int j = xy.x + BOARD_W / 2; j <= xy.x + BOARD_W / 2 + l; j++) {
			printf("%c ", __board[j][i] ? '@' : '.');
		}
		printf("\n");
	}
	for (int i = 0; i <= l; i++) {
		printf("--");
	}
	printf("\n");
}
point::point():x(0),y(0) {}
point::point(const point& p):x(p.x),y(p.y) {}
point::point(int x, int y):x(x),y(y) {}
void point::set(const point& p) {
	x = p.x, y = p.y;
}
void point::set(int x, int y) {
	this->x = x, this->y = y;
}
void point::move(int x, int y) {
	set(this->x + x, this->y + y);
}
int point::draw() {
	__board[x + BOARD_W / 2][y + BOARD_H / 2] = 1;
	return 0;
}
rectangle::rectangle() :p1(0, 0), p2(0, 0) {}
rectangle::rectangle(const rectangle& rec):p1(rec.p1),p2(rec.p2) {}
rectangle::rectangle(const point& p1, const point& p2):p1(p1),p2(p2) {}
rectangle::rectangle(int x1, int y1, int x2, int y2):p1(x1,y1),p2(x2,y2) {}
void rectangle::set(const rectangle& rec) {
	p1.set(rec.p1), p2.set(rec.p2);
}
void rectangle::set(const point& p1, const point& p2) {
	this->p1.set(p1), this->p2.set(p2);
}
void rectangle::set(int x1, int y1, int x2, int y2) {
	p1.set(x1, y1), p2.set(x2, y2);
}
void rectangle::format() {
	using namespace std;
	int nx1 = min(p1.x, p2.x), nx2 = max(p1.x, p2.x);
	int ny1 = max(p1.y, p2.y), ny2 = min(p1.y, p2.y);
	p1.set(nx1, ny1), p2.set(nx2, ny2);
}
void rectangle::move(int x, int y) {
	p1.move(x, y), p2.move(x, y);
}
int rectangle::draw(bool cover) {
	if (p1.y<p2.y || p1.x>p2.x) {//负矩形无法画入画板
		return -1;
	}
	if (cover) {
		for (int i = p1.x; i <= p2.x; i++) {
			for (int j = p1.y; j >= p2.y; j--) {
				__board[i + BOARD_W/2][j + BOARD_H/2] = 1;
			}
		}
	}
	else {
		for (int i = p1.x; i <= p2.x; i++) {
			__board[i + BOARD_W / 2][p1.y + BOARD_H / 2] = __board[i + BOARD_W / 2][p2.y + BOARD_H / 2] = 1;
		}
		for (int i = p1.y; i >= p2.y; i--) {
			__board[p1.x + BOARD_W / 2][i + BOARD_H / 2] = __board[p2.x + BOARD_W / 2][i + BOARD_H / 2] = 1;
		}
	}
	return 0;
}
circle::circle() :p(0, 0), R(1) {}
circle::circle(int x, int y, int R) :p(x, y), R(R) {}
circle::circle(const point& p, int R):p(p),R(R) {}
circle::circle(const circle& circle):p(circle.p),R(circle.R) {}
void circle::set(int x, int y, int R) {
	p.set(x, y), this->R = R;
}
void circle::set(const point& p, int R) {
	this->p.set(p), this->R = R;
}
void circle::set(const circle& circle) {
	p.set(circle.p), R = circle.R;
}
void circle::move(int x, int y) {
	p.move(x, y);
}
int circle::draw(bool cover) {
	for (int i = p.x - R; i <= p.x + R; i++) {
		for (int j = p.y - R; j <= p.y + R; j++) {
			__board[i + BOARD_W/2][j + BOARD_H/2] = cover?(floor(sqrt((i-p.x)*(i-p.x)+(j-p.y)*(j-p.y))+0.5)<=R):(floor(sqrt((i-p.x)*(i-p.x)+(j-p.y)*(j-p.y))+0.5)==R);
		}
	}
	return 0;
}
car::car() :size(2), mass(1), speed(0, 0), position(0, 0), _body(0, 0, 10, -4), _wheel1(2, -6, 2), _wheel2(8, -6, 2) {}
car::car(const point& speed, const point& position, int size, int mass)	:size(size), mass(mass), speed(speed), position(position), _body(position.x, position.y, position.x + 5 * size, position.y - 2 * size), _wheel1(position.x + size, position.y - 3 * size, size), _wheel2(position.x + 4 * size, position.y - 3 * size, size) {}
car::car(const car& car) : size(car.size), mass(car.mass), speed(car.speed), position(car.position), _body(car._body), _wheel1(car._wheel1), _wheel2(car._wheel2) {}
void car::set(const car& car) {
	size = car.size, mass = car.mass;
	position.set(car.position);
	speed.set(car.speed);
	_body.set(car._body);
	_wheel1.set(car._wheel1);
	_wheel2.set(car._wheel2);
}
void car::setSpeed(int x, int y) {
	speed.set(x, y);
}
void car::move(int x, int y) {
	position.move(x, y), _body.move(x, y), _wheel1.move(x, y), _wheel2.move(x, y);
}
void car::move(int time) {
	position.move(time * speed.x, time * speed.y), _body.move(time * speed.x, time * speed.y), _wheel1.move(time * speed.x, time * speed.y), _wheel2.move(time * speed.x, time * speed.y);
}
int car::draw(bool cover) {
	_body.draw(cover), _wheel1.draw(cover), _wheel2.draw(cover);
	return 0;
}