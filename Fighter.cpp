#include "Fighter.h"
Fighter::Fighter(int id, int at, int d) : Enemy(id, at, d)
{
	;
}
void Fighter::Move() {
	if (Health > 0.5 * originalHealth) {
		if (Distance > 2 + Speed)
			Distance -= Speed;
		else if (Distance <= 2 + Speed)
			Distance = 2;
	}
	else {
		if (Distance > 2 + Speed * 0.5)
			Distance -= Speed * 0.5;
		else if (Distance <= 2 + Speed * 0.5)
			Distance = 2;

	}
}
double Fighter::Act() {
	double pow = (double)Power;
	double Dis = (double)Distance;
	if (tRemain != 0)
		return 0;
	double Damage = 0;     // Damage from fighter to castle;
	if (Health >= (originalHealth/2))
		Damage = pow/Dis;
	else if (Health < (originalHealth/2))
		Damage = 0.5*pow/Dis;
	tRemain = Reload_Period+1;
	return Damage;
}

void Fighter::DecreaseTimeRemaning() {
	--tRemain;
}
int Fighter::getTimeRemaning() {
	return tRemain;
}