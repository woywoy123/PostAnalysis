#include<PostAnalysis/UnitTest.h>
#include<PostAnalysis/BaseFunctions.h>
#include<PostAnalysis/Plotting.h>
#include<PostAnalysis/Constants.h>

void BaseFunctionTest::Subtraction()
{
    DistributionGenerators D; 
    BaseFunctions B;
    Plotting P; 

    // Example parameters
    std::vector<float> LDau = {1, 0.9, 0.1};
    std::vector<float> ratio = {0.5, 0.5, 0.5, 0.5};
    float min = 0; 
    float max = 20; 
    int bins = 500; 
    int npts = 500000;
    std::vector<TString> trk_2 = {"dEdx_ntrk_2_ntru_1", "dEdx_ntrk_2_ntru_2", "dEdx_ntrk_2_ntru_3", "dEdx_ntrk_2_ntru_4"};

    // Make Hists
    std::vector<TH1F*> trk2_N = B.MakeTH1F(trk_2, bins, min, max); 
    TH1F* Data = new TH1F("Data", "Data", bins, min, max);      
    D.Landau(trk2_N, ratio, LDau, npts, min, max);
    
    // Get Closure values and fill data 
    std::vector<float> CLS2 = B.ClosureAndData(trk2_N, Data); 
    
    B.Subtraction(trk2_N, Data, 2, CLS2);
    
    TCanvas* can = P.PlotHists(trk2_N[1], Data); 
    can -> Draw(); 
}

void BaseFunctionTest::NormalFit(std::vector<TH1F*> Hists, TH1F* Data, std::vector<float> CL, float min, float max )
{
  BaseFunctions B; 

  B.Normalize(Hists);
  RooRealVar* x = new RooRealVar("x", "x", min, max); 
 
  std::vector<float> Begin(Constants::trk_2.size(), 1); 
  std::vector<float> End(Constants::trk_2.size(), Data -> Integral()); 
  
  std::vector<RooRealVar*> Var = B.RooVariables(Constants::trk_2, Begin, End);
  std::vector<RooHistPdf*> Hist = B.RooPDF(Hists, x);
  RooDataHist* data = B.RooData(Data, x);

  RooAddPdf model("Model", "Model", B.RooList(Hist), B.RooList(Var));
  model.fitTo(*data);

  Plotting P;
  TCanvas* can = P.PlotHists(model, x, Hist, data);
  can -> Draw(); 
}

void BaseFunctionTest::Convolve(TH1F* Hist1, TH1F* Hist2, TH1F* Expectation)
{
  BaseFunctions B; 
  Plotting P;
   
  TH1F* Conv = (TH1F*)Expectation -> Clone("Conv"); 
  B.ConvolveHists(Hist1, Hist2, Conv);
  B.Normalize(Conv);
  Conv -> Scale(Expectation -> Integral());
  TCanvas* can = P.PlotHists(Conv, Expectation);
  can -> Draw();
}

void BaseFunctionTest::Deconvolve(TH1F* Trk2, TH1F* Trk1, float offset, int iter)
{
  BaseFunctions B;
  Plotting P;
   
  std::vector<float> Data_V = B.TH1FDataVector(Trk2, offset);
  std::vector<float> deconv(Data_V.size(), 0.5); 
  for (int i(0); i < iter; i++)
  {
    deconv = B.LucyRichardson(Data_V, deconv, deconv, 1);  
  }  
  
  TH1F* Hist = new TH1F("Hist", "Hist", 500, 0, 20); 
  B.ToTH1F(deconv, Hist);
 
  P.PlotHists(Hist, Trk1); 


}

void DerivedFunctionTest::NormalFit(std::vector<TH1F*> Hists, TH1F* Data, std::vector<float> CL, float min, float max)
{
  DerivedFunctions DF; 
  BaseFunctions B; 
  std::vector<RooRealVar*> Vars = DF.FitToData(Hists, Data, min, max);
  std::vector<float> pred = B.Ratio(Vars, Data);  
  float distance = B.ChiSquare(pred, CL);
  std::cout << distance << std::endl;
  B.PredictionTruthPrint(CL, pred); 
}
