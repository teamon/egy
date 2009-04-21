/*
	G - ground
	D - distance
	M - motor
	-----------------
	| G1 D1 D3 D2 G2
	|
	|
	| M1 			M2
	|
	|
	| G3 D4 D6 D5 G4
	-----------------
*/

#include "lib/sumo.h"
#include "lib/motor.h"
#include "lib/queue.h"


#define ITIME 20
#define DEBUG 0
#define WAIT 1000

Queue q;
bool back = 0;
bool zwarcie = 0;
unsigned char zwarcieLen = 0;

void fikumiku(){
	//motory, disty, groundy
	//o ile dobrze pamietam to motorow nie trzeba bylo zamieniac stronami
	//bo czujniki nie sa zamieniane stronami, wiec wystarczy zamiana
	//przod<->tyl
	
	back = !back;
	motor[0].reverse = motor[1].reverse = back;
	motor[0].setPower(0);
	motor[1].setPower(0);
	q.clear();
}

//2100 - caly ring
void moveStraight(int time, char pri){
	q.push(100, 100, time/ITIME, pri);
}

void stopMotor(int time, char pri){
	if (dist<0){
		motor[0].setPower(0);
		motor[1].setPower(0);
	}
	q.push(0, 0, time, pri);
}

const char inPlace = 0;
const char oneWheel = 1;
const char lightTurn = 2;

Move turnPowers[] = {
	{100, -100, 0, 1400/ITIME}, // obrot w prawo dookola prawego kola, lewy na 50% prawy na 0, czas=1000ms
	{100, 0, 0, 2300/ITIME}, // jakis tam skret inny w prawo
	{100, 60, 0, 7000/ITIME}
};

void setTurn(char rad, float angle, char pri){
	Move m = turnPowers[rad];
	if(angle < 0){
		char p = m.left;
		m.left = m.right;
		m.right = p;
	}
	m.time = int(mabs(angle)*m.time);
	m.pri = pri;
	q.push(m);
}

void unik(char pri){
	led_set(255);
	q.clear();
	/*//zakladam ze zatrzymanie i zmiana kierunku to proces czasochlonny
	//wiec daze do zachowania jak najmniejszej ilosci zatrzyman/zmian	
	bool ktorym = 0;
	int wyn = motor[0].getPower()*motor[1].getPower();
	if (wyn > 0){
		ktorym = (Dist[back][0] > Dist[back][1] && back == 0);//jezeli jest
		//szansa ze z jednej strony nic nie ma to zatrzymaj ten motor
	}else if (wyn == 0){
		//wybierz ten z mniejsza moca (czyli ten z zerem)
		ktorym = (mabs(motor[0].getPower())>mabs(motor[1].getPower())) && back == 0;
	}else{
		//wybierz ten z wieksza moca (czyli dodatni)
		ktorym = (motor[0].getPower()<motor[1].getPower() && back==0);
	}
	
	//jeden z silnikow sie zatrzyma, 2 pojedzie do tylu
	//q.push(-(ktorym!=0)*100, -(ktorym!=1)*100, 20, pri);*/
	//fikumiku();
	moveStraight(20, 2);
	setTurn(oneWheel, .5, 2);
	//tu by sie moglo przydac wrzucanie fikumiku na kolejke?
	led_set(0);
}

unsigned char getGround(){
	unsigned char out=1;
	if (ground1_detected()) out*=2; // przod lewy
	if (ground2_detected()) out*=3; // przod prawy
	if (ground3_detected()) out*=5; // tyl lewy
	if (ground4_detected()) out*=7; // tyl prawy
	return out;
}
 
const char wZwarciu = 2;
const char koniecRingu = 1;
char getProbe(bool side){
	if (Dist[side][2] < 90){
			return wZwarciu; //zwarcie
	}else if (Dist[side][2] > 130){
			return koniecRingu; //koniec ringu
	}
	
	return 0;
}
 
void planEscape(unsigned char grd, char fp, char bp){
	//led_set(grd);
	q.clear();
	if (grd == 1){
		if (bp==1)
			fikumiku();
		
		if (zwarcie)
			unik(3);
		else
			moveStraight(20, 3);
	}else{
		if (grd!=14 && grd!=15 && 
		((grd%2==0 || grd%3==0) && !back || 
		(grd%5==0 || grd%7==0) && back)){
			fikumiku();
		}
		switch(grd){
			case 35: // tyl
			case 6: // przod
				moveStraight(400, 3);
				setTurn(oneWheel, .125, 2);
				return;
			
			case 2: // przod lewy
			case 5: // tyl lewy
				setTurn(lightTurn, ((back)?-1:1)*.125, 3); // skret o 45 stopni w prawo
				moveStraight(200, 3);
				return;
			
			case 3: // przod prawy
			case 7: // tyl prawy
				setTurn(lightTurn, ((!back)?-1:1)*.125, 3); // skret o 45 stopni w prawo
				moveStraight(200, 3);
				return;
				
			case 15: // lewo
				setTurn(lightTurn, ((back)?-1:1)*.25, 3);
				moveStraight(200, 3);
				return;
				
			case 14: // prawo
				setTurn(lightTurn, ((!back)?-1:1)*.25, 3);
				moveStraight(200, 3);
				return;
		}
	}
}

void debug(){
	progress();
	//send_ground_state_on_usart();
	send_distance_state_on_usart();
	
	unsigned char c = usart_read_byte();
	while (c!=0){
		switch(c){
			case '*':
				reset();
				break;
			case '%':
				fikumiku();
				break;
		}
		c = usart_read_byte();
	}
}

void setup(){
	led_init();
	motor_init();
	switch_init();
	ground_init();
	dist_init();
	// servo_init(); // na razie niepotrzebne
	if(DEBUG) {
		usart_init();
	}
	
	setb(SERVO1_DDR, SERVO1_PIN);
	setb(SERVO2_DDR, SERVO2_PIN);
	clr(SERVO1_PORT, SERVO1_PIN);
	clr(SERVO2_PORT, SERVO2_PIN);
}

void klapy(){
	setb(SERVO1_PORT, SERVO1_PIN);
	setb(SERVO2_PORT, SERVO2_PIN);
	wait_ms(500);
	clr(SERVO1_PORT, SERVO1_PIN);
	clr(SERVO2_PORT, SERVO2_PIN);
}

struct ValAndDist{
	char dist;
	int val;
};

ValAndDist vnd[] = {
{10, 120},
{15, 87},
{20, 70},
{25, 55},
{30, 50},
{35, 40},
{40, 35},
{45, 30},
{-1, 29}};

const char valuesLen = 9;

char getDistance(int value, char probe){
	if (value < 30) return 100;
	if (probe == 2) return 0;
	
	char n = valuesLen, left = 0;
	for(;;){
		int center = (left + n)/2;
		if (vnd[center].val == value || n-left < 2){
			return vnd[center].dist;
		}else if (vnd[center].val < value){
			n = center;
		}else{
			left = center;
		}
	}
	return 100;
}
unsigned char ticks = 0;
bool odliczanie = false;
bool hold = false, hold2 = false;
char strategia = 0;
int power = 1;
bool preLoop(){
	if (DEBUG){
		usart_write_byte(0);
		if (usart_read_byte() == '!'){
			led_set(255);
			usart_write_progmem_string(PSTR("Bonjour\n"));
			return true;
		}
	}
	if (switch1_pressed() && !hold){
		odliczanie = !odliczanie;
		ticks = 0;
		hold = true;
	}else if(!switch1_pressed()){
		hold = false;
	}

	if (switch2_pressed() && !hold2){
		strategia ++;
		if (strategia>7) strategia = 0;
		led_set(1<<strategia);
        
		odliczanie = false;
		hold2 = true;
	}else if (!switch2_pressed())
		hold2 = false;

	ticks += odliczanie;
	if (ticks >= WAIT/ITIME) return true;
	if (odliczanie)
		led_set(1<<(5-ticks*5*ITIME/WAIT));

	return false;
}

void loop(){
	kalmanize();
	if(DEBUG){
		debug();
		return;
	}
	
	int pri = 0;
	if (!q.empty()){
		pri = q.front()->pri;
	}
	
	char fProbe = 0;
	char bProbe = 0;
	
	if (pri < 3){
		//sprawdzam disty 3 i 6 i grd
		unsigned char ground = getGround();

		fProbe = getProbe(back);
		bProbe = getProbe(!back);
		led_set(fProbe);
		
		if (ground!=1/* || fProbe == koniecRingu || bProbe == koniecRingu*/){
			planEscape(ground, fProbe, bProbe);
			pri = 3;
		}
	}
	if (pri < 2){
		if (fProbe == wZwarciu || bProbe == wZwarciu){
			zwarcie = true;
			zwarcieLen+=1;
		}else{
			//zwarcieLen-=(zwarcieLen>0);
			zwarcie = false;
		}
		if (zwarcieLen>=100 && zwarcie){ //maksymalna sensowna dl zwarcia
			if (fProbe==wZwarciu)
				fikumiku();
			zwarcieLen = 0;
			unik(2);
			pri = 2;
		}
		/*//sprawdzam disty
		
		char vals[][2] = {{0, 0}, {0, 0}};
		vals[back][0] = getDistance(Dist[back][0], fProbe); 
		//fProbe zawsze jest z przodu
		vals[back][1] = getDistance(Dist[back][1], fProbe);
		
		vals[!back][0] = getDistance(Dist[!back][0]), bProbe);
		vals[!back][1] = getDistance(Dist[!back][0]), bProbe);
		
		bool side = back;
		if (min(vals[back][0], vals[back][1]) > min(vals[!back][0], vals[!back][1])){
			side = !back;
			fikumiku();
		}
		
		char d = vals[side][0] - vals[side][1];
		
		if (d == 0){
			if (vals[side][0] != 100){
				setStraight(200, 1);
			}
		}else if(d > 0){
			q.push(100, d*2.0/5, 200/ITIME, 1);
		} else {
			q.push(d*2.0/5, 100, 200/ITIME, 1);
		}
	
		*/
		pri = 1;
	}
	
	if (!q.empty()){
		motor[0].setPower(q.front()->left);
		motor[1].setPower(q.front()->right);
		q.dec(1);
	}else{
		//szukaj
		motor[0].setPower(60);
		motor[1].setPower(60);
	}	
}

int main() {
	setup();
	
	led_set(1);
	
	while(!preLoop()) wait_ms(ITIME);
	led_set(0);
	
	q.clear();
	
	switch (strategia){
		case 1:
			motor[0].setPower(50);
			motor[1].setPower(50);
		break;
		case 2:
		
		break;
		default:
		break;
	}
	klapy();
	for(;;){
		loop();
		// unsigned char ground = getGround();
		// led_set(ground);
		wait_ms(ITIME);
	}
}
