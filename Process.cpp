void TimerTick(){
	IOTimer += 1;
}

void CPUTick(){
	CPUTimer++;
}

void IncCPUTot(){
	CPUTotal +=1;
}

void IncITot(){
	ITotal += 1;
}

void IncOTot(){
	OTotal += 1;
}

void ICountTick(){
	ICount += 1
}

void OCountTick(){
	OCount += 1;
}

void CPUCountTick(){
	CPUCount += 1;
}

void Debug(){
	cout << "Name\t" << ProcessName <<endl;
	cout << "Priority\t" << Prieority << endl;
	cout << "ID\t" << ProcessID <<endl;
	cout << "Arrival\t" << ArrivalTime << endl;
	for (unsigned int i=0, i<10, i++){
		cout << History[i][0] << History[i][1] << " ";
	}
	//more for later
}

void Begin(int clock){
	Start = clock;
}



void DataOutput(){
	cout << "A Procces has terminated.\n";
	cout << "Process ID is " << ProcessID <<endl;
	cout << "Process Name is " << ProcessName << endl;
	cout << "Priority is " << Priority << endl;
	cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << " bursts.\n";
	cout << "Total output time = " << OTotal << " in " << OCount << " bursts\n";
	cout << "Total input time = " << ITotal << " in " << ICount << " bursts\n";
	cout << "Started at " << Start << " Terminated at " << End << endl;
	// there needs to be a cout somewhere for time waiting, and start nd end time
}
void SetEnd(){
	End = Start + ITotal + OTotal + CPUTotal;
}
void Setdata(string l1, string l2, int iter, int clock){
	ProcessID = 99 + iter;
	Start = clock;
	string F=l1
	int  L=F.find(" ");
	ProcessName = F.substr(0,L);
	F.erase(0,L+1);
L=F.find(" ");
	Priority = F.substr(0,L); //need string to int?
	F.erase(0,L+1);
	ArrivalTime = F;

		string S=l2;

		for(int h=0, h<10, h++){
			History[h][0]=strtok(S, " ");
			History[h][1]=strtok(S, " ");
		}
		Sub = 0;
		//while ((int r=strtok(S, " ")) >0){ // should loop through strings till no more spaces


}	
}
