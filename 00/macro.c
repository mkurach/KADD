int macro() {
	TF1 *fun1 = new TF1("fun1","TMath::Sin(x)",0,2*TMath::Pi());
	TF1 *fun2 = new TF1("fun2","TMath::Cos(x)",0,2*TMath::Pi());

	TCanvas *c1 = new TCanvas("c1","Ex1",10,10,500,200);
	c1->Divide(2,2);

	c1->cd(1);
	fun1->Draw();

	c1->cd(2);
	fun2->DrawCopy();

	c1->cd(3);
	fun1->Draw();
	fun2->Draw("same");
	fun2->SetLineColor(kMagenta);

	TH1D *h1 = new TH1D("h1","histogram",6,1,6);
	h1->SetBinContent(1,2);
	h1->SetBinContent(2,1);
	h1->SetBinContent(3,5);
	h1->SetBinContent(4,4);
	h1->SetBinContent(5,10);
	h1->SetBinContent(6,12);
	c1->cd(4);
	h1->Draw();

	TCanvas *c2 = new TCanvas("c2","Ex2",10,10,500,200);
	TGraph *gr = new TGraph();
	gr->SetPoint(0,1,2);
	gr->SetPoint(1,2,1);
	gr->SetPoint(2,3,5);
	gr->SetPoint(3,4,4);
	gr->SetPoint(4,5,10);
	gr->SetPoint(5,6,12);
	gr->SetMarkerStyle(29);
	gr->SetMarkerSize(6);
	gr->SetMarkerColor(kYellow);	
	//gr->GetXAxis()->SetTitle("blabla");
	gr->Draw("AP");
 }


