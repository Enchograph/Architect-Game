#include <QEventLoop>
#include <QTimer>

void sleep(int time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, &QEventLoop::quit);  // �ӳ� 1 ��
    loop.exec();  // �����¼�ѭ�����ȴ� QTimer ���
}
