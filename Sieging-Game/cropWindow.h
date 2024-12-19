#ifndef CROPWINDOW_H
#define CROPWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QRect>
#include <QPushButton>
#include <QPainter>


#include <QVBoxLayout>
#include <QLabel>

class CropWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CropWindow(const QPixmap &pixmap, QWidget *parent = nullptr);
    ~CropWindow();

    QPixmap getCroppedImage(); // 获取裁剪后的图片

signals:
    void imageCropped(const QPixmap &croppedImage); // 裁剪完成信号

protected:
    void paintEvent(QPaintEvent *event) override;          // 绘制事件
    void mousePressEvent(QMouseEvent *event) override;     // 鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event) override;      // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event) override;   // 鼠标释放事件
    void wheelEvent(QWheelEvent *event) override;          // 滚轮事件

private:
    QPixmap originalImage;   // 原始图片
    QPixmap image;           // 缩放后的图片
    QRect selectionRect;     // 裁剪框
    double scaleFactor;      // 图片缩放比例
    QPoint lastMousePos;     // 鼠标上一次位置
    bool dragging;           // 是否正在拖动裁剪框
    bool resizing;           // 是否正在调整裁剪框大小
    QPushButton *cropButton; // 裁剪按钮
    QLabel *imageLabel;
};

#endif // CROPWINDOW_H
