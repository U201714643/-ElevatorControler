// 单级中断机器码生成器.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define IADDR1 0x300	//300是字地址（也是行号） 这后面藏了2个0
#define IADDR2 0x350	//350是字地址（也是行号） 这后面藏了2个0
#define IADDR3 0x3A0	//3A0是字地址（也是行号） 这后面藏了2个0

#define source "D:\\[[learn]]\\组成原理课程设计\\团队\\HEX\\INTMAIN3.hex"
#define intcode1 "D:\\[[learn]]\\组成原理课程设计\\团队\\HEX\\中断演示3-1.hex"
#define intcode2 "D:\\[[learn]]\\组成原理课程设计\\团队\\HEX\\中断演示3-2.hex"
#define intcode3 "D:\\[[learn]]\\组成原理课程设计\\团队\\HEX\\中断演示3-3.hex"
#define outpath "D:\\[[learn]]\\组成原理课程设计\\团队\\HEX\\INTFULL3.hex"
#define duizhansheding "20100001\n40906000\n201e0ffc\n201d0ffc\n40806000\n"	//设置堆栈（这个过程中要关中断）

char zd1[1024][16];
char zd2[1024][16];
char zd3[1024][16];
char rbq[1024][16];

int main()
{
	FILE * fpo, *fps, *fp1i, *fp2i, *fp3i;
	int i = 5;	//初始化内容（#define duizhansheding）的行数
	printf("源文件放置于%s\n中断源文件1放置于%s\n中断源文件1放置于%s\n中断源文件1放置于%s\n新文件放置于%s\n", source, intcode1, intcode2, intcode3, outpath);
	printf("中断程序1起始地址(16进制)：0x%08x\n", IADDR1 << 2);
	printf("中断程序2起始地址(16进制)：0x%08x\n", IADDR2 << 2);
	printf("中断程序3起始地址(16进制)：0x%08x\n", IADDR3 << 2);
	if (fopen_s(&fps, source, "rb")) {
		printf("源文件放置于%s!!!!!\n源文件放置于%s!!!!!\n源文件放置于%s!!!!!\n", source, source, source);
		getchar();
		return -1;
	}
	if (fopen_s(&fp1i, intcode1, "rb")) {
		printf("中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n", intcode1, intcode1, intcode1);
		getchar();
		return -1;
	}
	if (fopen_s(&fp2i, intcode2, "rb")) {
		printf("中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n", intcode2, intcode2, intcode2);
		getchar();
		return -1;
	}
	if (fopen_s(&fp3i, intcode3, "rb")) {
		printf("中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n中断源文件放置于%s\n!!!!!\n", intcode3, intcode3, intcode3);
		getchar();
		return -1;
	}
	fopen_s(&fpo, outpath, "wb");
	printf("堆栈初始位置(16进制)：0x00000ffc\n");
	fprintf(fpo, "%s", duizhansheding);
	while (fgets(rbq[i], 32, fps)) {
		fprintf(fpo, "%s", rbq[i]);
		i++;
	}
	for (; i < IADDR1; i++) {	//地址实际为12位
		fprintf(fpo, "00000000\n");
	}
	while (fgets(zd1[i], 32, fp1i)) {
		fprintf(fpo, "%s", zd1[i]);
		i++;
	}
	for (; i < IADDR2; i++) {	//地址实际为12位
		fprintf(fpo, "00000000\n");
	}
	while (fgets(zd2[i], 32, fp2i)) {
		fprintf(fpo, "%s", zd2[i]);
		i++;
	}
	for (; i < IADDR3; i++) {	//地址实际为12位
		fprintf(fpo, "00000000\n");
	}
	while (fgets(zd3[i], 32, fp3i)) {
		fprintf(fpo, "%s", zd3[i]);
		i++;
	}
	fclose(fpo);
	fclose(fps);
	fclose(fp1i);
	fclose(fp2i);
	fclose(fp3i);
	printf("成功\n");
	getchar();
	return 0;
}