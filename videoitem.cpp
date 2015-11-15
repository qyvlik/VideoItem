#include "videoitem.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QPixmap>
#include <QDebug>

VideoItem::VideoItem()
{
    setFlag(QQuickItem::ItemHasContents);
    connect(&player, SIGNAL(readOneFrame(QPixmap,int,int)), this,
            SLOT(slotgetFrame(QPixmap,int,int)));
}


VideoItem::~VideoItem()
{
}


void VideoItem::slotgetFrame(QPixmap p, int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
    mFrame = p;
    this->update();
}


void VideoItem::paint(QPainter *painter)
{
    painter->drawPixmap(this->x(),this->y(),
                        mFrame.scaled(this->width(),this->height(),Qt::KeepAspectRatio));
}


void VideoItem::setSource(QString str)
{
    player.setSource(str);
}


void VideoItem::play()
{
    player.play();
}


void VideoItem::pause()
{
    player.pause();
}


void VideoItem::stop()
{
    player.stop();
}


void VideoItem::setVolume(int value)
{
    player.setVolume(value);
}


void VideoItem::seek(qint64 s)
{
    player.seek(s);
}
