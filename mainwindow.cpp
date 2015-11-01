/*
 * 
Disposera GUI
 hvis - image viewer with touchscreen swipe
 
Copyright 2015 Waitman Gobble <ns@waitman.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

* 
*/

#include "mainwindow.h"
#include "ui_hvis.h"
#include <QStringList>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QImage>
#include <QKeyEvent>
#include <QDir>
#include <QFileInfo>
#include <QDesktopWidget>
#include <QProcess>

#define CONVERT "/usr/bin/convert"
#define THUMBSIZE "1000x1000"
#define THUMBQUALITY "90"
#define THUMBDENSITY "120"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::MainWindow)
{

	QFileInfo fi(QDir::currentPath());
	bool can_write=fi.permission(QFile::WriteUser);
	if (!can_write)
	{
			qDebug() << "Error: Write Access Denied in current Directory.";
			exit(1);
	}
	
	QByteArray value;
	value = qgetenv("CONVERT");
	if (value.isEmpty())
	{
		def_convert = CONVERT;
	} else {
		def_convert = value.constData();
	}
	value = qgetenv("THUMBSIZE");
	if (value.isEmpty())
	{
		def_thumbsize = THUMBSIZE;	
	} else {
		def_thumbsize = value.constData();
	}
	value = qgetenv("THUMBQUALITY");
	if (value.isEmpty())
	{
		def_thumbquality = THUMBQUALITY;
	} else {
		def_thumbquality = value.constData();		
	}
	value = qgetenv("THUMBDENSITY");
	if (value.isEmpty())
	{
		def_thumbdensity = THUMBDENSITY;		
	} else {
		def_thumbdensity = value.constData();
	}
	
	QStringList filters;
	filters << "*.JPG" << "*.jpg";
	QDir dir(QDir::currentPath());
	image_list = dir.entryInfoList(filters, 
		QDir::Files|QDir::NoDotAndDotDot);

	if (image_list.count()<1)
	{
		qDebug() << "Error: No JPEG Images Exist in Current Directory.";
		exit(1);
	}
	
	ui->setupUi(this);

	scene = new HVisScene(this);
	
	QRect rec = QApplication::desktop()->screenGeometry();
	int height = rec.height();
	int width = rec.width();

	QHBoxLayout *layout = new QHBoxLayout;
	view = new QGraphicsView(scene);
	view->resize(width,height);
	view->setBackgroundBrush(QColor(48,48,48));
	
	layout->addWidget(view);
	
	layout->setSpacing(0);
	layout->setMargin(0);
	layout->setContentsMargins(0,0,0,0);

	if (!QDir("save").exists())
	{
			QDir().mkdir("save");
	}
	if (!QDir("save/th").exists())
	{
		QDir().mkdir("save/th");
	}
	save_path = QDir("save").absolutePath();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    index=0;
    vw = view->width();
    vh = view->height();
    
    connect(scene,SIGNAL(swipeRight()),SLOT(advanceScene()));
    connect(scene,SIGNAL(swipeLeft()),SLOT(retractScene()));
    
    displayScene();

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	QString key = event->text().toLower();
	
	if ((key=="x")||(key=="q"))
	{
		exit(0);
	}
	if (key==" ")
	{
		advanceScene();
	}
	if (key=="+")
	{
		index+=9;
		advanceScene();
	}
	if (key=="-")
	{
		index-=9;
		retractScene();
	}
	if (key=="b")
	{
		retractScene();
	}
	if (key=="s")
	{
		QFileInfo f = image_list[index];
		QString dest(save_path + "/" + f.fileName());
		QString thumdest(save_path + "/th/" + f.fileName());
		QFile::copy(f.absoluteFilePath(), dest);
		QProcess opp;
		opp.deleteLater();
		opp.startDetached(def_convert, QStringList() << "-scale" << 
			def_thumbsize << "-size" << def_thumbsize << "-strip" << 
			"-quality" << def_thumbquality << "-density" << 
			def_thumbdensity << dest << thumdest);
		
	}
	if (key=="r") 
	{
		QFileInfo f = image_list[index];
		QProcess opp;
		opp.start(def_convert, QStringList() << "-rotate" << "90" << 
			"-quality" << "100" << f.absoluteFilePath() << 
			f.absoluteFilePath());
		opp.waitForFinished();
		opp.close();
		displayScene();
	}
	if (key=="l")
	{
		QFileInfo f = image_list[index];
		QProcess opp;
		opp.start(def_convert, QStringList() << "-rotate" << "-90" << 
			"-quality" << "100" << f.absoluteFilePath() << 
			f.absoluteFilePath());
		opp.waitForFinished();
		opp.close();
		displayScene();
	}
}
void MainWindow::displayScene(void)
{
	    QFileInfo f = image_list[index];
		scene->displayImage(f.absoluteFilePath(), vh, vw);
}
void MainWindow::advanceScene(void)
{
		index++;
		if (index>=image_list.count()) index=0;
	    QFileInfo f = image_list[index];
		scene->displayImage(f.absoluteFilePath(), vh, vw);
}
void MainWindow::retractScene(void)
{
		index--;
		if (index<0) index=image_list.count()-1;
	    QFileInfo f = image_list[index];
		scene->displayImage(f.absoluteFilePath(), vh, vw);

}
MainWindow::~MainWindow()
{
	delete ui;
}

//EOF
