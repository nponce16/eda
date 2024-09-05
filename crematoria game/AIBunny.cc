#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Bunny


struct PLAYER_NAME : public Player {

    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
    return new PLAYER_NAME;
    }


    typedef vector<int> VI;

    bool validMove(const Pos p) {
        if (pos_ok(p)) {
            Cell currentCell = cell(p);
            return currentCell.type != Rock;
        }
        return false;
    }

    //aleja la unidad de un hellhound
    Dir runFrom_enemy(Pos &myPos, int &id_enemy) {
        Pos enemyPos = unit(id_enemy).pos;
        int dx = enemyPos.j - myPos.j;
        int dy = enemyPos.i - myPos.i;

        if (dx == 0 and dy > 0) {
            if (validMove(myPos+Top)) return Top;
            else if (validMove(myPos+TL)) return TL;
            else if (validMove(myPos+RT)) return RT;
            else if (validMove(myPos+Right)) return Right;
            else if (validMove(myPos+Left)) return Left;
        }
        if (dx == 0 and dy < 0) {
            if (validMove(myPos+Bottom)) return Bottom;
            else if (validMove(myPos+LB)) return LB;
            else if (validMove(myPos+BR)) return BR;
            else if (validMove(myPos+Right)) return Right;
            else if (validMove(myPos+Left)) return Left;
        }
        if (dx > 0 and dy >= 0) {
            if (validMove(myPos+TL))return TL;
            else if (validMove(myPos+Top)) return Top;
            else if (validMove(myPos+Left)) return Left;
            else if (validMove(myPos+TL)) return TL;
        }
        if (dx < 0 and dy >= 0) {
            if (validMove(myPos+RT)) return RT;
            else if (validMove(myPos+Top)) return Top;
            else if (validMove(myPos+Right)) return Right;
            else if (validMove(myPos+RT)) return RT;
        }
        if (dx > 0 and dy < 0) {
            if (validMove(myPos+LB)) return LB;
            else if (validMove(myPos+Bottom)) return Bottom;
            else if (validMove(myPos+Left)) return Left;
            else if (validMove(myPos+RT)) return RT;
        }
        if (dx < 0 and dy < 0) {
            if (validMove(myPos+BR)) return BR;
            else if (validMove(myPos+Bottom)) return Bottom;
            else if (validMove(myPos+Right)) return Right;
            else if (validMove(myPos+LB)) return LB;
        }
        Dir getDir = Dir(random(0,7));
        while (not validMove(myPos + getDir)) getDir = Dir(random(0,7));
        return getDir;
    }

    //mira si hay hellhounds alrededor, retorna el id si encuentra uno o -1 si no hay.
    int safe_CavePerimeter(Pos &currentPos) {

        //Inside: run from hellhounds
        VI hellhoundsId = hellhounds();
        int size = hellhoundsId.size();
        
        for (int i = 0; i < size; ++i) {
            int id_hellhound = hellhoundsId[i];
            Pos hellhoundsPos = unit(id_hellhound).pos;

            int dx = abs(hellhoundsPos.j - currentPos.j);
            int dy = abs(hellhoundsPos.i - currentPos.i);

            //HELLHOUND_ESCAPE_DISTANCE = 4
            if (dy <= 4 and dx <= 4) return id_hellhound;
            if (dy <= 80 and dy >= 77) return id_hellhound;
        }
        //safe
        return -1;
    }

    //mira si es seguro subir al exterior
    bool safe_Perimeter(Pos &currentPos) {
        //Outside: run from sun
        if (currentPos.k == 1) {
            int SUN_ESCAPE_DISTANCE = 16;
            Pos sunPos = currentPos;
            if (sunPos.j - SUN_ESCAPE_DISTANCE >= 0) sunPos.j -= SUN_ESCAPE_DISTANCE;
            else sunPos.j += SUN_ESCAPE_DISTANCE;
            if (pos_ok(sunPos) and not daylight(sunPos)) return true;
        }
        return false;
    }

    //Busca la gema mas cercana y mueve la unidad hacia ella
    Dir move_to_nearestGem(Pos &myPos) {
        queue< pair<Pos, queue<Dir> > > q;      // cola con < ultima posicion, cola de posiciones recorridas hasta ultima posicion > 
		vector<vector<int>> visited(40,vector<int>(80, 0));
		queue<Dir> q_path;
    
		q.push({myPos, q_path});
		visited[myPos.i][myPos.j] = 1;

		while(not q.empty()) {
		    Pos currentPos = q.front().first;
		    q_path = q.front().second;
		    q.pop();

		    //si encontramos una gema
            if (pos_ok(currentPos)) {
                Cell currentCell = cell(currentPos);
                if(currentCell.gem) return q_path.front();
            }

		    //si no la encontramos, recorremos los vecinos
		    for (int d = 0; d < 8; ++d) {
                Pos nextPos = currentPos + Dir(d);
                Dir nextMov = Dir(d);

                if (validMove(nextPos) and not visited[nextPos.i][nextPos.j]) {
                    queue<Dir> q_newPath = q_path;
                    visited[nextPos.i][nextPos.j] = 1;
                    
                    q_newPath.push(nextMov);
                    q.push({nextPos,q_newPath});
                }
		    }
		}
		//si no encuentra una gema: caso improbable, sería un error
		return None;
    }

    //Busca el elevador mas cercano y mueve la unidad hacia el
    Dir move_to_nearestElevator(Pos &myPos) {
        queue< pair<Pos, queue<Dir> > > q;      // cola con < ultima posicion, cola de posiciones recorridas hasta ultima posicion > 
		vector<vector<int>> visited(40,vector<int>(80, 0));
		queue<Dir> q_path;
    
		q.push({myPos, q_path});
		visited[myPos.i][myPos.j] = 1;

		while(not q.empty()) {
		    Pos currentPos = q.front().first;
		    q_path = q.front().second;
		    q.pop();

		    //si encontramos el elevador
		    Cell currentCell = cell(currentPos);
		    if(currentCell.type == Elevator and currentPos.k == 0) {
                Pos outsidePos = currentPos;
                outsidePos.k = 1;
                if (not daylight(outsidePos)) {
                    if (safe_Perimeter(outsidePos)) return q_path.front();
                }
            }
            else if(currentCell.type == Elevator and currentPos.k == 1) return q_path.front();

		    //si no lo encontramos, recorremos los vecinos
		    for (int d = 0; d < 8; ++d) {
                Pos nextPos = currentPos + Dir(d);
                Dir nextMov = Dir(d);

                if(validMove(nextPos) and not visited[nextPos.i][nextPos.j]){

                    queue<Dir> q_newPath = q_path;
                    visited[nextPos.i][nextPos.j] = 1;
                    
                    q_newPath.push(nextMov);
                    q.push({nextPos,q_newPath});
                }
		    }
		}
		return None;
    }

    //Busca el enemigo mas cercano y envia al furyan hacia el
    Dir move_to_nearestEnemy(Pos &myFuryan_pos, int &health){
		queue< pair<Pos, queue<Dir> > > q;      // cola con < ultima posicion, cola de posiciones recorridas hasta ultima posicion > 
		vector<vector<int>> visited(40,vector<int>(80, 0));
		queue<Dir> q_path;
    
		q.push({myFuryan_pos, q_path});
		visited[myFuryan_pos.i][myFuryan_pos.j] = 1;

		while(not q.empty()) {
		    Pos currentPos = q.front().first;
		    q_path = q.front().second;
		    q.pop();

		    //si encontramos el enemigo
		    Cell currentCell = cell(currentPos);
		    if(currentCell.id != -1 and unit(currentCell.id).player != me()) {
                if (health <= 25) {
                    //atacar solo pioneers
                    if (unit(currentCell.id).type == Pioneer) return q_path.front();
                }
                else {
                    if (unit(currentCell.id).type == Furyan or unit(currentCell.id).type == Pioneer) {
                        return q_path.front();
                    }
                }
		    }

		    //si no lo encontramos, recorremos los vecinos
		    for (int d = 0; d < 8; ++d) {
                Pos nextPos = currentPos + Dir(d);
                Dir nextMov = Dir(d);

                if(validMove(nextPos) and not visited[nextPos.i][nextPos.j]){

                    queue<Dir> q_newPath = q_path;
                    visited[nextPos.i][nextPos.j] = 1;
                    
                    q_newPath.push(nextMov);
                    q.push({nextPos,q_newPath});
                }
		    }
		}
		//si no encuentra un enemigo: caso improbable, sería un error
		return None;
	}

    //Busca celdas sin conquistar y devuelve la direccion para ir hacia ella
    Dir paintCells(Pos &myPos) {
        vector<Dir> notPainted;

        //primero mirar alrededor y conquistar las celdas vacias
        for (int i = 0; i < 8; ++i) {
            Pos nextPos = myPos + Dir(i);
            if (validMove(nextPos)) {
                Cell myCell = cell(nextPos);
                if (myCell.owner != me() and myCell.id == -1) {
                    notPainted.push_back(Dir(i));
                }
            }
        }

        //direccion a casilla sin conquistar aleatoria
        if (not notPainted.empty()) {
            int rand = random(0, notPainted.size() - 1);
            return notPainted[rand];
        }
        
        queue< pair<Pos, queue<Dir> > > q;      // cola con < ultima posicion, cola de posiciones recorridas hasta ultima posicion > 
		vector<vector<int>> visited(40,vector<int>(80, 0));
		queue<Dir> q_path;
    
		q.push({myPos, q_path});
		visited[myPos.i][myPos.j] = 1;
        
		while(not q.empty()) {
		    Pos currentPos = q.front().first;
		    q_path = q.front().second;
		    q.pop();

		    //si encontramos el enemigo
		    Cell currentCell = cell(currentPos);
		    if (currentCell.id == -1 and currentCell.owner != me() and currentCell.type == Cave) return q_path.front();
            if (currentCell.id != -1 and unit(currentCell.id).player != me() and unit(currentCell.id).type == Furyan ) return Dir((q_path.front()+4)%8);
            

		    //si no lo encontramos, recorremos los vecinos
		    for (int d = 0; d < 8; ++d) {
                Pos nextPos = currentPos + Dir(d);
                Dir nextMov = Dir(d);

                if(validMove(nextPos) and not visited[nextPos.i][nextPos.j]){

                    queue<Dir> q_newPath = q_path;
                    visited[nextPos.i][nextPos.j] = 1;
                    
                    q_newPath.push(nextMov);
                    q.push({nextPos,q_newPath});
                }
		    }
		}
		//si no encuentra un enemigo: caso improbable, sería un error
		return None;
    }

    //Mira si hay enemigos alrededor y los evita
    Dir enemiesAround(Pos &myPos) {
        for (int i = -2; i < 2; ++i) {
            for (int j = -2; j < 2; ++j) {
               
                Pos currentPos = Pos(myPos.i + i, myPos.j + j, myPos.k);
                if (currentPos.j < 0) currentPos.j += 80;

                if (validMove(currentPos)) {
                    Cell currentCell = cell(currentPos);
                    if (currentCell.id != -1 and unit(currentCell.id).player != me() and (unit(currentCell.id).type == Furyan or unit(currentCell.id).type == Necromonger)) {
                        return runFrom_enemy(myPos, currentCell.id);
                    }
                }
            }
        }
        return None;
    }

    //Mueve las unidades de tipo Furyan
    void move_furyans() {
        VI myfuryans = furyans(me());
        int size = myfuryans.size();
        for(int i = 0; i < size; ++i) {
            int id = myfuryans[i];

            Pos myFuryanPos = unit(id).pos;

            //si no hay hellhounds cerca
            int id_nearestHellhound = safe_CavePerimeter(myFuryanPos);
            if (id_nearestHellhound == -1) {
                
                //miro la salud del furyan actual
                int myHealth = unit(id).health;

                //mover furyan hacia un enemigo
                Dir getDir = move_to_nearestEnemy(myFuryanPos, myHealth);
                Cell getCell = cell(myFuryanPos+getDir);
                if (getCell.id != -1 and unit(getCell.id).type == Furyan and myHealth <= 25) command(id, Dir((getDir+4)%8));
                else command(id, getDir);

            }
            else {
                //esquivar a los hellhounds
                Dir getDir_hellhound = runFrom_enemy(myFuryanPos, id_nearestHellhound);
                command(id, getDir_hellhound);
            }
        }
    }

    //Mueve las unidades de tipo Pioneer
    void move_pioneers() {
        VI mypioneers = pioneers(me());
        int size = mypioneers.size();

        for (int i = 0; i < size; ++i) {
            int id = mypioneers[i];
            Pos myPioneer_pos = unit(id).pos;
            Cell myCell = cell(myPioneer_pos);
            //dentro de la cueva
            if (myPioneer_pos.k == 0) {

                //si no hay Hellhounds cerca
                int id_nearestHellhound = safe_CavePerimeter(myPioneer_pos);
                if (id_nearestHellhound == -1) {

                    //miro si hay furyans
                    Dir getDir_enemy = enemiesAround(myPioneer_pos);
                    if (getDir_enemy == None) {

                        //pintar celdas
                        if (nb_cells(me()) < 600) {
                            Dir getDir_cells = paintCells(myPioneer_pos);
                            command(id, getDir_cells);
                        }
                        //buscar gemas
                        else {
                            if (myCell.type == Elevator) command(id, Up);
                            else {
                                Dir getDir_elevator = move_to_nearestElevator(myPioneer_pos);
                                command(id, getDir_elevator);
                            }
                        }
                    }
                    else command(id, getDir_enemy);
                }
                else {
                    Dir getDir_hellhound = runFrom_enemy(myPioneer_pos, id_nearestHellhound);
                    command(id, getDir_hellhound);
                }
            }
            //en el exterior
            else {
                //miro si hay necromongers
                Dir getDir_enemy = enemiesAround(myPioneer_pos);
                if (getDir_enemy == None) {
                    //mover a gema
                    if (safe_Perimeter(myPioneer_pos)) {
                        Dir getDir_gem = move_to_nearestGem(myPioneer_pos);
                        command(id, getDir_gem);
                    }
                }
                else {
                    if (myCell.type == Elevator) command(id, Down);
                    else {
                        Dir getDir_elevator = move_to_nearestElevator(myPioneer_pos);
                        command(id, getDir_elevator);
                    }
                }
            }
        }
    }

    /**
     * Types and attributes for your player can be defined here.
     */

    /**
     * Play method, invoked once per each round.
     */
    virtual void play () {
        move_furyans();
        move_pioneers();
    }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
