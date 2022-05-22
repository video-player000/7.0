#include "core.h"

//普通队列初始化函数
void packet_queue_init(PacketQueue* q)
{
    //memset为初始化函数,作用是将某一块内存中的全部设置为指定的值
    //void *memset(void *s, int c, size_t n) 
    //s指向要填充的内存块,c是要被设置的值,n是要被设置该值的字符数,返回类型是一个指向存储区s的指针
    //memset函数是按照字节对内存块进行初始化
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
}
static int packet_queue_put(PacketQueue* q, AVPacket* pkt)
{
    //初始化AVPacketList* pkt1
    AVPacketList* pkt1;
    pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if (!pkt1) {
        return -1;
    }
    if (av_packet_ref(&pkt1->pkt, pkt) < 0) {
        return -1;
    }
    pkt1->next = NULL;

    //压进队列
    SDL_LockMutex(q->mutex);
    if (!q->first_pkt) {
        q->first_pkt = pkt1;
    }
    else {
        q->last_pkt->next = pkt1;
    }
    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    SDL_UnlockMutex(q->mutex);

    return 0;
}
static int packet_queue_get(PacketQueue* q, AVPacket* pkt)
{
    int ret = 0;

    SDL_LockMutex(q->mutex);
    AVPacketList* pkt1 = q->first_pkt;
    if (pkt1) {
        q->first_pkt = pkt1->next;
        if (!q->first_pkt) {
            q->last_pkt = NULL;
        }
        q->nb_packets--;
        q->size -= pkt1->pkt.size;
        //av_copy_packet();
        av_packet_ref(pkt, &pkt1->pkt);
        av_packet_unref(&pkt1->pkt);
        av_freep(pkt1);
    }
    else {
        ret = -1;
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}
static int packet_queue_clean(PacketQueue* q)
{
    SDL_LockMutex(q->mutex);
    AVPacketList* pkt = q->first_pkt;
    while (pkt != NULL) {
        av_packet_unref(&pkt->pkt);
        av_freep(pkt);
        pkt = pkt->next;
    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
    return 0;
}
void packet_queue_free(PacketQueue* q)
{
    packet_queue_clean(q);
    SDL_DestroyMutex(q->mutex);
}

//倒退队列初始化函数
void upend_queue_init(UpendQueue* q)
{
    memset(q, 0, sizeof(UpendQueue));
    q->mutex = SDL_CreateMutex();
}
static int upend_queue_put(UpendQueue* q, UpendImage* begin_image, UpendImage* end_image, int size)
{
    int ret;
    if (size == 0) {
        ret = -1;
    }
    else {
        SDL_LockMutex(q->mutex);
        if (!q->last_img) {//队列中不存在图片帧
            q->last_img = end_image;
            q->first_img = begin_image;
            q->size = size;
        }
        else {//队列中存在图片帧
            q->first_img->last = end_image;
            q->first_img = begin_image;
            q->size += size;
        }
        SDL_UnlockMutex(q->mutex);
        ret = 0;
    }
    return ret;
}
static int upend_queue_get(UpendQueue* q, UpendImage*& a_image)
{
    //如果第二个参数定义为UpendImage* a_image,即函数用一个临时变量a_image保存传入参数的内容
    //(相当于用一个新的UpendImage指针指向于传入参数的那个UpendImage指针所指向的内容)
    //函数内部如果对临时变量(新的UpendImage指针)进行修改,为其赋值为新分配的内存地址(相当于新的指针重指向新内容,从而丢失了原来的指向)
    int ret;
    SDL_LockMutex(q->mutex);
    if (q->size == 0) {
        ret = -1;
    }
    else {
        if (q->last_img == q->first_img) {//队列中只剩下一帧图片的情况
            q->first_img = NULL;
        }
        a_image = q->last_img;
        q->last_img = q->last_img->last;
        a_image->last = NULL;
        q->size -= 1;
        ret = 0;
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}
static int upend_queue_clean(UpendQueue* q)
{
    SDL_LockMutex(q->mutex);

    while (q->size != 0) {
        UpendImage* t_img = q->last_img;
        q->last_img = q->last_img->last;
        delete t_img;
        q->size -= 1;
    }
    q->first_img = NULL;
    q->last_img = NULL;
    SDL_UnlockMutex(q->mutex);
    return 0;
}
void upend_queue_free(UpendQueue* q)
{
    upend_queue_clean(q);
    SDL_DestroyMutex(q->mutex);
}

//构建/析构
Core::Core()
{
    init = false;
    mediacodec = new MediaCodec;
    mediacontrol = new MediaControl;
    centralcontrol = NULL;
    CentralControl_init();
    SDL_CreateThread(thread_console_debug, "thread_console_debug", centralcontrol);
}
Core::~Core()
{

}

//初始化
int Core::MediaCodec_init(MediaCodec*& mediacodec)
{
    //创建AVFormatContext对象-对应avformat_free_context()
    mediacodec->FormatCtx = avformat_alloc_context();

    //打开文件-对应avformat_close_input()
    string string_path = file_path.toStdString();
    const char* path = string_path.c_str();
    cout << path;
    if (avformat_open_input(&mediacodec->FormatCtx, path, NULL, NULL) != 0) {
        fprintf(stderr, "Open file - failed.\n");
        return -1;
    }

    //对文件探测流信息
    if (avformat_find_stream_info(mediacodec->FormatCtx, NULL) < 0) {
        fprintf(stderr, "Find stream - failed.\n");
        return -1;
    }
    //输出文件信息
    av_dump_format(mediacodec->FormatCtx, 0, path, 0);

    //循环查找视频中包含的流信息
    mediacodec->audioStream_i = -1;
    mediacodec->videoStream_i = -1;
    for (int i = 0; i < mediacodec->FormatCtx->nb_streams; i++) {
        enum AVMediaType mediaType = mediacodec->FormatCtx->streams[i]->codecpar->codec_type;
        if (mediaType == AVMEDIA_TYPE_AUDIO && mediacodec->audioStream_i < 0) {//音频流
            mediacodec->audioStream_i = i;
        }
        else if (mediaType == AVMEDIA_TYPE_VIDEO && mediacodec->videoStream_i < 0) {//视频流
            mediacodec->videoStream_i = i;
        }
    }
    //cout << " audioStream:" << mediacodec.audioStream << "  videoStream:" << mediacodec.videoStream << endl;
    //如果audioStream或videoStream为-1,说明没有找到音频流/视频流

    if (mediacodec->audioStream_i != -1) {//只有音频流存在,mediacodec->audiocodec才会被初始化
        if (AudioCodec_init(mediacodec->FormatCtx, mediacodec->audioStream_i, mediacodec->audiocodec) != 0) {
            fprintf(stderr, "Create AudioCodec - failed.\n");
            return -1;
        }
    }
    else {
        mediacodec->audiocodec = NULL;
    }

    if (mediacodec->videoStream_i != -1) {//只有视频流存在,mediacodec->videocodec才会被初始化
        if (VideoCodec_init(mediacodec->FormatCtx, mediacodec->videoStream_i, mediacodec->videocodec) != 0) {
            fprintf(stderr, "Create VideoCodec - failed.\n");
            return -1;
        }
    }
    else {
        mediacodec->videocodec = NULL;
    }

    //分配一个packet,接着不仅初始化字段,但并没有为data分配了存储空间
    //malloc:动态内存分配函数,用于申请一块连续的指定大小的内存块区域以void*类型返回分配的内存区域地址
    mediacodec->Packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    av_init_packet(mediacodec->Packet);

    //源码:
    //if (pFormatCtx->duration != AV_NOPTS_VALUE) {
    //    int hours, mins, secs, us;
    //    int64_t duration = pFormatCtx->duration + 5000;
    //    secs = duration / AV_TIME_BASE;
    //    us = duration % AV_TIME_BASE;//1000000
    //    mins = secs / 60;
    //    secs %= 60;
    //    hours = mins / 60;
    //    mins %= 60;
    //    printf("%02d:%02d:%02d.%02d\n", hours, mins, secs, (100 * us) / AV_TIME_BASE);
    //}
    mediacodec->duration = (double(mediacodec->FormatCtx->duration + 5000)) / AV_TIME_BASE;

    mediacodec->audio_clock = 0;
    mediacodec->video_clock = 0;
    mediacodec->emit_audio_clock = 0;
    mediacodec->emit_video_clock = 0;
    mediacodec->read_mutex = SDL_CreateMutex();
    return 0;
}
int Core::AudioCodec_init(AVFormatContext* FormatCtx, int audioStream_i, AudioCodec*& audiocodec)
{
    audiocodec = new AudioCodec;
    audiocodec->mutex = SDL_CreateMutex();
    //查找音频解码器
    audiocodec->Codec = avcodec_find_decoder(FormatCtx->streams[audioStream_i]->codecpar->codec_id);
    if (!audiocodec->Codec) {
        fprintf(stderr, "Find audio Codec - failed.\n");
        return -1;
    }
    //配置音频解码器
    audiocodec->CodecCtx = avcodec_alloc_context3(NULL);
    if (!audiocodec->CodecCtx) {
        fprintf(stderr, "Allocate audio AVCodecContext - failed.\n");
        return -1;
    }
    avcodec_parameters_to_context(audiocodec->CodecCtx, FormatCtx->streams[audioStream_i]->codecpar);
    //打开音频解码器
    if (avcodec_open2(audiocodec->CodecCtx, audiocodec->Codec, NULL) < 0) {
        fprintf(stderr, "Open audio Codec - failed.\n");
        return -1;
    }
    SoundTouch_init(audiocodec->CodecCtx->sample_rate, audiocodec->CodecCtx->channels, audiocodec->soundtouch, audiocodec->soundtouch_buffer);
    audiocodec->Stream = FormatCtx->streams[audioStream_i];

    //初始化队列
    audiocodec->queue = new PacketQueue;
    packet_queue_init(audiocodec->queue);
    audiocodec->max_queue_size = 1024 * 32;

    audiocodec->Packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    av_init_packet(audiocodec->Packet);
    //分配AVFrame,并将其字段设置为默认值
    audiocodec->Frame = av_frame_alloc();
    //音频缓存分配
    audiocodec->out_buffer = (uint8_t*)av_malloc(MAX_AUDIO_FRAME_SIZE * 2); 

    //音频转换上下文参数
    int64_t out_ch_layout = av_get_default_channel_layout(audiocodec->CodecCtx->channels);//返回给定数量通道的默认通道布局
    enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;//音频样本格式(采样位数-signed 16 bits)
    int out_sample_rate = audiocodec->CodecCtx->sample_rate;//采样率
    int64_t in_ch_layout = av_get_default_channel_layout(audiocodec->CodecCtx->channels);
    enum AVSampleFormat in_sample_fmt = audiocodec->CodecCtx->sample_fmt;
    int in_sample_rate = audiocodec->CodecCtx->sample_rate;
    //初始化音频转换上下文(重新采样)
    audiocodec->convert_ctx = swr_alloc();
    audiocodec->convert_ctx = swr_alloc_set_opts(audiocodec->convert_ctx, out_ch_layout, out_sample_fmt, out_sample_rate, in_ch_layout, in_sample_fmt, in_sample_rate, 0, NULL);
    swr_init(audiocodec->convert_ctx);

    int out_channels = av_get_channel_layout_nb_channels(out_ch_layout);//返回通道布局中的通道数,也可以写成audiocodec->CodecCtx->channels
    int out_nb_samples = audiocodec->CodecCtx->frame_size;//音频帧中每个信道的采样数
    audiocodec->out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);//获取给定音频参数所需的缓冲区大小(单位:字节)

    audiocodec->now_pts = 0;

    return 0;
}
void Core::SoundTouch_init(int sample_rate, int channels, SoundTouch*& soundtouch, short*& soundtouch_buffer)
{
    soundtouch = new SoundTouch;
    soundtouch->setSampleRate(sample_rate); // 设置采样率
    soundtouch->setChannels(channels); // 设置通道数
    soundtouch->setPitch(1);//变调不变速
    soundtouch->setRate(1);//变速和变调
    soundtouch->setTempo(1);//变速不变调
    soundtouch_buffer = (short*)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
}
int Core::VideoCodec_init(AVFormatContext* FormatCtx, int videoStream_i, VideoCodec*& videocodec)
{
    videocodec = new VideoCodec;
    videocodec->mutex = SDL_CreateMutex();
    //查找视频解码器
    videocodec->Codec = avcodec_find_decoder(FormatCtx->streams[videoStream_i]->codecpar->codec_id);
    if (!videocodec->Codec) {
        fprintf(stderr, "Find video Codec - failed.\n");
        return -1;
    }
    //配置视频解码器
    videocodec->CodecCtx = avcodec_alloc_context3(NULL);
    if (!videocodec->CodecCtx) {
        fprintf(stderr, "Allocate video AVCodecContext - failed.\n");
        return -1;
    }
    avcodec_parameters_to_context(videocodec->CodecCtx, FormatCtx->streams[videoStream_i]->codecpar);
    //打开视频解码器
    if (avcodec_open2(videocodec->CodecCtx, videocodec->Codec, NULL) < 0) {
        fprintf(stderr, "Open video Codec - failed.\n");
        return -1;
    }
    videocodec->Stream = FormatCtx->streams[videoStream_i];

    //初始化队列
    videocodec->queue = new PacketQueue;
    packet_queue_init(videocodec->queue);
    videocodec->max_queue_size = 1024 * 1024;
    videocodec->upend_queue = new UpendQueue;
    upend_queue_init(videocodec->upend_queue);
    videocodec->max_upend_size = 50;

    videocodec->Packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    av_init_packet(videocodec->Packet);
    videocodec->Frame = av_frame_alloc();
    videocodec->FrameRGB = av_frame_alloc();
    //视频缓存分配
    //通过指定像素格式、图像宽、图像高来计算所需的内存大小
    int dstW = videocodec->CodecCtx->width;
    int dstH = videocodec->CodecCtx->height;
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB32, dstW, dstH, 1);
    videocodec->out_buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    //瓜分所分配的内存
    av_image_fill_arrays(videocodec->FrameRGB->data, videocodec->FrameRGB->linesize, videocodec->out_buffer, AV_PIX_FMT_RGB32, dstW, dstH, 1);

    //视频转换上下文参数
    int srcW = videocodec->CodecCtx->width;
    int srcH = videocodec->CodecCtx->height;
    enum AVPixelFormat srcFormat = videocodec->CodecCtx->pix_fmt;
    enum AVPixelFormat dstFormat = AV_PIX_FMT_RGB32;
    int flags = SWS_BICUBIC;
    //初始化视频转换上下文(对像素格式和尺寸进行转换)
    videocodec->convert_ctx = sws_getContext(srcW, srcH, srcFormat, dstW, dstH, dstFormat, flags, NULL, NULL, NULL);

    videocodec->fps = (double)videocodec->Stream->avg_frame_rate.num / videocodec->Stream->avg_frame_rate.den;

    videocodec->now_pts = 0;
    videocodec->video_clock_change = false;

    return 0;
}
void Core::MediaControl_init(MediaControl*& mediacontrol)
{
    mediacontrol->pause = true;
    mediacontrol->volume = SDL_MIX_MAXVOLUME;
    mediacontrol->timestamp = 0;
    mediacontrol->seek = false;
    mediacontrol->skip = false;
    mediacontrol->upend = false;

    mediacontrol->thread_mutex = SDL_CreateMutex();
    mediacontrol->running_thread = 0;
    mediacontrol->exit = false;

    mediacontrol->speed_change = false;
    mediacontrol->speed = 1.0;
}
void Core::MediaControl_reinit(MediaControl*& mediacontrol)
{
    mediacontrol->pause = true;
    mediacontrol->timestamp = 0;
    mediacontrol->seek = false;
    mediacontrol->skip = false;
    mediacontrol->upend = false;

    mediacontrol->running_thread = 0;
    mediacontrol->exit = false;

    mediacontrol->speed_change = false;
    mediacontrol->speed = 1.0;
}
void Core::CentralControl_init()
{
    centralcontrol = new CentralControl;
    centralcontrol->mediacodec = mediacodec;
    centralcontrol->mediacontrol = mediacontrol;
    centralcontrol->processing = this;
}
int Core::SDL_init()
{
    //初始化SDL
    if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "Initialize SDL - failed:%s.\n", SDL_GetError());
        return -1;
    }

    //锁定音频设备
    SDL_LockAudio();

    //SDL_AudioSpec是包含音频输出格式的结构体,同时它也包含当音频设备需要更多数据时调用的回调函数
    //struct SDL_AudioSpec
    //{
    //    int freq;                   // DSP频率—每秒采样数
    //    SDL_AudioFormat format;     // 音频数据格式
    //    Uint8 channels;             // 通道数1-单声道,2-立体声
    //    Uint8 silence;              // 音频缓冲静音值(计算)
    //    Uint16 samples;             // 基本是512 1024,设置不合适可能会导致卡顿
    //    Uint16 padding;             // 对于某些编译环境是必需的
    //    Uint32 size;                // 音频缓冲区大小(字节)(计算)
    //    SDL_AudioCallback callback; // 为音频设备提供数据回调(空值使用SDL 自身预先定义的SDL_QueueAudio()回调函数)
    //    void* userdata;             // 传递给回调的Userdata(对于空回调忽略)
    //};
    SDL_AudioSpec desired_spec;
    desired_spec.freq = 44100;
    desired_spec.format = AUDIO_S16SYS;
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
    desired_spec.channels = av_get_channel_layout_nb_channels(out_channel_layout);
    desired_spec.silence = 0;
    desired_spec.samples = mediacodec->audiocodec->CodecCtx->frame_size;
    desired_spec.callback = callback_audio;
    desired_spec.userdata = centralcontrol;
    //打开音响设备
    if (SDL_OpenAudio(&desired_spec, NULL) < 0) {
        fprintf(stderr, "Open audio device - failed:%s.\n", SDL_GetError());
        return -1;
    }
    //解锁音频设备
    SDL_UnlockAudio();
    return 0;
}
int Core::core_init(QString file_path)
{
    this->file_path = file_path;
    if (!init) {//初始化
        if (MediaCodec_init(mediacodec) != 0) {
            fprintf(stderr, "MediaCodec_init - failed.\n");
            return -1;
        }
        MediaControl_init(mediacontrol);
        if (mediacodec->audioStream_i != -1) {//只有音频流存在,才初始化SDL
            if (SDL_init() != 0) {
                fprintf(stderr, "SDL_init - failed.\n");
                return -1;
            }
        }
        init = true;
    }
    else {//重新初始化
        mediacontrol->exit = true;//使得所有线程都主动结束
        while (true) {
            SDL_LockMutex(mediacontrol->thread_mutex);
            int now_thread = mediacontrol->running_thread;
            SDL_UnlockMutex(mediacontrol->thread_mutex);
            if (now_thread == 0) {
                init = false;
                MediaCodec_free(mediacodec);
                if (mediacodec->audioStream_i != -1) {//只有音频流存在,才需要释放SDL
                    SDL_free();
                }
                break;
            }
        }
        if (MediaCodec_init(this->mediacodec) != 0) {
            fprintf(stderr, "MediaCodec_init - failed.\n");
            return -1;
        }
        MediaControl_reinit(this->mediacontrol);
        if (mediacodec->audioStream_i != -1) {//只有音频流存在,才初始化SDL
            if (SDL_init() != 0) {
                fprintf(stderr, "SDL_init - failed.\n");
                return -1;
            }
        }
        init = true;
    }
    return 0;
}

//释放
void Core::MediaCodec_free(MediaCodec*& mediacodec)
{
    AudioCodec_free(mediacodec->audiocodec);
    VideoCodec_free(mediacodec->videocodec);
    //关闭文件
    avformat_close_input(&mediacodec->FormatCtx);
    //AVFrameContext结构体销毁函数
    avformat_free_context(mediacodec->FormatCtx);
    av_packet_free(&mediacodec->Packet);
    SDL_DestroyMutex(mediacodec->read_mutex);
}
void Core::AudioCodec_free(AudioCodec*& audiocodec)
{  
    SDL_DestroyMutex(audiocodec->mutex);
    avcodec_close(audiocodec->CodecCtx);
    SoundTouch_free(audiocodec->soundtouch, audiocodec->soundtouch_buffer);
    packet_queue_free(audiocodec->queue);
    swr_free(&audiocodec->convert_ctx);
    av_packet_free(&audiocodec->Packet);
    av_frame_free(&audiocodec->Frame);
    av_free(audiocodec->out_buffer);
}
void Core::SoundTouch_free(SoundTouch*& soundtouch, short*& soundtouch_buffer)
{
    delete soundtouch;
    av_free(soundtouch_buffer);
}
void Core::VideoCodec_free(VideoCodec*& videocodec)
{
    SDL_DestroyMutex(videocodec->mutex);
    avcodec_close(videocodec->CodecCtx);
    packet_queue_free(videocodec->queue);
    upend_queue_free(videocodec->upend_queue);
    sws_freeContext(videocodec->convert_ctx);
    av_packet_free(&videocodec->Packet);
    av_frame_free(&videocodec->Frame);
    av_frame_free(&videocodec->FrameRGB);
    av_free(videocodec->out_buffer);
}
void Core::MediaControl_free(MediaControl*& mediacontrol)
{
    SDL_DestroyMutex(mediacontrol->thread_mutex);
}
void Core::SDL_free()
{
    SDL_CloseAudio();
    SDL_Quit();
}
void Core::core_free()
{   
    if (init) {
        mediacontrol->exit = true;//使得所有线程都主动结束
        while (true) {
            SDL_LockMutex(mediacontrol->thread_mutex);
            int now_thread = mediacontrol->running_thread;
            SDL_UnlockMutex(mediacontrol->thread_mutex);

            if (now_thread == 0) {
                init = false;
                MediaCodec_free(mediacodec);
                MediaControl_free(mediacontrol);
                SDL_free();
                break;
            }
        }
    }
}



//操作
void Core::run()
{
    //暂停播放控制:对三个线程(thread_read_frame thread_video thread_audio)进行控制
    //音量控制:对回调函数(callback_audio)进行控制
    //跳转播放控制:对一个线程(thread_read_frame)进行控制
    //寻找控制:对一个线程(assist_thread_video_seek)进行控制
    //倒放播放控制:对三个线程(thread_read_frame thread_video thread_audio)进行控制
    //SDL_CreateThread(thread_read_frame, "Core::thread_read_frame", centralcontrol);
    //SDL_CreateThread(thread_audio, "thread_audio", centralcontrol);
    //SDL_CreateThread(thread_video, "thread_video", centralcontrol);
    //SDL_CreateThread(assist_thread_video_seek, "assist_thread_video_seek", centralcontrol);

    emit signal_core_duration(mediacodec->duration);
    if (mediacodec->audioStream_i != -1 && mediacodec->videoStream_i != -1) {//音频流和视频流都存在
        cout << "Both streams" << endl;
        SDL_CreateThread(thread_read_frame, "thread_read_frame", centralcontrol);
        SDL_CreateThread(thread_upend_read_frame, "thread_upend_read_frame", centralcontrol);
        SDL_CreateThread(thread_audio, "thread_audio", centralcontrol);
        SDL_CreateThread(thread_video, "thread_video", centralcontrol);

        SDL_CreateThread(assist_thread_video_seek, "assist_thread_video_seek", centralcontrol);
    }
    else if (mediacodec->audioStream_i != -1 && mediacodec->videoStream_i == -1) {//只存在音频流
        cout << "Only audio stream" << endl;
        SDL_CreateThread(thread_read_frame, "thread_read_frame", centralcontrol);
        SDL_CreateThread(thread_audio, "thread_audio", centralcontrol);
    }
    else if (mediacodec->audioStream_i == -1 && mediacodec->videoStream_i != -1) {//只存在视频流
        cout << "Only video stream" << endl;
        SDL_CreateThread(thread_read_frame, "thread_read_frame", centralcontrol);
        SDL_CreateThread(thread_upend_read_frame, "thread_upend_read_frame", centralcontrol);
        SDL_CreateThread(thread_video, "thread_video", centralcontrol);

        SDL_CreateThread(assist_thread_video_seek, "assist_thread_video_seek", centralcontrol);
    }
    else {//不存在流
        cout << "No stream";
    }
}

int Core::thread_read_frame(void* arg)
{
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;
    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread += 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);

    AVFormatContext* FormatCtx = mediacodec->FormatCtx;
    int audioStream_i = mediacodec->audioStream_i;
    int videoStream_i = mediacodec->videoStream_i;
    AVPacket* Packet = mediacodec->Packet;
    SDL_mutex* read_mutex = mediacodec->read_mutex;

    AVCodecContext* aCodecCtx = NULL;
    AVStream* aStream = NULL;
    PacketQueue* aqueue = NULL;
    int a_max_queue_size = 0;
    if (audioStream_i != -1) {
        aCodecCtx = mediacodec->audiocodec->CodecCtx;
        aStream = mediacodec->audiocodec->Stream;
        aqueue = mediacodec->audiocodec->queue;
        a_max_queue_size = mediacodec->audiocodec->max_queue_size;
    }

    AVCodecContext* pCodecCtx = NULL;
    AVStream* vStream = NULL;
    PacketQueue* vqueue = NULL;
    int v_max_queue_size = 0;
    if (videoStream_i != -1) {
        pCodecCtx = mediacodec->videocodec->CodecCtx;
        vStream = mediacodec->videocodec->Stream;
        vqueue = mediacodec->videocodec->queue;
        v_max_queue_size = mediacodec->videocodec->max_queue_size;
    }

    while (true) {
        //退出控制
        if (mediacontrol->exit) {
            break;
        }

        //暂停播放控制
        if (mediacontrol->pause) {
            SDL_Delay(10);
            continue;
        }

        //倒退播放控制,并且一旦结束倒放,跳转置现在时间点所对应的帧进行播放,即调用跳转播放控制
        if (mediacontrol->upend && videoStream_i != -1) {
            if (!mediacontrol->skip) {
                mediacontrol->skip = true;
            }
            if (mediacontrol->timestamp != int64_t(mediacodec->video_clock)) {
                mediacontrol->timestamp = int64_t(mediacodec->video_clock);
            }
            SDL_Delay(10);
            continue;
        }

        //跳转播放控制
        if (mediacontrol->skip) {
            if (videoStream_i != -1) {//只要视频流存在则以视频流跳转
                if (av_seek_frame(FormatCtx, videoStream_i, mediacontrol->timestamp / av_q2d(vStream->time_base), AVSEEK_FLAG_BACKWARD) < 0) {
                    fprintf(stderr, "Skip video frame - failed.\n");
                }
                if (audioStream_i != -1) {//视频流存在的前提下,如果音频流也存在,则也需要对其进行解码结构的更新
                    //此处涉及到了文件解码器结构的更新,因此为防止更新的时候使用文件解码器结构进行解码操作,此处进行加锁操作
                    SDL_LockMutex(read_mutex);
                    SDL_LockMutex(mediacodec->audiocodec->mutex);
                    packet_queue_clean(aqueue);
                    //缓冲区刷新
                    avcodec_flush_buffers(aCodecCtx);
                    //解锁操作
                    SDL_UnlockMutex(mediacodec->audiocodec->mutex); 
                    SDL_UnlockMutex(read_mutex);
                }
                SDL_LockMutex(read_mutex);
                SDL_LockMutex(mediacodec->videocodec->mutex);
                packet_queue_clean(vqueue);
                avcodec_flush_buffers(pCodecCtx);
                if (audioStream_i == -1) {//重置视频时钟
                    mediacodec->videocodec->video_clock_change = true;
                }
                SDL_UnlockMutex(mediacodec->videocodec->mutex);
                SDL_UnlockMutex(read_mutex);
            }
            else if (audioStream_i != -1) {//否则以音频流跳转
                if (av_seek_frame(FormatCtx, audioStream_i, mediacontrol->timestamp / av_q2d(aStream->time_base), AVSEEK_FLAG_BACKWARD) < 0) {
                    fprintf(stderr, "Skip audio frame - failed.\n");
                }
                //不存在视频流,只需要对音频流的解码结构进行更新
                SDL_LockMutex(read_mutex);
                SDL_LockMutex(mediacodec->audiocodec->mutex);
                packet_queue_clean(aqueue);
                avcodec_flush_buffers(aCodecCtx);
                SDL_UnlockMutex(mediacodec->audiocodec->mutex);
                SDL_UnlockMutex(read_mutex);
            }
            else {
                fprintf(stderr, "No stream - failed.\n");
            }
            mediacontrol->skip = false;
        }

        //避免瞬间把整个文件都读入内存,导致空间分配不足,因此这里有限制
        //当队列里面的数据超过阈值时,暂停读取
        if (audioStream_i != -1 && videoStream_i != -1) {
            if (aqueue->size > a_max_queue_size && vqueue->size > v_max_queue_size) {
                SDL_Delay(10);
                continue;
            }
        }
        else if (audioStream_i != -1) {
            if (aqueue->size > a_max_queue_size) {
                SDL_Delay(10);
                continue;
            }
        }
        else if (videoStream_i != -1) {
            if (vqueue->size > v_max_queue_size) {
                SDL_Delay(10);
                continue;
            }
        }

        SDL_LockMutex(read_mutex);
        if (av_read_frame(FormatCtx, Packet) < 0) {//全部读完
            //即使av_read_frame()<0时,它也产生了堆内存,也需要用av_packet_unref进行释放
            av_packet_unref(Packet);
            SDL_UnlockMutex(read_mutex);
            continue;
        }

        //将Packet压入队列中
        if (audioStream_i != -1 && Packet->stream_index == audioStream_i) {
            if (packet_queue_put(aqueue, Packet) != 0) {
                fprintf(stderr, "Put audio packet queue- failed.\n");
            }
            av_packet_unref(Packet);
        }
        else if (videoStream_i != -1 && Packet->stream_index == videoStream_i) {
            if (packet_queue_put(vqueue, Packet) != 0) {
                fprintf(stderr, "Put video packet queue- failed.\n");
            }
            av_packet_unref(Packet);
        }
        else {
            av_packet_unref(Packet);
        }
        SDL_UnlockMutex(read_mutex);
    }

    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread -= 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);
    cout << "thread_read_frame exit.\n";
    return 0;
}

int Core::thread_upend_read_frame(void* arg)
{
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;
    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread += 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);

    AVFormatContext* FormatCtx = mediacodec->FormatCtx;
    int videoStream_i = mediacodec->videoStream_i;
    AVPacket* Packet = mediacodec->Packet;
    SDL_mutex* read_mutex = mediacodec->read_mutex;

    AVCodecContext* aCodecCtx = mediacodec->audiocodec->CodecCtx;
    PacketQueue* aqueue = mediacodec->audiocodec->queue;
    AVCodecContext* pCodecCtx = mediacodec->videocodec->CodecCtx;
    PacketQueue* vqueue = mediacodec->videocodec->queue;
    AVStream* vStream = mediacodec->videocodec->Stream;
    UpendQueue* upend_queue = mediacodec->videocodec->upend_queue;
    int max_upend_size = mediacodec->videocodec->max_upend_size;
    AVFrame* Frame = mediacodec->videocodec->Frame;
    AVFrame* FrameRGB = mediacodec->videocodec->FrameRGB;
    struct SwsContext* convert_ctx = mediacodec->videocodec->convert_ctx;
    uint8_t* out_buffer = mediacodec->videocodec->out_buffer;

    int64_t begin_pts = -1;
    int64_t end_pts = -1;
    int64_t now_pts = -1;
    double begin_clock;
    double end_clock;//下一次进行回退的时间点(单位:秒)
    double now_clock;
    double upend_interval = 1;//回退间隔(单位:秒)

    int ret, got_picture;
    while (true) {
        //退出控制
        if (mediacontrol->exit) {
            break;
        }

        if (!mediacontrol->upend) {
            if (end_pts != -1) {//如果刚结束倒放操作,end_pts != -1
                upend_queue_clean(upend_queue);
                end_pts = -1;
            }
            SDL_Delay(10);
            continue;
        }

        if (upend_queue->size > max_upend_size) {
            SDL_Delay(10);
            continue;
        }

        //正常情况下进行倒放操作时,只有该线程读取Packet并使用文件解码器结构解码
        //但是这里还是需要加锁,需要保证在同一时刻,线程thread_read_frame和线程thread_upend_read_frame只能有一个处于工作循环状态
        //否则两个线程的av_read_frame(FormatCtx, Packet)有可能产生冲突
        //如果以下操作正在进行, 突然mediacontrol->upend为false, 即倒放操作取消了
        //thread_read_frame线程立刻可以运作了,可是以下操作还在继续,此时就会产生冲突
        //当用户的倒退播放指令下达后,线程thread_upend_read_frame进入工作循环状态
        //当用户的倒退播放停止指令下达后,线程thread_read_frame进入工作循环状态
        SDL_LockMutex(read_mutex);

        //正式开始倒退播放控制
        if (end_pts == -1) {//说明刚进行倒放操作,清除文件解码器结构和队列数据,同时初始化倒放操作
            SDL_LockMutex(mediacodec->audiocodec->mutex);
            packet_queue_clean(aqueue);//本着尽早释放不用资源的原则
            avcodec_flush_buffers(aCodecCtx);//同
            SDL_UnlockMutex(mediacodec->audiocodec->mutex);

            SDL_LockMutex(mediacodec->videocodec->mutex);
            packet_queue_clean(vqueue);//同
            avcodec_flush_buffers(pCodecCtx);//倒放需求
            SDL_UnlockMutex(mediacodec->videocodec->mutex);
            end_pts = mediacodec->videocodec->now_pts;
            end_clock = av_q2d(vStream->time_base) * end_pts;
            //初始化end_clock时不直接使用video_clock的原因:
            //我们需要知道什么时候结束,因此pts是一个重要标志,而video_clock回推pts可能是不准确的
            begin_pts = -1;
            now_pts = -1;
        }

        double temp_begin_clock = end_clock - upend_interval;
        if (temp_begin_clock < 0) {
            temp_begin_clock = 0;
        }
        if (av_seek_frame(FormatCtx, videoStream_i, int64_t(temp_begin_clock / av_q2d(vStream->time_base)), AVSEEK_FLAG_BACKWARD) < 0) {
            fprintf(stderr, "Upend skip video frame - failed.\n");
        }

        UpendImage* begin_image = NULL;
        UpendImage* end_image = NULL;
        int size = 0;
        while (true) {
            //begin_pts------------------------------------------end_pts
            //now_pts--------------------------------------------end_pts//开始
            //-----------------now_pts---------------------------end_pts
            //----------------------------------now_pts----------end_pts
            //---------------------------------------------------now_pts//结束
            if (now_pts == end_pts) {
                break;
            }
            av_read_frame(FormatCtx, Packet);
            while (Packet->stream_index != videoStream_i) {
                av_packet_unref(Packet);
                av_read_frame(FormatCtx, Packet);
            }//只取视频帧
            ret = avcodec_send_packet(pCodecCtx, Packet);
            got_picture = avcodec_receive_frame(pCodecCtx, Frame);
            if (ret == 0 && got_picture == 0) {
                if (begin_pts == -1) {//只有第一次解析帧成功,才正式设定begin_pts
                    begin_pts = Packet->pts;
                    begin_clock = av_q2d(vStream->time_base) * begin_pts;
                }
                sws_scale(convert_ctx, (uint8_t const* const*)Frame->data, Frame->linesize, 0, pCodecCtx->height, FrameRGB->data, FrameRGB->linesize);
                QImage image = QImage((uchar*)out_buffer, pCodecCtx->width, pCodecCtx->height, QImage::Format_RGB32);
                UpendImage* now_image = new UpendImage;
                now_image->image = image.copy();
                now_image->pts = Packet->pts;

                if (!end_image) {
                    now_image->last = NULL;
                    begin_image = now_image;
                    end_image = now_image;
                }
                else {
                    now_image->last = end_image;
                    end_image = now_image;
                }
                size += 1;
            }
            now_pts = Packet->pts;
            now_clock = av_q2d(vStream->time_base) * now_pts;
        }
        upend_queue_put(upend_queue, begin_image, end_image, size);
        avcodec_flush_buffers(pCodecCtx);
        end_pts = begin_pts;
        end_clock = av_q2d(vStream->time_base) * end_pts;
        begin_pts = -1;
        now_pts = -1;
        SDL_UnlockMutex(read_mutex);
    }

    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread -= 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);
    cout << "thread_upend_read_frame exit.\n";
    return 0;
}


int Core::assist_thread_video_seek(void* arg)
{
    //该线程已经默认视频流存在
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    AVFormatContext* FormatCtx = avformat_alloc_context();
    string string_path = centralcontrol->processing->file_path.toStdString();
    const char* path = string_path.c_str();
    avformat_open_input(&FormatCtx, path, NULL, NULL);
    avformat_find_stream_info(FormatCtx, NULL);
    AVStream* vStream = mediacodec->videocodec->Stream;
    int videoStream_i = mediacodec->videoStream_i;
    const AVCodec* Codec = avcodec_find_decoder(FormatCtx->streams[videoStream_i]->codecpar->codec_id);
    AVCodecContext* CodecCtx = avcodec_alloc_context3(NULL);
    avcodec_parameters_to_context(CodecCtx, FormatCtx->streams[videoStream_i]->codecpar);
    avcodec_open2(CodecCtx, Codec, NULL);

    AVPacket* Packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    av_init_packet(Packet);
    AVFrame* Frame = av_frame_alloc();
    AVFrame* FrameRGB = av_frame_alloc();
    int dstW = CodecCtx->width;
    int dstH = CodecCtx->height;
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB32, dstW, dstH, 1);
    uint8_t* out_buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(FrameRGB->data, FrameRGB->linesize, out_buffer, AV_PIX_FMT_RGB32, dstW, dstH, 1);

    int srcW = CodecCtx->width;
    int srcH = CodecCtx->height;
    enum AVPixelFormat srcFormat = CodecCtx->pix_fmt;
    enum AVPixelFormat dstFormat = AV_PIX_FMT_RGB32;
    int flags = SWS_BICUBIC;
    struct SwsContext* convert_ctx = sws_getContext(srcW, srcH, srcFormat, dstW, dstH, dstFormat, flags, NULL, NULL, NULL);

    while (true) {
        //退出控制
        if (mediacontrol->exit) {
            break;
        }

        //寻找控制
        if (mediacontrol->seek) {
            if (av_seek_frame(FormatCtx, videoStream_i, mediacontrol->timestamp / av_q2d(vStream->time_base), AVSEEK_FLAG_BACKWARD) < 0) {
                fprintf(stderr, "Seek video frame - failed.\n");
            }
            for (int i = 0; i < 10; i++)
            {
                int exit = av_read_frame(FormatCtx, Packet);
                while (Packet->stream_index != videoStream_i && exit >= 0) {
                    av_packet_unref(Packet);
                    exit = av_read_frame(FormatCtx, Packet);
                }
                if (exit < 0) {//结尾帧
                    av_packet_unref(Packet);
                    break;
                }
                int ret = avcodec_send_packet(CodecCtx, Packet);
                int got_picture = avcodec_receive_frame(CodecCtx, Frame);
                if (ret == 0 && got_picture == 0) {
                    sws_scale(convert_ctx, (uint8_t const* const*)Frame->data, Frame->linesize, 0, CodecCtx->height, FrameRGB->data, FrameRGB->linesize);
                    QImage image = QImage((uchar*)out_buffer, CodecCtx->width, CodecCtx->height, QImage::Format_RGB32);
                    emit centralcontrol->processing->signal_core_getimage_seekwidget(image.copy());
                    av_packet_unref(Packet);
                    break;
                }
            }
            mediacontrol->seek = false;
        }
        //休息一会,不要太忙碌了
        SDL_Delay(10);
    }
    sws_freeContext(convert_ctx);
    av_free(out_buffer);
    av_frame_free(&Frame);
    av_frame_free(&FrameRGB);
    av_packet_free(&Packet);
    avcodec_close(CodecCtx);
    //const AVCodec* Codec不需要单独释放,输出流结构体AVCodecContext释放的时候,会顺便释放编码器
    avformat_close_input(&FormatCtx);
    avformat_free_context(FormatCtx);
    cout << "assist_thread_video_seek exit.\n";
    return 0;
}

void Core::decode_video_frame(CentralControl* centralcontrol)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    SDL_LockMutex(mediacodec->videocodec->mutex);
    AVStream* Stream = mediacodec->videocodec->Stream;
    PacketQueue* queue = mediacodec->videocodec->queue;
    AVPacket* Packet = mediacodec->videocodec->Packet;
    AVCodecContext* CodecCtx = mediacodec->videocodec->CodecCtx;
    AVFrame* Frame = mediacodec->videocodec->Frame;
    AVFrame* FrameRGB = mediacodec->videocodec->FrameRGB;
    struct SwsContext* convert_ctx = mediacodec->videocodec->convert_ctx;
    uint8_t* out_buffer = mediacodec->videocodec->out_buffer;
    bool video_clock_change = mediacodec->videocodec->video_clock_change;
    int ret, got_picture;

    if (packet_queue_get(queue, Packet) >= 0) {
        ret = avcodec_send_packet(CodecCtx, Packet);
        got_picture = avcodec_receive_frame(CodecCtx, Frame);
        if (ret == 0 && got_picture == 0) {
            sws_scale(convert_ctx, (uint8_t const* const*)Frame->data, Frame->linesize, 0, CodecCtx->height, FrameRGB->data, FrameRGB->linesize);
            //out_buffer与pFrameRGB是捆绑的,将out_buffer里面的数据存在QImage里面
            QImage image = QImage((uchar*)out_buffer, CodecCtx->width, CodecCtx->height, QImage::Format_RGB32);
            //把图像复制一份,传递给界面显示
            //显示到控件,发射信号
            emit centralcontrol->processing->signal_core_getimage_display(image.copy());
        }
        if (Packet->pts != AV_NOPTS_VALUE) {//值存在
            mediacodec->videocodec->now_pts = Packet->pts;
            if (video_clock_change) {
                mediacodec->video_clock = av_q2d(Stream->time_base) * Packet->pts;
                video_clock_change = false;
            }
        }
        av_packet_unref(Packet);
    }
    SDL_UnlockMutex(mediacodec->videocodec->mutex);
}

void Core::synchronize_video(CentralControl* centralcontrol)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    int audioStream_i = mediacodec->audioStream_i;
    AVStream* Stream = mediacodec->videocodec->Stream;
    int64_t now_pts = mediacodec->videocodec->now_pts;
    //这里有一个坑:
    //av_q2d(Stream->time_base)表示视频的时间基,其与now_pts之积为该帧在视频中的时间
    //fps表示视频每秒多少帧,其倒数即为两相邻帧的时间间隔
    //两值可以相同,也可以不相同
    double video_clock = av_q2d(Stream->time_base) * now_pts;
    double fps = mediacodec->videocodec->fps;
    //mediacodec->video_clock 表示现在视频达到的时间点
    if (audioStream_i != -1) {//既有音频流也有视频流,此时视频流根据音频流的时钟来更新
        //cout << video_clock << "   " << mediacodec->audio_clock << endl;
        //视频时间与音频时间比较
        //如果两者差距过大:如果前者过慢则跳过更新等待时间直接更新下一帧视频值,否则下一帧直到两者差距小于某个阈值时才会更新
        //如果两者差距不是太大:如果前者过慢则下一帧视频更新时间比time_base小一点,否则下一帧视频更新时间比time_base大一点
        if (video_clock < mediacodec->audio_clock - 1) {
            //do nothing
        }
        else if (video_clock > mediacodec->audio_clock + 1) {
            do {
                SDL_Delay(100);
            } while (video_clock > mediacodec->audio_clock + 0.2);
        }
        else if (video_clock < mediacodec->audio_clock - 0.2) {
            SDL_Delay(1 / fps * 1000 * 0.75);
        }
        else if (video_clock > mediacodec->audio_clock + 0.2) {
            SDL_Delay(1 / fps * 1000 * 1.25);
        }
        else {
            SDL_Delay(1 / fps * 1000);
        }
    }
    else {//只有视频流没有音频流,此时视频流根据自己的时钟来更新
        double next_video_clock = mediacodec->video_clock + 1 / fps;
        if (video_clock <= mediacodec->video_clock) {
            //do nothing
        }
        else if (video_clock <= next_video_clock + 0.2) {
            SDL_Delay(1 / fps * 1000);
        }
        else if (video_clock > next_video_clock + 1) {
            do {
                SDL_Delay(1 / fps * 1000);
                mediacodec->video_clock += 1 / fps;
                next_video_clock += 1 / fps;
            } while (video_clock > next_video_clock + 0.2);
        }
        else {
            SDL_Delay(1 / fps * 1000 * 1.25);
        }
    }
    mediacodec->video_clock = video_clock;
    if (audioStream_i == -1) {
        if (abs(mediacodec->video_clock - mediacodec->emit_video_clock) >= 1) {//只有差值过大,才会发送时间信号
            mediacodec->emit_video_clock = mediacodec->video_clock;
            emit centralcontrol->processing->signal_core_clock(mediacodec->emit_video_clock);
        }
    }
}

void Core::upend_video_show(CentralControl* centralcontrol)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    AVStream* Stream = mediacodec->videocodec->Stream;
    double fps = mediacodec->videocodec->fps;
    UpendQueue* upend_queue = mediacodec->videocodec->upend_queue;
    UpendImage* a_image = new UpendImage;
    if (upend_queue_get(upend_queue, a_image) >= 0) {
        emit centralcontrol->processing->signal_core_getimage_display(a_image->image.copy());
    }

    double video_clock = av_q2d(Stream->time_base) * a_image->pts;
    double last_video_clock = mediacodec->video_clock - 1 / fps;

    if (video_clock >= mediacodec->video_clock) {
        //do nothing
    }
    else if (video_clock >= last_video_clock - 0.2) {
        SDL_Delay(1 / fps / mediacontrol->upend_speed * 1000);
    }
    else if (video_clock < last_video_clock - 1) {
        do {
            SDL_Delay(1 / fps / mediacontrol->upend_speed * 1000);
            mediacodec->video_clock -= 1 / fps;
            last_video_clock -= 1 / fps;
        } while (video_clock > last_video_clock - 0.2);
    }
    else {
        SDL_Delay(1 / fps / mediacontrol->upend_speed * 1000 * 1.25);
    }
    mediacodec->video_clock = video_clock;
    if (abs(mediacodec->video_clock - mediacodec->emit_video_clock) >= 1) {//只有差值过大,才会发送时间信号
        mediacodec->emit_video_clock = mediacodec->video_clock;
        emit centralcontrol->processing->signal_core_clock(mediacodec->emit_video_clock);
    }
    delete a_image;
}

int Core::thread_video(void* arg)
{
    //该线程已经默认视频流存在
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;
    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread += 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);

    while (true) {
        //退出控制
        if (mediacontrol->exit) {
            break;
        }

        //暂停播放控制
        if (mediacontrol->pause) {
            SDL_Delay(10);
            continue;
        }

        //倒退播放控制
        if (!mediacontrol->upend) {
            decode_video_frame(centralcontrol);
            synchronize_video(centralcontrol);
        }
        else {
            upend_video_show(centralcontrol);
        }
    }

    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread -= 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);
    cout << "thread_video exit.\n";
    return 0;
}


int Core::decode_audio_frame(CentralControl* centralcontrol, uint8_t* audio_buf)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    SDL_LockMutex(mediacodec->audiocodec->mutex);
    PacketQueue* queue = mediacodec->audiocodec->queue;
    AVPacket* Packet = mediacodec->audiocodec->Packet;
    AVCodecContext* CodecCtx = mediacodec->audiocodec->CodecCtx;
    AVFrame* Frame = mediacodec->audiocodec->Frame;
    SwrContext* convert_ctx = mediacodec->audiocodec->convert_ctx;
    uint8_t* out_buffer = mediacodec->audiocodec->out_buffer;
    int out_buffer_size = mediacodec->audiocodec->out_buffer_size;
    int ret, got_sound;
    memset(audio_buf, 0, out_buffer_size);
    if (packet_queue_get(queue, Packet) >= 0) {
        ret = avcodec_send_packet(CodecCtx, Packet);
        got_sound = avcodec_receive_frame(CodecCtx, Frame);
        //apacket->pts 和 aFrame->pts 是一样的
        if (ret == 0 && got_sound == 0) {
            swr_convert(convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)Frame->data, Frame->nb_samples);
            //函数有三个参数,第一个是目标地址,第二个是源地址,第三个是数据长度
            //注意:数据长度(第三个参数)的单位是字节(1byte = 8bit)
            memcpy(audio_buf, out_buffer, out_buffer_size);
        }
        if (Packet->pts != AV_NOPTS_VALUE) {//值存在
            mediacodec->audiocodec->now_pts = Packet->pts;
        }
        av_packet_unref(Packet);
    }
    SDL_UnlockMutex(mediacodec->audiocodec->mutex);
    return out_buffer_size;
}

void Core::callback_audio(void* userdata, Uint8* stream, int len)
{
    CentralControl* centralcontrol = (CentralControl*)userdata;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;
    //audio_buf:
    //|------------------------------------------------------------...
    //decode_audio_frame-return:
    //0--------------------------------------------------size
    //index----------len---------------------------------size
    //|||||||||||||||index----------len------------------size
    //||||||||||||||||||||||||||||||index----------len---size
    //|||||||||||||||||||||||||||||||||||||||||||||index-len(size)
    //||||||||||||||||||||||||||||||||||||||||||||||||||||
    static uint8_t audio_buf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];
    //index和size标示我们自己用来放置解码出来的数据的缓冲区,这些数据待copy到SDL缓冲区
    //当index == size的时候意味着我们的缓冲为空,没有数据可供copy,
    //这时候需要调用decode_audio_frame函数来解码出更多的桢数据  
    static unsigned int index = 0;
    static unsigned int size = 0;
    int len1;

    SDL_memset(stream, 0, len);
    //len是由SDL传入的SDL缓冲区的大小,如果这个缓冲未满,我们就一直往里填充数据
    while (len > 0) {
        if (index == size) {
            size = decode_audio_frame_(centralcontrol, audio_buf);
            index = 0;
        }
        //查看stream可用空间,决定一次copy多少数据,剩下的下次继续copy
        len1 = size - index;
        if (len1 > len) {
            len1 = len;
        }
        //将缓冲区数据复制到SDL-stream中
        //同时音量控制
        SDL_MixAudio(stream, (uint8_t*)audio_buf + index, len, mediacontrol->volume);
        len -= len1;
        stream += len1;
        index += len1;
        update_audio_clock(centralcontrol, index);
    }
}

void Core::update_audio_clock(CentralControl* centralcontrol, unsigned int index)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    AVCodecContext* aCodecCtx = mediacodec->audiocodec->CodecCtx;
    AVStream* Stream = mediacodec->audiocodec->Stream;
    int64_t now_pts = mediacodec->audiocodec->now_pts;
    double audio_clock = 0;
    int channels = 2 * aCodecCtx->channels;
    int sample_rate = aCodecCtx->sample_rate;

    //apacket的第一帧播放完所对应的时间
    audio_clock = av_q2d(Stream->time_base) * now_pts;
    //如果上一行变量增加:
    //int aout_buffer_size = mediacodec->aout_buffer_size;
    //audio_clock +=(double)aout_buffer_size / (double)(channels * sample_rate)则为apacket的最后一帧播放完所对应的时间
    //apacket中某一帧存入SDL缓冲区所对应的时间
    audio_clock += (double)index / (double)(channels * sample_rate);

    mediacodec->audio_clock = audio_clock;
    if (abs(mediacodec->audio_clock - mediacodec->emit_audio_clock) >= 1) {//只有差值过大,才会发送时间信号
        mediacodec->emit_audio_clock = mediacodec->audio_clock;
        emit centralcontrol->processing->signal_core_clock(mediacodec->emit_audio_clock);
    }
}

int Core::thread_audio(void* arg)
{
    //该线程已经默认音频流存在
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;
    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread += 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);
    int videoStream_i = mediacodec->videoStream_i;

    //SDL_PauseAudio(int)为启停音频设备函数,传入参数0来使SDL调用回调函数来播放音频;若传入的是大于0的值此时将暂停音频播放设备,期间将传入静音数据
    bool sdl_on = false;
    while (true) {
       
        //退出控制
        if (mediacontrol->exit) {
            break;
        }
        //暂停播放控制
        if (mediacontrol->pause) {
            if (sdl_on) {
                SDL_PauseAudio(1);
                sdl_on = false;
            }
        }
        else {
            if (!sdl_on) {
                SDL_PauseAudio(0);
                sdl_on = true;
            }
        }

        //倒退播放控制(只对视频流有控制作用,即如果视频流不存在则忽略该控制)
        if (mediacontrol->upend && videoStream_i != -1) {
            if (sdl_on) {
                SDL_PauseAudio(1);
                sdl_on = false;
            }
        }
        
        //休息一会,不要太忙碌了
        SDL_Delay(10);
    }
    
    SDL_LockMutex(mediacontrol->thread_mutex);
    mediacontrol->running_thread -= 1;
    SDL_UnlockMutex(mediacontrol->thread_mutex);
    cout << "thread_audio exit.\n";
    return 0;
}


int Core::thread_console_debug(void* arg)
{
    CentralControl* centralcontrol = (CentralControl*)arg;
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    cout << "0:pause/play" << endl;
    cout << "1:volume+" << endl;
    cout << "2:volume-" << endl;
    cout << "3:skip1/4" << endl;
    cout << "4:skip3/4" << endl;
    cout << "5:seek" << endl;
    cout << "6:upend*1.0" << endl;
    cout << "7:upend*2.0" << endl;
    cout << "8:speed(a little mistake)" << endl;
    cout << "9:exit" << endl;
    char kind;
    while (cin >> kind) {
        if (!centralcontrol->processing->init) {
            continue;
        }
        switch (kind) {
        case '0':
            mediacontrol->pause = !mediacontrol->pause;
            break;
        case '1':
            if (mediacontrol->volume + 30 <= 128)
            {
                mediacontrol->volume += 30;
            }
            break;
        case '2':
            if (mediacontrol->volume - 30 >= 0)
            {
                mediacontrol->volume -= 30;
            }
            break;
        case '3':
            mediacontrol->timestamp = (int64_t)(mediacodec->duration / 4);
            mediacontrol->skip = true;
            break;
        case '4':
            mediacontrol->timestamp = (int64_t)(mediacodec->duration / 4 * 3);
            mediacontrol->skip = true;
            break;
        case '5':
            mediacontrol->timestamp = (int64_t)(mediacodec->duration / 2);
            mediacontrol->seek = true;
            break;
        case '6':
            if (!(mediacontrol->upend_speed == 2.0 && mediacontrol->upend)) {
                mediacontrol->pause = !mediacontrol->pause;
                mediacontrol->upend = !mediacontrol->upend;
            }
            mediacontrol->upend_speed = 1.0;
            break;
        case '7':
            if (!(mediacontrol->upend_speed == 1.0 && mediacontrol->upend)) {
                mediacontrol->pause = !mediacontrol->pause;
                mediacontrol->upend = !mediacontrol->upend;
            }
            mediacontrol->upend_speed = 2.0;
            break;
        case '8':
            if (mediacontrol->speed == 1) {
                mediacontrol->speed = 1.5;
            }
            else  if (mediacontrol->speed == 1.5) {
                mediacontrol->speed = 2;
            }
            else  if (mediacontrol->speed == 2) {
                mediacontrol->speed = 4;
            }
            else  if (mediacontrol->speed == 4) {
                mediacontrol->speed = 8;
            }
            else if (mediacontrol->speed == 8) {
                mediacontrol->speed = 0.5;
            }
            else if (mediacontrol->speed == 0.5) {
                mediacontrol->speed = 1;
            }
            mediacontrol->speed_change = true;
            break;
        case '9':
            mediacontrol->exit = true;
            break;
        }
    }
    return 0;
}


void Core::slot_core_pause(bool pause)
{
    mediacontrol->pause = pause;
}
void Core::slot_core_volume(int volume)
{
    mediacontrol->volume = int(volume * 1.28);
}
void Core::slot_core_seek(int64_t timestamp)
{
    mediacontrol->timestamp = timestamp;
    mediacontrol->seek = true;
}
void Core::slot_core_skip()
{
    mediacontrol->skip = true;
}
void Core::slot_core_upend(double upend_speed)
{
    mediacontrol->upend = true;
    mediacontrol->upend_speed = upend_speed;
}
void Core::slot_core_upend_cancel()
{
    mediacontrol->upend = false;
}


int Core::decode_audio_frame_(CentralControl* centralcontrol, uint8_t* audio_buf)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    SDL_LockMutex(mediacodec->audiocodec->mutex);
    PacketQueue* queue = mediacodec->audiocodec->queue;
    AVPacket* Packet = mediacodec->audiocodec->Packet;
    AVCodecContext* CodecCtx = mediacodec->audiocodec->CodecCtx;
    SoundTouch* soundtouch = mediacodec->audiocodec->soundtouch;
    AVFrame* Frame = mediacodec->audiocodec->Frame;
    SwrContext* convert_ctx = mediacodec->audiocodec->convert_ctx;
    uint8_t* out_buffer = mediacodec->audiocodec->out_buffer;
    SAMPLETYPE* soundtouch_buffer = mediacodec->audiocodec->soundtouch_buffer;
    int out_buffer_size = mediacodec->audiocodec->out_buffer_size;
    int ret, got_sound;
    int return_buffer_size = 0;
    memset(audio_buf, 0, out_buffer_size);
    if (packet_queue_get(queue, Packet) >= 0) {
        ret = avcodec_send_packet(CodecCtx, Packet);
        got_sound = avcodec_receive_frame(CodecCtx, Frame);
        //apacket->pts 和 aFrame->pts 是一样的
        if (ret == 0 && got_sound == 0) {
            swr_convert(convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)Frame->data, Frame->nb_samples);

            if (mediacontrol->speed_change == true) {
                //soundtouch->flush();
                //soundtouch->setTempo(0.5);
                mediacontrol->speed_change = false;
                cout << mediacontrol->speed << endl;
            }
            if (mediacontrol->speed != 1) {//倍速处理
                //函数有三个参数,第一个是目标地址,第二个是源地址,第三个是数据长度
                //注意:数据长度(第三个参数)的单位是字节(1byte = 8bit)
                //memcpy(soundtouch_buffer, out_buffer, out_buffer_size);
                for (int i = 0; i < out_buffer_size / 2; i++)
                {
                    soundtouch_buffer[i] = (out_buffer[i * 2] | (out_buffer[i * 2 + 1] << 8));
                }
                soundtouch->putSamples(soundtouch_buffer, out_buffer_size / 2 / 2);

                int nb_samples = soundtouch->receiveSamples(soundtouch_buffer, 4096);
                memcpy(audio_buf, soundtouch_buffer, nb_samples * 2);
                //for (int i = 0; i < nb_samples + 1; i++)
                //{
                //    audio_buf[i * 2] = (uint8_t)soundtouch_buffer[i];
                //    audio_buf[i * 2 + 1] = (uint8_t)(soundtouch_buffer[i] >> 8);
                //}

                return_buffer_size = nb_samples * 2;

                //存在bug
                //用法就不是这么用的..
                //据说:不基于流的方法由于解码一帧数据会flush掉数组中剩下的没有处理的数据并填充空数据,会产生刺啦刺啦的声音
            }
            else {
                memcpy(audio_buf, out_buffer, out_buffer_size);
                return_buffer_size = out_buffer_size;
            }
        }
        if (Packet->pts != AV_NOPTS_VALUE) {//值存在
            mediacodec->audiocodec->now_pts = Packet->pts;
        }
        av_packet_unref(Packet);
    }
    SDL_UnlockMutex(mediacodec->audiocodec->mutex);
    return return_buffer_size;
}
int Core::decode_audio_frame__(CentralControl* centralcontrol, uint8_t* audio_buf)
{
    MediaCodec* mediacodec = centralcontrol->mediacodec;
    MediaControl* mediacontrol = centralcontrol->mediacontrol;

    SDL_LockMutex(mediacodec->audiocodec->mutex);
    PacketQueue* queue = mediacodec->audiocodec->queue;
    AVPacket* Packet = mediacodec->audiocodec->Packet;
    AVCodecContext* CodecCtx = mediacodec->audiocodec->CodecCtx;
    AVFrame* Frame = mediacodec->audiocodec->Frame;
    SwrContext* convert_ctx = mediacodec->audiocodec->convert_ctx;
    uint8_t* out_buffer = mediacodec->audiocodec->out_buffer;
    int out_buffer_size = mediacodec->audiocodec->out_buffer_size;
    int ret, got_sound;
    memset(audio_buf, 0, out_buffer_size);
    if (packet_queue_get(queue, Packet) >= 0) {
        ret = avcodec_send_packet(CodecCtx, Packet);
        got_sound = avcodec_receive_frame(CodecCtx, Frame);
        //apacket->pts 和 aFrame->pts 是一样的
        if (ret == 0 && got_sound == 0) {
            swr_convert(convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)Frame->data, Frame->nb_samples);
            //函数有三个参数,第一个是目标地址,第二个是源地址,第三个是数据长度
            //注意:数据长度(第三个参数)的单位是字节(1byte = 8bit)








            memcpy(audio_buf, out_buffer, out_buffer_size);
        }
        if (Packet->pts != AV_NOPTS_VALUE) {//值存在
            mediacodec->audiocodec->now_pts = Packet->pts;
        }
        av_packet_unref(Packet);
    }
    SDL_UnlockMutex(mediacodec->audiocodec->mutex);
    return out_buffer_size;
}
