#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class MainWindow : public QWidget {
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
   void paintEvent(QPaintEvent *) override;
   void keyPressEvent(QKeyEvent *) override;
   void timerEvent(QTimerEvent *) override;

private:
   static const int screen_width = 1500;
   static const int screen_height = 900;
   static const int unit_size = 30;
   static const int game_units = (screen_width * screen_height) / unit_size;
   static const int delay = 65;

   bool isRunning;
   int points, score;
   int bodyParts, initialSnakeLength;
   int appleX, appleY;
   int applesEaten;
   int direction;
   int timerId;
   int textWidth;

   QString message;
   QString stringScore, stringApplesEaten;

   enum Direction {
       up = 1, right, down, left
   };

   struct Snake {
       int x, y;
   }snake[game_units];

   void StartGame();
   void SetSnakePos();
   void NewApple();

   void Draw(QPainter *painter);
   void DrawApple(QPainter *painter);
   void DrawSnake(QPainter *painter);
   void DrawWalls(QPainter *painter);
   void DrawScore(QPainter *painter);
   void DrawApplesEaten(QPainter *painter);
   void GameOver(QPainter *painter);

   void CheckCollision();
   void CheckApple();
   void Move();
};

#endif // MAINWINDOW_H
