#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::switchPage(QWidget *targetPage)
{

    if (ui->contentPage->currentWidget() != targetPage)
    {
        int pageHeight = ui->contentPage->height();
        QWidget *currentPage = ui->contentPage->currentWidget();

        updatePageLayout(getPageIndex(targetPage));
        updatePageLayout(getPageIndex(currentPage));

        QPropertyAnimation *hideAnim = new QPropertyAnimation(currentPage, "geometry", this);
        QPropertyAnimation *showAnim = new QPropertyAnimation(targetPage, "geometry", this);

        int direction = getPageIndex(targetPage) < getPageIndex(currentPage) ? 1 : -1;

        // 隐藏当前页面的动画
        hideAnim->setDuration(500);
        hideAnim->setEasingCurve(QEasingCurve::Linear);
        hideAnim->setStartValue(currentPage->geometry());
        hideAnim->setEndValue(QRect(0, direction * pageHeight, currentPage->width(), currentPage->height()));

        // 显示目标页面的动画
        showAnim->setDuration(500);
        showAnim->setEasingCurve(QEasingCurve::Linear);
        showAnim->setStartValue(QRect(0, -direction * pageHeight, targetPage->width(), targetPage->height()));
        showAnim->setEndValue(QRect(0, 0, targetPage->width(), targetPage->height()));

        // 页面切换结束后开始显示动画
        connect(hideAnim, &QPropertyAnimation::finished, this, [=]()
                {
            ui->contentPage->setCurrentWidget(targetPage);

            //这一行是成功的解决方案 updatePageLayout(getPageIndex(targetPage));

            showAnim->start(); });

        hideAnim->start();
    }
}

void MainWindow::updatePageLayout(int pageIndex) // 强制刷新页面布局
{
    // 获取目标页面
    QWidget *page = ui->contentPage->widget(pageIndex);
    if (!page)
        return; // 确保页面有效

    page->adjustSize();
    page->updateGeometry();

    QResizeEvent resizeEvent(ui->contentPage->size(), ui->contentPage->size());
    QApplication::sendEvent(page, &resizeEvent);

    QLayout *layout = page->layout();
    if (layout)
    {
        layout->activate(); // 重新计算布局
    }

    QSize originalSize = page->size();
    page->resize(originalSize.width() + 1, originalSize.height() + 1);
    page->resize(originalSize);

    ui->contentPage->setCurrentIndex(pageIndex);
    ui->contentPage->update(); // 更新 contentPage
    page->update();            // 更新目标页面
}

int MainWindow::getPageIndex(QWidget *page)
{
    if (page == ui->beginPage)
        return 0;
    if (page == ui->vsComptrPage)
        return 1;
    if (page == ui->vsPeoplePage)
        return 2;
    if (page == ui->loginPage)
        return 3;
    if (page == ui->settingPage)
        return 4;
    if (page == ui->aboutPage)
        return 5;
    if (page == ui->gamePage)
        return 6;
    return -1;
}

void MainWindow::on_vsComptrBtn_clicked() { switchPage(ui->vsComptrPage); }
void MainWindow::on_vsPeopleBtn_clicked() { switchPage(ui->vsPeoplePage); }
void MainWindow::on_mainPageBtn_clicked() { switchPage(ui->beginPage); }
void MainWindow::on_loginBtn_clicked() { switchPage(ui->loginPage); }
void MainWindow::on_settingsBtn_clicked() { switchPage(ui->settingPage); }
void MainWindow::on_aboutBtn_clicked() { switchPage(ui->aboutPage); }

void MainWindow::on_vsComptrBtn_2_clicked() { switchPage(ui->vsComptrPage); }
void MainWindow::on_vsPeopleBtn_2_clicked() { switchPage(ui->vsPeoplePage); }
void MainWindow::on_mainPageBtn_2_clicked() { switchPage(ui->beginPage); }
void MainWindow::on_loginBtn_2_clicked() { switchPage(ui->loginPage); }
void MainWindow::on_settingsBtn_2_clicked() { switchPage(ui->settingPage); }
void MainWindow::on_aboutBtn_2_clicked() { switchPage(ui->aboutPage); }

void MainWindow::on_ruleBtn_clicked() { switchPage(ui->aboutPage); }
void MainWindow::on_ruleBtn_2_clicked() { switchPage(ui->aboutPage); }

void MainWindow::on_pushButton_16_clicked() { dialog11->exec(); }
void MainWindow::on_pushButton_17_clicked() { dialog12->exec(); }
void MainWindow::on_pushButton_18_clicked() { dialog13->exec(); }
void MainWindow::on_pushButton_19_clicked() { dialog21->exec(); }
void MainWindow::on_pushCowButton_clicked() { dialog14->exec(); }
