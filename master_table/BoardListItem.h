/* GPL  preample. */

#ifndef __scoring_sys_board_list_item_h
#define __scoring_sys_board_list_item_h 1
#include  <QListWidgetItem>
#include  <QObject>

class Board;

class BoardListItem : public QObject, public QListWidgetItem
{
    Q_OBJECT 
    Board *_board;
public :
    BoardListItem(Board*, QListWidget *parent=0);

    Board* getBoard() const;
private slots:
    void updateBoardName();
};

#endif 
