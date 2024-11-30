#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
class ScoreWidget: public QHBoxLayout
{
    Q_OBJECT

public:
    ScoreWidget(); //constructor

    void updateScore(); //function to update the text widget
    void zeroScore(); //function to zero the score

public slots:
    void retryButton_clicked(); //slot to enable when retryButton clicked
    void hintButton_clicked(); //slot to enable when hintButton clicked
//signals
signals:
    void retry_clicked(); //signal function when retry button has pressed
    void hint_clicked(); //signal function for the hint button
    void game_won(); // slot when the score becomes the highest possible


private:
    void createUnits(); //function to create members of the layout
    //variables
    QLabel *score;
    QPushButton *retryButton;
    QPushButton *hintButton;
    QSpacerItem *spacer;
    int score_point=0;


};

#endif // SCOREWIDGET_H
