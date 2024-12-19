#include "cropWindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

CropWindow::CropWindow(const QPixmap &pixmap, QWidget *parent)
    : QDialog(parent), originalImage(pixmap), dragging(false), resizing(false)
{
    setWindowModality(Qt::NonModal);
    setFixedSize(600, 700);  // 增加了 100 像素的高度用于显示裁剪按钮和文字说明

    // 缩放图片到窗口大小范围内，同时保持宽高比
    image = originalImage.scaled(600,600, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 记录缩放比例
    scaleFactor = static_cast<double>(image.width()) / originalImage.width();

    // 初始化裁剪框大小（为缩放图片的 1/2 尺寸）并居中
    int rectWidth = image.width() / 2;
    int rectHeight = image.height() / 2;
    selectionRect = QRect((width() - rectWidth) / 2, (height() - rectHeight) / 2, qMin(rectWidth, rectHeight),qMin(rectWidth, rectHeight));

    // 创建一个主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建一个显示图片的 QLabel  这是占位组件，并不真的显示图片
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(600,600);
    mainLayout->addWidget(imageLabel, 0, Qt::AlignCenter);  // 将图片居中显示

    // 添加文字说明
    QLabel *instructionLabel = new QLabel("请进行图片裁剪，使用滚轮缩放裁剪框。", this);
    instructionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(instructionLabel);

    // 创建裁剪按钮
    cropButton = new QPushButton("确定", this);
    mainLayout->addWidget(cropButton, 0, Qt::AlignCenter);  // 将按钮居中显示
    connect(cropButton, &QPushButton::clicked, [this] {
        emit imageCropped(getCroppedImage());
        close();
    });

    // 设置整个窗口的布局
    setLayout(mainLayout);
}

CropWindow::~CropWindow() {}

void CropWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap((600 - image.width()) / 2, (600 - image.height()) / 2, image);

    // 绘制裁剪框
    painter.setPen(QPen(Qt::red, 2));
    painter.drawRect(selectionRect);
}

void CropWindow::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = event->pos();
    if (selectionRect.contains(event->pos()))
    {
        dragging = true;
    }
}

void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging)
    {
        QPoint offset = event->pos() - lastMousePos;
        selectionRect.translate(offset);

        // 限制裁剪框在图片范围内
        selectionRect.moveLeft(qMax(selectionRect.left(), (600 - image.width()) / 2));
        selectionRect.moveTop(qMax(selectionRect.top(), (600 - image.height()) / 2));
        selectionRect.moveRight(qMin(selectionRect.right(), (600 + image.width()) / 2));
        selectionRect.moveBottom(qMin(selectionRect.bottom(), (600 + image.height()) / 2));

        lastMousePos = event->pos();
        update();
    }
}

void CropWindow::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}

QPixmap CropWindow::getCroppedImage()
{
    int top=
            (selectionRect.left() - (600 - image.width()) / 2)/ scaleFactor;
    int left=
            (selectionRect.top()-(600 - image.height()) / 2)/ scaleFactor;
    // 将裁剪框的坐标转换回原始图片的坐标
    QRect originalRect(top,left,
        selectionRect.width() / scaleFactor,
        selectionRect.height() / scaleFactor
    );

    // 返回原始图片中对应裁剪区域的 QPixmap
    return originalImage.copy(originalRect);
}

void CropWindow::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();  // 获取滚轮的滚动量
    const int zoomStep = 10;  // 设置每次滚动的增量

    QPoint center = selectionRect.center();

    if (delta > 0) // 放大
    {
        QRect newRect = selectionRect.adjusted(-zoomStep / 2, -zoomStep / 2, zoomStep / 2, zoomStep / 2);
        if (newRect.width() <= image.width() && newRect.height() <= image.height())
        {
            selectionRect = newRect;
        }
    }
    else if (delta < 0) // 缩小
    {
        if (selectionRect.width() >= zoomStep && selectionRect.height() >= zoomStep)
        {
            selectionRect.adjust(zoomStep / 2, zoomStep / 2, -zoomStep / 2, -zoomStep / 2);
        }
    }


    selectionRect.moveCenter(center);


    // 限制裁剪框在图片范围内
    selectionRect.moveLeft(qMax(selectionRect.left(), (600 - image.width()) / 2));
    selectionRect.moveTop(qMax(selectionRect.top(), (600 - image.height()) / 2));
    selectionRect.moveRight(qMin(selectionRect.right(), (600 + image.width()) / 2));
    selectionRect.moveBottom(qMin(selectionRect.bottom(), (600 + image.height()) / 2));
    update();
}
