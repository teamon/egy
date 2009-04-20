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
bool front = 0;
bool zwarcie = 0;
unsigned char zwarcieLen = 0;

void fikumiku(){
	//motory, disty, groundy
	//o ile dobrze pamietam to motorow nie trzeba bylo zamieniac stronami
	//bo czujniki nie sa zamieniane stronami, wiec wystarczy zamiana
	//przod<->tyl
	
	front = !front;
	motor[0].reverse = motor[1].reverse = front;
	
	q.clear();
}

void moveStraight(int time, char pri){
	q.push(100, 100, time, pri);
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
	{100, 0, 0, 2500/ITIME}, // jakis tam skret inny w prawo
	{100, 60, 0, 4000/ITIME}
};

void setTurn(char rad, float angle, char pri){
	// ja bym tu nie kombinowal tylko ustalil doswiadczalnie kilka wartosci i radius zrobil jako kilka opcji typu: 
	// 0(w miejscu), 1(ciasny), 2(troche szerszy), 3 .. itp. bo to przeliczanie VelToPow i odwrotnie jest raczej kiepskim rozwiazaniem ;]
	// a jako angle czesc pelnego obrotu (po co sie jebac z pi)
	// no i wygladaloby to wtedy jakos tak:
	// turnPowers jako tablica elementow Move (left, right, time)
	// left, right - wartosci mocy na silniki
	// time = czas pelnego obrotu (to by trzeba w miare mozliwosci policzyc, wiem ze moze byc z tym problem ;p ale moze da sie policzyc np czas 10 obrotow i wtedy podzielic to powinno byc lepsze przyblizenie)
	// no i angle tak jak w pazdzierzu jak dodatnie to w prawo, jak ujemne to w lewo(czyli zamieniamy powery)
	// i na koncu byloby tylko
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
	//zakladam ze zatrzymanie i zmiana kierunku to proces czasochlonny
	//wiec daze do zachowania jak najmniejszej ilosci zatrzyman/zmian	
	bool ktorym = 0;
	int wyn = motor[0].getPower()*motor[1].getPower();
	if (wyn > 0){
		ktorym = (Dist[front][0] > Dist[front][1]);//jezeli jest
		//szansa ze z jednej strony nic nie ma to zatrzymaj ten motor
	}else if (wyn == 0){
		//wybierz ten z mniejsza moca (czyli ten z zerem)
		ktorym = (mabs(motor[0].getPower())>mabs(motor[1].getPower()));
	}else{
		//wybierz ten z wieksza moca (czyli dodatni)
		ktorym = (motor[0].getPower()<motor[1].getPower());
	}
	
	//jeden z silnikow sie zatrzyma, 2 pojedzie do tylu
	q.push(-(ktorym!=0)*100, -(ktorym!=1)*100, 20, pri);
}

unsigned char getGround(){
	unsigned char out=1;
	if (ground1_detected()) out*=(!front)?2:5; // przod lewy
	if (ground2_detected()) out*=(!front)?3:7; // przod prawy
	if (ground3_detected()) out*=(!front)?5:2; // tyl lewy
	if (ground4_detected()) out*=(!front)?7:3; // tyl prawy
	return out;
}
 
char getProbe(bool side){
	if (!inrange(Dist[side][2], 120, 140)){ //zakres dla ringu
		if (!inrange(Dist[side][0], 20, 70)
		&& !inrange(Dist[side][1], 20, 70)){ //nic nie ma z przodu więc kres
			return 1; //koniec ringu
		}else{
			return 2; //zwarcie
		}
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
		if (grd%2==0 || grd%3==0){
			fikumiku();
			led_set(255);
		}
		switch(grd){
			// czy jak zobaczy z przodu to zawsze dajemy fikumiku? (chyba tak bedzie wygodniej)
			//default:
			case 35: // tyl
			case 6: // przod
				moveStraight(20, 3);
				//stopMotor(10,3);
				return;
			
			case 2: // przod lewy
			case 5: // tyl lewy
				// stopMotor(10, 3);
				//moveStraight(20, 3);
				setTurn(1, 0.125, 3); // skret o 45 stopni w prawo
				return;
			
			case 3: // przod prawy
			case 7: // tyl prawy
				// stopMotor(10, 3);
				//moveStraight(20, 3);
				setTurn(1, -0.125, 3); // skret o 45 stopni w lewo
				return;
				
			case 10: // lewo
				stopMotor(10, 3);
				//moveStraight(20, 3);
				return;
				
			case 21: // prawo
				stopMotor(10, 3);
				//moveStraight(20, 3);
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
}

unsigned char ticks = 0;
bool odliczanie = false;
bool hold = false, hold2 = false;
char strategia = 0;
int power = 8;
bool preLoop(){
	led_set(getGround());
	if (switch1_pressed() && !hold){
		//test silnikow
		hold = true;
		
	}else if(!switch1_pressed() && hold){
		hold = false;
		led_set(1<<(power-1));
		motor[0].setPower(power*10);
		motor[1].setPower(10*power++);
		int czas = 0; 
		while(getGround()%2!=0 && getGround()%3!=0){ wait_ms(ITIME);czas++;}
		usart_write_number(czas);
		usart_write_byte('\n');
		fikumiku();
		motor[0].setPower(80);
		motor[1].setPower(80);
		wait_ms(500);
		motor[0].setPower(0);
		motor[1].setPower(0);
		led_set(255);
	}
	
	if (switch2_pressed() && !hold2){
		//zakrety
		strategia ++;
		hold2 = true;
	}else if (!switch2_pressed() && hold2){
		led_set(1<<(strategia-1));
		hold2 = false;
		float angle = -.75;
		setTurn(1, angle, 0);	
		unsigned char g = 1;
		int czas = 0;
		while (!q.empty()){
			progress();
			motor[0].setPower(q.front()->left);
			motor[1].setPower(q.front()->right);
			q.dec(1);
			g = getGround();
			wait_ms(ITIME);
			czas++;
		}
		led_set(255);
		usart_write_number(czas);
		usart_write_byte('\n');
		fikumiku();
		motor[0].setPower(80);
		motor[1].setPower(80);
		wait_ms(500);
		motor[0].setPower(0);
		motor[1].setPower(0);
		
	}

	return false;
}

void loop(){
	kalmanize();
	unsigned char ground = getGround();
	
	if(DEBUG){
		debug();
		return;
	}
	int pri = 0;
	if (!q.empty()){
		pri = q.front()->pri;
		//led_set(pri);
	}
			
	if (pri < 3){
		//sprawdzam disty 3 i 6 i grd
		unsigned char ground = getGround();
		//if (pri == 0) led_set(ground);
		char fProbe = 0;//getProbe(front);
		char bProbe = 0;//getProbe(!front);
		
		if (fProbe == 2 || bProbe == 2){
			zwarcie = true;
			zwarcieLen+=(zwarcieLen < 200);
		}else{
			zwarcieLen-=(zwarcieLen!=0);
			zwarcie = false;
		}
		
		if (ground!=1 || fProbe == 1 || bProbe == 1){
			planEscape(ground, fProbe, bProbe);
			pri = 3;
		}else if (zwarcieLen>100 && zwarcie){ //maksymalna sensowna dl zwarcia
			if (bProbe==2)
				fikumiku();
 
			unik(2);
			pri = 2;
		}
	}
	if (pri < 2){
		//sprawdzam disty
		
		pri = 1;
	}
	
	if (!q.empty()){
		motor[0].setPower(q.front()->left);
		motor[1].setPower(q.front()->right);
		q.dec(1);
	}else{
		//szukaj
		motor[0].setPower(60);
		motor[1].setPower(100);
		/*
		motor[0].stop();
		motor[1].stop();*/
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
	for(;;){
		loop();
		// unsigned char ground = getGround();
		// led_set(ground);
		wait_ms(ITIME);
	}
}
