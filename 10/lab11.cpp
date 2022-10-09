#include <vector>

using namespace std;

double poziom = 0.01;

double cdf(double *x, double *param)
{
	if(x[0]>0)
	{
		return TMath::Power(x[0], param[0]/2-1)*TMath::Exp(-x[0]/2)/(TMath::Gamma(param[0]/2)*TMath::Power(2, param[0]/2));
	}
	return 0;
}


TF1 *cdffun = new TF1("fun1", cdf, 0, 8, 2);

double chi2_cdf(double *x, double *param)
{
	if(x[0]>0)
	{
		cdffun->SetParameter(0, param[0]);
		return cdffun->Integral(0, x[0]);
	}
	return 0;
}

double wielomian(double *x, double *params) 
{
	double value = 0;
	for(int v = 0; v <= params[0]; v++)
	{
		value += params[v+1]*pow(x[0], v);
	}
	return value;
}


bool testChi2(double T, double alpha, int ndf, double &SS)
{
    TF1 *kw = new TF1(" ", chi2_cdf, 0, 50, 2);
    kw -> SetParameter(0,ndf);
    kw -> SetParameter(1, poziom);
    SS = kw -> GetX(1. - alpha);
    if(T < SS) {return true;} else {return false;}
}

void MNK(vector<double> ts, vector<double> ys, int n, int r, vector<double> err, double *wsp)
{
	r++;
	TMatrixD *A = new TMatrixD(ts.size(), r); //macierz A
	
	vector<vector<double>> ret;
	
	for(int i=0; i<ts.size(); i++) //wypełniamy A
	{
		for(int j=0; j<r; j++)
		{
			(*A)(i, j)=TMath::Power(ts[i], j);
		}
	}
	
	//A.Print();
	
	int size = ts.size();
	
	TMatrixD *y = new TMatrixD(ts.size(), 1);
	TMatrixD *sigma = new TMatrixD(ts.size(), 1);
	TMatrixD *G = new TMatrixD(ts.size(), ts.size());
	TMatrixD *H = new TMatrixD(ts.size(), ts.size());
	
	for(int i=0; i<size; i++) //macierz y
	{
		(*y)(i, 0) = ys.at(i);
	}
	
	for(int i=0; i<size; i++) //sigma
	{
		(*sigma)(i, 0) = TMath::Sqrt(ys.at(i));
	}
	
	//sigma->Print();
	
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(i==j)
			{
				(*G)(i,j) = 1/TMath::Power((*sigma)(i, 0), 2);
				(*H)(i,j) = 1/((*sigma)(i, 0));
			}
			else
			{
				(*G)(i,j)=0;
				(*H)(i,j)=0;
			}
		}
	}
	//cout<<"H"<<endl;
	//H.Print();
	//cout<<"G"<<endl;
	//G.Print();
	
	
	
	TMatrixD *A_prim = new TMatrixD(*H, TMatrixD::kMult, *A);
	TMatrixD *y_prim = new TMatrixD(*H, TMatrixD::kMult, *y);
	
	TMatrixD *A_prim_T = new TMatrixD(TMatrixD::kTransposed, *A_prim);
	
	TMatrixD *aaa = new TMatrixD(*A_prim_T, TMatrixD::kMult, *A_prim);
	
	*aaa=aaa->Invert();
	
	TMatrixD *tmp = new TMatrixD(*A_prim_T, TMatrixD::kMult, *y_prim);
	
	TMatrixD *x_falka = new TMatrixD(*aaa, TMatrixD::kMult, *tmp);
	
	//x_falka.Print();
	
	TMatrixD *eta_falka = new TMatrixD(*A, TMatrixD::kMult, *x_falka);
	
	//eta_falka->Print();
	
	double M = 0;
	
	for(int j=0; j<n; j++)
	{
		M+=TMath::Power(((*y)(j,0)-(*eta_falka)(j,0))/(*sigma)(j,0) ,2);
	}
	
	//cout<<"M = "<<M<<endl;
	
	
	for(int n = 0; n < r; n++) 
	{
		for(int m = 0; m < r; m++)
		{
			if(m == n) 
			{
				err.push_back(TMath::Sqrt((*aaa)(n,m)));
			}
		}
	}
	
	for(int z = 0; z < x_falka -> GetNrows(); z++) 
	{
		wsp[z] = (*x_falka)(z,0);
	}
	
	for(int h = 0; h < x_falka -> GetNrows(); h++) 
    {
        if(h == 0)
        {
            cout << "Wielomian stopnia: " << r-1<< endl; 
            cout << "M = " <<M<< endl;
            cout << "NDF = " << size - r << endl;
            cout << "Poziom istotnosci = " << poziom << endl; 
            double kwant;
			if(testChi2(M, poziom, size - r - 1, kwant))
			{
				cout << "Kwantyl = " << kwant << endl; cout << "Stopień " << r-1 << ": " << "Akceptujemy" << endl;
			} 
            else 
            {
				cout << "Kwantyl = " << kwant << endl; cout << "Stopień " << r-1 << ": " << "Odrzucamy" << endl;
			}
        } 
        cout << "x_" << h << " = " << (*x_falka)(h, 0) << " +/- " << err.at(h) << endl;
    }
    cout << "===========================" << endl;
}


int lab11(void)
{
	TCanvas *c1 = new TCanvas("c1","c1",500,500);
	TLegend *leg = new TLegend(0.1,0.9,0.4,0.6);
	
	vector<double> ts;
	vector<double> ys;
	vector<double> err;
	double wsp[6];
	
	std::ifstream inFile;
	inFile.open("data11.dat");
	double x_val, y_val;
	while(inFile>>x_val>>y_val)
	{
	ts.push_back(x_val);
	ys.push_back(y_val);
	}
	inFile.close();
	
	for(int r = 0; r<6; r++)
	{
		MNK(ts, ys, ts.size(), r, err, wsp);
		if(r == 0)
        {
			TGraphErrors *gr = new TGraphErrors(ts.size(),&ts[0],&ys[0],0,&err[0]);
			gr -> SetMarkerColor(kBlack);
			gr -> SetMarkerStyle(kFullCircle);
			gr -> SetTitle("Wyniki dopasowan MNK; t, cos(#Theta); y, liczba obserwacji");
			gr -> Draw("ALP");
		}
		
		TF1 *fa0 = new TF1(" ",wielomian,-1,1,r+2);
        fa0 -> SetParameter(0,r);
        for(int o = 0; o < r+1; o++) 
		{
			fa0 -> SetParameter(o+1, wsp[o]);
		} 
		
        fa0 -> SetLineColor(r+1);
		
        string x = "st"+to_string(r);
        const char *tab = x.c_str();
        leg -> AddEntry(fa0,tab,"l");
        fa0 -> Draw("SAME");
	}
	leg -> Draw();
	
	return 0;
}
