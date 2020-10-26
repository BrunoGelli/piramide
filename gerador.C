#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "TH1F.h"
#include "TVirtualFFT.h"
#include "TRandom.h"
#include "TF1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include <math.h> 
#include <stdio.h>
#include <string.h>
#include <TSpectrum.h>
#include <TSpectrumTransform.h>

void MakeTable();
void graph(vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6, vector<double> v7, vector<double> v8);
void setstyle();

std::vector<double> XrandVec;
std::vector<double> YrandVec;
std::vector<double> ZrandVec;

std::vector<double> XdirVec;
std::vector<double> YdirVec;
std::vector<double> ZdirVec;

std::vector<double> ChargeVec;
std::vector<double> ErandVec;

const double AngleProb[9] = 
{
  0.00, 
  5.30, 
  20.50, 
  45.42, 
  65.91, 
  81.62, 
  90.65, 
  97.09, 
  100.00
};

const double Angle[9] = 
{
    0, 
    5, 
    15, 
    25, 
    35, 
    45, 
    55, 
    65, 
    75
};


const double MuonMomentum[15] = 
{
    0.131, 
    0.213, 
    0.342, 
    0.553, 
    0.881, 
    1.43, 
    2.30, 
    3.69, 
    5.96, 
    9.59, 
    15.5, 
    24.9, 
    40.2, 
    64.7, 
    105
};

const double MuonMomentumPDF[16][8] =
{
    {0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000}, 
    {0.16246305, 0.22237624, 0.20566954, 0.18329773, 0.15851571, 0.22614293, 0.19653444, 0.22972740}, 
    {0.31558499, 0.39058550, 0.38678123, 0.35339988, 0.33077922, 0.33766611, 0.38621707, 0.44291657}, 
    {0.47939276, 0.54712745, 0.52377692, 0.49357547, 0.48440640, 0.47411048, 0.54252774, 0.60525251}, 
    {0.65362573, 0.69380418, 0.68168568, 0.65204567, 0.61612543, 0.60579791, 0.63647344, 0.70672237}, 
    {0.78709814, 0.81432919, 0.79549050, 0.77271476, 0.74325199, 0.71868978, 0.73853798, 0.76530462}, 
    {0.88587360, 0.89709085, 0.88837214, 0.86830248, 0.84396858, 0.82764590, 0.83325496, 0.82651851}, 
    {0.94493897, 0.95049451, 0.94469256, 0.93045821, 0.91768968, 0.89849454, 0.89730864, 0.88560645}, 
    {0.97678529, 0.97928826, 0.97569497, 0.96779938, 0.96198512, 0.95245070, 0.94419399, 0.92556005}, 
    {0.99156674, 0.99173342, 0.99129457, 0.98695369, 0.98470662, 0.97905569, 0.97236501, 0.95982537}, 
    {0.99720840, 0.99726319, 0.99661551, 0.99603256, 0.99427399, 0.99166781, 0.98800569, 0.97884433}, 
    {0.99921790, 0.99919442, 0.99905022, 0.99893223, 0.99814648, 0.99697768, 0.99602866, 0.99121313}, 
    {0.99979967, 0.99975669, 0.99966404, 0.99960721, 0.99938279, 0.99912690, 0.99839609, 0.99707577}, 
    {0.99995328, 0.99992841, 0.99989832, 0.99992719, 0.99979350, 0.99978665, 0.99935420, 0.99894743}, 
    {0.99998917, 0.99997239, 0.99996162, 0.99999078, 0.99995974, 0.99995286, 0.99975763, 0.99976741}, 
    {1.00000000, 1.00000000, 1.00000000, 1.00000000, 1.00000000, 1.00000000, 1.00000000, 1.00000000}
};

void gerador()
{
    srand(1115529);

    long int size = 550000;

    setstyle();

    for (int i = 0; i < size; ++i)
    {
        MakeTable();
    }

    graph(XrandVec,YrandVec,ZrandVec,XdirVec,YdirVec,ZdirVec,ErandVec,ChargeVec);


    ofstream myfile ("lookup.hh");

    if (myfile.is_open())
    {
        myfile << "// PosX (m), PosY (m), PosZ (m), DirX, DirY, DirZ, P (GeV/c), charge" << endl;
        myfile << "const double lookup[" << size+1 << "][" << 8 << "] =" << endl;
        myfile << "{" << endl;


        for (int i = 0; i < size; ++i)
        {
            myfile << "    {"   <<  XrandVec[i]     << ", ";
            myfile <<               YrandVec[i]     << ", ";
            myfile <<               ZrandVec[i]     << ", ";
            myfile <<               XdirVec[i]      << ", ";
            myfile <<               YdirVec[i]      << ", ";
            myfile <<               ZdirVec[i]      << ", ";
            myfile <<               ErandVec[i]     << ", ";
            myfile <<               ChargeVec[i]    << "}," << endl;
        }

        myfile << "    {0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}" << endl;

        myfile << "};" << endl;
        myfile.close();
    }
    else cout << "Unable to open file";




    return;
}

void MakeTable()
{


    double  Zenith          = 0;                     // initialize the Zenith variable
    double  ZenithSelector  = rand() % 100;          // a random number between 0 and 100
    int     ZenithIndex     = 0;                     // initialize the index for the angle selector     

    for (int i = 1; i < 9; ++i)
    {
        if(AngleProb[i-1] <= ZenithSelector && AngleProb[i] > ZenithSelector)
        {
            Zenith = Angle[i]*3.1415/180; // Zenith receives the angle in radians
            ZenithIndex = i;              // ZenithIndex receive the angle index
            break;
        }
    }

    double theta = rand()%100;
    theta = (theta/100) *2*3.1415; //random between 0 and 2pi

    double raio  = 100.0;

    double xrand = 0;//rand() % 30000 - 15000;
    double yrand = 0;//rand() % 30000 - 15000;
    double zrand = -33;//rand() % 30000 - 15000;

    // xrand = xrand / 15000;
    // yrand = yrand / 15000;
    // zrand = -32 + zrand / 15000;


    XrandVec.push_back(raio*sin(Zenith)*cos(theta)  + xrand); 
    YrandVec.push_back(raio*sin(Zenith)*sin(theta)  + yrand); 
    ZrandVec.push_back(raio*cos(Zenith)             + zrand); 

    double mod =    pow(raio*sin(Zenith)*cos(theta) , 2) + 
                    pow(raio*sin(Zenith)*sin(theta) , 2) + 
                    pow(raio*cos(Zenith)            , 2);

    mod = pow(mod,0.5);

    XdirVec.push_back(-(raio*sin(Zenith)*cos(theta) )/mod);
    YdirVec.push_back(-(raio*sin(Zenith)*sin(theta) )/mod);
    ZdirVec.push_back(-(raio*cos(Zenith)            )/mod);


    double  Energy = 0;


    while(Energy < 16)
    {
        double  EnergySelector  = (rand() % 10000000) ;

        for (int i = 1; i < 16; ++i)
        {
            if (MuonMomentumPDF[i-1][ZenithIndex-1] <= EnergySelector/10000000 && MuonMomentumPDF[i][ZenithIndex-1] > EnergySelector/10000000)
            {
                Energy = MuonMomentum[i];
                break;
            }
        }
       
    }

    ErandVec.push_back(Energy); // changer here



    double chargeSelector = rand() % 10000;

    chargeSelector = chargeSelector / 100;
  
   

    if (chargeSelector > 45.45)
    {
        ChargeVec.push_back(-1);
    }
    else 
    {
        ChargeVec.push_back(1);
    }
    

    return;
}

void graph(vector<double> v1, vector<double> v2, vector<double> v3, vector<double> v4, vector<double> v5, vector<double> v6, vector<double> v7, vector<double> v8)
{

    TH1D *simpleX   = new TH1D("simpleX", "simpleX", 200, -100, 100);
    TH1D *simpleY   = new TH1D("simpleY", "simpleY", 200, -100, 100);
    TH1D *simpleZ   = new TH1D("simpleZ", "simpleZ", 200,    0, 110);
    
    TH1D *dirX      = new TH1D("dirX", "dirX", 200, -1.0, 1);
    TH1D *dirY      = new TH1D("dirY", "dirY", 200, -1.0, 1);
    TH1D *dirZ      = new TH1D("dirZ", "dirZ", 200, -1.1, 0);


    TH1D *simpleE   = new TH1D("simpleE", "simpleE", 30000, 5, 200);
    TH1D *simpleC   = new TH1D("simpleC", "simpleC", 22, -2, 2);

    for (Int_t i=0; i < v1.size(); i++)
    {
        simpleX->Fill(v1[i]);
        simpleY->Fill(v2[i]);
        simpleZ->Fill(v3[i]);

        dirX->Fill(v4[i]);
        dirY->Fill(v5[i]);
        dirZ->Fill(v6[i]);

        simpleE->Fill(v7[i]);
        simpleC->Fill(v8[i]);
    }
    
    simpleX->SetTitle("Position - X axis");
    simpleX->GetXaxis()->SetTitle("Position (m)");
    simpleX->GetYaxis()->SetTitle("#");
    simpleX->SetLineWidth(1);

    simpleY->SetTitle("Position - Y axis");
    simpleY->GetXaxis()->SetTitle("Position (m)");
    simpleY->GetYaxis()->SetTitle("#");
    simpleY->SetLineWidth(1);

    simpleZ->SetTitle("Position - Z axis");
    simpleZ->GetXaxis()->SetTitle("Position (m)");
    simpleZ->GetYaxis()->SetTitle("#");
    simpleZ->SetLineWidth(1);

    dirX->SetTitle("Direction - X axis");
    dirX->GetXaxis()->SetTitle("normalized units");
    dirX->GetYaxis()->SetTitle("#");
    dirX->SetLineWidth(1);
    
    dirY->SetTitle("Direction - Y axis");
    dirY->GetXaxis()->SetTitle("normalized units");
    dirY->GetYaxis()->SetTitle("#");
    dirY->SetLineWidth(1);

    dirZ->SetTitle("Direction - Z axis");
    dirZ->GetXaxis()->SetTitle("normalized units");
    dirZ->GetYaxis()->SetTitle("#");
    dirZ->SetLineWidth(1);

    simpleE->SetTitle("Momentum");
    simpleE->GetXaxis()->SetTitle("Momentum (GeV/c)");
    simpleE->GetYaxis()->SetTitle("#");
    simpleE->SetLineWidth(1);

    simpleC->SetTitle("Muon charge");
    simpleC->GetXaxis()->SetTitle("charge");
    simpleC->GetYaxis()->SetTitle("#");
    simpleC->SetLineWidth(1);


    TCanvas *Simple = new TCanvas("Simple", "Simple plots", 1600, 900);
    Simple->Divide(3,3);

    Simple->cd(1);
    simpleX->Draw();

    Simple->cd(2);
    simpleY->Draw();

    Simple->cd(3);
    simpleZ->Draw();

    Simple->cd(4);
    dirX->Draw();

    Simple->cd(5);
    dirY->Draw();

    Simple->cd(6);
    dirZ->Draw();

    Simple->cd(7);
    gPad-> SetLogx();
    gPad-> SetLogy();
    simpleE->Draw();

    Simple->cd(8);
    simpleC->Draw();

    return;
}

void setstyle()
{
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
    gStyle->SetStatY(0.9);
    gStyle->SetStatX(0.95);
    gStyle->SetStatW(0.3);
    gStyle->SetStatH(0.2);
    gStyle->SetStatBorderSize(3);

    return;
}