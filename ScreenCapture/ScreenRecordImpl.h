#pragma once

#include <atomic>
#include <QObject>
#include <QString>
#include <QMutex>

#include <Windows.h>

#ifdef	__cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
};
#endif

struct AVFormatContext;
struct AVCodecContext;
struct AVCodec;
struct AVFifoBuffer;
struct AVAudioFifo;
struct AVFrame;
struct SwsContext;

class ScreenRecordImpl : public QObject
{
	Q_OBJECT
public:
	ScreenRecordImpl();

	int OpenVideo();
	int OpenAudio();
	int OpenOutput();

	private slots:
	void Start();

private:
	//��fifobuf��ȡ����Ƶ֡��д������������ã������ļ�
	void MuxThreadProc();
	//����Ƶ��������ȡ֡��д��fifobuf
	void ScreenRecordThreadProc();
	//����Ƶ��������ȡ֡��д��fifobuf
	void SoundRecordThreadProc();

private:

	QString				m_filePath;
	int					m_width;
	int					m_height;
	int					m_fps;

	int m_vIndex;		//������Ƶ������
	int m_aIndex;		//������Ƶ������
	AVFormatContext		*m_vFmtCtx;
	AVFormatContext		*m_aFmtCtx;
	AVFormatContext		*m_oFmtCtx;
	AVCodecContext		*m_vDecodeCtx;
	AVCodecContext		*m_aDecodeCtx;
	AVCodecContext		*m_vEncodeCtx;
	AVCodecContext		*m_aEncodeCtx;
	SwsContext			*m_swsCtx;
	AVFifoBuffer		*m_vBuf;
	AVAudioFifo			*m_aBuf;

	AVFrame				*m_vOutFrame;
	AVFrame				*m_aOutFrame;
	uint8_t				*m_vOutFrameBuf;
	uint8_t				*m_aOutFrameBuf;
	int					m_vOutFrameSize;
	int					m_aOutFrameSize;
	std::atomic_bool	m_stop;
	int					m_videoFrameSize;

	CRITICAL_SECTION	m_vSection, m_aSection;
	int					m_vFrameIndex, m_aFrameIndex;	//��ǰ֡λ��

	bool				m_started;
};