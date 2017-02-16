#ifndef LUNAWORKER_H
#define LUNAWORKER_H

#include <QThread>


namespace luna {
    class LunaWorker : public QThread
    {
        Q_OBJECT
    public:
        explicit LunaWorker(QObject * parent = nullptr);
    signals:
        void shutdown();

    protected:
        void run() override;
    private:
        class LunaManager * mLunaManager;
        void init();
        void cleanup();
    };
}

#endif // LUNAWORKER_H
