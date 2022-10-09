const int N = 1000000;

/*int generator (int g, int m, int x0) {
	int values[N];
	values[0]=x0;
	for (int i = 1; i<(N-1); i++) {
		values[i]=g*values[i-1]%m;
	}
	return values;
	
}*/

void macro1() {
	unsigned int seed = time(NULL);
	int m1 = 97;
	int m2 = 32363;
	int m3 = 146483647;
	int g1 = 23;
	int g2 = 157;
	int g3 = 16807;
	
	ofstream ofile1, ofile2, ofile3;
	ofile1.open("dane1.dat");
	ofile2.open("dane2.dat");
	ofile3.open("dane3.dat");


	
	double scaledx;
	unsigned int x, xprev; 
	xprev = seed;
	for(int i=0; i<N ; i++) { 
		x = (g1*xprev)%m1;
		scaledx = (double)(x/ m1);
		ofile1<<scaledx<<endl;
		xprev = x;	
		
	}
	xprev = seed;
	for(int i=0; i<N ; i++) { 
		x = (g2*xprev)%m2;
		scaledx = (double)(x/ m2);
		ofile2<<scaledx<<endl;
		xprev = x;	
		
	}
	xprev = seed;
	for(int i=0; i<N ; i++) { 
		x = (g3*xprev)%m3;
		scaledx = (double)(x/ m3);
		ofile3<<scaledx<<endl;
		xprev = x;	
		
	}
	
	ofile1.close();
	ofile2.close();
	ofile3.close();

	
	
	
	
	
	
	
	
	
	
	
	
	
}
