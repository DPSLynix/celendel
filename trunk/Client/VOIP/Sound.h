#ifndef DEF_SOUND
#define DEF_SOUND
#include <QObject>
#include <QQueue>

#include "global.h"

class QTimer;

namespace VOIPSystem
{

class Sound : public QObject
{
    Q_OBJECT
public:
    Sound(ALsizei sampleRate);
    ALint state();
    ~Sound();



public slots:
    void stop();
    void play();
    void pause();
    void queue(const ALshortVector & samples);
    void volume(const ALfloat& v);
    void mute();
    void unmute();

private slots:
    void testPlaying();

private:
    void allocateBuffers(int nb);
    void cleanBuffers();

private:
    size_t  m_sampleRate;
    ALfloat m_volume;
    bool    m_paused;
    bool    m_playing;
    ALuint  m_source;
    QQueue<ALuint> m_freeBuffers;
    QTimer *m_timer;
    bool m_freeze;

    int getQueuedBuffers();

};

}

#endif
