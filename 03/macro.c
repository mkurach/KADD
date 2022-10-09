double function1 (double *x, double *params) {
	if ( 0<=x[0]*x[1]<= TMath::Pi())
		 return params[0]*TMath::Sin(x[0]*x[1]);
	return 0;
}



void macro() {
	double xmin = 0;
	double ymin = 0;
	double xmax = TMath::Pi()/2;
	double ymax = TMath::Pi()/2;
	
	TCanvas *c1 = new TCanvas("c1", "Ex1", 1000,1000);
	c1->Divide(2,2);
	
	int nparams = 1;
	TF2 *fun1 = new TF2("fun1",function1,xmin,xmax,ymin,ymax,nparams);
	fun1->SetParameter(0,1/1.18412);
	
	double I = fun1->Integral(xmin, TMath::Pi()/2, ymin, TMath::Pi()/2);
	cout<<I<<endl;
	
	double xbins=20, ybins = 20;
	
	TH2D *hist1 = new TH2D("hist1", "histogram", xbins, xmin, xmax, ybins, ymin, ymax);
	
	double tx,ty;
	for (int i = 0; i<10000; i++) {
		fun1->GetRandom2(tx,ty);
		hist1->Fill(tx,ty);
	}
	
	double Ihist= hist1->Integral();
	hist1->Scale(1/Ihist);
	c1->cd(1);
	hist1->Draw("lego1");
	
	TH2D *hist2 = new TH2D("hist2", "dystrybuanta",xbins,xmin,xmax, ybins, ymin, ymax);
	for (int x = 1; x<xbins; x++) {
		for (int y=1; y<ybins; y++) {
			hist2->SetBinContent(x,y,hist1->Integral(xmin,x,ymin,y));
		}
	}
	c1->cd(2);
	hist2->Draw("lego1");
	
	c1->cd(3);
	TH1D *hist3 = hist2->ProjectionX("projectionx",1, ybins);
	hist3->Draw();
	
	c1->cd(4);
	TH1D *hist4 = hist2->ProjectionY("projectiony",1, xbins);
	hist4->Draw();
	
	cout<<"E(X): "<<hist1->GetMean(1)<<endl;
	cout<<"E(Y): "<<hist1->GetMean(2)<<endl;
	
	cout<<"Sigma(X): "<<hist1->GetRMS(1)<<endl;
	cout<<"Sigma(Y): "<<hist1->GetRMS(2)<<endl;
	
	cout<<"Covariance: "<<hist1->GetCovariance(1,2)<<endl;
	
	cout<<"Correlation factor: "<<hist1->GetCorrelationFactor(1,2)<<endl;
	
	
	
}
