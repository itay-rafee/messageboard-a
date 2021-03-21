#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <cmath>
#include "Board.hpp"
using namespace std;

#include "Direction.hpp"

using ariel::Direction;

const unsigned int imax = numeric_limits<unsigned int>::max();

namespace ariel {
    class Board {
    private:
        map<unsigned int, map<unsigned int, char>> board;
        map<unsigned int, map<unsigned int, char>>::iterator it1;
        map<unsigned int, char>::iterator it2;
        unsigned int max_row = 0, max_col = 0;
        unsigned int min_row = imax, min_col = imax;
        const int zero = 0, one = 1, two = 2, ten = 10;

        void set_min_max(unsigned int row, unsigned int col, Direction n, int len_s) {
            //set minimum
            if (row < min_row) {
                min_row = row;
            }
            if (col < min_col) {
                min_col = col;
            }


            //set maximum
            if (n == Direction::Vertical) {
                if (row + len_s > max_row) {
                    max_row = row + len_s;
                }
                if (col > max_col) {
                    max_col = col;
                }
            }
            if (n == Direction::Horizontal) {
                if (col + len_s > max_col) {
                    max_col = col + len_s;
                }
                if (row > max_row) {
                    max_row = row;
                }
            }
        }

        void set_s_h(unsigned int row, unsigned int col, string s, int len_s) {
            for (size_t i = 0; i < len_s; i++) {
                board[row][col] = s.at(i);
                col++;
            }
        }

        void set_s_v(unsigned int row, unsigned int col, string s, int len_s) {
            for (size_t i = 0; i < len_s; i++) {
                board[row][col] = s.at(i);
                row++;
            }
        }

        void set_s(unsigned int row, unsigned int col, Direction n, string &s, int len_s) {
            if (n == Direction::Horizontal)
                set_s_h(row, col, s, len_s);
            else
                set_s_v(row, col, s, len_s);
        }

        bool contain(unsigned int row, unsigned int col) {
            bool ans = false;
            it1 = board.find(row);
            if (it1 != board.end()) {
                it2 = board[row].find(col);
                if (it2 != board[row].end()) {
                    ans = true;
                }
            }
            return ans;
        }

        string read_h(unsigned int row, unsigned int col, int len) {
            string ans;
            for (size_t i = 0; i < len; i++) {
                if (contain(row, col)) {
                    ans += board[row][col];
                } else {
                    ans += "_";
                }
                col++;
            }
            return ans;
        }

        string read_v(unsigned int row, unsigned int col, int len) {
            string ans;
            for (size_t i = 0; i < len; i++) {
                if (contain(row, col)) {
                    ans += board[row][col];
                } else {
                    ans += "_";
                }
                row++;
            }
            return ans;
        }

        int set_space(int a) const {
            int i = 1;
            while (a/pow(ten, i) >= one){
                i++;
            }
            return i;
        }

    public:
        void post(unsigned int row, unsigned int col, Direction n, string s) {
            int len_s = s.size();
            set_min_max(row, col, n, len_s);
            set_s(row, col, n, s, len_s);
        }

        string read(unsigned int row, unsigned int col, Direction n, int len) {
            string ans;
            if (n == Direction::Horizontal) {
                ans = read_h(row, col, len);
            } else {
                ans = read_v(row, col, len);
            }

            return ans;
        }



        void show() {
            if (board.empty()) {
                cout << "1: _________\n2: _________\n3: _________\n4: _________\n5: _________" << endl;
                return;
            }
            int min_r = min(min_row, min_row - one);
            int min_c = min(min_col, min_col - two);
            int max_r = max(max_row, max_row + two);
            int max_c = max(max_col, max_col + two);
            string ans;
            for (int i = min_r; i < max_r; ++i) {
                int space = set_space(i);
                ans += to_string(i) + ":";
                for (int j = space; j < 5; ++j) {
                    ans += " ";
                }
                for (int j = min_c; j < max_c; ++j) {
                    if (contain(i, j)) {
                        ans += board[i][j];
                    } else {
                        ans += "_";
                    }
                }
                cout << ans << endl;
                ans = "";
            }
        }
    };
}