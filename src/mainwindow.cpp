#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QRandomGenerator>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget {parent}
{
    setFixedSize(screen_width, screen_height);
    setStyleSheet("background-color: black");
    setWindowIcon(QIcon(":/icon/game_icon.png"));
    setWindowTitle(tr("The Snake Game"));

    StartGame();
}

void MainWindow::StartGame()
{
    isRunning = true;
    direction = right;
    timerId = startTimer(delay);

    initialSnakeLength = 4;
    bodyParts = initialSnakeLength;
    applesEaten = 0;
    points = 7;

    SetSnakePos();
    NewApple();
}

void MainWindow::SetSnakePos()
{
    snake[0].y = unit_size;
    for(int i = 0; i < initialSnakeLength; ++i)
        snake[i].x = 2 * unit_size - i * unit_size;
}

void MainWindow::NewApple()
{
    appleX = QRandomGenerator::global()->bounded(0, screen_width / unit_size) * unit_size;
    appleY = QRandomGenerator::global()->bounded(0, screen_height / unit_size) * unit_size;

    if(!appleX)
        appleX = unit_size;

    if(appleX >= screen_width - unit_size)
        appleX = screen_width - 2 * unit_size;

    if(!appleY)
        appleY = unit_size;

    if(appleY >= screen_height - unit_size)
        appleY = screen_height - 2 * unit_size;
}

void MainWindow::Draw(QPainter *painter)
{
    if(isRunning)
    {
        DrawApple(painter);
        DrawSnake(painter);
        DrawWalls(painter);

        painter->setPen(Qt::white);
        DrawScore(painter);
        DrawApplesEaten(painter);
    }
    else
        GameOver(painter);
}

void MainWindow::DrawApple(QPainter *painter)
{
    if(!(applesEaten % 10) && applesEaten)
    {
        painter->setPen(Qt::yellow);
        painter->setBrush(Qt::yellow);
    }
    else
    {
        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);
    }
    painter->drawEllipse(appleX, appleY, unit_size, unit_size);
}

void MainWindow::DrawSnake(QPainter *painter)
{
    for(int i = 0; i < bodyParts; ++i)
    {
        if(!(i % 2))
        {
            painter->setPen(QColor(59, 144, 184));
            painter->setBrush(QColor(59, 144, 184));
        }
        else
        {
            painter->setPen(QColor(18, 68, 92));
            painter->setBrush(QColor(18, 68, 92));
        }

        painter->drawRect(snake[i].x, snake[i].y, unit_size, unit_size);
    }
}

void MainWindow::DrawWalls(QPainter *painter)
{
    for(int i = 0; i <= screen_width; i += unit_size)
    {
        painter->setPen(QColor(48, 48, 47));
        painter->setBrush(QColor(48, 48, 47));

        painter->drawRect(i, 0, unit_size, unit_size);
        painter->drawRect(i, screen_height - unit_size, unit_size, unit_size);
    }

    for(int i = 0; i <= screen_height; i += unit_size)
    {
        painter->setPen(QColor(48, 48, 47));
        painter->setBrush(QColor(48, 48, 47));

        painter->drawRect(0, i, unit_size, unit_size);
        painter->drawRect(screen_width - unit_size, i, unit_size, unit_size);
    }
}

void MainWindow::DrawScore(QPainter *painter)
{
    stringScore = QString::number(score);
    message = "score: " + stringScore;
    QFont font ("Courier New", unit_size - 5, QFont::StyleItalic);
    QFontMetrics fontMetrics(font);
    textWidth = fontMetrics.horizontalAdvance(message);

    painter->setFont(font);
    painter->drawText(screen_width / 2 - textWidth / 2, unit_size - unit_size / 5, message);
}

void MainWindow::DrawApplesEaten(QPainter *painter)
{
    stringApplesEaten = QString::number(applesEaten);
    message = "apples eaten: " + stringApplesEaten;
    QFont font ("Courier New", unit_size - 5, QFont::StyleItalic);
    QFontMetrics fontMetrics(font);
    textWidth = fontMetrics.horizontalAdvance(message);

    painter->setFont(font);
    painter->drawText(screen_width / 2 - textWidth / 2, screen_height - unit_size / 5, message);
}

void MainWindow::GameOver(QPainter *painter)
{
    message = "Game Over";
    QFont font ("Ink Free", 160, QFont::ExtraBold);
    QFontMetrics fontMetrics1(font);
    textWidth = fontMetrics1.horizontalAdvance(message);

    painter->setPen(QColor(125, 36, 36));
    painter->setFont(font);
    painter->drawText(screen_width / 2 - textWidth / 2, screen_height / 2 - 8 * unit_size, message);

    painter->setPen(QColor(128, 124, 124));
    font.setPointSize(70);
    font.setWeight(QFont::DemiBold);

    message = "SCORE: " + stringScore;
    QFontMetrics fontMetrics2(font);
    textWidth = fontMetrics2.horizontalAdvance(message);

    painter->setFont(font);
    painter->drawText(screen_width / 2 - textWidth / 2, screen_height / 2 - 2 * unit_size, message);

    message = "APPLES EATEN: " + stringApplesEaten;
    QFontMetrics fontMetrics3(font);
    textWidth = fontMetrics3.horizontalAdvance(message);

    painter->setFont(font);
    painter->drawText(screen_width / 2 - textWidth / 2, screen_height / 2 + 2 * unit_size, message);
}

void MainWindow::CheckCollision()
{
    if(snake[0].x == screen_width - unit_size  || snake[0].x < unit_size
            || snake[0].y == screen_height - unit_size || snake[0].y < unit_size)
        isRunning = false;

    for(int i = bodyParts; i; --i)
        if(snake[i].x == snake[0].x && snake[i].y == snake[0].y)
                isRunning = false;

    if(!isRunning)
        killTimer(timerId);
}

void MainWindow::CheckApple()
{
    if((snake[0].x == appleX) && (snake[0].y == appleY))
    {
        if(!(applesEaten % 10) && applesEaten)
            score += 2 * points;
        else
            score += points;

       ++bodyParts;
       ++applesEaten;

        NewApple();
    }
}

void MainWindow::Move()
{
    for(int i = bodyParts; i; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    switch(direction)
    {
        case up :
            snake[0].y -= unit_size;
            break;

        case right :
            snake[0].x += unit_size;
            break;

        case down :
            snake[0].y += unit_size;
            break;

        case left :
            snake[0].x -= unit_size;
            break;
    }

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    Draw(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W :
            if(direction != down)
                direction = up;
            break;

        case Qt::Key_D :
            if(direction != left)
                direction = right;
            break;


        case Qt::Key_S :
            if(direction != up)
                direction = down;
            break;

        case Qt::Key_A :
            if(direction != right)
                direction = left;
            break;

        case Qt::Key_Up :
            if(direction != down)
                direction = up;
            break;

        case Qt::Key_Right :
            if(direction != left)
                direction = right;
            break;

        case Qt::Key_Down :
            if(direction != up)
                direction = down;
            break;

        case Qt::Key_Left :
            if(direction != right)
                direction = left;
            break;
    }
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if(isRunning)
    {
        CheckApple();
        CheckCollision();
        Move();
    }

    repaint();
}
