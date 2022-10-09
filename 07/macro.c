// f - tablica wskaznikow do obiektow TF1, rozklady skladowe
// k - wymiar tablicy f
// h - histogram do ktorego wrzucamy wynik splotu
// n - liczba losowan
void splot(TF1 **f, int k, TH1D *h, int n) {
	double suma = 0;
	for ( int i = 0; i < n ; i++) { //dla każdego losowania
		for (int j = 0; j < k ; j++) { //dla każdej funkcji
			suma += f[j]->GetRandom();	
		}
		h->Fill(suma);
		suma=0;
	}
}

void deskaGaltona(TH1D *h, int n, int l, double p) {
	int poz = 0;
	double rand = 0;
	for (int i = 0; i < n ; i++) { //dla każdej kuli
		for (int j = 0; j < l ; j++) { //dla każdego rzedu
			rand = gRandom->Uniform(0,1);
			if (rand>p)
				poz++;
			else
				poz--;
						
		}
		//cout<<poz<<endl;
		h->Fill(poz);
		poz = 0;
	}
	
	
}

void macro () {
	
	//int k = 3;
	int n = 100000;
	
	TF1 *fun1 = new TF1("fun1","0*x+1",0,2);
	TF1 *fun[3] = {fun1,fun1,fun1};
	TH1D *hist2 = new TH1D("hist2","hist dla dwoch",100,0,4);
	TH1D *hist3 = new TH1D("hist3","hist dla trzech",100,0,6);
	
	
	splot(fun,2,hist2,n);
	splot(fun,3,hist3,n);
	
	TCanvas *c1 = new TCanvas("c1", "Ex1", 1000,1000);
	c1->Divide(2,2);
	c1->cd(1);
	hist2->Draw();
	c1->cd(2);
	hist3->Draw();
	
	TF1 *fun2 = new TF1("fun2","ROOT::Math::gaussian_pdf(x,0.2,1)",-5,5);
	TF1 *fun3 = new TF1("fun3","ROOT::Math::gaussian_pdf(x,0.5,3)",-5,5);
	TF1 *nor[2] = {fun2,fun3};
	TH1D *hist4 = new TH1D("hist4","hist dla normlanych",100,0,8);
	
	splot(nor,2,hist4,n);
	c1->cd(3);
	hist4->Draw();
	
	cout<<"EX1: 1"<<endl;
	cout<<"EX2: 3"<<endl;
	cout<<"EX: "<<hist4->GetMean()<<endl;
	cout<<endl;
	
	cout<<"VX1: 0.04"<<endl;
	cout<<"VX1: 0.25"<<endl;
	cout<<"VX: "<<hist4->GetRMS()*hist4->GetRMS()<<endl;
	
	TH1D *hist5 = new TH1D("hist5","deska Galtona",100,-20,20);
	deskaGaltona(hist5,1000,10,0.5);
	
	//TCanvas *c2 = new TCanvas("c2", "Ex2.", 1000,1000);
	//c2->Divide(2,2);
	c1->cd(4);
	hist5->Draw();

}
