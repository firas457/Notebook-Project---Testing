#include <iostream>
#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>
#include <unordered_map>
#include <limits.h>

using namespace ariel;
using namespace std;
using ariel::Direction;

  const int ascii_start = 32;
  const int ascii_end = 126;
  const int nine = 9;
  const int ten = 10;
  const int five = 5;
  const int width = 100;
    


namespace ariel{

   


    void Notebook::write(int page, int row, int col, Direction dir, string word) {
        
        if(page < 0 || col < 0 || row < 0) {
            throw std::invalid_argument("unvalid input");
        }

        if( col >= width || (dir == Direction::Horizontal && col + (int)word.length() > width)) {
            throw std::invalid_argument("unvalid input");
        }



        for(size_t i = 0; i < word.length(); i++) {
            if(((int)word.at(i) > ascii_end||(int)word.at(i) < ascii_start || word.at(i) == '~')) {
                throw std::invalid_argument("unvalid word");
            }
        }
        

        string bar;
        for(int i = 0; i < word.length(); i++) {
            bar += "_";
        }
        


        string st;
        st = this->read(page, row, col, dir, (int)word.length());


        if(st != bar) {
            throw std::invalid_argument("you can't write here");
        }
        
     

        for(size_t i = 0; i < word.length(); i++) {
            if(dir == Direction::Vertical) {

                this->nootebook[page][row + (int)i][col] = word.at(i);
            }

            else {

                this->nootebook[page][row][col + (int)i] = word.at(i);
            }
        }

    }

   
    string Notebook::read(int page, int row, int col, Direction dir, int len) {
        
        if(page < 0 || col < 0 || row < 0 || len < 0 ) {
            throw std::invalid_argument("unvalid input");
        }

         if( col >= width || (dir == Direction::Horizontal && col + len > width)) {
            throw std::invalid_argument("unvalid input");
        }


        string bar; 

        for(int i = 0; i < len; i++) {
            

            if(dir == Direction::Vertical) {
               
             if(this->nootebook[page][row + i][col] == '\0') {
                    bar += "_";
                }

             if(this->nootebook[page][row + i][col] != '\0'){
                    bar += this->nootebook[page][row + i][col];
                }

            
            }

            if(dir == Direction::Horizontal) {
               
              if(this->nootebook[page][row][col + i] == '\0') {
                    bar += "_";
                }

              if(this->nootebook[page][row][col + i] != '\0'){
                    bar += this->nootebook[page][row][col + i];
                }


            }

        }
        return bar;
    }

 

    void Notebook::erase(int page, int row, int col, Direction dir, int len) {
        
        if(page < 0 || col < 0 || row < 0 || len < 0 ) {
            throw std::invalid_argument("unvalid input");
        }

          if( col >= width || (dir == Direction::Horizontal && col + len > width)) {
            throw std::invalid_argument("unvalid input");
        }
        

        for(int i = 0; i < len; i++) {

            if(dir == Direction::Vertical) {  
                this->nootebook[page][row + i][col] = '~';
            }

            else {
                this->nootebook[page][row][col + i] = '~';
            }

        }
    }

    
    void Notebook::show(int page) {
     
        if(page < 0) {
            throw std::invalid_argument("negitive page number");
        }

        int _max = 0;
        int _min= INT_MAX;


       
        for(auto const &row: this->nootebook[page]) {

              if(row.first < _min) {
                _min = row.first;
            }

              if(row.first > _max) {
                _max = row.first;
            }
          
        }


        int temp=max(_min - 2, 0);
        int n=0;
        int dig_sum=1;

        for(int i = temp; i < _max + 3; i++) {

            n = i;
            
            
            while(n > nine) {
               dig_sum++;
                n /= ten;
            }

            cout << i << ":";

            for(int j = dig_sum; j < five; j++) {
                cout << " ";
            }
            
            for(int d = 0; d < width; d++) {


                if(this->nootebook[page][i][d] != '\0') {
                     cout << this->nootebook[page][i][d];
                }

                else {
                   cout << "_";
                }

            }
            cout << endl;
        }
      
    }
}