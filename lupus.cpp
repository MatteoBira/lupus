#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

void gameLoop();
void fillLobby(vector<string> lob);
void roleAssigments(unordered_map<string, Player> players);

class Player {
public:
    string name;
    string role;
    bool alive = true;
    bool protected;
};

vector<string> lobby;
unordered_map<string, Player> Alive;
unordered_map<string, Player> Dead;

class Lupo : public Player {
public:
    Lupo(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
    bool action(Player &obj) {
	if (obj.role == "lupo" || !obj.alive){
		return false;
	}
        if (!obj.protected) {
            obj.alive = false;
            Dead[obj.name] = obj;
	    auto it = Alive.find(obj.name);
	    Alive.erase(it);
	    // votazione dell'altro lupo????
	    return true;
        }
	return true;
    }
};

class Becchino : public Player {
public:
    Becchino(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
    bool action(Player &obj) {
    	if (!obj.alive) {
	    	string role = obj.role;
	    // L'azione deve stampare a video il risultato solo al becchino. (si fa altrove con wsocket)
	    	return true;
	    }  
	    return false;
    }
};

class Veggente : public Player {
public:
    Veggente(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
    bool action(Player &obj) {
	    if (obj.alive) {
	    	string role = obj.role;
	    // L'azione deve stampare a video il risultato solo al veggente. (si fa altrove con wsocket)
	    	return true;
	    }  
	    return false;
    }
};

class Protettore : public Player {
public:
    Protettore(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
    bool action(Player &obj) {
	    if (obj.alive) {
	    	obj.protected = true;
		// dopo come lo rimettiamo false alla fine del turno???
	    // L'azione deve stampare a video il risultato solo al veggente. (si fa altrove con wsocket)
	    	return true;
	    }  
	    return false;
    }
};

class Cacciatore : public Player {
public:
    bool ammo = true;
    Protettore(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
    bool action(Player &obj) {
	    if (!obj.alive) {
		    // scrivere che non e' possibile uccidere un morto
	    	return false;
	    }  
	    if (!obj.protected) {
		obj.alive = false;
	        Dead[obj.name] = obj;
	        auto it = Alive.find(obj.name);
		Alive.erase(it);
	    } 
	    return true;
    }
};

int main() {
    gameLoop();
    return 0;
}

void gameLoop() {


}

void roleAssigments(unordered_map<string, Player> players) {
    srand(static_cast<unsigned int>(std::time(nullptr)));
    int lupi,villager,cacciatore,protettore,veggente,becchino,choice;
    lupi = villager = cacciatore = protettore = veggente = becchino = 0;

    choice = rand()%6+1;
    switch (choice) {
	case 1:
	    if (lupi > 1){
		break;
	    }
	    
	
    	default:
    
    		break;
    }
    
}

// roleAssigment
