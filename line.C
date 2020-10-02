
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

void Highlight2(TVirtualPad *pad, TObject *obj, Int_t xhb, Int_t yhb);

std::vector<TH1D *> EnergyDist;

	// teste de comentário
void line()
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
	
	TCanvas *C_Frente = new TCanvas("C_Frente", "Parede frontal",0,0,900,900);
	C_Frente->cd();

	// gPad->SetRightMargin(.45);	

	int number_of_bins = 120;

	TH1D* Frente = new TH1D("Distribuicao na base da pir#hat{a}mide", "Distribuicao na base da pir#hat{a}mide", number_of_bins, 0, 60);

	for (int i = 0; i < size; ++i)
	{
		Frente->Fill(dataX[i]);
	}


	
	for (int i = 0; i < number_of_bins; ++i)
	{
		TH1D *h = new TH1D(Form("histogram of detected energy for the bin number %d", i), Form("histogram of detected energy for the bin number %d", i), 500, 0, 20); 

		h->GetXaxis()->SetTitle("Energy (GeV)");
		h->GetYaxis()->SetTitle("Distance (m)");
		h->SetLineWidth(3);

		EnergyDist.push_back(h); 
	}


	Int_t bin = 0;
	int max = 0;
	int min = 0;

	for (int i = 0; i < size; ++i)
	{
		bin = Frente->FindBin(dataX[i]);
		EnergyDist[bin]->Fill(dataE[i]);
	}

	Frente->Reset("ICES");

	for (int i = 0; i < number_of_bins; ++i)
	{		
		Frente->SetBinContent(i, EnergyDist[i]->GetMean());
		Frente->SetBinError(i, 50*EnergyDist[i]->GetMeanError());

		if (i==90)
		{
			for (int j = 0; j < number_of_bins/2; ++j)
			{
				max = EnergyDist[i]->GetBinContent(j);
				min = EnergyDist[i]->GetBinContent(number_of_bins-j);

				EnergyDist[i]->SetBinContent(j,min);
				EnergyDist[i]->SetBinContent(number_of_bins-j,max);

			}

			EnergyDist[i]->Draw("");
			// TF1 *f1 = new TF1("f1","[0]*TMath::Landau(-x,[1],[2])",0,20);
			// f1->SetParameters(9.2e2,1.7e1,0.139);
			// EnergyDist[i]->Fit(f1,"r");
		}

	}

	// Frente->Smooth(10,"k3a");

	Frente->SetTitle("Mean energy of the muons at the pyramid base");
	Frente->GetXaxis()->SetTitle("Distance (m)");
	Frente->GetYaxis()->SetTitle("Energy (GeV)");
	Frente->GetZaxis()->SetTitleOffset(1);
	Frente->SetLineWidth(1);
	// Frente->Draw("");
	// Frente->SetMaximum(max);

	C_Frente->Update();

	// printf("tes\n");
	// Frente->SetHighlight();
 //   	printf("tes\n");
	// C_Frente->HighlightConnect("Highlight2(TVirtualPad*,TObject*,Int_t,Int_t)");
	// printf("tes\n");
	return;
} 


void Highlight2(TVirtualPad *pad, TObject *obj, Int_t xhb, Int_t yhb)
{
	auto Frente = (TH1D *)obj;

	if(!Frente)
	{
		printf("caguei\n");
		return;	
	} 

	auto CanvasProj = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("CanvasProj");
	printf("======================%d\n",xhb );
	if (!Frente->IsHighlight())
	{ // after highlight disabled
		if (CanvasProj) delete CanvasProj;
		return;
	}


	if (!CanvasProj) 
	{
		CanvasProj = new TCanvas("CanvasProj", "CanvasProj", 505, 0, 600, 600);
		CanvasProj->cd();
		EnergyDist[xhb]->Draw("");
	}
	CanvasProj->cd();

	EnergyDist[xhb]->Draw("");
	
	CanvasProj->GetPad(1)->Modified();
	CanvasProj->Update();

}
