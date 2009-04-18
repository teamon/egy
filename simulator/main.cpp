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

#define ITIME 50
#define DEBUG 1
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

void moveStraight(int dist, char pri){
	q.push(100, 100, dist, pri);
}

void stopMotor(int dist, char pri){
	q.push(0, 0, dist, pri);
}

void setTurn(int rad, int angle, char pri){
	
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
			//default:
			case 35: // tyl
			case 6: // przod
				moveStraight(20, 3);
				//stopMotor(10,3);
				return;
			
			case 2: // przod lewy
			case 5: // tyl lewy
				stopMotor(10,3);
				//moveStraight(20, 3);
				return;
			
			case 3: // przod prawy
			case 7: // tyl prawy
				stopMotor(10,3);
				//moveStraight(20, 3);
				return;
				
			case 10: // lewo
				stopMotor(10,3);
				//moveStraight(20, 3);
				return;
				
			case 21: // prawo
				stopMotor(10,3);
				//moveStraight(20, 3);
				return;
		}
	}
}

void debug(){
	progress();
	return;
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
		/*
		else if (c == '~'){ //motor
			char lp = usart_read_byte();
			char sign_c = usart_read_byte();
			char sign;
			switch (sign_c){
				case 'f':
					sign = 1;
					break;
				case 'b':
					sign = -1;
					break;
				case 'n':
					sign=0;
					break;
			}
			char power = usart_read_byte();
			power *= sign;
			SetMotor(lp, power);
		}*/
		
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
int power = 1;
bool preLoop(){
	if (DEBUG){
		usart_write_byte(0);
		if (usart_read_byte() == '!'){
			led_set(255);
			// usart_write_progmem_string(PSTR("Bonjour\n"));
			return true;
		}
	}//else {
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
	//}
	return false;
}

void loop(){
	simulate();
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
	
	// while(!preLoop()) wait_ms(ITIME);
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
