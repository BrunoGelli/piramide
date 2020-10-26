
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


void signal()
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

	std::vector<int> dataEvent;
	std::vector<double> dataX;
	std::vector<double> dataY;
	std::vector<double> dataZ;
	std::vector<double> dataT;
	std::vector<double> dataE;

	int size = 0; 
	int nentries = 0;
	
	Int_t event;
	Double_t x;
	Double_t y;
	Double_t z;
	Double_t t;
	Double_t e;

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

		T->SetBranchAddress("evt",&event);
		T->SetBranchAddress("x",&x);
		T->SetBranchAddress("y",&y);
		T->SetBranchAddress("z",&z);
		T->SetBranchAddress("t",&t);
		T->SetBranchAddress("energy",&e);
		
		nentries = (int)T->GetEntries();

		for (int i = 0; i < nentries; ++i)
		{
			T->GetEntry(i);
			dataEvent.push_back(event);
			dataX.push_back(x);
			dataY.push_back(y);
			dataZ.push_back(z);
			dataT.push_back(t);
			dataE.push_back(e);
		}

 	}

 	// checks how many events were read
 	
 	size = dataEvent.size();
 	printf("There were %d events.\n", size);

 	// now we create a preliminary plot of each axis to see if anything went wrong

	TH1D *simpleX	= new TH1D("simpleX", "simpleX", 100, -6, 6);
	TH1D *simpleY	= new TH1D("simpleY", "simpleY", 100, -6, 6);
	TH1D *simpleZ	= new TH1D("simpleZ", "simpleZ", 100, -6, 6);
	TH1D *simpleT	= new TH1D("simpleT", "simpleT", 200, 200, 400);

	for (Int_t i=0; i<size; i++)
	{
		simpleX->Fill(dataX[i]);
		simpleY->Fill(dataY[i]);
		simpleZ->Fill(dataZ[i]);
		simpleT->Fill(dataT[i]);

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

	simpleT->SetTitle("Tempo de voo");
	simpleT->GetXaxis()->SetTitle("Tempo (ns)");
	simpleT->GetYaxis()->SetTitle("Contagem de eventos");
	simpleT->SetLineWidth(1);

	//create a canvas and draw the histograms

	// TCanvas *Simple = new TCanvas("Simple", "Simple plots", 1600, 900);
	// Simple->Divide(2,2);

	// Simple->cd(1);
	// simpleX->Draw();

	// Simple->cd(2);
	// simpleY->Draw();

	// Simple->cd(3);
	// simpleZ->Draw();

	// Simple->cd(4);
	// gPad-> SetLogy();
	// simpleT->Draw();


	//*********************************************************************************
	

	TH2D* Frente = new TH2D("Distribuicao na base da pir#hat{a}mide", "Distribuicao na base da pir#hat{a}mide", 8, -0.2, 0.2, 8, -0.2, 0.2);
	
	Int_t bin = 0;
	Int_t number_of_bins = TMath::Power(TMath::Sqrt(Frente->GetSize()), 2);
	cout << number_of_bins << endl;
	// std::vector<TH1D *> EnergyDist;


	for (int i = 0; i < size; ++i)
	{
		Frente->Fill(dataX[i],dataY[i]);
	}
	
	for (int i = 0; i < number_of_bins; ++i)
	{
		TH1D *h = new TH1D(Form("histogram of detected energy for the bin number %d", i), Form("histogram of detected energy for the bin number %d", i), 100, -5, 100); 

		h->GetXaxis()->SetTitle("Energy (GeV)");
		h->GetYaxis()->SetTitle("entries");
		h->SetLineWidth(3);

		EnergyDist.push_back(h); 
	}


	for (int i = 0; i < size; ++i)
	{
		bin = Frente->FindBin(dataX[i],dataY[i]);
		EnergyDist[bin]->Fill(dataE[i]);
		// EnergyDist[bin]->SetMaximum(150);
	}
// 
	Frente->Reset("ICES");

	TCanvas *c = new TCanvas();
	c->cd();

	std::vector<double> chi2;
	std::vector<double> ratio;

	for (int i = 0; i < number_of_bins; ++i)
	{		
		if (EnergyDist[i]->GetEntries() > 5)
		{	
			TF1 *f1 = new TF1("f1","[0]*TMath::Landau(-x,[1],[2])", 0, 20);

			f1->SetParameters(9.2e2,-EnergyDist[i]->GetMean(),0.139);
			
			TFitResultPtr r = EnergyDist[i]->Fit(f1,"MRQS");
			
			ratio.push_back(-(r->Parameter(1))/EnergyDist[i]->GetMean());
			chi2.push_back(r->Chi2()/EnergyDist[i]->GetEntries());
		}

		Frente->SetBinContent(i, EnergyDist[i]->GetMean());
		Frente->SetBinError(i, EnergyDist[i]->GetMeanError());
		
	}


	TCanvas *C_Frente = new TCanvas("C_Frente", "Parede frontal",0,0,1800,900);
	C_Frente->cd();
	gPad->SetRightMargin(.45);	

	Frente->SetTitle("Mean energy of the muons at the pyramid base");
	Frente->GetXaxis()->SetTitle("Distance (m)");
	Frente->GetYaxis()->SetTitle("Distance (m)");
	Frente->GetZaxis()->SetTitle("Mean energy (GeV)");
	Frente->GetZaxis()->SetTitleOffset(1);
	Frente->SetLineWidth(1);
	Frente->Draw("colz");

	C_Frente->Update();

	Frente->SetHighlight();
	C_Frente->HighlightConnect("Highlight2(TVirtualPad*,TObject*,Int_t,Int_t)");




	// vamos implementar a saida txt no formato: Evento BinXY(Plano 1) BinXY(Plano 2) BinXY(Plano 3)
	int Total = 500000;
	int saida[Total][4];
	int eventFinder = 0;
	double altura = 0;
	int soma = 0;

	for (int i = 0; i < Total; ++i)
	{
		saida[i][0] = i;
		saida[i][1] = -1;
		saida[i][2] = -1;
		saida[i][3] = -1;
	}

	for (int i = 0; i < dataEvent.size(); ++i)
	{
		eventFinder = dataEvent[i];
		altura = TMath::Nint(dataZ[i]*10);
		altura = altura/10;
		
		if (altura > -32.5)
		{
			saida[eventFinder][1] = Frente->FindBin(dataX[i],dataY[i])-10;
		}
		else if (altura >= -33.0 && altura < -32.5 )
		{
			saida[eventFinder][2] = Frente->FindBin(dataX[i],dataY[i])-10;

		}
		else if (altura < -33.0)
		{
			saida[eventFinder][3] = Frente->FindBin(dataX[i],dataY[i])-10;
		}
		else printf("ops... %lf %lf\n", dataZ[i], altura);
	}
	
	FILE* ptr = fopen("DataOut.txt","w");

	if (ptr==NULL)
	{
		printf("no such file.");
		return;
	}

	fprintf(ptr, "Evento BinXY(Plano 1) BinXY(Plano 2) BinXY(Plano 3)\n");

	for (int i = 0; i < Total; ++i)
	{
		if (saida[i][1] != -1)
		{
			soma++;
		}

		if (saida[i][2] != -1)
		{
			soma++;
		}

		if (saida[i][3] != -1)
		{
			soma++;
		}

		if (soma>=2)
		{
			fprintf(ptr, "%d %d %d %d\n", saida[i][0], saida[i][1], saida[i][2], saida[i][3]);
		}

		soma = 0;
	}

	fclose(ptr);

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

	// gStyle->SetOptFit(0011);

	if (!CanvasProj) 
	{
		TCanvas *CanvasProj = new TCanvas("CanvasProj", "CanvasProj", 0, 0, 800, 800);
		CanvasProj->cd();
		EnergyDist[F->GetBin(xhb,yhb)]->SetTitle(Form("histogram of detected energy for the binX %d and binY %d", xhb, yhb));
		EnergyDist[F->GetBin(xhb,yhb)]->Draw("");

	}
	else
	{
		CanvasProj->cd();
		// CanvasProj->SetLogy();
		EnergyDist[F->GetBin(xhb,yhb)]->SetTitle(Form("histogram of detected energy for the binX %d and binY %d", xhb, yhb));
		EnergyDist[F->GetBin(xhb,yhb)]->Draw("");
		
		CanvasProj->Update();
	}

	if (!F->IsHighlight())
	{ 
		if (CanvasProj) delete CanvasProj;
		return;
	}

}