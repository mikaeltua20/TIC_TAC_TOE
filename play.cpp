#include <ncurses.h>

char board[3][3]{};

bool has_won(char player)
{
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }

    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int row = 0;
    int col = 0;
    char player = 'X';
    int moves = 0;
    bool finished = false;

    while (!finished)
    {
        clear();
        mvprintw(0, 3, "Tic-Tac-Toe - Player %c", player);
        mvprintw(1, 3, "Use arrow keys to move, Enter to mark, q to quit");

        for (int r = 0; r < 3; ++r)
        {
            if (r > 0)
                mvprintw(2 + r * 2, 3, "---+---+---");

            for (int c = 0; c < 3; ++c)
            {
                const int y = 3 + r * 2;
                const int x = 4 + c * 4;
                if (c > 0)
                    mvaddch(y, x - 2, '|');

                if (r == row && c == col)
                    attron(A_REVERSE);
                mvaddch(y, x, board[r][c] == '\0' ? ' ' : board[r][c]);
                if (r == row && c == col)
                    attroff(A_REVERSE);
            }
        }
        refresh();

        const int key = getch();
        if (key == 'q' || key == 'Q')
            break;
        if (key == KEY_UP && row > 0)
            --row;
        else if (key == KEY_DOWN && row < 2)
            ++row;
        else if (key == KEY_LEFT && col > 0)
            --col;
        else if (key == KEY_RIGHT && col < 2)
            ++col;
        else if ((key == '\n' || key == KEY_ENTER || key == ' ') && board[row][col] == '\0')
        {
            board[row][col] = player;
            ++moves;
            if (has_won(player))
            {
                clear();
                mvprintw(2, 3, "Player %c wins! Press any key to exit.", player);
                refresh();
                getch();
                finished = true;
            }
            else if (moves == 9)
            {
                clear();
                mvprintw(2, 3, "It's a draw! Press any key to exit.");
                refresh();
                getch();
                finished = true;
            }
            else
                player = player == 'X' ? 'O' : 'X';
        }
    }

    endwin();
    return 0;
}