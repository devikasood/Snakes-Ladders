#include<iostream>
using namespace std;

class Props { 

public:

    int start;
    int end;

    Props(int start, int end) {

        if( !validate(start, end) ) {
            this->start = end;
            this->end = start;
        }
        else{
            this->start = start;
            this->end = end;
        }
    }

    bool validate( int start, int end ) {
        return true;
    }

    int getStart() {
        return start;
    }

    int getEnd() {
        return end;
    }

};


class Snake : public Props {

public:

    // props constructor
    Snake(int start, int end) : Props(start, end){}
    // function override  
    bool validate(int start, int end) {

        if (end < start) { 
            return true;
        }   
        return false;
    }
    
};

class Ladder : public Props {

public:

    Ladder(int start, int end) : Props(start, end){}
    bool validate(int start, int end) {

        if(start < end) {
            return true;
        }
        return false;
    }

};

class Player {

public:

    string name;
    int currpos;

    Player(string name) {
        this->name = name;
        currpos = 0;
    }

    int getPos() {
        return currpos;
    }

    void setPos(int newpos) {
        currpos += newpos;
    }

    string getName() {
        return name;
    }

};

class Board {

public:

    int size; 
    vector<Snake> snakes;
    vector<Ladder> ladders;
    
    Board(){} // default board constructor 
    Board(int size, vector<Snake> snakes, vector<Ladder> ladders) {

        this->size = size;
        this->snakes = snakes;
        this->ladders = ladders;
    }

    int getSize(){
        return size;
    }
};

class Game {

public:
    Board gameboard;
    vector<Player> players;
    int die;

    Game(){} // default game constructor 
    Game(Board gameboard,  vector<Player> players, int die) { 

        this->gameboard = gameboard;
        this->players = players;
        this->die = die;
    }

    //function to actually play the game
    void start() {

        cout<<"WELCOME TO SNAKES AND LADDERS!!"<<endl;
        cout<<" "<<endl;

        int n = players.size();
        int winning = 0;
        int boardsize = gameboard.getSize();
        Player winner("");

        while( winning<=boardsize ) {

            for(int i = 0; i < n; i = (i+1) % n) {
                
                Player current = players[i];
                cout << "It is your turn to play " << current.getName() << endl;
                int pos_before = current.getPos();
                cout << "You are currently standing at " << pos_before << endl;
    
                //ROLL DICE
                //GET OUTPUT FROM DICE LETS SAY DICE
                int dice_val = 1;

                current.setPos(dice_val + pos_before);
                int pos_after = current.getPos();
                int temp = pos_after;

                // check if there are any snakes or ladders present here
                for(int j = 0; j < gameboard.snakes.size(); j++) {
                    int startofsnake = gameboard.snakes[j].getStart();
                    if(startofsnake == temp){
                        int endofsnake = gameboard.snakes[j].getEnd();
                        temp = endofsnake;
                    }
                }
                for(int j = 0; j < gameboard.ladders.size(); j++) {
                    int startofladder = gameboard.ladders[j].getStart();
                    if(startofladder == temp){
                        int endofladder = gameboard.ladders[j].getEnd();
                        temp = endofladder;
                    }
                }

                pos_after = temp;
                cout << "You are now at " << pos_after << endl;
                winning = max(winning, pos_after);
                if( winning >= boardsize ) {
                    winner = current;
                }
            }
        }
        cout << "Congratulations! " << winner.getName() << " has won the game" << endl;
    }
};


int main() {

    vector<Snake> snakes = { Snake(20, 2), Snake(38, 13), Snake(44, 28) };
    vector<Ladder> ladders = { Ladder(3,16), Ladder(22,33), Ladder(42, 49) };
    Board b1(3, snakes, ladders);
    vector<Player> players = { Player("Devika"), Player("Astitva"), Player("Richa"), Player("Pankaj") };
    int dice = 1;
    Game game1(b1, players, 1);
    game1.start();



}
