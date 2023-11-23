#include <bits/stdc++.h>
using namespace std;

long long counter = 0;

struct Connect_Four
{
  int h, w;
  int turn;
  // 1 : first, 2 : second
  vector<vector<int>> board;
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
    for (size_t i = 0; i < h * w; i++)
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
    if (count.at(column) == h)
      return 1;
    else
    {
      // cerr << "success" << endl;
      board.at(count.at(column)).at(column) = turn % 2 + 1;
      log.at(turn++) = make_pair(count.at(column)++, column);
      return 0;
    }
  }

  void solve()
  {
    if (turn == h * w)
    {
      counter++;
      if (counter % 100000 == 0)
        cout << counter << endl;
      // print_board();
      // print_log();
      // cout << "/* code */" << endl;
    }
    else
    {
      for (size_t i = 0; i < w; i++)
      {
        if (play(i) == 0)
        {
          solve();
          rollback();
        }
      }
    }
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
};

int main()
{
  Connect_Four cf(4, 5);
  cf.solve();
  cout << "counter : " << counter << endl;
}