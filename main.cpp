#include <bits/stdc++.h>
using namespace std;

long long counter = 0;
int column_last = -1;
long long start = clock();

bool for_first_win = true;
bool for_second_win = true;

int first_player = 1;
int second_player = 2;

struct Connect_Four
{
  int h, w;
  int turn;
  // 1 : first, 2 : second
  vector<vector<int>> board;
  map<vector<vector<int>>, int> board_map;
  map<vector<vector<int>>, pair<int, int>> board_win_first;
  map<vector<vector<int>>, pair<int, int>> board_win_draw;
  map<vector<vector<int>>, pair<int, int>> board_win_second;
  vector<int> count;
  vector<pair<int, int>> log;
  Connect_Four() : h(6), w(7)
  {
    initialize_board();
  }

  Connect_Four(int h_, int w_) : h(h_), w(w_)
  {
    initialize_board();
  }

  void initialize_board()
  {
    board.resize(h, vector<int>(w, 0));
    count.resize(w, 0);
    log.resize(h * w, make_pair(-1, -1));
    turn = 0;
  }

  void print_board()
  {
    for (int i = h - 1; i >= 0; i--)
      for (int j = 0; j < w; j++)
        cout << (board.at(i).at(j) == 0 ? '-' : (board.at(i).at(j) == 1 ? 'F' : 'S')) << (j == w - 1 ? "\n" : "");
  }

  void print_log()
  {
    for (int i = 0; i < h * w; i++)
    {
      if (log.at(i).first == -1)
        break;
      else
        // cout << log.at(i).first << ':' << log.at(i).second << ',';
        cout << log.at(i).second << ',';
    }
    cout << endl;
  }

  int play(int column)
  {
    if (!(0 <= column && column < w) || count.at(column) == h)
      return 1;
    else
    {
      // cerr << "success" << endl;
      board.at(count.at(column)).at(column) = turn % 2 + 1;
      log.at(turn++) = make_pair(count.at(column)++, column);
      return 0;
    }
  }

  bool check_ij(int h_, int w_)
  {
    return 0 <= h_ && h_ < h && 0 <= w_ && w_ < w;
  }

  int conncet(int h0, int w0, int h1, int w1)
  {
    return check_ij(h0, w0) && check_ij(h1, w1) && board.at(h0).at(w0) != 0 && board.at(h0).at(w0) == board.at(h1).at(w1);
  }

  // 0 : not finish, 1 : fast win, 2 : second win
  int verify_win()
  {
    if (turn == 0)
      return 0;
    int base_h, base_w;
    tie(base_h, base_w) = log.at(turn - 1);
    // cout << "base : " << base_h << ", " << base_w << endl;
    int connect = 1;
    for (int i = -3; i < 3; i++)
    {
      if (check_ij(base_h + i, base_w + 0) && check_ij(base_h + (i + 1), base_w + (0 + 0)))
      {
        if (conncet(base_h + i, base_w + 0, base_h + (i + 1), base_w + (0 + 0)) && ++connect == 4)
          return next_player();
      }
      else
        connect = 1;
      // cout << "connect : " << connect << " (" << base_h + i << ", " << base_w + 0 << "), " << check_ij(base_h + i, base_w + 0) << ", " << check_ij(base_h + (i + 1), base_w + (0 + 0)) << endl;
    }
    for (int i = -3; i < 3; i++)
    {
      if (check_ij(base_h + i, base_w + i) && check_ij(base_h + (i + 1), base_w + (i + 1)))
      {
        if (conncet(base_h + i, base_w + i, base_h + (i + 1), base_w + (i + 1)) && ++connect == 4)
          return next_player();
      }
      else
        connect = 1;
      // cout << "connect : " << connect << " (" << base_h + i << ", " << base_w + i << "), " << check_ij(base_h + i, base_w + i) << ", " << check_ij(base_h + (i + 1), base_w + (i + 1)) << endl;
    }
    for (int i = -3; i < 3; i++)
    {
      if (check_ij(base_h + i, base_w - i) && check_ij(base_h + (i + 1), base_w - (i + 1)))
      {

        if (conncet(base_h + i, base_w - i, base_h + (i + 1), base_w - (i + 1)) && ++connect == 4)
          return next_player();
      }
      else
        connect = 1;
      // cout << "connect : " << connect << " (" << base_h + i << ", " << base_w - i << "), " << check_ij(base_h + i, base_w - i) << ", " << check_ij(base_h + (i + 1), base_w - (i + 1)) << endl;
    }
    for (int i = -3; i < 3; i++)
    {
      if (check_ij(base_h + 0, base_w + i) && check_ij(base_h + (0 + 0), base_w + (i + 1)))
      {

        if (conncet(base_h + 0, base_w + i, base_h + (0 + 0), base_w + (i + 1)) && ++connect == 4)
          return next_player();
      }
      else
        connect = 1;
      // cout << "connect : " << connect << " (" << base_h + 0 << ", " << base_w + i << "), " << check_ij(base_h + 0, base_w + i) << ", " << check_ij(base_h + (0 + 0), base_w + (i + 1)) << endl;
    }

    return 0;
  }

  int solve()
  {
    if (board_map.count(board) == false)
    {
      int check = verify_win();
      if (check != 0 || turn == h * w)
      {
        board_map[board] = check;
        // for debug
        {
          counter++;
          if (log.at(5).first != column_last)
          {
            cout << counter << ", " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
            column_last = log.at(5).first;
            print_log();
          }
        }
      }
      else
      {
        pair<int, int> first_win = make_pair(-1, -1),
                       second_win = make_pair(-1, -1),
                       win_draw = make_pair(-1, -1);
        for (int i = 0; i < w; i++)
        {
          if (play(i) == 0)
          {
            int memo = solve();
            if (memo == 0)
            {
              // board_win_draw[board] = log.at(turn - 1);
              win_draw = log.at(turn - 1);
            }
            else if (memo == 1)
            {
              // board_win_first[board] = log.at(turn - 1);
              first_win = log.at(turn - 1);
            }
            else if (memo == 2)
            {
              // board_win_second[board] = log.at(turn - 1);
              second_win = log.at(turn - 1);
            }
            rollback();
          }
        }
        // last is first
        if (now_player() == first_player)
          board_map[board] = first_win.first == -1 ? (win_draw.first == -1 ? 2 : 0) : 1;
        else
          board_map[board] = second_win.first == -1 ? (win_draw.first == -1 ? 1 : 0) : 2;

        board_win_draw[board] = win_draw;
        board_win_first[board] = first_win;
        board_win_second[board] = second_win;
      }
    }
    return board_map.at(board);
  }

  string player(int id)
  {
    return id == 0 ? "draw" : (id == 1 ? "F" : "S");
  }

  int now_player()
  {
    return (turn + 0) % 2 + 1;
  }

  int next_player()
  {
    return (turn + 1) % 2 + 1;
  }

  void rollback()
  {
    if (turn == h * w || log.at(turn).first == -1)
    {
      turn--;
      int h_, w_;
      tie(h_, w_) = log.at(turn);
      count.at(w_)--;
      board.at(h_).at(w_) = 0;
      log.at(turn) = make_pair(-1, -1);
    }
  }
  void print_win_log()
  {
    if (board_win_draw.count(board) == false)
    {
      cerr << "game is end" << endl;
      return;
    }
    print_board();
    cout << "input winner, best result is winner is " << player(board_map.at(board)) << ", next player is " << player(turn % 2 + 1) << endl;
    cout << "print win draw : " << board_win_draw.at(board).second << endl;
    cout << "print win first : " << board_win_first.at(board).second << endl;
    cout << "print win second : " << board_win_second.at(board).second << endl;
    int i;
    cin >> i;
    if (i == 0)
    {
      if (play(board_win_draw.at(board).second) == 0)
      {
        print_win_log();
        cout << "winner : " << verify_win() << endl;
      }
      else
      {
        cout << "can't win;" << endl;
      }
    }
    else if (i == 1)
    {
      if (play(board_win_first.at(board).second) == 0)
      {
        print_win_log();
        cout << "winner : " << verify_win() << endl;
      }
      else
      {
        cout << "can't win" << endl;
      }
    }
    else if (i == 2)
    {
      if (play(board_win_second.at(board).second) == 0)
      {
        print_win_log();
        cout << "winner : " << verify_win() << endl;
      }
      else
      {
        cout << "can't win" << endl;
      }
    }
  }
};

int main()
{
  Connect_Four cf(4, 4);
  // cf.play(0);
  // cf.play(1);
  // cf.play(0);
  // cf.play(1);
  // cf.play(2);
  cf.solve();
  cout << "winner : " << cf.board_map.at(cf.board) << endl;
  cout << "counter : " << counter << endl;
  // while (true)
  // {
  //   cf.print_board();
  //   int i;
  //   cin >> i;
  //   cf.play(i);
  //   cout << "judge : " << cf.verify_win() << endl;
  // }
  while (true)
  {
    cf.print_win_log();
    while (cf.turn > 0)
    {
      cf.rollback();
    }
  }
}