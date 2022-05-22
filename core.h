#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <QThread>
#include <QImage>
#include <SoundTouch.h> //#define SOUNDTOUCH_INTEGER_SAMPLES

extern "C"
{
//avcodec:编解码(最重要的库)
#include <libavcodec/avcodec.h>
//avformat:封装格式处理
#include <libavformat/avformat.h>
//swscale:视频像素数据格式转换
#include <libswscale/swscale.h>
//swresample:音频采样频率转换,声道格式转换
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
#include <SoundTouch.h>
//#include <libavfilter>

//avdevice:各种设备的输入输出
//#include <libavdevice/avdevice.h>
//avutil:工具库（大部分库都需要这个库的支持）
//#include <libavutil/avutil.h>
//#include <libavutil/frame.h>
//#include <libavutil/mem.h>
//#include <libavutil/time.h>
//#include "libavutil/pixfmt.h"

#include <SDL.h>
#include <SDL_audio.h>
//#include <SDL_types.h>
//#include <SDL_name.h>
//#include <SDL_main.h>
//#include <SDL_config.h>
}
using namespace soundtouch;
using namespace std;

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio(48000 * 32 * 1 / 8 = 192000)
//static int index = 0;
//static int index_ = 0;

struct PacketQueue;
struct MediaCodec;
struct AudioCodec;
struct VideoCodec;
struct MediaControl;
class Core;

//1.声道数:主要有单声道和双声道之分,双声道又称为立体声,在硬件中要占两条线路,但立体声数字化后所占空间比单声道多一倍
// 
//2.量化位数/采样位数:量化位是对模拟音频信号的幅度轴进行数字化,它决定了模拟信号数字化以后的动态范围,由于计算机按字节运算,一般的量化位数为8位和16位.
// 可以理解为声卡的分辨率或声卡处理声音的解析度,量化位越高,信号的动态范围越大,数字化后的音频信号就越可能接近原始信号,但所需要的存贮空间也越大.
// 每个采样数据记录的是振幅, 采样精度取决于采样位数的大小:
//      1 字节(也就是8bit) 只能记录 256 个数, 也就是只能将振幅划分成 256 个等级;
//      2 字节(也就是16bit) 可以细到 65536 个数, 这已是 CD 标准了;
//      4 字节(也就是32bit) 能把振幅细分到 4294967296 个等级, 实在是没必要了.
//
//3.采样频率:采样频率这个专业术语是指一秒钟内采样的次数(每秒钟取得声音样本的次数),采样频率的选择应该遵循奈奎斯特(Harry Nyquist)采样理论
// (如果对某一模拟信号进行采样,则采样后可还原的最高信号频率只有采样频率的一半,或者说只要采样频率高于输入信号最高频率的两倍,就能从采样信号系列重构原始信号)
// 
//4.码率,比特率也叫码率,指音乐每秒播放的数据量,单位用bit表示,也就是二进制位.
//bps:b就是比特(bit),s就是秒(second),p就是每(per),一个字节相当于8个二进制位.
//如128bps的4分钟的歌曲的文件大小是这样计算的(128 / 8) * 4 * 60 = 3840kB = 3.8MB.而采样率为44.1HZ,采样精度为16位的双音频,你可以算出比特率是44100 * 16 * 2bps
//
//交错模式:数字音频信号存储的方式,数据以连续帧的方式存放,即首先记录帧1的左声道样本和右声道样本,再开始帧2的记录
//非交错模式:首先记录的是一个周期内所有帧的左声道样本,再记录所有右声道样本

//time base:时间基,即时间单位
//fps:帧每秒,即每秒显示多少帧

//AVPacket pkt:它保存复用之后解码之前的数据(仍然是压缩后的数据)以及关于这些数据的一些附加信息,如:显示时间戳(pts),解码时间戳(dts),数据时长,所在媒体流的索引等
//对于视频(Video)来说,AVPacket通常包含一个压缩的Frame
//而音频(Audio)则有可能包含多个压缩的Frame
//并且一个Packet也有可能是空的,不包含任何压缩数据,只含有side data(side data,容器提供的关于Packet的一些附加信息.例如在编码结束的时候更新一些流的参数)

//AVPacket中的字段可用分为两部分:数据的缓存及管理,关于数据的属性说明
//
//关于数据的属性有以下字段:
//    pts 显示时间戳
//    dts 解码时间戳
//    stream_index Packet所在stream的index
//    flats 标志,其中最低为1表示该数据是一个关键帧
//    duration 数据的时长,以所属媒体流的时间基准为单位
//    pos 数据在媒体流中的位置,未知则值为 -1
//数据缓存,AVPacket本身只是个容器,不直接的包含数据,而是通过数据缓存的指针引用数据.AVPacket中包含有两种数据
//    data 指向保存压缩数据的指针,这就是AVPacket实际的数据
//    side_data 容器提供的一些附加数据
//    buf 是AVBufferRef类型的指针,用来管理data指针引用的数据缓存的

//将一个Packet作为参数传递的时候,就要根据具体的需要,对data引用的这部分数据缓存空间进行特殊的处理
//当从一个Packet去创建另一个Packet的时候,有两种情况:
//    两个Packet的data引用的是同一数据缓存空间,这时候要注意数据缓存空间的释放问题
//    两个Packet的data引用不同的数据缓存空间,每个Packet都有数据缓存空间的copy
//对于多个Packet共享同一个缓存空间,FFmpeg使用的引用计数的机制(reference-count)
//当有新的Packet引用共享的缓存空间时就将引用计数+1;当释放了引用共享空间的Packet就将引用计数-1;引用计数为0时就释放掉引用的缓存空间
//AVPacket中的AVBufferRef *buf就是用来管理这个引用计数的

//stdout, stdin, stderr:分别是标准输出(行缓冲),标准输入和标准错误(无缓冲)
//当一个用户进程被创建的时候,系统会自动为该进程创建这三个数据流

struct PacketQueue
{
    //struct AVPacketList {
    //    AVPacket pkt;
    //    struct AVPacketList* next;};
    AVPacketList* first_pkt, * last_pkt;
    int nb_packets;
    int size;//队列中的所有数据包带的音频数据的总量或者视频数据的总量(并不是包的数量)
    SDL_mutex* mutex;
};

struct UpendImage
{
    QImage image;//储存一帧图片
    int64_t pts;//该帧图片的显示时间
    UpendImage* last;
};

struct UpendQueue
{
    //first_img储存该队列中时间最前的一帧图片,而last_img则储存该队列中时间最后的一帧图片
    //结构UpendImage的UpendImage*指针方向是"向前",即时间靠后的一帧指向时间靠前的一帧
    UpendImage* first_img, * last_img;
    int size;
    SDL_mutex* mutex;
};

struct MediaCodec
{
    AVFormatContext* FormatCtx;//ffmpeg的全局上下文

    int audioStream_i;//音频流所在的序号
    int videoStream_i;//视频流所在的序号

    //解码器结构
    AudioCodec* audiocodec;//音频解码器结构
    VideoCodec* videocodec;//视频解码器结构

    //读取缓存结构
    AVPacket* Packet;//ffmpag单帧数据包

    //静态参数
    double duration;//总时长

    //动态参数 
    SDL_mutex* read_mutex;
    double audio_clock;//用于保存音视频播放了多久
    double video_clock;//用于保存音视频播放了多久
    double emit_audio_clock;//emit_audio_clock和audio_clock相差过大才会更新
    double emit_video_clock;//emit_video_clock和video_clock相差过大才会更新


    MediaCodec() { memset(this, 0, sizeof(MediaCodec)); }
};

struct AudioCodec
{
    SDL_mutex* mutex;//互斥锁,有些控制涉及文件解码器结构的更新

    const AVCodec* Codec;//ffmpeg音频解码器
    AVCodecContext* CodecCtx;//ffmpeg音频解码器上下文
    SoundTouch* soundtouch;//Soundtouch库-倍速
    AVStream* Stream;//音频流
    PacketQueue* queue;//音频packet队列
    struct SwrContext* convert_ctx;//ffmpeg音频转换上下文

    //解析缓存结构
    AVPacket* Packet;
    AVFrame* Frame;
    uint8_t* out_buffer;//ffmpag解码后的音频数据存放缓存区
    short* soundtouch_buffer;//soundtouch缓存区

    //静态参数
    int max_queue_size;//音频packet队列大小限制
    int out_buffer_size;//音频缓冲区大小

    //动态参数
    int64_t now_pts;//音频帧的pts

    AudioCodec() { memset(this, 0, sizeof(AudioCodec)); }
};

struct VideoCodec
{
    SDL_mutex* mutex;//互斥锁,有些控制涉及文件解码器结构的更新
    const AVCodec* Codec;//ffmpeg视频解码器
    AVCodecContext* CodecCtx;//ffmpeg视频解码器上下文
    AVStream* Stream;//视频流
    PacketQueue* queue;//视频packet队列
    UpendQueue* upend_queue;//视频倒退Image队列
    struct SwsContext* convert_ctx;//ffmpeg视频转换上下文

    //解析缓存结构
    AVPacket* Packet;
    AVFrame* Frame;
    AVFrame* FrameRGB;//(转换颜色空间后)
    uint8_t* out_buffer;//ffmpag解码后的视频数据存放缓存区

    //静态参数 
    int max_queue_size;//视频packet队列大小限制 
    int max_upend_size;//视频倒退Image队列帧数限制
    double fps;//视频帧率

    //动态参数
    int64_t now_pts;//视频帧的pts
    bool video_clock_change;//辅助更新MediaCodec结构下的video_clock
    //"如果video_clock改变则将其置为-1"这种做法将导致video_clock在两个线程进行危险的修改
    //因此引入辅助变量video_clock_change,目的是逻辑正确地更新video_clock

    VideoCodec() { memset(this, 0, sizeof(VideoCodec)); }
};

struct MediaControl//文件控制结构
{
    bool pause;//true:暂停; false:播放
    int volume;//音量值
    int64_t timestamp;//寻找或跳转的时间戳(单位为秒)
    bool seek;//true:寻找帧; false不需要寻找帧或寻找帧已完成
    bool skip;//true:跳转播放; false正常播放

    bool upend;//true:倒退播放; false:正常播放
    double upend_speed;//倒退播放速度 1.0正常播放; 2.0二倍速播放

    int running_thread;
    SDL_mutex* thread_mutex;//互斥锁
    bool exit;

    bool speed_change;
    double speed;
    
    MediaControl() { memset(this, 0, sizeof(MediaControl)); }
};

struct CentralControl
{
    MediaCodec* mediacodec;
    MediaControl* mediacontrol;

    Core* processing;
    CentralControl() { memset(this, 0, sizeof(CentralControl)); }
};

class Core :public QThread
{
    Q_OBJECT

public:
    
    explicit Core();
    void CentralControl_init();
    ~Core();

    //初始化
    int MediaCodec_init(MediaCodec*& mediacodec);
    int AudioCodec_init(AVFormatContext* FormatCtx, int audioStream_i, AudioCodec*& audiocodec);
    void SoundTouch_init(int sample_rate, int channels, SoundTouch*& soundtouch, short*& soundtouch_buffer);
    int VideoCodec_init(AVFormatContext* FormatCtx, int videoStream_i, VideoCodec*& videocodec);
    void MediaControl_init(MediaControl*& mediacontrol);
    void MediaControl_reinit(MediaControl*& mediacontrol);
    int SDL_init();
    int core_init(QString file_path);

    //释放
    void MediaCodec_free(MediaCodec*& mediacodec);
    void AudioCodec_free(AudioCodec*& audiocodec); 
    void SoundTouch_free(SoundTouch*& soundtouch, short*& soundtouch_buffer);
    void VideoCodec_free(VideoCodec*& videocodec);
    void MediaControl_free(MediaControl*& mediacontrol);
    void SDL_free();
    void core_free();

    //操作
    //线程-将video/audio frame送入相应的队列
    static int thread_read_frame(void* arg);
    //线程-视频倒放解码
    static int thread_upend_read_frame(void* arg);
    //视频解码操作
    //根据音频时间同步视频时间
    //视频倒放显示操作
    //线程-视频解码
    static void decode_video_frame(CentralControl* centralcontrol);
    static void synchronize_video(CentralControl* centralcontrol);
    static void upend_video_show(CentralControl* centralcontrol);
    static int thread_video(void* arg);
    //音频解码操作
    //回调函数-音频解码
    //线程-音频控制
    //更新音频时间
    static int decode_audio_frame(CentralControl* centralcontrol, uint8_t* audio_buf);
    static void callback_audio(void* udata, Uint8* stream, int len);
    static int thread_audio(void* arg);
    static void update_audio_clock(CentralControl* centralcontrol, unsigned int index);
    //辅助线程-视频寻帧
    static int assist_thread_video_seek(void* arg);
    //线程-控制台(debug)
    static int thread_console_debug(void* arg);

    //不完善的函数
    static int decode_audio_frame_(CentralControl* centralcontrol, uint8_t* audio_buf);
    static int decode_audio_frame__(CentralControl* centralcontrol, uint8_t* audio_buf);

signals:
    void signal_core_duration(double duration);
    void signal_core_clock(double clock);
    void signal_core_getimage_display(QImage image); //每获取到一帧图像就发送此信号(播放帧)
    void signal_core_getimage_seekwidget(QImage image); //每获取到一帧图像就发送此信号(寻找帧)

public slots:
    void slot_core_pause(bool pause);
    void slot_core_volume(int volume);
    void slot_core_seek(int64_t timestamp);
    void slot_core_skip();
    void slot_core_upend(double upend_speed);
    void slot_core_upend_cancel();

protected:
    void run();

private:
    QString file_path;
    bool init;
    MediaCodec* mediacodec;
    MediaControl* mediacontrol;
    CentralControl* centralcontrol;
};
#endif // CORE_H


//如果只有视频流,倍速功能未实现
//音频倍速存在bug
