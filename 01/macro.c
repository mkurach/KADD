void macro()
{
	TF1 *fun1 = new TF1("fun","1./[0]*TMath::Exp(-x/[0])",0,50);
	fun1->SetParameter(0,6);
	
	TCanvas *c1 = new TCanvas("c1", "c1", 800,800);
	c1->Divide(2);
	
	c1->cd(1);	
	fun1->Draw();
	
	c1->cd(2);
	fun1->DrawIntegral();
	
	
	cout<<"Integral"<<fun1->Integral(0,100)<<endl;
	cout<<"P(5<X<10) TF1: "<<fun1->Integral(5,10)<<endl;
	cout<<"Mean value TF1: "<<fun1->Mean(0,100)<<endl;
	cout<<"Variance TF1: "<<fun1->Variance(0,100)<<endl;
	cout<<"Mode: "<<fun1->GetMaximumX(0,100)<<endl;
	
	const int nq = 3;
	double xq[nq] = {0.25,0.5,0.75};
	double yq[nq];
	fun1->GetQuantiles(nq,yq,xq);
	
	cout<<"Lower quartile: "<<yq[0]<<endl;
	cout<<"Median: "<<yq[1]<<endl;
	cout<<"Upper quartile: "<<yq[2]<<endl;

	
	
	
}
