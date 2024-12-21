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

    QPixmap getCroppedImage();

signals:
    void imageCropped(const QPixmap &croppedImage); // 裁剪完成信号

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

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
