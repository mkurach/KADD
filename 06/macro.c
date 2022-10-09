const int N = 100000;
void macro() {
	TGraph *gr1 = new TGraph();
	TGraph *gr2 = new TGraph();
	TCanvas *c1 = new TCanvas("c1", "Ex1", 1000,1000);
	
	double x,y;
	double Ac=0;
	double Asq=0;
	double pi;
	gr1->SetMarkerColor(kRed);
	gr1->SetMarkerSize(10);
	gr2->SetMarkerColor(kBlue);
	
	for (int i = 0; i < N; i++) {
		x= gRandom->Uniform(0,1);
		y= gRandom->Uniform(0,1);
		if ( (x*x+y*y)<1) {
			gr1->SetPoint(i,x,y);
			
			Ac++;
			Asq++;
		}
		else {
			gr2->SetPoint(i,x,y);
			Asq++;
		}
		
	}
	
	pi= 4*Ac/Asq;
	gr1->Draw("AP");
	gr2->Draw("sameP");
	
	cout<<pi<<endl;
	
	
	
	
	
}
