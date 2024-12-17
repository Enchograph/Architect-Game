#include <QEventLoop>
#include <QTimer>

void sleep(int time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, &QEventLoop::quit);  // 延迟 1 秒
    loop.exec();  // 进入事件循环并等待 QTimer 完成
}
