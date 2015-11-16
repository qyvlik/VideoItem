//! 修改自
//! [分享一个 Qt + FFMPEG + SDL 实现的视频播放器【申精】](http://bbs.csdn.net/topics/390386771)

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include <QImage>
#include <QList>
#include <QPixmap>
#include <QDebug>

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <SDL_stdinc.h>
    #include <SDL_mutex.h>
}

/*解码视频的线程*/
class DecodeVideo :public QThread
{
    Q_OBJECT
public:
    explicit DecodeVideo();
    ~DecodeVideo();
    void setPacket(AVPacket pkt){packet = pkt;}
    void setAVCodecContext(AVCodecContext*ctx);
    void setMutex(SDL_mutex *m){mutex = m;}

    static void set_dst_width(int w){
        DecodeVideo::dst_width = w;
    }

    static void set_dst_height(int h){
        DecodeVideo::dst_height = h;
    }

protected:
    void run();

signals:
    void readOneFrame(QPixmap,int,int);

private:
    static int dst_width;
    static int dst_height;

    AVCodecContext  *pCodecCtx; //视频解码器
    AVPacket packet;
    uint8_t *bufferRGB;


    int width;
    int height;
    PixelFormat pix_fmt;

    SDL_mutex *mutex;
};

/*读取视频的线程*/
class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    explicit VideoPlayer();
    ~VideoPlayer();

    enum State//表示播放状态的值
    {
        PlayingState,
        PausedState,
        StoppedState
    };
    enum Type //表示播放模式的值
    {
        VideoType, //视频模式
        AudioType,  //音频模式
        NoneType  //表示当前处于停止状态
    };

    void setSource(QString str); //设置播放文件
    void play();
    void pause();
    void stop();
    void setVolume(int value); //设置音量（0-128）
    void seek(qint64); //快进和快退（微秒）
    qint64 totalTime(){return totaltime;} //获取总时间 （微秒）
    qint64 currentTime(){return currenttime;} //获取当前时间 （毫秒）

    State state(){return curState;} //当前播放状态
    Type type(){return curType;}//当前播放模式
signals:
    void updateTime(long currentTime); //更新时间(毫秒)
    void finished(); //播放完毕
    void stateChanged(VideoPlayer::State); //播放状态发生改变

    void readOneFrame(QPixmap,int,int);

protected:
    void run();
private:
    AVFormatContext *pFormatCtx;
    AVCodecContext  *pCodecCtx; //视频解码器
    AVCodecContext  *aCodecCtx; //音频解码器

    int videoStream;
    int audioStream;

    qint64 totaltime; //总时间
    qint64 currenttime; //当前时间
    AVPacket nextPacket;//接下来要播放的包

    State curState; //播放状态
    Type curType; //播放模式

    QEventLoop *eventloop;
    SDL_mutex *mutex;
    SDL_mutex *decodeVideoMutex;

    /*解码用的线程,提高性能可通过增加次线程的数量来实现*/
    DecodeVideo *decodeVideoThread;
    DecodeVideo *decodeVideoThread_2;
    DecodeVideo *decodeVideoThread_3;

    void initAvcodec();
    bool openVideo(char *filename);
    void closeVideo(); //关闭音频

    bool openSDL();  //打开声音
    bool closeSDL(); //关闭声音
    void clearQuene(); //清空声音队列的内容

private slots:
    void readPacket();
};

#endif // VIDEOPLAYER_H
