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

void printout();

std::vector<double> xrandVec;
std::vector<double> yrandVec;
std::vector<double> zrandVec;

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
    1.31E-01, 
    2.13E-01, 
    3.42E-01, 
    5.53E-01, 
    8.81E-01, 
    1.43E+00, 
    2.30E+00, 
    3.69E+00, 
    5.96E+00, 
    9.59E+00, 
    1.55E+01, 
    2.49E+01, 
    4.02E+01, 
    6.47E+01, 
    1.05E+02
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

    for (int i = 0; i < 10000; ++i)
    {
        printout();
    }




    TH1D *simpleX   = new TH1D("simpleX", "simpleX", 200, -100, 100);
    TH1D *simpleY   = new TH1D("simpleY", "simpleY", 200, -100, 100);
    TH1D *simpleZ   = new TH1D("simpleZ", "simpleZ", 200, 0, 120);

    for (Int_t i=0; i<xrandVec.size(); i++)
    {
        simpleX->Fill(xrandVec[i]);
        simpleY->Fill(yrandVec[i]);
        simpleZ->Fill(zrandVec[i]);
    }
    
    simpleX->SetTitle("Eixo X");
    simpleX->GetXaxis()->SetTitle("Distancia (cm)");
    simpleX->GetYaxis()->SetTitle("#");
    simpleX->SetLineWidth(1);

    simpleY->SetTitle("Eixo Y");
    simpleY->GetXaxis()->SetTitle("Distancia (cm)");
    simpleY->GetYaxis()->SetTitle("#");
    simpleY->SetLineWidth(1);

    simpleZ->SetTitle("Eixo Z");
    simpleZ->GetXaxis()->SetTitle("Distancia (cm)");
    simpleZ->GetYaxis()->SetTitle("#");
    simpleZ->SetLineWidth(1);


    TCanvas *Simple = new TCanvas("Simple", "Simple plots", 1600, 900);
    Simple->Divide(2,2);

    Simple->cd(1);
    simpleX->Draw();

    Simple->cd(2);
    simpleY->Draw();

    Simple->cd(3);
    simpleZ->Draw();

    return;
}

void printout()
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

    double xrand = rand() % 300 - 150;
    double yrand = rand() % 300 - 150;
    double zrand = rand() % 300 - 150;

    xrand = xrand / 20;
    yrand = yrand / 20;
    zrand = zrand / 20;


    xrandVec.push_back(raio*sin(Zenith)*cos(theta)  + xrand); 
    yrandVec.push_back(raio*sin(Zenith)*sin(theta)  + yrand); 
    zrandVec.push_back(raio*cos(Zenith)             + zrand); 


    // cout << raio*sin(Zenith)*cos(theta) + xrand << " " << raio*sin(Zenith)*sin(theta)  + yrand << " " << raio*cos(Zenith)  + zrand ;    
    // cout <<  xrand/20 << " " <<  yrand/20 << " " << zrand/20 ;

    double  Energy          = 0;
    double  EnergySelector  = (rand() % 100) ;

    // cout << " " << EnergySelector/100 << endl;


    for (int i = 1; i < 16; ++i)
    {
        if (MuonMomentumPDF[i-1][ZenithIndex-1] <= EnergySelector/100 && MuonMomentumPDF[i][ZenithIndex-1] > EnergySelector/100)
        {
            Energy = MuonMomentum[i];
            break;
        }
    }

    // cout << " " << Energy << endl;

    return;
}