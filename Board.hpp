#include<stdexcept>
#include "Direction.hpp"

namespace ariel{
    class Board{
        public:
        void post(unsigned int row, unsigned int column,ariel::Direction n, string s);
        string read(unsigned int row, unsigned int column, ariel::Direction n, int len);
        void show();
    };
}