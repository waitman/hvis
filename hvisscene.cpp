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

#include "hvisscene.h"
#include <QString>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

HVisScene::HVisScene(QObject *parent)
    : QGraphicsScene(parent)
{
	has_shown=false;
}

void HVisScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	mouse_x = mouseEvent->scenePos().x();
}

/*
void HVisScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

}
*/

void HVisScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (mouseEvent->scenePos().x()>mouse_x)
	{
		emit swipeRight();
	} else {
		emit swipeLeft();
	}
}

void HVisScene::displayImage(QString path, int vh, int vw)
{
	//scene->clear();
	if (has_shown)
	{
		removeItem(pitem);
		delete pitem;
	}
	image.load(path);
	
	pitem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	pitem->setTransformationMode(Qt::SmoothTransformation);

	double scale;
	int nh = image.height();
	
	scale = 1.0;
	if (image.width()>=vw)
	{
		scale = (double) (vw-5)/image.width();
		nh = image.height()*scale;
	}
	if (nh>=vh)
	{
		scale = (double) (vh-5)/image.height();
	}
	
	if (scale>1) scale=1;
	pitem->setScale( scale );
	setSceneRect(0, 0, image.width()*scale, image.height()*scale);
 	addItem(pitem);	
 	has_shown = true;

}
