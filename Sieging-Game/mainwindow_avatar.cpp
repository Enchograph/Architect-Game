#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_selectAvatarBtn_clicked()
{
    // 弹出文件对话框让用户选择图片
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = QFileDialog::getOpenFileName(this, "选择图片", desktopPath, "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty())
    {
        QPixmap pixmap(filePath);
        if (!pixmap.isNull())
        {
            // 创建裁剪窗口
            CropWindow *cropWindow = new CropWindow(pixmap, this);
            connect(cropWindow, &CropWindow::imageCropped, this, &MainWindow::onImageCropped);
            cropWindow->exec();  // 弹出裁剪窗口（模态）
        }
        else
        {
            ui->avatarLabel->setText("无法加载图片");
        }
    }
}
void MainWindow::onImageCropped(const QPixmap &croppedPixmap)
{
    // 将图片缩放到128x128
        QPixmap scaledPixmap = croppedPixmap.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 创建一个透明的图片，用来绘制圆形
        QImage circleImage(128, 128, QImage::Format_ARGB32);
        circleImage.fill(Qt::transparent);

        // 创建 QPainter 用于绘制圆形
        QPainter painter(&circleImage);
        painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿效果
        painter.setBrush(QBrush(scaledPixmap));  // 使用缩放后的图片作为画刷
        painter.setPen(Qt::NoPen);  // 不使用边框

        // 绘制一个圆形（直径128）
        painter.drawEllipse(0, 0, 128, 128);

        painter.end();


        // 将处理后的圆形图像设置到 avatarLabel
        //ui->avatarLabel->setPixmap(QPixmap::fromImage(circleImage));

        if(currentUser)
        {

            QString filePath = currentUser->currentUid + ".png";  // 保存路径，可以根据需要修改
            circleImage.save(filePath, "PNG");  // 保存为PNG文件
        }
        else
        {
            qDebug()<<"error on saving avatar.";
        }
        updateUserInformation();
}
