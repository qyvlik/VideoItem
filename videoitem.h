#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QQuickPaintedItem>

#include "videoplayer.h"

class VideoItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    VideoItem();
    ~VideoItem();
    void paint(QPainter *painter);

    Q_INVOKABLE void setSource(QString str); //设置播放文件
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void setVolume(int value); //设置音量（0-128）
    Q_INVOKABLE void seek(qint64); //快进和快退（微秒）
    Q_INVOKABLE qint64 totalTime(){return player.totalTime();} //获取总时间 （微秒）
    Q_INVOKABLE qint64 currentTime(){return player.currentTime();} //获取当前时间 （毫秒）

private slots:
    void slotgetFrame(QPixmap p,int w,int h);

private:
    QPixmap mFrame;
    VideoPlayer player;
};

#endif // VIDEOITEM_H
