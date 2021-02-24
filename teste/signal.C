
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


void signal()
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
 
 	Double_t initial = 15;

 	std::vector<TString> fileNames;
 	fileNames.push_back("OutPut_t0.root");
 	fileNames.push_back("OutPut_t1.root");
 	fileNames.push_back("OutPut_t2.root");
 	fileNames.push_back("OutPut_t3.root");
 	fileNames.push_back("OutPut_t4.root");
 	fileNames.push_back("OutPut_t5.root");
 	fileNames.push_back("OutPut_t6.root");
	
	std::vector<double> dataX;
	std::vector<double> dataY;
	std::vector<double> dataZ;
	std::vector<double> dataT;
	std::vector<double> dataE;

	int size = 0; 
	int nentries = 0;
	
	Double_t x;
	Double_t y;
	Double_t z;
	Double_t t;
	Double_t e;

	TFile *f;
	TTree *T;

 	for (int i = 0; i < fileNames.size(); ++i)
 	{
 		
		f = new TFile(fileNames[i],"READ");
		
		if ( f->IsOpen() )
		{
			printf("File opened successfully\n");
		} 
		else 
		{
			printf("Error! Invalid File Name\n");
			return;
		}

		T = (TTree*)f -> Get("ntuple");

		T->SetBranchAddress("x",&x);
		T->SetBranchAddress("y",&y);
		T->SetBranchAddress("z",&z);
		T->SetBranchAddress("t",&t);
		T->SetBranchAddress("energy",&e);
		
		nentries = (int)T->GetEntries();

		for (int i = 0; i < nentries; ++i)
		{
			T->GetEntry(i);
			dataX.push_back(x);
			dataY.push_back(y);
			dataZ.push_back(z);
			dataT.push_back(t);
			dataE.push_back(e);
		}

 	}

 	size = dataE.size();

 	printf("There were %d events.\n", size);

	std::vector<double> wasVisited;
	std::vector<double> howMany;




	TH1D *simpleX	= new TH1D("simpleX", "simpleX", 100, -60, 60);
	TH1D *simpleY	= new TH1D("simpleY", "simpleY", 100, -60, 60);
	TH1D *simpleZ	= new TH1D("simpleZ", "simpleZ", 100, -60, 60);
	TH1D *simpleT	= new TH1D("simpleT", "simpleT", 200, 200, 400);

	for (Int_t i=0; i<size; i++)
	{
		simpleX->Fill(dataX[i]);
		simpleY->Fill(dataY[i]);
		simpleZ->Fill(dataZ[i]);
		simpleT->Fill(dataT[i]);

		if (dataZ[i] == 0)
		{
			break;
			size = i;
		}
		// printf("%3.3lf %3.3lf %3.3lf %3.3lf %3.3lf\n",x[i],y[i],z[i],t[i], e[i]);
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

	simpleT->SetTitle("Tempo de voo");
	simpleT->GetXaxis()->SetTitle("Tempo (ns)");
	simpleT->GetYaxis()->SetTitle("Contagem de eventos");
	simpleT->SetLineWidth(1);


	TCanvas *Simple = new TCanvas("Simple", "Simple plots", 1600, 900);
	Simple->Divide(2,2);

	Simple->cd(1);
	simpleX->Draw();

	Simple->cd(2);
	simpleY->Draw();

	Simple->cd(3);
	simpleZ->Draw();

	Simple->cd(4);
	gPad-> SetLogy();
	simpleT->Draw();


	//*********************************************************************************
	
	TCanvas *C_Frente = new TCanvas("C_Frente", "Parede frontal",0,0,1800,900);
	C_Frente->cd();

	gPad->SetRightMargin(.45);	
	TH2D* Frente = new TH2D("Distribuicao na base da pir#hat{a}mide", "Distribuicao na base da pir#hat{a}mide", 60, -60, 60, 60, -60, 60);
	
	Int_t bin = 0;

	for (int i = 0; i < size; ++i)
	{
			Frente->Fill(dataX[i],dataY[i]);
	}

	for (int i = 0; i < size; ++i)
	{
		bin = Frente->FindBin(dataX[i],dataY[i]);
		howMany.push_back(Frente->GetBinContent(bin));
	}

	Frente->Reset("ICES");

	for (int i = 0; i < size; ++i)
	{
		bin = Frente->FindBin(dataX[i],dataY[i]);
		Frente->SetBinContent(bin, dataE[i]/(howMany[i]) + Frente->GetBinContent(bin));
	}

	// Frente->Smooth(10,"k3a");

	Frente->SetTitle("Mean energy of the muons at the pyramid base");
	Frente->GetXaxis()->SetTitle("Distance (m)");
	Frente->GetYaxis()->SetTitle("Distance (m)");
	Frente->GetZaxis()->SetTitle("Mean energy (GeV)");
	Frente->GetZaxis()->SetTitleOffset(1);
	Frente->SetLineWidth(1);
	Frente->Draw("colz");
	// Frente->SetMaximum(max);




	return;
} 

