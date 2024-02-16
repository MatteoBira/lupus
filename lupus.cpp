#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

void gameLoop();
void fillLobby(vector<string> lob);
void roleAssigments(unordered_map<string, Player> players);
bool isGameCont(unordered_map<string, Player> alive, int *winner);

class Player {
public:
    string name;
    string role;
    bool alive = true;
    bool protected;
    Player(string nameV, string roleV, bool aliveV, bool protectedV) {
	name = nameV; role = roleV; alive = aliveV; protected = protectedV;
	}
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

void gameLoop(){
   string choice;
   fillLobby(lobby);
   cout << "Do you want to start a new game? ";
   cin >> choice;
    if(choice == "yes" || choice == "yeah"){
	roleAssigment(Alive);
	while(isGameCont(Alive,&winner){
	    // notte e poi giorno
	}

	if(winner==0){
	    printf("I lupi hanno vinto! \n");
	}else{
	    printf("I buoni hanno vinto! \n");
	}
    }
}

void roleAssigments(unordered_map<string, Player> players) {
    srand(static_cast<unsigned int>(std::time(nullptr)));
    int lupi,villager,cacciatore,protettore,veggente,becchino,choice,index;
    lupi = index = villager = cacciatore = protettore = veggente = becchino = 0;

    do {
	choice = rand()%6+1;
	switch (choice) {
	    case 1:
		if (lupi > 2){
		    break;
		}else{
		    lupi++;
		    Alive[lobby[index]] = Lupo(lobby[index],"lupo",true,false);
		    index++;
		    break;
		}
		
	    case 2:
		if (villager > 4){
		    break;
		}else{
		    villager++;
		    Alive[lobby[index]] = Player(lobby[index],"Villager",true,false);
		    index++;
		    break;
		}
	    case 3:
		if (cacciatore > 1){
		    break;
		}else{
		    cacciatore++;
		    Alive[lobby[index]] = Cacciatore(lobby[index],"Cacciatore",true,false);
		    index++;	    }
		    break;
	    case 4:
		if (veggente > 1){
		    break;
		}else{
		    veggente++;
		    Alive[lobby[index]] = Veggente(lobby[index],"Veggente",true,false);
		    index++;
		    break;
		}
	    case 5:
		if (protettore > 1){
		    break;
		}else{
		    protettore++;
		    Alive[lobby[index]] = Protettore(lobby[index],"Protettore",true,false);
		    index++;
		    break;
		}
	    case 6:
		if (becchino > 1){
		    break;
		}else{
		    becchino++;
		    Alive[lobby[index]] = Becchino(lobby[index],"Becchino",true,false);
		    index++;
		    break;
		}
	    
	    default:
		    break;
	}
    }while(index<10);
    
}

void fillLobby(vector<string> lob){
    string name;
    for(int i=0;i<10;i++){
	if(i==0){
	    cout << "what is your name? ";
	    cin >> name;
	}else{
	    name = "bot" + to_string(i);
	}

	lobby.push_back(name);
    }

}

bool isGameCont(unordered_map<string, Player> alive, int *winner)
{
    int lupi=0,buoni=0;
    for(int i=0;i<10;i++){
	if(alive[i].role == "lupo"){
	    lupi++;
	}
	else{
	    buoni++;
	}
    }
    if(lupi==0){
	*winner = 1;
	return false;
    }else if(buoni <= 1){
	*winner = 0;
	return false;
    }else{
	return true;
    }
}
