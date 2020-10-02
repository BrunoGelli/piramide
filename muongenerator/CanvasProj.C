void CanvasProj()
{
//=========Macro generated from canvas: CanvasProj/CanvasProj
//=========  (Fri Aug 14 19:47:23 2020) by ROOT version 6.20/06
   TCanvas *CanvasProj = new TCanvas("CanvasProj", "CanvasProj",67,57,800,802);
   CanvasProj->Range(-2.19897,-1.080066,2.80103,4.387685);
   CanvasProj->SetFillColor(0);
   CanvasProj->SetBorderMode(0);
   CanvasProj->SetBorderSize(2);
   CanvasProj->SetLogx();
   CanvasProj->SetLogy();
   CanvasProj->SetGridx();
   CanvasProj->SetGridy();
   CanvasProj->SetTickx(1);
   CanvasProj->SetTicky(1);
   CanvasProj->SetFrameBorderMode(0);
   CanvasProj->SetFrameBorderMode(0);
   
   TH1D *DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1 = new TH1D("DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1","Detected momentum spectrum for 34.8 degrees",10000,0,200);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(11,3327);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(18,3599);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(28,3136);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(45,2693);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(72,2562);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(116,2028);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(185,1522);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(299,869);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(480,492);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(776,212);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(1246,70);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(2011,30);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(3236,7);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetBinContent(5251,2);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetEntries(20549);
   
   TPaveStats *ptstats = new TPaveStats(0.65,0.7,0.95,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(3);
   ptstats->SetFillColor(0);
   ptstats->SetLineWidth(2);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Detected momentum spectrum for 34.8 degrees");
   ptstats_LaTex->SetTextSize(0.046);
   ptstats_LaTex = ptstats->AddText("Entries = 20549  ");
   ptstats_LaTex = ptstats->AddText("Mean  =   1.79");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  3.451");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetLineWidth(3);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetMarkerColor(2);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->SetMarkerStyle(20);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetXaxis()->SetTitle("Energy (GeV)");
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetXaxis()->SetLabelFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetXaxis()->SetTitleOffset(1);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetXaxis()->SetTitleFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetYaxis()->SetTitle("entries");
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetYaxis()->SetLabelFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetYaxis()->SetTitleFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetZaxis()->SetLabelFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetZaxis()->SetTitleOffset(1);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->GetZaxis()->SetTitleFont(42);
   DetectedsPmomentumsPspectrumsPforsP34dO8sPdegrees__1->Draw("E");
   
   TPaveText *pt = new TPaveText(0.15,0.9346129,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Detected momentum spectrum for 34.8 degrees");
   pt->Draw();
   CanvasProj->Modified();
   CanvasProj->cd();
   CanvasProj->SetSelected(CanvasProj);
}
