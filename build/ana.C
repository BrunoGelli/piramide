

	#include "TH1D.h"
	#include <time.h>
	#include "TVirtualFFT.h"
	#include "TRandom.h"
	#include "TF1.h"
	#include "TCanvas.h"
	#include "TStyle.h"
	#include "TMath.h"
	#include <math.h> 
	#include <stdlib.h>
	#include <stdio.h>





void ana()
{


	FILE* ptr = fopen("FiltroOutPut.txt","r");

	if (ptr==NULL)
	{
		printf("no such file.");
		return;
	}

	double x[200], y[200];
	int i=0;

	while (fscanf(ptr,"%lf\n",&y[i])!= EOF)
	{
		// printf3("%lf\n", y[i] );
		i++;
	}
	x[0]=0.20;
	for (int j = 1; j < i; ++j)
	{
		x[j]=j*0.01+0.2;
		// printf("%lf\n",x[j]);
	}

	fclose(ptr);

	TGraph* Gconv1 = new TGraph(i,x,y);

// for (int i = counter1; i > -1; i--)
// {
// 	if (ey1[i] > 2)
// 	{
// 		Gconv1->RemovePoint(i);
// 	}
// 	if (ey2[i] > 20 || A2[i] < 1E-5)
// 	{
// 		Gconv2->RemovePoint(i);
// 	}
// }

	Gconv1->SetMarkerStyle(7);

	auto mg2 = new TMultiGraph;

	mg2->SetTitle("X-ARAPUCA Efficiency;Bar thickness (cm);Efficiency");
	mg2->Add(Gconv1,"P");

	mg2-> Draw("A");

	return;

} 
