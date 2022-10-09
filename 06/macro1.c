double generateVonNeumann(TF1 *g, double min, double max) {
	double n1,n2;
	do {
		n1 = gRandom->Uniform(min,max);
		n2 = gRandom->Uniform(0, g->GetMaximum(min,max));
	}	while (n2 < g(n1));

	return n1;
	
	
}

double efficiencyVonNeumann(TF1 *g, double min, double max, int n) {
	double n1,n2;
	double counter = 0;
	for (int i =0; i<n; i++) {
		n1 = gRandom->Uniform(min,max);
		n2 = gRandom->Uniform(0, g->GetMaximum(min,max));
		if (n2 <= g(n1)) 
			counter++;
	}	
	return counter/n;
	
	
	
	
}
double integralVonNeumann(TF1 *g, double min, double max, int n) {
	double acc = 0;
	double rej = 0;
	double n1,n2;
	for (int i =0; i<n; i++) {
		n1 = gRandom->Uniform(min,max);
		n2 = gRandom->Uniform(0, g->GetMaximum(min,max));
		rej++;
		if (n2 <= g(n1)) 
			acc++;
		
	}
	return acc/rej*(max-min)*g->GetMaximum(min,max);
	
	
}

/*double integralVonNeumannWithHelper(TF1 *g, TF1 *s, double min, double max, int n, double &wydajnosc) {
	double n1, n2, n3;
	TF1 *ds = new TF1("ds","x-x*x/2",0,1);
	TF1 *rds = new TF1("rds","TMath::Sqrt(-2*x+1) +1",0,1);
	double acc = 0;
	double rej = 0;
	
	for (int i =0; i<n; i++) {
		n1 = gRandom->Uniform(min,max);
		n2 = gRandom->Uniform(ds->GetMinimum,ds->GetMaximum);
		n3 = rds(n2);
		rej++;
		if (n1 <= g(n3)/s(n3)) 
			acc++;
		
	}
	wydajnosc = efficiencyVonNeumann(g,min,max,n);
	return acc/rej*(max-min)*g->GetMaximum(min,max);
	
}*/
void macro1() {
	double wydajnosc;
	TF1 *s = new TF1("s", "1-x",0,1);
	TF1 *fun1 = new TF1("fun1","TMath::Exp(-5*x)",0,1);
	cout<<"Integral: "<<integralVonNeumann(fun1,0,1,100000)<<endl;
	cout<<"Efficiency: "<<efficiencyVonNeumann(fun1,0,1,100000)<<endl;
	//cout<<"Integral: "<<integralVonNeumannWithHelper(fun1,s,0,1,100000,wydajnosc)<<endl;
	//cout<<"wydajnosc z helperem: "<<wydajnosc<<endl;
	
	
	
}
