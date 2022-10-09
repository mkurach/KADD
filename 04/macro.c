void macro() {
	 double x1min = 1.5, x1max = 5.0;
	double x2min = 0.0, x2max = 3.0;
	double x3min = 4.0, x3max = 16.0;
	
	TCanvas *c1 = new TCanvas("c1", "Ex1", 1000,1000);
	c1->Divide(2,2);
	TH2D *h12 = new TH2D("h12","Hist12",100,x1min,x1max,100,x2min,x2max);
	TH2D *h13 = new TH2D("h13","Hist13",100,x1min,x1max,100,x3min,x3max);
	TH2D *h23 = new TH2D("h23","Hist23",100,x2min,x2max,100,x3min,x3max);

	TH1D *h1 = new TH1D("h1","Hist1",100,x1min,x1max);
	TH1D *h2 = new TH1D("h2","Hist2",100,x2min,x2max);
	TH1D *h3 = new TH1D("h3","Hist3",100,x3min,x3max);
	
	
	ifstream ifile1,ifile2,ifile3;
	ifile1.open("Dane1.dat");
	ifile2.open("Dane2.dat");
	ifile3.open("Dane3.dat");
	double val1,val2,val3;
	while(ifile1>>val1 && ifile2>>val2  && ifile3>>val3)
	{
		h12->Fill(val1,val2);
		h13->Fill(val1,val3);
		h23->Fill(val2,val3);
		h1->Fill(val1);
		h2->Fill(val2);
		h3->Fill(val3);
		
	}
	ifile1.close();
	ifile2.close();
	ifile3.close();
	
	c1->cd(1);
	h12->Draw("colz");
	c1->cd(2);
	h13->Draw("colz");
	c1->cd(3);
	h23->Draw("colz");
	
	TMatrixD Cx(3,3);
	Cx(0,0)=h1->GetRMS()*h1->GetRMS();
	Cx(0,1)=h12->GetCovariance(1,2);
	Cx(0,2)=h13->GetCovariance(1,2);
	
	Cx(1,0)=h12->GetCovariance(1,2);
	Cx(1,1)=h2->GetRMS()*h2->GetRMS();
	Cx(1,2)=h23->GetCovariance(1,2);
	
	Cx(2,0)=h13->GetCovariance(1,2);
	Cx(2,1)=h23->GetCovariance(1,2);
	Cx(2,2)=h3->GetRMS()*h3->GetRMS();
	
	Cx.Print();
	
	TMatrixD T(2,3);
	T(0,0)=2;
	T(0,1)=5;
	T(0,2)=1;
	T(1,0)=0.5;
	T(1,1)=4;
	T(1,2)=0;
	
	TMatrixD Tt(3,2);
	Tt.Transpose(T);
		
	TMatrixD Cy(2,2);
	
	Cy=T*Cx*Tt;
	Cy.Print();
	
	double X1=h12->GetMean(1);
	double X2=h12->GetMean(2);
	double X3=h23->GetMean(2);

	
	cout<<"Y1="<<2*X1+5*X2+X3<<endl;
	cout<<"Y2="<<3+0.5*X1+4*X2<<endl;
	cout<<"u(Y1)="<<TMath::Sqrt(Cy(0,0))<<endl;
	cout<<"u(Y2)="<<TMath::Sqrt(Cy(1,1))<<endl;
	cout<<"rho(Y1,Y2)="<<Cy(1,0)/(TMath::Sqrt(Cy(0,0))*TMath::Sqrt(Cy(1,1)))<<endl;
	cout<<"rho(Y2,Y1)="<<h12->GetCorrelationFactor(2,1)<<endl;
	
}
