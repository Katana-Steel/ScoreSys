/* GPL  preample. */

#ifndef __scoring_sys_board_list_item_h
#define __scoring_sys_board_list_item_h 1
#include  <QListWidgetItem>
class Board;

class BoardListItem : public QListWidgetItem 
{
    Q_OBJECT 
    Board *_board;
public :
    BoardListItem(Board*, QListWidget *parent=0);

private slots:
    updateBoardName();
};

#endif 