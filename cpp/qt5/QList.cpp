/*============================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename : QList.cpp
 *   author : sulit - sulitsrc@163.com
 *   last modified : 2015-09-02 17:06
 *   description :
 *
 *============================================*/

#include <QDebug>

int main(int argc, char *argv[])
{
	QList<QString> list;

	QString str("This is a test string");
	list<<str;

	qDebug()<<list[0]<<"How are you!";
	return 0;
}
