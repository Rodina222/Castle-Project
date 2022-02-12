#include "Battle.h"
#include <time.h>
#include <fstream>
#include<iostream>

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	EDrawCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;

	/////// by Rodina
	Frosted_Fighters = 0;
	Frosted_Healers = 0;
	Frosted_Freezers = 0;
	Killed_Fighters = 0;
	Killed_Healers = 0;
	Killed_Freezers = 0;
}
//--------------------------------------------getters------------------------------------------// added by Nour
int Battle::getCurrentTimeStep()const
{
	return CurrentTimeStep;
}
int Battle::getEDrawCount()
{
	return  EDrawCount;
}
bool Battle::getisModeSelected() const
{
	return isModeSelected;
}
int Battle::getEnemyCount() const
{
	return EnemyCount;
}
//--------------------------------------------Setters------------------------------------------// added by Nour

void Battle::setisModeSelected(bool cond)
{
	isModeSelected = cond;
}
void Battle::setCurrentTimetep(int step)
{
	CurrentTimeStep = step;
}
void Battle::setEnemyCount(int count)
{
	EnemyCount = count;
}
//---------------------------------------------------------------------------------------------//
void Battle::DrawEnemies(GUI* pGUI)
{
	//pGUI->DrawAllItems(BEnemiesForDraw, EnemyCount);
}
//---------------------------------------------------------------------------------------------//
void Battle::Parsing()
{
	string filename ="";
	ifstream finput;
	while (filename == "")
	{
		filename = OpenWindow("Choose the input text file: ");
	}

	finput.open(filename);

	//ifstream finput("text - Copy.txt");
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];

	if (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, " ", &context);
		if (pch != NULL)
		{
			if (pch != NULL)
			{
				int CH = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetHealth(CH);
				BCastle.setOriginalHealth(CH);
			}
			if (pch != NULL)
			{
				int N = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetMax_Enemy(N);
			}
			if (pch != NULL)
			{
				int CP = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetPower(CP);
			}
		}
	}

	if (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, " ", &context);
		if (pch != NULL)
		{
			EnemyCount = stoi(pch);

		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		//Enemy enemy1(1,2,3);
		if (finput.getline(line, size))
		{
			int ID{};
			int AT{};
			int POW{}, RLD{}, SPD{};
			double H{};
			int TYP1;
			pch = strtok_s(line, " ", &context);
			if (pch != NULL)
			{
				ID = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << ID << " ";
			}

			if (pch != NULL)
			{
				TYP1 = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << TYP << " ";
			}

			if (pch != NULL)
			{
				AT = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << AT << " ";
			}

			if (pch != NULL)
			{
				H = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Health(H);
				//enemy1->Set_Original_Health(H);
			}

			if (pch != NULL)
			{
				POW = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Power(POW);
			}

			if (pch != NULL)
			{
				RLD = stoi(pch);
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Reload(RLD);
			}

			if (pch != NULL)
			{
				SPD = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Speed(SPD);
			} //torevise 
			//Q_Inactive.enqueue(enemy1);



			
			if (TYP1 == 0)
			{
				//Fighter* Fi = dynamic_cast<Fighter*>(pE);
				Fighter* fighter = new Fighter(ID, AT, MaxDistance);
				fighter->SetStatus(INAC);
				fighter->Set_Health(H);
				fighter->Set_Original_Health(H);
				fighter->Set_Power(POW);
				fighter->Set_Reload(RLD);
				fighter->Set_Speed(SPD);
				Q_Inactive.enqueue(fighter);
			}
			else if (TYP1 == 1)
			{
				Healer* healer = new Healer(ID, AT, MaxDistance);
				healer->SetStatus(INAC);
				healer->Set_Health(H);
				healer->Set_Original_Health(H);
				healer->Set_Power(POW);
				healer->Set_Reload(RLD);
				healer->Set_Speed(SPD);
				Q_Inactive.enqueue(healer);
			}
			else if (TYP1 == 2)
			{
				Freezer* freezer = new Freezer(ID, AT, MaxDistance);
				freezer->SetStatus(INAC);
				freezer->Set_Health(H);
				freezer->Set_Original_Health(H);
				freezer->Set_Power(POW);
				freezer->Set_Reload(RLD);
				freezer->Set_Speed(SPD);
				Q_Inactive.enqueue(freezer);
			}
		}
	}
}


string Battle::OpenWindow(const string& Message) 
{
	const int BUFSIZE = 512;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.lpstrFilter = "Text Files\0*.txt\0";
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = Message.c_str();
	GetOpenFileName(&ofns);
	return buffer;
}


void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}
void Battle::AddtoBEnemiesForDraw(Enemy* Ptr)//added by Nour
{
	if (EnemyCount < MaxEnemyCount)
	{
		BEnemiesForDraw[EDrawCount++] = Ptr;

	}
}


Castle* Battle::GetCastle()
{
	return & BCastle;
}


void Battle::RunSimulation()//starting the battle
{
	//bool flag = true;// added by Nour
	Parsing();
	pGUI = new GUI;//create a new GUI with pGUI pointing to it
	PROG_MODE	mode = pGUI->getGUIMode();
	//while (flag == true)//added by Nour
	//{
		//-------------------------------Added by Nour----------------------------------------//
	keytype key = pGUI->GetPress();

	//if (key != 2)
	//{
	//	//cout << "Lets Play" << endl; //for debugging 
	//	#pragma comment(lib,"winmm.lib")
	//	PlaySound("jujutsukaisen.wav", NULL, SND_ASYNC);
	//}
	//else { PlaySound("pszSound", NULL, SND_ASYNC); }
	////------------------------------------------------------------------------------------//
	setisModeSelected(false);
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		setisModeSelected(true);//added by Nour
		InteractiveMode();//added by Nour
		break;
	case MODE_STEP:
		setisModeSelected(true);//added by Nour
		StepMode();//added by nour
		break;
	case MODE_SLNT:
		SilentMode();//added by nour
		break;
	case MODE_DEMO://to be removed "nour"
		//Just_A_Demo();
		break;
	}
	delete pGUI;//deletes the interface 
}




void Battle::InteractiveMode()//added by nour
{
	/*char c = NULL;
	keytype key = pGUI->pWind->GetKeyPress(c);
	key = pGUI->pWind->GetKeyPress(c);*/
	//cout << "key" << key << endl;
	//keytype key = pGUI->GetPress();
	bool flag = false;
	
	setCurrentTimetep(0);
	KilledCount = 0;
	pGUI->UpdateInterface(CurrentTimeStep);
	//while ((key != ESCAPE) && (getisModeSelected()==true))
	//{
	pGUI->FlushForClick();//Needed to change pWind to public because of flushing issues 
//	key = pGUI->pWind->GetKeyPress(c);
//	if (key != 4)
	//{
	BCastle.SetHealth(34);
	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)//by Nour
	{

		pGUI->waitForClick();	//check if click is inside the yellow box//by Nour
		CurrentTimeStep++;//by Nour
		pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive//by Nour
		

		ActivateEnemies();//by Nour
		UpdateEnemies();//by Nour
		ActivateSuperSolidiers(CurrentTimeStep);
		
		pGUI->UpdateInterface(CurrentTimeStep);//by Nour
		///////////Update Battle Info/////////////// by Rodina
		pGUI->Set_Active_Healers(S_Healers.getSize());
		pGUI->Set_Active_Freezers(Q_freezers.getSize());
		pGUI->Set_Active_Fighters(Q_fighters.getSize());


		pGUI->Set_Frosted_Healers(Frosted_Healers);
		pGUI->Set_Frosted_Freezers(Frosted_Freezers);
		pGUI->Set_Frosted_Fighters(Frosted_Fighters);


		pGUI->Set_Killed_Healers(Killed_Healers);
		pGUI->Set_Killed_Freezers(Killed_Freezers);
		pGUI->Set_Killed_Fighters(Killed_Fighters);


		///////////////Update_castle_Info/////////// by Rodina
		pGUI->Set_Castle_Health(BCastle.GetHealth());
		pGUI->Set_Castle_Status(BCastle.Get_Frosted());

		/// ///////
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->AddSSToDrawingList(currSS);
		pGUI->UpdateInterface(CurrentTimeStep);

	
		
	
		//kill 1 enemy added by Nour
		if (S_Healers.getSize() != 0 && Killed_Healers != 1 && ActiveCount != 1 && flag == false)
		{
			Healer* killed = nullptr;
			//Enemy* PE = killed;
			S_Healers.Pop(killed);
			killed->SetStatus(KILD);//edited by Nour
			L_Killed.enqueue(killed);
			Killed_Healers++;

		}
		pGUI->ResetDrawingList();//by Nour
		AddAllListsToDrawingList();//by Nour
		pGUI->UpdateInterface(CurrentTimeStep);//by Nour

		BCastle.Set_Frosted();

	
	}

	OutputFile();

	


}
void Battle::SilentMode()//added by nour
{

}
void Battle::StepMode()//added by nour
{
	//char c = NULL;
	//keytype key = pGUI->pWind->GetKeyPress(c);
	//CurrentTimeStep = 0;

	bool flag = false;

	setCurrentTimetep(0);
	KilledCount = 0;
	pGUI->UpdateInterface(CurrentTimeStep);
	//while (key != 4)
	//{
		//key = pGUI->pWind->GetKeyPress(c);
	//int x = 0;
	//int y = 0;
	//pGUI->pWind->WaitMouseClick(x, y);	//check if click is inside the yellow box
	
	//pGUI->InDrawingArea(y);

	BCastle.SetHealth(34);
	while (KilledCount < EnemyCount)
	{
		CurrentTimeStep++;
		Sleep(1000);
		pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
		cout << CurrentTimeStep << endl;
		ActivateEnemies();//by Nour
		UpdateEnemies();//by Nour

		//Freezing2ActiveEnemies(); 
		//Defreezing2ActiveEnemies();

		ActivateSuperSolidiers(CurrentTimeStep);

		pGUI->UpdateInterface(CurrentTimeStep);//by Nour
		///////////Update Battle Info/////////////// by Rodina
		pGUI->Set_Active_Healers(S_Healers.getSize());
		pGUI->Set_Active_Freezers(Q_freezers.getSize());
		pGUI->Set_Active_Fighters(Q_fighters.getSize());


		pGUI->Set_Frosted_Healers(Frosted_Healers);
		pGUI->Set_Frosted_Freezers(Frosted_Freezers);
		pGUI->Set_Frosted_Fighters(Frosted_Fighters);


		pGUI->Set_Killed_Healers(Killed_Healers);
		pGUI->Set_Killed_Freezers(Killed_Freezers);
		pGUI->Set_Killed_Fighters(Killed_Fighters);


		///////////////Update_castle_Info/////////// by Rodina
		pGUI->Set_Castle_Health(BCastle.GetHealth());
		pGUI->Set_Castle_Status(BCastle.Get_Frosted());

		/// ///////
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
	
		pGUI->UpdateInterface(CurrentTimeStep);


		//kill 1 enemy added by Nour
		if (S_Healers.getSize() != 0 && Killed_Healers != 1 && ActiveCount != 1 && flag == false)
		{
			Healer* killed = nullptr;
			//Enemy* PE = killed;
			S_Healers.Pop(killed);
			killed->SetStatus(KILD);//edited by Nour
			L_Killed.enqueue(killed);
			Killed_Healers++;

		}
		
		UpdateEnemies();

		ActiveForMove.copyQueue(CopyofActive);//Nour
		ActOnAllHealers(S_Healers);//Nour


		pGUI->ResetDrawingList();//by Nour
		AddAllListsToDrawingList();//by Nour
		pGUI->AddSSToDrawingList(currSS);
		
		pGUI->UpdateInterface(CurrentTimeStep);//by Nour
	
		

		BCastle.Set_Frosted();


    }

	OutputFile();
}





//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//-------------------------------added by Nour-------------------------------------//
	int KilledCount;
	Enemy* const* KilledList = L_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(KilledList[i]);
	
	int FrostedCount;
	Enemy* const* FrostedList = Q_froozen.toArray(FrostedCount);
	for (int i = 0; i < FrostedCount; i++)
		pGUI->AddToDrawingList(FrostedList[i]);

	


	int HealersCount;
	Healer* const* HealersList = S_Healers.toArray(HealersCount);
	for (int i = 0; i < HealersCount; i++)
	{
		pGUI->AddToDrawingList(HealersList[i]);

	}

	int FighterCount;
	Fighter* const* FighterList = Q_fighters.toArray(FighterCount);
	for (int i = 0; i < FighterCount; i++)
		pGUI->AddToDrawingList(FighterList[i]);

	int FreezersCount;
	Freezer* const* FreezersList = Q_freezers.toArray(FreezersCount);
	for (int i = 0; i < FreezersCount; i++)
	{
		pGUI->AddToDrawingList(FreezersList[i]);
	}

}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy* pE;
	if (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;
		else if (pE->GetArrvTime() == CurrentTimeStep)
		{
			ActiveCount++;
			Q_Inactive.dequeue(pE);	      //remove enemy from the queue
			ActiveForMove.enqueue(pE);
			pE->SetStatus(ACTV);	     //make status active

			Fighter* Fi = dynamic_cast<Fighter*>(pE);
			Healer* He = dynamic_cast<Healer*>(pE);
			Freezer* Fr = dynamic_cast<Freezer*>(pE);

		

			if (Fi != NULL)
			{
				double priority;
				double dis=(double)Fi->GetDistance();
				if (Fi->Get_Health() > Fi->Get_Original_Health() / 2)
					priority = (1 / (dis) * Fi->Get_Power()) - Fi->getTimeRemaning();
				else {
					priority = (0.5 / dis) * Fi->Get_Power() - Fi->getTimeRemaning();
				}
				Q_fighters.push(Fi, priority);
				
				Fi->SetStatus(ACTV);
			}
			else if (He != NULL)
			{
				S_Healers.Push(He);
				He->SetStatus(ACTV);
			}
			else if (Fr != NULL)
			{
				Q_freezers.enqueue(Fr);
				Fr->SetStatus(ACTV);
			}

		}
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}
}
void Battle::UpdateEnemies()
{
	Enemy* pE;
	double ice=0;
	double health = 0;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < ActiveCount; i++)
	{
		Fighter* Fi = nullptr;
		Healer* HE = nullptr;
		Freezer* Fr = nullptr;
	
		//pE = BEnemiesForDraw[i];
		if (ActiveCount != 0)
		{
			ActiveForMove.dequeue(pE);
			pE->Melting_Rate();
			if (pE->GetStatus() == ACTV)
			{
				ActiveForMove.enqueue(pE);
			}
			Fighter* Fi = dynamic_cast<Fighter*>(pE);
			Healer* HE = dynamic_cast<Healer*>(pE);
			Freezer* Fr = dynamic_cast<Freezer*>(pE);

			

			if (pE->GetStatus() == ACTV)
			{
				if (Fi != nullptr) {
					Fi->Move();
					double Damage = Fi->Act();
					Fi->DecreaseTimeRemaning();
					BCastle.DecreaseHealth(Damage);
					
					health = Fi->Get_Health();
					cout << "This is the Fighters Health " << health << endl;

				}
			
				else if (HE != nullptr)
				{
					HE->Move();
					HE->Get_Health();
					health = HE->Get_Health();
					cout << "This is the Healer's Health " << health << endl;

			
				}
					
				  
				else if (Fr != nullptr) {
					Fr->Move();
					 ice = Fr->Act();
					Fr->DecreaseTimeRemaning();	
					BCastle.FreezingAmount(ice);
					health = Fr->Get_Health();
					cout << "This is the Freezzer's Health " << health << endl;

				}
					


			}
		}
	}
}


void Battle::ActivateSuperSolidiers(int currTimeStep) {
	double currHealth = BCastle.GetHealth();
	double origHealth = BCastle.getOriginalHealth();
	Priority_queue<Fighter*> temp;
	Q_fighters.copyPrioQueue(temp);
	Fighter* f;
	if (currHealth > (origHealth / 3))
		return;

	///  Castle Helath behind threshold  

	if (waitingTofSS % 5 == 0 && Achieve == true) {
		currSS = BCastle.getSuperSolider();
		Achieve = false;
	}
	if (currSS != nullptr && currSS->getDistance() != placeOfMaxNE ) {
		currSS->Move(placeOfMaxNE);
		Achieve = false;
		return;
	}
	if (currSS != nullptr && currSS->getDistance() == placeOfMaxNE) {
		Achieve = true;
		while (temp.isEmpty() != true) {
			temp.pop(f);
			currSS->Act(f, currTimeStep);
			
		}
		++waitingTofSS;
	}
	
}

void  Battle::setplaceOfMaxNE(int d) {
	placeOfMaxNE = d;
}
int Battle::getplaceOfMaxNE() const {
	return placeOfMaxNE;
}

void Battle::ActOnAllHealers(Stack<Healer*>& Healers)
{
	int n; //No.of Active healers

	Stack<Healer*> temp;
	Healer* T;
	n = Healers.getSize();
	for (int i = 0; i < n; i++)
	{
		Healers.Pop(T);
		T->increaseHealth(CopyofActive);
		temp.Push(T);
	}
	for (int i = 0; i < n; i++)
	{
		temp.Pop(T);
		Healers.Push(T);
	}
}


void Battle::OutputFile() {
	Enemy* e;
	ofstream output;
	int countOfKilled = 0;
	double sumFSD = 0;
	double sumKillDelay=0;
	output.open("OutoutFile.txt");
	if (!output) {
		cout << "Could not open output file";
			return ;
	}
	if (state == WIN)
		output << "GAME IS WIN" << endl;
	else if (state == LOSS)
		output << "GAME IS LOSS" << endl;
	else if (state == DRAWN)
		output << "GAME IS DRAWN"<<endl;
	
	while (L_Killed.isEmpty() != true) {
		L_Killed.dequeue(e);
		output << e->getKillingTime() << " " << e->GetID() << " " << e->getFirstShotDelay() << " " << e->getKilldelay() << " " << e->getLifeTime() << endl;
		countOfKilled++;
		sumFSD = sumFSD + e->getFirstShotDelay();
		sumKillDelay = sumKillDelay + e->getKilldelay();
	}

	double averageFSD = sumFSD / ((double)countOfKilled);
	double averageKD = sumKillDelay / ((double)countOfKilled);
	output << "Castle Total Damage = " << BCastle.getOriginalHealth() - BCastle.GetHealth() << endl;
	if (state == WIN) {
		output << "Total Enemies = " << countOfKilled << endl;
		output << "Average First-Shot Delay = " << averageFSD << endl;
		output << "Average Kill Delay = " << averageKD << endl;
	}
	else {
		output << "Total Killed = " << countOfKilled << endl;
		output << "Average First-Shot Delay = " << averageFSD << endl;
		output << "Average Kill Delay = " << averageKD << endl;
	}



	output.close();
}

void  Battle::increment_Frosted_Fighters(int frostedCount)
{
	Frosted_Fighters = Frosted_Fighters + frostedCount;
}
void  Battle::increment_Frosted_Healers(int frostedCount)
{
	Frosted_Healers = Frosted_Healers + frostedCount;
}
void  Battle::increment_Frosted_Freezers(int frostedCount)
{
	Frosted_Freezers = Frosted_Freezers + frostedCount;
}
void  Battle::increment_Killed_Fighters(int KilledCount)
{
	Killed_Fighters = Killed_Fighters + KilledCount;
}
void  Battle::increment_Killed_Healers(int KilledCount)
{
	Killed_Healers = Killed_Healers + KilledCount;
}
void  Battle::increment_Killed_Freezers(int KilledCount)
{
	Killed_Freezers = Killed_Freezers + KilledCount;
}
void  Battle::increment_ActiveCount(int Active)
{
	ActiveCount + Active;
}

/*void Battle::Freezing2ActiveEnemies() //by Rodina
{

	Freezer* F_E = nullptr;
	Healer* H_E = nullptr;
	Fighter* FIG_E = nullptr;

	if (Q_freezers.getSize() >= 2)
	{
		Q_freezers.dequeue(F_E);
		F_E->SetStatus(FRST);

		Q_froozen.enqueue(F_E);
		Frosted_Freezers++;
		FrostedCount++;
		ActiveCount--;


		Q_freezers.dequeue(F_E);
		F_E->SetStatus(FRST);

		Q_froozen.enqueue(F_E);
		Frosted_Freezers++;
		FrostedCount++;
		ActiveCount--;

	}
	if (S_Healers.getSize() >= 2)
	{
		S_Healers.Pop(H_E);
		H_E->SetStatus(FRST);
		Q_froozen.enqueue(H_E);
		FrostedCount++;
		Frosted_Healers++;
		ActiveCount--;

		S_Healers.Pop(H_E);
		H_E->SetStatus(FRST);
		Q_froozen.enqueue(H_E);
		FrostedCount++;
		Frosted_Healers++;
		ActiveCount--;

	}
	if (Q_fighters.getSize() >= 2)
	{

		Q_fighters.pop(FIG_E);
		FIG_E->SetStatus(FRST);
		Q_froozen.enqueue(FIG_E);
		FrostedCount++;
		Frosted_Fighters++;
		ActiveCount--;

		Q_fighters.pop(FIG_E);
		FIG_E->SetStatus(FRST);
		Q_froozen.enqueue(FIG_E);
		FrostedCount++;
		Frosted_Fighters++;
		ActiveCount--;

	}


}*/
/*void Battle::Defreezing2ActiveEnemies() //by Rodina
{
	Enemy* enemy;
	Freezer* Fr = nullptr;
	Healer* HE = nullptr;
	Fighter* Fi = nullptr;

	if (Q_froozen.peekFront(enemy) != false && Q_froozen.getSize() >= 2)
	{
		Fi = dynamic_cast<Fighter*>(enemy);
		HE = dynamic_cast<Healer*>(enemy);
		Fr = dynamic_cast<Freezer*>(enemy);



		if (Fr != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_freezers.enqueue(Fr);
			ActiveCount++;
			Frosted_Freezers--;
			FrostedCount--;


			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_freezers.enqueue(Fr);
			ActiveCount++;
			Frosted_Freezers--;
			FrostedCount--;


		}
		else if (HE != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			S_Healers.Push(HE);
			ActiveCount++;
			Frosted_Healers--;
			FrostedCount--;

			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			S_Healers.Push(HE);
			ActiveCount++;
			Frosted_Healers--;
			FrostedCount--;


		}
		else if (Fi != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_fighters.push(Fi, ActiveCount);
			ActiveCount++;
			Frosted_Fighters--;
			FrostedCount--;



			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_fighters.push(Fi, ActiveCount);
			ActiveCount++;
			Frosted_Fighters--;
			FrostedCount--;



		}

	}

}*/



