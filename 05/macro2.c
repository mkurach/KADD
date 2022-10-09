void macro2() {
	
	
	
	TH2D *hist1 = new TH2D("hist1", "histogram1",100, 0, 1, 100, 0, N);
	TH2D *hist2 = new TH2D("hist2", "histogram2",100, 0, 1, 100, 0, N);
	TH2D *hist3 = new TH2D("hist3", "histogram3",100, 0, 1, 100, 0, N);
	ifstream ifile1, ifile2, ifile3;
	ifile1.open("dane1.dat");
	ifile2.open("dane2.dat");
	ifile3.open("dane3.dat");
	
	int i = 0;
	double xprev =0;
	double x;
	while(ifile1>>x){
		if(i>0) 
			hist1->Fill(x,xprev);
		xprev=x;
		i++;
		
	}
	i=0;
	while(ifile2>>x){
		if(i>0) 
			hist2->Fill(xh,xprev);
		xprev=x;
		i++;
		
	}
	i = 0;
	while(ifile3>>x){
		if(i>0) 
			hist3->Fill(xh,xprev);
		xprev=x;
		i++;
		
	}
	
	
	
	
	
	TCanvas *c1 = new TCanvas("c1", "Ex1", 1000,1000);
	c1->Divide(4);
	c1->cd(1);
	hist1->Draw("colz");
	
	c1->cd(2);
	hist2->Draw("colz");
	
	c1->cd(3);
	hist3->Draw("colz");
	
	}
