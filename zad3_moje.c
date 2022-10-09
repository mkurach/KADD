#include <iostream>
#include <vector>
#define alfa 0.005
#define n_pom 7

void read_data(string nazwa, vector<double> &x, vector<double> &y, vector<double> &niepewnosc)
{
    double val1,val2;
    ifstream ifile;
	ifile.open("dane.dat");
    ifile >> val1 >> val2;
    while(!ifile.eof()) {
        x.push_back(val1); 
        y.push_back(val2); 
        niepewnosc.push_back(0.6); 
        ifile >> val1 >> val2;
    }
	ifile.close();
}  

double gestosc(double *x, double *params) {
    return 1./(TMath::Gamma(params[0])*pow(2,params[0]))*pow(x[0],params[0]-1)*TMath::Exp(-0.5*x[0]);
}

double dyst(double *x, double *params) {
    TF1 *f = new TF1("",gestosc,0,50,1); 
    f -> SetParameter(0,params[0]*0.5); 
    return f -> Integral(params[1],x[0]);
}

bool testChi2(double T, double alpha, int ndf, double &kwantyl)
{
    TF1 *fun = new TF1(" ", dyst, 0, 50, 2);
    fun -> SetParameter(0,ndf);
    fun -> SetParameter(1,0.01);
    kwantyl = fun -> GetX(1. - alpha);
    if(T < kwantyl) {
        return true;
    } 
    else {
        return false;
    }
}

void dopasuj(int stopien, int n, vector<double> &x_i,vector<double> &y_i, vector<double> &sigma_i, double *wsp, double *wsp_sigma)
{
    read_data("dane.dat", x_i, y_i, sigma_i);
    TMatrixD *MacierzA = new TMatrixD(n,stopien+1);
    TMatrixD *MacierzC = new TMatrixD(n,1);
    TMatrixD *MacierzG_y = new TMatrixD(n,n);
    TMatrixD *MacierzH = new TMatrixD(n,n);

    for(int i = 0; i < n; i++) //dla każdego wiersza, czyli pomiaru
    {
        (*MacierzA)(i,0) = 1; 
        (*MacierzC)(i,0) = y_i[i];
        for(int j = 1; j < stopien+1; j++){
            (*MacierzA)(i,j) = pow(x_i[i],j); //kolumny, kolejne potęgi
        }
        for(int jj = 0; jj < n; jj++) { //kolumny 
            if(i == jj) { //na diagonali
                (*MacierzG_y)(i,jj) = 1/(pow(sigma_i[jj],2)); 
                (*MacierzH)(i,jj) = 1/(sigma_i[jj]);
            }
            else {
                (*MacierzG_y)(i,jj) = 0; 
                (*MacierzH)(i,jj) = 0;
            }
        }
    }
    
    TMatrixD *MacierzAprim = new TMatrixD(n,stopien+1);
    MacierzAprim -> Mult(*MacierzH,*MacierzA);

    TMatrixD *MacierzCprim = new TMatrixD(n,1);
    MacierzCprim -> Mult(*MacierzH,*MacierzC);

    TMatrixD *MacierzAprimT = new TMatrixD(TMatrixD::kTransposed,*MacierzAprim);
    TMatrixD *MacierzCalyNawias = new TMatrixD(*MacierzAprimT, TMatrixD::kMult, *MacierzAprim);
    TMatrixD MacierzNawiasOdw = MacierzCalyNawias -> Invert();
    TMatrixD *MacierzAprimT_Cprim = new TMatrixD(*MacierzAprimT, TMatrixD::kMult, *MacierzCprim);
    TMatrixD *MacierzX = new TMatrixD(MacierzNawiasOdw, TMatrixD::kMult, *MacierzAprimT_Cprim);

    TMatrixD *MacierzEta = new TMatrixD(*MacierzA, TMatrixD::kMult, *MacierzX);
    TMatrixD *MacierzYminusEtaT = new TMatrixD(TMatrixD::kTransposed,*MacierzC - *MacierzEta);
    TMatrixD *MacierzRazyGy = new TMatrixD(*MacierzYminusEtaT, TMatrixD::kMult,*MacierzG_y);
    TMatrixD *MacierzM = new TMatrixD(*MacierzRazyGy, TMatrixD::kMult, *MacierzC - *MacierzEta);

    for(int n = 0; n < stopien+1; n++) {
        for(int m = 0; m < stopien+1; m++){
            if(m == n) {
                wsp_sigma[m] = TMath::Sqrt((MacierzNawiasOdw)(n,m));
            }
        }
    }

    for(int z = 0; z < MacierzX -> GetNrows(); z++) {
        wsp[z] = (*MacierzX)(z,0);
    }

    for(int kk = 0; kk < MacierzX -> GetNrows(); kk++) {
        if(kk == 0) {
            cout << "Wielomian stopnia: " << stopien << endl; 
            cout << "M = " << (*MacierzM)(0,0) << endl;
            cout << "NDF = " << n-stopien-1 << endl;
            cout << "Alfa = " << alfa << endl; 
            double kwant;
            if(testChi2((*MacierzM)(0,0), alfa, n-stopien-1, kwant)) {
                cout << "Kwantyl = " << kwant << endl; 
                cout << "Stopień " << stopien << ": " << "Akceptujemy" << endl;
            } 
            else {
                cout << "Kwantyl = " << kwant << endl;
                cout << "Stopień " << stopien << ": " << "Odrzucamy" << endl;
            }
        } 
        cout << "x_" << kk << " = " << wsp[kk] << " +- " << wsp_sigma[kk] << endl;
    }
    cout << "===========================" << endl;


}

double wielomian(double *x, double *params) 
{
	double suma = 0;
	for(int v = 0; v <= params[0]; v++) {
        suma += params[v+1]*pow(x[0], v);
    }
	return suma;
}

int zad3_moje(void)
{
    TCanvas *can1 = new TCanvas("can1","zad3",900,800);
    TLegend *leg = new TLegend(0.1,0.9,0.4,0.6);
    vector<double> x,y,niep;
    double wspolczynniki[6],wspolczynniki_sigma[6];


    for(int p = 0; p <= 5; p++) {

        dopasuj(p,n_pom,x,y,niep,wspolczynniki,wspolczynniki_sigma);

        if(p == 0) {
            TGraphErrors *gr = new TGraphErrors(x.size(),&x[0],&y[0],0,&niep[0]);
            gr -> SetMarkerColor(kBlack); 
            gr -> SetMarkerStyle(kFullCircle);
            gr -> SetTitle("Wyniki dopasowan MNK; t, cos#Theta; y, liczba obserwacji");
            gr -> Draw("ALP");
        }

        TF1 *fun = new TF1(" ",wielomian,0,15,p+2);
        fun -> SetParameter(0,p);
        for(int o = 0; o < p+1; o++) {
            fun -> SetParameter(o+1, wspolczynniki[o]);
        } 

        fun -> SetLineColor(p+1);
        const char *tab = ("st."+to_string(p)).c_str();
        leg -> AddEntry(fun,tab,"l");
        fun -> Draw("SAME");
    }
    leg -> Draw();
    return 0;
}