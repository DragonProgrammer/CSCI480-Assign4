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
