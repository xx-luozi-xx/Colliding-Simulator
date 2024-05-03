/************************************************************************************
 * 程序：基础图形化及物理碰撞测试主函数文件
 * 语言：C++
 * 编程人：呆呆兽（计科**班2021********）
 * 指导老师：钟凡
 * 创建时间：2022/4/10
 * 完成时间：2022/4/13
 *
 * 程序描述：    来不及写注释了，十一点多了要被公开处刑了啊啊啊啊啊啊啊
 *
 ************************************************************************************/
#include "shape.h"
#include "collide.h"
#include <stdio.h>
#include <vector>
#include <windows.h>

int test1();//完全弹性碰墙
int test2();//等质量完全弹性正碰
int test3();//等质量完全弹性斜碰
int test4();//等质量完全弹性对角正碰
int test5();//二车等质量等速度完全弹性碰墙
int test6();//二车不等质量不等速度近似完全弹性碰墙
int test7();//质量不等一碰三（低速，以地表为参考系）
int test8();//质量不等一碰三（中速，以被撞一号车为参考系）
int test9();//质量不等一碰三（高速，以被撞二号车为参考系）
int test10();//质量不等一碰三（高速，以被撞二号车为参考系）

int main() {
 	SetConsoleOutputCP(CP_UTF8);

	test7();
	test1(); //完全弹性碰墙
	test2(); //等质量完全弹性正碰
	test3(); //等质量完全弹性斜碰
	test4(); //等质量完全弹性对角正碰
	test5(); //二车等质量等速度完全弹性碰墙
	test6(); //二车不等质量不等速度近似完全弹性碰墙
	test7(); //质量不等一碰三（低速，以地表为参考系）
	test8(); //质量不等一碰三（中速，以被撞一号车为参考系）
	test9(); //质量不等一碰三（较高速，以被撞二号车为参考系）
	test10();//质量不等一碰三（高速，以被撞二号车为参考系）
	return 0;
}

int test10() {//质量不等一碰三（高速，以被撞二号车为参考系）
	point car1speed(20, 0);
	point car1poistion(-60, 12);
	car car1(car1speed, car1poistion, 1, 100);

	point car2speed(0, 0);
	point car2poistion(15, 12);
	car car2(car2speed, car2poistion, 1, 3);

	point car3speed(0, 0);
	point car3poistion(car2.position.x + 5 * car2.size + 1, 12);
	car car3(car3speed, car3poistion, 1, 1);

	point car4speed(0, 0);
	point car4poistion(car3.position.x + 5 * car3.size + 1, 12);
	car car4(car4speed, car4poistion, 1, 2);

	car cars[4] = { car1, car2, car3, car4 };
	//cars[0].set(car1), cars[1].set(car2), cars[2].set(car3), cars[3].set(car4);

	for (int i = 1; i <= 30; i++) {
		resetBoard();
		int steadyState;
		do {
			steadyState = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = i + 1; j < 4; j++) {
					int co = ifCollideCar(cars[i], cars[j]);
					steadyState += co;
					if (co) {
						collideCar(cars[i], cars[j], co);
					}
				}
			}

		} while (steadyState);

		for (int i = 0; i < 4; i++) {
			cars[i].move(1);
		}
		/*
		for (auto i : cars) {
			i.move(1);
		}
		*/
		for (auto i : cars) {
			i.draw();
		}

		cars[2].draw(1);
		/*
		car1.draw(1);
		car2.draw();
		car3.draw(1);
		car4.draw();
		*/
		printBoard(-30 + cars[2].position.x, 0, 20, 60 - 2);
		printf("\n      test 9 质量不等一碰三（高速，以被撞二号车为参考系） Round %d/30", i);
		printf("\n        四辆车的速度 ：  %d %d %d %d", cars[0].speed.x, cars[1].speed.x, cars[2].speed.x, cars[3].speed.x);
	}

	return 0;
}
int test9() {//质量不等一碰三（较高速，以被撞二号车为参考系）
	point car1speed(10, 0);
	point car1poistion(-30, 12);
	car car1(car1speed, car1poistion, 1, 100);

	point car2speed(0, 0);
	point car2poistion(15, 12);
	car car2(car2speed, car2poistion, 1, 3);

	point car3speed(0, 0);
	point car3poistion(car2.position.x + 5 * car2.size + 1, 12);
	car car3(car3speed, car3poistion, 1, 1);

	point car4speed(0, 0);
	point car4poistion(car3.position.x + 5 * car3.size + 1, 12);
	car car4(car4speed, car4poistion, 1, 2);

	car cars[4] = { car1, car2, car3, car4 };
	//cars[0].set(car1), cars[1].set(car2), cars[2].set(car3), cars[3].set(car4);

	for (int i = 1; i <= 30; i++) {
		resetBoard();
		int steadyState;
		do {
			steadyState = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = i + 1; j < 4; j++) {
					int co = ifCollideCar(cars[i], cars[j]);
					steadyState += co;
					if (co) {
						collideCar(cars[i], cars[j], co);
					}
				}
			}

		} while (steadyState);

		for (int i = 0; i < 4; i++) {
			cars[i].move(1);
		}
		/*
		for (auto i : cars) {
			i.move(1);
		}
		*/
		for (auto i : cars) {
			i.draw();
		}

		cars[2].draw(1);
		/*
		car1.draw(1);
		car2.draw();
		car3.draw(1);
		car4.draw();
		*/
		printBoard(-30 + cars[2].position.x, 0, 20, 60 - 2);
		printf("\n      test 9 质量不等一碰三（较高速，以被撞二号车为参考系） Round %d/30", i);
		printf("\n        四辆车的速度 ：  %d %d %d %d", cars[0].speed.x, cars[1].speed.x, cars[2].speed.x, cars[3].speed.x);
	}

	return 0;
}
int test8() {//质量不等一碰三（中速，以被撞一号车为参考系）
	point car1speed(5, 0);
	point car1poistion(-10, 12);
	car car1(car1speed, car1poistion, 1, 100);

	point car2speed(0, 0);
	point car2poistion(15, 12);
	car car2(car2speed, car2poistion, 1, 3);

	point car3speed(0, 0);
	point car3poistion(car2.position.x + 5 * car2.size + 1, 12);
	car car3(car3speed, car3poistion, 1, 1);

	point car4speed(0, 0);
	point car4poistion(car3.position.x + 5 * car3.size + 1, 12);
	car car4(car4speed, car4poistion, 1, 2);

	car cars[4] = { car1, car2, car3, car4 };
	//cars[0].set(car1), cars[1].set(car2), cars[2].set(car3), cars[3].set(car4);

	for (int i = 1; i <= 30; i++) {
		resetBoard();
		int steadyState;
		do {
			steadyState = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = i + 1; j < 4; j++) {
					int co = ifCollideCar(cars[i], cars[j]);
					steadyState += co;
					if (co) {
						collideCar(cars[i], cars[j], co);
					}
				}
			}

		} while (steadyState);

		for (int i = 0; i < 4; i++) {
			cars[i].move(1);
		}
		/*
		for (auto i : cars) {
			i.move(1);
		}
		*/
		for (auto i : cars) {
			i.draw();
		}

		cars[2].draw(1);
		/*
		car1.draw(1);
		car2.draw();
		car3.draw(1);
		car4.draw();
		*/
		printBoard(-20+cars[1].position.x, 0, 20, 60 - 2);
		printf("\n      test 8 质量不等一碰三（中速，以被撞一号车为参考系） Round %d/30", i);
		printf("\n        四辆车的速度 ：  %d %d %d %d", cars[0].speed.x, cars[1].speed.x, cars[2].speed.x, cars[3].speed.x);
	}

	return 0;
}
int test7() {//质量不等一碰三（低速，以地表为参考系）
	point car1speed(5, 0);
	point car1poistion(-10, 12);
	car car1(car1speed, car1poistion, 1, 100);

	point car2speed(0, 0);
	point car2poistion(15, 12);
	car car2(car2speed, car2poistion, 1, 3);

	point car3speed(0,0);
	point car3poistion(car2.position.x + 5 * car2.size + 1, 12);
	car car3(car3speed, car3poistion, 1, 1);

	point car4speed(0, 0);
	point car4poistion(car3.position.x + 5 * car3.size + 1,12);
	car car4(car4speed, car4poistion, 1, 2);

	car cars[4] = {car1, car2, car3, car4};
	//cars[0].set(car1), cars[1].set(car2), cars[2].set(car3), cars[3].set(car4);

	for (int i = 1; i <= 30; i++) {
		resetBoard();
		int steadyState;
		do {
			steadyState = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = i + 1; j < 4; j++) {
					int co = ifCollideCar(cars[i], cars[j]);
					steadyState += co;
					if (co) {
						collideCar(cars[i],cars[j],co);
					}
				}
			}
			
		} while (steadyState);
		
		for (int i = 0; i < 4; i++) {
			cars[i].move(1);
		}
		/*
		for (auto i : cars) {
			i.move(1);
		}
		*/
		for (auto i : cars) {
			i.draw();
		}

		cars[2].draw(1);
		/*
		car1.draw(1);
		car2.draw();
		car3.draw(1);
		car4.draw();
		*/
		printBoard(0, 0, 20, 60 - 2);
		printf("\n      test 7 质量不等一碰三（低速，以地表为参考系） Round %d/30", i);
		printf("\n        四辆车的速度 ：  %d %d %d %d", cars[0].speed.x, cars[1].speed.x, cars[2].speed.x, cars[3].speed.x);
	
	}

	return 0;
}
int test6() {//二车不等质量不等速度近似完全弹性碰墙
	rectangle wall[4];
	wall[0].set(0, 20, 0, 0);
	wall[1].set(0, 20, 40, 20);
	wall[2].set(40, 20, 40, 0);
	wall[3].set(0, 0, 40, 0);

	point car1speed(4, 2);
	point car1poistion(8, 12 - 6);
	car car1(car1speed, car1poistion, 2, 3);

	point car2speed(-1, -1);
	point car2poistion(20, 12 + 6);
	car car2(car2speed, car2poistion, 1, 1);

	for (int i = 1; i <= 128*2; i++) {
		resetBoard();
		int steadyState;
		do {
			steadyState = 0;
			for (auto i : wall) {
				int co = ifCollideWall(car1, i);
				steadyState += co;
				if (co) {
					collideWall(car1, co);
				}
				co = ifCollideWall(car2, i);
				steadyState += co;
				if (co) {
					collideWall(car2, co);
				}
			}
			int co = ifCollideCar(car1, car2);
			steadyState += co;
			if (co) {
				collideCar(car1, car2, co);
			}
		} while (steadyState);
		car1.move(1);
		car2.move(1);

		car1.draw();
		car2.draw();

		for (auto i : wall) {
			i.draw();
		}

		printBoard(0, 0);
		printf("\n      test 6 二车不等质量不等速度近似完全弹性碰墙 Round %d/256", i);
		printf("\n      小车速度:(%d，%d),大车速度:(%d,%d)", car2.speed.x, car2.speed.y, car1.speed.x, car1.speed.y);
	}

	return 0;
}
int test5() {//二车等质量等速度完全弹性碰墙
	rectangle wall[4];
	wall[0].set(0, 20, 0, 0);
	wall[1].set(0, 20, 40, 20);
	wall[2].set(40, 20, 40, 0);
	wall[3].set(0, 0, 40, 0);

	point car1speed(1, 1);
	point car1poistion(8, 12 - 6);
	car car1(car1speed, car1poistion, 1, 1);

	point car2speed(-1, -1);
	point car2poistion(20, 12 + 6);
	car car2(car2speed, car2poistion, 1, 1);

	for (int i = 1; i <= 128; i++) {
		resetBoard();

		for (auto i : wall) {
			int co = ifCollideWall(car1, i);
			if (co) {
				collideWall(car1, co);
			}
			co = ifCollideWall(car2, i);
			if (co) {
				collideWall(car2, co);
			}
		}

		int co = ifCollideCar(car1, car2);
		if (co) {
			collideCar(car1, car2, co);
		}

		car1.move(1);
		car2.move(1);

		car1.draw();
		car2.draw();

		for (auto i : wall) {
			i.draw();
		}

		printBoard(0, 0);
		printf("\n      test 5 二车等质量等速度完全弹性碰墙 Round %d/128", i);
	
	}

	return 0;
}
int test4() {
	point car1speed(1, 1);
	point car1poistion(0, 2);
	car car1(car1speed, car1poistion, 1, 1);

	point car2speed(0, 0);
	point car2poistion(10+2, 15+2);
	car car2(car2speed, car2poistion, 2, 1);

	for (int i = 1; i <= 25; i++) {
		resetBoard();

		int co = ifCollideCar(car1, car2);
		if (co) {
			collideCar(car1, car2, co);
		}

		car1.move(1);
		car2.move(1);

		car1.draw();
		car2.draw(1);

		printBoard(0, 0);
		printf("\n      test 4 等质量完全弹性对角正碰 Round %d/25", i);
	}
	return 0;
}
int test3() {//等质量完全弹性斜碰
	point car1speed(1, 1);
	point car1poistion(0, 2);
	car car1(car1speed, car1poistion, 1, 1);

	point car2speed(0, 0);
	point car2poistion(10, 15);
	car car2(car2speed, car2poistion, 1, 1);

	for (int i = 1; i <= 25; i++) {
		resetBoard();

		int co = ifCollideCar(car1, car2);
		if (co) {
			collideCar(car1, car2, co);
		}

		car1.move(1);
		car2.move(1);

		car1.draw();
		car2.draw(1);

		printBoard(0, 0);
		printf("\n      test 3 等质量完全弹性斜碰 Round %d/25", i);
	}
	return 0;
}
int test2() {//等质量完全弹性正碰
	point car1speed(1, 0);
	point car1poistion(0, 10);
	car car1(car1speed, car1poistion, 1, 1);

	point car2speed(-1, 0);
	point car2poistion(20, 10);
	car car2(car2speed, car2poistion, 1, 1);

	for (int i = 1; i <= 20; i++) {
		resetBoard();

		int co = ifCollideCar(car1, car2);
		if (co) {
			collideCar(car1, car2, co);
		}

		car1.move(1);
		car2.move(1);
		
		car1.draw();
		car2.draw(1);

		printBoard(0, 0);
		printf("\n      test 2 等质量完全弹性正碰 Round %d/20", i);
	}
	return 0;
}
int test1(){//test 1 完全弹性碰墙 
	rectangle wall[4];
	wall[0].set(0, 20, 0, 0);
	wall[1].set(0, 20, 40, 20);
	wall[2].set(40, 20, 40, 0);
	wall[3].set(0, 0, 40, 0);

	point car1speed(1, 1);
	point car1poistion(10, 10);
	car car1(car1speed, car1poistion, 2, 1);
	
	for (int i = 1; i <= 128; i++) {
		resetBoard();

		for (auto i : wall){
			int co = ifCollideWall(car1,i);
			if (co) {
				collideWall(car1, co);
			}
		}

		car1.move(1);

		car1.draw();
		for (auto i : wall) {
			i.draw();
		}

		printBoard(0,0);
		printf("\n      test 1 完全弹性碰墙 Round %d/128", i);
	}
	
	return 0;
}