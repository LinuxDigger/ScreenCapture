#include "ScreenRecordTest.h"
#include "ScreenRecordImpl.h"
#include <QTimer>

ScreenRecord::ScreenRecord(QObject *parent) :
	QObject(parent)
{
	ScreenRecordImpl *sr = new ScreenRecordImpl(this);
	connect(this, SIGNAL(StartRecord()), sr, SLOT(Start()));
	connect(this, SIGNAL(FinishRecord()), sr, SLOT(Finish()));
	Start();
	//QTimer *t = new QTimer(this);
	//connect(t, SIGNAL(timeout()), this, SLOT(Finish()));
	//t->start(1000);
	QTimer::singleShot(5000, this, SLOT(Finish()));
}

void ScreenRecord::Start()
{
	emit StartRecord();
}

void ScreenRecord::Stop()
{
}

void ScreenRecord::Finish()
{
	emit FinishRecord();
}