#include "rgbwidget.h"
#include<QDebug>
#include<QFile>
#include<QRandomGenerator>
#include"utility.h"
#include<QTimer>

// Widget shows a RGB view

RGBWidget::RGBWidget():sharedMemory("RGBWidget")
{
	QTimer *timer = new QTimer(this);
	if (!sharedMemory.attach())
	{
		sharedMemory.create(sizeof(float[3]));
	}

	connect(timer, &QTimer::timeout, [=]() {
		sharedMemory.lock();
		const float *data = (float*)sharedMemory.constData();
		rotate_x = data[0];
		rotate_y = data[1];
		rotate_z = data[2];
		sharedMemory.unlock();
		update();
	});
	timer->start(40);

}


void RGBWidget::mouseMoveEvent(QMouseEvent *event)
{
	OpenGL3DWidget::mouseMoveEvent(event);
	sharedMemory.lock();
	float *data = (float*)sharedMemory.data();
	data[0] = rotate_x;
	data[1] = rotate_y;
	data[2] = rotate_z;
	sharedMemory.unlock();
}

double RGBWidget::_rotate_x = 15.;
double RGBWidget::_rotate_y = -70.;
double RGBWidget::_rotate_z = 0.;