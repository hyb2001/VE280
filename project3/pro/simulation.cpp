//
// Created by hyb_2001 on 2020/10/21.
//

#include "simulation.h"
#include "fstream"
#include "iostream"
#include "sstream"

using namespace std;

bool fileValidation(string s){
    fstream input;
    input.open(s);
    if (!input){
        input.close();
        return false;
    }else{
        input.close();
        return true;
    }
}

void printGrid(const grid_t &grid){
    for (int i = 0; i < (int)grid.height; ++i) {
        for (int j = 0; j < (int)grid.width; ++j) {
            if (grid.squares[i][j]== nullptr){
                cout<<"____ ";
            }else{
                string s;
                s=grid.squares[i][j]->species->name;
                s=s.substr(0,2);
                s.append("_");
                for (int k = 0; k < 4; ++k) {
                    if (grid.squares[i][j]->direction==direction_t(k)){
                        s.append(directShortName[k]);
                    }
                }
                cout<<s<<" ";
            }
        }
        cout<<endl;
    }
}

bool isEmpty(creature_t &creature, grid_t &grid){
    if (creature.direction==EAST && creature.location.c<(int)grid.width-1){
        //if (grid.squares[creature.location.r][creature.location.c+1]!=nullptr){
            return true;
    }
    if (creature.direction==WEST && creature.location.c>0){
        //if (grid.squares[creature.location.r][creature.location.c-1]!=nullptr){
            return true;
    }
    if (creature.direction==NORTH && creature.location.r>0){
        //if (grid.squares[creature.location.r-1][creature.location.c]!=nullptr){
            return true;
    }
    if (creature.direction==SOUTH && creature.location.r<(int)grid.height-1){
        //if (grid.squares[creature.location.r-1][creature.location.c]!=nullptr){
            return true;
    }
    return false;
}

bool initWorld(world_t &world, const string &speciesFile,
               const string &creaturesFile){
    for (int i = 0; i < (int)MAXHEIGHT; ++i)
        for (int j = 0; j < (int)MAXWIDTH; ++j)
           world.grid.squares[i][j]= nullptr;
    if (!fileValidation(speciesFile)){
        cout<<"Error: Cannot open file "<<speciesFile<<"!"<<endl;
        return false;}
    if (!fileValidation(creaturesFile)){
        cout<<"Error: Cannot open file "<<creaturesFile<<"!"<<endl;
        return false;}
    string directory,creatureming;
    fstream speciesSummary,worldFile;
    speciesSummary.open(speciesFile);
    getline(speciesSummary,directory);
    world.numSpecies=0;
    world.numCreatures=0;
    while ((getline(speciesSummary,creatureming))){
        world.numSpecies++;
        if (world.numSpecies>MAXSPECIES){
            cout<<"Error: Too many species!"<<endl;
            cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
            return false;}
        world.species[world.numSpecies].name=creatureming;
        fstream creature;
        string filedir="";
        filedir.append(directory).append("/").append(creatureming);
        if (!fileValidation(filedir)){
            cout<<"Error: Cannot open file "<<filedir<<"!"<<endl;
            return false;
        }else{
            creature.open(filedir);
            world.species[world.numSpecies].programSize=0;
            int size=-1;
            string option;
            while (getline(creature,option) && option[0]!='\n' && option[0]!='\r' && option[0]!='\0'){
                    size++;
                    if (size>= (int) MAXPROGRAM) {
                        cout << "Error: Too many instructions for species " << creatureming <<"!"<< endl;
                        cout << "Maximal number of instructions is " << MAXPROGRAM <<"."<< endl;
                        return false;}
                    world.species[world.numSpecies].programSize++;
                    string temp;
                    stringstream caozuo(option);
                    caozuo >> temp >> world.species[world.numSpecies].program[size].address;
                    world.species[world.numSpecies].program[size].address--;
                    bool opright = false;
                    if (temp == "hop") {
                        world.species[world.numSpecies].program[size].op = HOP;
                        opright = true;}
                    if (temp == "left") {
                        world.species[world.numSpecies].program[size].op = LEFT;
                        opright = true;}
                    if (temp == "right") {
                        world.species[world.numSpecies].program[size].op = RIGHT;
                        opright = true;}
                    if (temp == "infect") {
                        world.species[world.numSpecies].program[size].op = INFECT;
                        opright = true;}
                    if (temp == "ifempty") {
                        world.species[world.numSpecies].program[size].op = IFEMPTY;
                        opright = true;}
                    if (temp == "ifenemy") {
                        world.species[world.numSpecies].program[size].op = IFENEMY;
                        opright = true;}
                    if (temp == "ifsame") {
                        world.species[world.numSpecies].program[size].op = IFSAME;
                        opright = true;}
                    if (temp == "ifwall") {
                        world.species[world.numSpecies].program[size].op = IFWALL;
                        opright = true;}
                    if (temp == "go") {
                        world.species[world.numSpecies].program[size].op = GO;
                        opright = true;}
                    if (!opright) {
                        cout << "Error: Instruction " << temp << " is not recognized!" << endl;
                        return false;}
                }
            }
        }
    speciesSummary.close();
    worldFile.open(creaturesFile);
    getline(worldFile,creatureming);
    stringstream length(creatureming);
    int len;
    length>>len;
    if (len<=0 || len>(int)MAXHEIGHT){
        cout<<"Error: The grid height is illegal!"<<endl;
        return false;
    }else{world.grid.height=len;}
    getline(worldFile,creatureming);
    stringstream width(creatureming);
    width>>len;
    if (len<=0 || len>(int)MAXWIDTH){
        cout<<"Error: The grid width is illegal!"<<endl;
        return false;
    }else{world.grid.width=len;}
    int size=0;
    while (getline(worldFile,creatureming)){
        size++;
        world.numCreatures++;
        if (size>(int)MAXCREATURES){
            cout<<"Error: Too many creatures!"<<endl;
            cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
            return false;
        }
        stringstream creatu(creatureming);
        string temp,direct;
        int row,colum;
        creatu>>temp>>direct>>row>>colum;
        if (colum<0 || colum>=(int)world.grid.width){
            cout<<"Error: Creature ("<<temp<<" "<<direct<<" "<<row<<" "<<colum<<") is out of bound!"<<endl;
            cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
            return false;}
        if (row<0 || row>=(int)world.grid.height){
            cout<<"Error: Creature ("<<temp<<" "<<direct<<" "<<row<<" "<<colum<<") is out of bound!"<<endl;
            cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
            return false;}
        bool flag=false;
        for (int i = 0; i < 4; ++i) {
            if (direct==directName[i]){
                world.creatures[size].direction=direction_t(i);
                flag=true;}
        }
        if (!flag){
            cout<<"Error: Direction "<<direct<<" is not recognized!"<<endl;
            return false;}
        flag=false;
        for (int i = 1; i <= (int)world.numSpecies; ++i) {
            if (temp==world.species[i].name){flag=true;}}
        if (!flag){
            cout<<"Error: Species "<<temp<<" not found!"<<endl;
            return false;}
        if (world.grid.squares[row][colum]!= nullptr){
            cout<<"Error: Creature ("<<temp<<" "<<direct<<" "<<row<<" "<<colum<<") overlaps with creature ("
                    <<world.grid.squares[row][colum]->species->name<<" "<<directName[world.grid.squares[row][colum]->direction]
                    <<" "<<world.grid.squares[row][colum]->location.r<<" "
                    <<world.grid.squares[row][colum]->location.c<<")!"<<endl;
            return false;}
        world.creatures[size].programID=0;
        world.creatures[size].location.r=row;
        world.creatures[size].location.c=colum;
        for (int i = 1; i <= (int)world.numSpecies; ++i) {
            if (temp==world.species[i].name){
                world.creatures[size].species=&world.species[i];
            }
        }
        world.grid.squares[row][colum]=&world.creatures[size];}
    return true;
}

point_t adjacentPoint(point_t pt, direction_t dir){
    point_t final;
    final=pt;
    if (dir==EAST){
        final.c++;
    }
    if (dir==WEST){
        final.c--;
    }
    if (dir==SOUTH){
        final.r++;
    }
    if (dir==NORTH){
        final.r--;
    }
    return final;
}

direction_t leftFrom(direction_t dir){
    direction_t final;
    for (int i = 0; i < 4; ++i) {
        if (dir==direction_t(i)){
            final=direction_t((i+4-1) % 4);
        }
    }
    return final;
}

direction_t rightFrom(direction_t dir){
    direction_t final;
    for (int i = 0; i < 4; ++i) {
        if (dir==direction_t(i)){
            final=direction_t((i+1) % 4);
        }
    }
    return final;
}

instruction_t getInstruction(const creature_t &creature){
    instruction_t final;
    final=creature.species->program[creature.programID];
    return final;
}

creature_t *getCreature(const grid_t &grid, point_t location){
    creature_t *final;
    final=grid.squares[location.r][location.c];
    return final;
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose){
    instruction_t caozuo;
    cout<<"Creature ("<<creature.species->name<<" ";
    for (int i = 0; i < 4; ++i) {
        if (creature.direction==direction_t(i)){
            cout<<directName[i];
        }
    }
    cout<<" "<<creature.location.r<<" "<<creature.location.c<<") takes action:";
    if (verbose){
        cout<<endl;
    }
    bool Finished=false;
    while (!Finished) {
        caozuo = getInstruction(creature);
        if (verbose){
            cout<<"Instruction "<<(creature.programID+1)<<": ";
            for (int i = 0; i < 9; ++i) {
                if (caozuo.op==opcode_t(i)){
                    cout<<opName[i];
                    if (caozuo.op==LEFT || caozuo.op==RIGHT || caozuo.op==HOP || caozuo.op==INFECT){
                        cout<<endl;
                    }else{
                        cout<<" "<<(caozuo.address+1)<<endl;
                    }
                }
            }
        }
        if (caozuo.op == HOP) {
            if (isEmpty(creature, grid)) {
                point_t next;
                next = adjacentPoint(creature.location, creature.direction);
                if (grid.squares[next.r][next.c] == nullptr) {
                    Finished=true;
                    grid.squares[creature.location.r][creature.location.c] = nullptr;
                    creature.location = next;
                    grid.squares[next.r][next.c] = &creature;
                }
            }
            creature.programID = (creature.programID+1) % creature.species->programSize;
        }
        if (caozuo.op == LEFT) {
            Finished= true;
            creature.direction = leftFrom(creature.direction);
            creature.programID = (creature.programID+1) % creature.species->programSize;
        }
        if (caozuo.op == RIGHT) {
            Finished=true;
            creature.direction = rightFrom(creature.direction);
            creature.programID = (creature.programID+1) % creature.species->programSize;
        }
        if (caozuo.op == INFECT) {
            if (isEmpty(creature, grid)) {
                point_t next;
                next = adjacentPoint(creature.location, creature.direction);
                if (grid.squares[next.r][next.c] != nullptr) {
                    Finished=true;
                    if (grid.squares[next.r][next.c]->species!=creature.species) {
                        grid.squares[next.r][next.c]->species = creature.species;
                        grid.squares[next.r][next.c]->programID = 0;
                        creature.programID = (creature.programID+1) % creature.species->programSize;
                    }else{creature.programID = (creature.programID+1) % creature.species->programSize;}
                } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
            } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
        }
        if (caozuo.op == IFEMPTY) {
            if (isEmpty(creature, grid)) {
                point_t next;
                next = adjacentPoint(creature.location, creature.direction);
                if (grid.squares[next.r][next.c] == nullptr) {
                    creature.programID = caozuo.address;
                } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
            } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
        }
        if (caozuo.op == IFENEMY) {
            if (isEmpty(creature, grid)) {
                point_t next;
                next = adjacentPoint(creature.location, creature.direction);
                if (grid.squares[next.r][next.c] != nullptr) {
                    if (grid.squares[next.r][next.c]->species!=creature.species) {
                        creature.programID = caozuo.address;
                    }else{creature.programID = (creature.programID+1) % creature.species->programSize;}
                } else {creature.programID =(creature.programID+1) % creature.species->programSize;}
            } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
        }
        if (caozuo.op == IFSAME) {
            if (isEmpty(creature, grid)) {
                point_t next;
                next = adjacentPoint(creature.location, creature.direction);
                if (grid.squares[next.r][next.c]!= nullptr) {
                    if (grid.squares[next.r][next.c]->species==creature.species) {
                        creature.programID = caozuo.address;
                    }else{creature.programID = (creature.programID+1) % creature.species->programSize;}
                } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
            } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
        }
        if (caozuo.op == IFWALL) {
            if (creature.direction == EAST && creature.location.c == (int)grid.width-1) {
                creature.programID = caozuo.address;
            } else if (creature.direction == WEST && creature.location.c == 0) {
                creature.programID = caozuo.address;
            } else if (creature.direction == NORTH && creature.location.r == 0) {
                creature.programID = caozuo.address;
            } else if (creature.direction == SOUTH && creature.location.r == (int)grid.height-1) {
                creature.programID = caozuo.address;
            } else {creature.programID = (creature.programID+1) % creature.species->programSize;}
        }
        if (caozuo.op == GO) {
            creature.programID = caozuo.address;}
        if (caozuo.op==HOP || caozuo.op==INFECT){
            Finished=true;}
        if (!verbose && Finished){
            if (caozuo.op==HOP){
                cout<<" hop"<<endl;}
            if (caozuo.op==LEFT){
                cout<<" left"<<endl;}
            if (caozuo.op==RIGHT){
                cout<<" right"<<endl;}
            if (caozuo.op==INFECT){
                cout<<" infect"<<endl;}
        }
    }
    if (verbose) {
        printGrid(grid);}
}