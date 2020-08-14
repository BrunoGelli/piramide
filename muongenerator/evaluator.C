
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


void evaluator()
{

	// define diversos padrões de plot

    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadGridX(1);
    gStyle->SetPadGridY(1);
	gStyle->SetStatY(0.9);
	gStyle->SetStatX(0.95);
	gStyle->SetStatW(0.3);
	gStyle->SetStatH(0.2);
	gStyle->SetStatBorderSize(3);
	gStyle->SetLineWidth(2);
	gStyle->SetLineColor(1);
	// gStyle->SetOptFit(0011);

	// define os nomes dos arquivos em quais 
	// os dados estão salvos

 	std::vector<TString> fileNames;
 	fileNames.push_back("OutPut_t0.root");
 	fileNames.push_back("OutPut_t1.root");
 	fileNames.push_back("OutPut_t2.root");
 	fileNames.push_back("OutPut_t3.root");
 	fileNames.push_back("OutPut_t4.root");
 	fileNames.push_back("OutPut_t5.root");
 	fileNames.push_back("OutPut_t6.root");
	
 	// cria vetores de dados e variáveis auxiliares

	std::vector<double> dataX;
	std::vector<double> dataY;
	std::vector<double> dataZ;
	std::vector<double> dataT;
	std::vector<double> dataE;
	std::vector<double> dataA;

	int size = 0; 
	int nentries = 0;
	
	Double_t x;
	Double_t y;
	Double_t z;
	Double_t t;
	Double_t e;
	Double_t a;

	TFile *f;
	TTree *T;

	// neste for os arquivos são abertos e lidos

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

		T->SetBranchAddress("x", &x);
		T->SetBranchAddress("y", &y);
		T->SetBranchAddress("z", &z);
		T->SetBranchAddress("t", &t);
		T->SetBranchAddress("energy", &e);
		T->SetBranchAddress("theta",  &a);
		
		nentries = (int)T->GetEntries();

		for (int i = 0; i < nentries; ++i)
		{
			T->GetEntry(i);
			dataX.push_back(x);
			dataY.push_back(y);
			dataZ.push_back(z);
			dataT.push_back(t);
			dataE.push_back(e);
			dataA.push_back(a);
		}

 	}

 	// checks how many events were read
 	
 	size = dataE.size();
 	printf("There were %d events.\n", size);

 	// now we create a preliminary plot of each axis to see if anything went wrong

	TH1D *simpleX	= new TH1D("simpleX", "simpleX", 100, -60, 60);
	TH1D *simpleY	= new TH1D("simpleY", "simpleY", 100, -60, 60);
	TH1D *simpleZ	= new TH1D("simpleZ", "simpleZ", 100, -60, 60);
	TH1D *simpleA	= new TH1D("simpleA", "simpleA", 100,   0, 100);

	for (Int_t i=0; i<size; i++)
	{
		simpleX->Fill(dataX[i]);
		simpleY->Fill(dataY[i]);
		simpleZ->Fill(dataZ[i]);
		simpleA->Fill(dataA[i]);

		if (dataZ[i] == 0)
		{
			// checks if detected Z coordenate is 0. If it is true, something went wrong
			printf("Something went wrong\n");
			size = i;
			break;
		}
	}
	
	// define some histogram formating atributes 

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

	simpleA->SetTitle("Tempo de voo");
	simpleA->GetXaxis()->SetTitle("Tempo (ns)");
	simpleA->GetYaxis()->SetTitle("Contagem de eventos");
	simpleA->SetLineWidth(1);

	//create a canvas and draw the histograms

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
	simpleA->Draw();


	//*********************************************************************************
	

	TH1I* Frente = new TH1I("Distribuicao angular", "Distribuicao angular", 100, 0, 99);
	
	Int_t bin = 0;
	Int_t number_of_bins = Frente->GetSize();
	cout << number_of_bins << endl;

	for (int i = 0; i < size; ++i)
	{
			Frente->Fill(dataA[i]);
	}

	for (int i = 0; i < number_of_bins; ++i)
	{
		TH1D *h = new TH1D(Form("Detected momentum spectrum for %d degrees", (int)Frente->GetBinCenter(i)), Form("Detected momentum spectrum for %d degrees", (int)Frente->GetBinCenter(i)), 10000, 0, 200); 

		h->GetXaxis()->SetTitle("Energy (GeV)");
		h->GetYaxis()->SetTitle("entries");
		h->SetLineWidth(3);
		h->SetLineColor(1);
		h->SetMarkerColor(2);
		h->SetMarkerStyle(20);
		h->SetLineColor(1);

		EnergyDist.push_back(h); 
	}


	for (int i = 0; i < size; ++i)
	{
		bin = Frente->FindBin(dataA[i]);
		EnergyDist[bin]->Fill(dataE[i]);
	}

	TCanvas *c = new TCanvas();
	c->cd();


	TCanvas *C_Frente = new TCanvas("C_Frente", "Parede frontal",0,0,1800,900);
	C_Frente->cd();
	// gPad->SetRightMargin(.45);	

	Frente->SetTitle("");
	Frente->GetXaxis()->SetTitle("Angle (degrees)");
	Frente->GetYaxis()->SetTitle("Entries");
	Frente->SetLineColor(1);
	Frente->SetLineWidth(3);
	Frente->Draw("");

	C_Frente->Update();

	Frente->SetHighlight();
	C_Frente->HighlightConnect("Highlight2(TVirtualPad*,TObject*,Int_t,Int_t)");


	return;
} 

void Highlight2(TVirtualPad *pad, TObject *obj, Int_t xhb, Int_t yhb)
{
	auto F = (TH1D *)obj;

	if(!F)
	{
		printf("Something went wrong\n");
		return;	
	} 

	auto CanvasProj = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("CanvasProj");

	gStyle->SetOptFit(0000);

	if (!CanvasProj) 
	{
		TCanvas *CanvasProj = new TCanvas("CanvasProj", "CanvasProj", 0, 0, 800, 800);
		CanvasProj->cd();
		EnergyDist[F->GetBin(xhb)]->SetTitle(Form("Detected momentum spectrum for %d degrees", (int)F->GetBinCenter(F->GetBin(xhb))));
		EnergyDist[F->GetBin(xhb)]->Draw("E");

	}

	else
	{
		CanvasProj->cd();
		EnergyDist[F->GetBin(xhb)]->SetTitle(Form("Detected momentum spectrum for %d degrees", (int)F->GetBinCenter(F->GetBin(xhb))));
		EnergyDist[F->GetBin(xhb)]->Draw("E");
		
		CanvasProj->Update();
	}

	if (!F->IsHighlight())
	{ 
		if (CanvasProj) delete CanvasProj;
		return;
	}

	gPad-> SetLogx();
	gPad-> SetLogy();
}