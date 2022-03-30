#include <iostream>
#include <unordered_map>
#include <iterator>
#include "Direction.hpp"
using namespace std;
using ariel::Direction;


namespace ariel {

    class Notebook {

        private:

        unordered_map<int, unordered_map<int, unordered_map<int, char>>> nootebook;
        

        public:

            void write(int page, int row, int col, Direction dir, string word);
            string read(int page, int row, int col, Direction dir, int len);
            void erase(int page, int row, int col, Direction dir, int len);
            void show(int page);
    };
}