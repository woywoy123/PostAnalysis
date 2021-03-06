#include<TStyle.h>
#include<TH1F.h>
#include<TLegend.h>
#include<TCanvas.h>
#include<RooRealVar.h>
#include<RooDataHist.h>
#include<RooAddPdf.h>
#include<RooPlot.h>
#include<PostAnalysis/BaseFunctions.h>


void Populate(std::vector<TH1F*> Hists, TCanvas* can, TLegend* len, ELineStyle Style);
void PlotHists(TH1F* Hist, TCanvas* can); 
void PlotHists(std::vector<TH1F*> Hists, TCanvas* can); 
void PlotHists(std::vector<TH1F*> Hists, std::vector<TString> Legend_Titles, TCanvas* can); 
void PlotHists(TH1F* Data, std::vector<TH1F*> truth, std::vector<TH1F*> prediction, TCanvas* can); 
void PlotHists(TH1F* Data, std::vector<TH1F*> truth, TCanvas* can); 
void RatioPlot(TH1F* H1, TH1F* H2, TCanvas* can); 
void PlotRooFit(RooAddPdf model, RooRealVar* Domain, RooDataHist* Data);
void GeneratePlot(TH1F* H, TString Title, TCanvas* can, Color_t color, ELineStyle style, TString DrawOption, float Intensity); 
TLegend* GenerateLegend(std::vector<TH1F*> Hist_V, TCanvas* can); 
void GenerateRatioPlot(TH1F* H1, TH1F* H2, TCanvas* can, TString Title, TString Xaxis);



