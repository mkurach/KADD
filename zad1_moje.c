//0 = mu
//1 = sigma
double norm_distr(double *x, double *param) {	
	return 1.0/(param[1]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power((x[0] - param[0])/param[1], 2));
}

void splot(TF1 **f, int k, TH1D *hist, int n){
	for(int i = 0; i<n;i++){
		double sum = 0.0;
		for(int j = 0; j<k;j++){
			sum+=f[j]->GetRandom();
		}
		
		hist->Fill(sum);
	}
}
void zad1(){

	TF1 *normalne12[12];
	
	for(int i = 0; i<12; i++) {
		normalne12[i] = new TF1("normalne12"+i, norm_distr, -10, 20, 2);
		normalne12[i]->SetParameter(0,0.4);
		normalne12[i]->SetParameter(1,0.8);
	}
	
	TH1D *hist = new TH1D("hist","Splot 12",40,-10,20);
	
	TCanvas *c1 = new TCanvas("c1","Splot 12",800, 800);
	c1->Divide(2,2);
	c1->cd(1);
	splot(normalne12, 12, hist, 10000);
	hist->Draw();
	
	TF1 *fun1;
	int m = 0;
	double u = 0;
	int n = 10000;
	do{
		m++;
		fun1 = new TF1("fun1", "gaus", -.5, m);
		
		hist->Fit(fun1);
	}
	while(fun1->GetChisquare()/fun1->GetNDF()>1);
	cout<<"chi^2/NDF value: "<<fun1->GetChisquare()/fun1->GetNDF()<<endl;
	
	
	TF1 *normal = new TF1("normal", norm_distr, -10, 20, 2);
	normal->SetParameter(0,0);
	normal->SetParameter(1,0.5);
	
	TF1 *uniform = new TF1("uniform", "0*x+1",0,1);	
	
	TF1 *funkcje2[2] = {normal,uniform};
	
	
	TH1D *hist2 = new TH1D("hist2","Splot 2",40,-5,5);
	splot(funkcje2, 2, hist2, 10000);
	
	c1->cd(2);
	hist2->Draw();
	
}
