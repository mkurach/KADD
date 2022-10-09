double func(double *x, double *params){
	if (x[0]<=1 && x[0]>=0 && x[1]<=1 && x[1]>=0){
		return params[0]*TMath::Power(x[0], params[1]) * TMath::Power(x[1], params[2]);
	}
	return 0;
}

void macro(){
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = 1;
	int nparams = 3;
	TF2 * fun1 = new TF2("fun1", func, xmin, xmax, ymin, ymax, nparams);
	double c = 0.1666667;
	fun1 -> SetParameters(1/c, 1, 2);
	double I = fun1 -> Integral(xmin, xmax, ymin, ymax);
	cout<<"Integral: "<<I<<endl;
	cout<<"Normalization factor c="<<1/c<<endl;
	
	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
	c1 -> Divide(2, 2);
	
	c1 -> cd(1);
	fun1-> SetTitle("Gestosc");
	fun1->DrawCopy("surf1");
	
	c1 -> cd(2);
	TGraph2D *t2d = new TGraph2D();
	int counter = 0;
	for (double i=0; i<=1; i+=0.1){
		for (double j=0; j<=1; j+=0.1){
			double F = fun1 -> Integral(0, i, 0, j);
			t2d -> SetPoint(counter, i, j, F);
			counter++;
		}
	}
	t2d ->SetTitle("Dystrybuanta");
	t2d ->Draw("surf1");

	TGraph *tx = new TGraph();
	int counter2 = 0;
	for (double i=0; i<=1; i+=0.01){
		double F = fun1 -> Integral(i, i+0.0001, 0, 1);
		tx -> SetPoint(counter2, i, F);
		counter2++;
	}
	c1->cd(3);
	tx -> SetTitle("Gestosc brzegowa g(x)");
	tx -> GetXaxis() -> SetTitle("x");
	tx -> GetYaxis() -> SetTitle("g(x)");
	tx -> Draw("APL");
	
	TGraph *ty = new TGraph();
	int counter3 = 0;
	for (double i=0; i<=1; i+=0.01){
		double F = fun1 -> Integral(0, 1, 0, i+0.0001);
		ty -> SetPoint(counter3, i, F);
		counter3++;
	}
	c1->cd(4);
	ty -> SetTitle("Gestosc brzegowa h(y)");
	ty -> GetXaxis() -> SetTitle("y");
	ty -> GetYaxis() -> SetTitle("h(y)");
	ty -> Draw("APL");
	

	
}
