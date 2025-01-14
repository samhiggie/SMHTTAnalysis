#include "TROOT.h"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/CMS_lumi.C"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/tdrstyle.C"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/MakeRatioPlot.cc"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/MakeStackErrors.cc"
#include <string>

void DrawControlPlot(string var, bool UseEmbedded,string axisLabel)
{
  setTDRStyle();

  writeExtraText = true;
  extraText = "Preliminary";
  lumi_sqrtS = "60 fb^{-1}, 13 TeV";
  
  TFile* HistoFile;
  if(!UseEmbedded)
    {
      HistoFile = new TFile("TemporaryFiles/ControlRegion_2018_MC.root","READ");
    }
  else
    {
      HistoFile = new TFile("TemporaryFiles/ControlRegion_2018.root","READ");
    }

  TCanvas* Canvas = new TCanvas("Canvas",var.c_str(),550,550);
  Canvas->SetTickx();
  Canvas->SetTicky();

  gStyle->SetOptStat(0);
  TH1F* Data = (TH1F*) HistoFile->Get(("Data_2018_"+var).c_str());
  TH1F* Data_Fake = (TH1F*) HistoFile->Get(("Fake_2018_"+var).c_str());
  TH1F* DYTT;
  if (UseEmbedded) DYTT = (TH1F*) HistoFile->Get(("Embedded_2018_genmatch_tt_"+var).c_str());
  else DYTT = (TH1F*) HistoFile->Get(("DY_2018_genmatch_tt_"+var).c_str());
  TH1F* DYMM = (TH1F*) HistoFile->Get(("DY_2018_genmatch_low_"+var).c_str());
  TH1F* TTToHadronic = (TH1F*) HistoFile->Get(("TTToHadronic_2018_"+var).c_str());
  TH1F* TTTo2L2Nu = (TH1F*) HistoFile->Get(("TTTo2L2Nu_2018_"+var).c_str());
  TH1F* TTToSemiLeptonic = (TH1F*) HistoFile->Get(("TTToSemiLeptonic_2018_"+var).c_str());  
  TH1F* WW = (TH1F*) HistoFile->Get(("WW_2018_"+var).c_str());
  TH1F* WZ = (TH1F*) HistoFile->Get(("WZ_2018_"+var).c_str());
  TH1F* ZZ = (TH1F*) HistoFile->Get(("ZZ_2018_"+var).c_str());
  TH1F* ST_tW_top = (TH1F*) HistoFile->Get(("ST_tW_top_2018_"+var).c_str());
  TH1F* ggH = (TH1F*) HistoFile->Get(("ggH_2018_"+var).c_str());
  TH1F* VBF = (TH1F*) HistoFile->Get(("VBF_2018_"+var).c_str());
  TH1F* WHPlus = (TH1F*) HistoFile->Get(("WHPlus_2018_"+var).c_str());
  TH1F* WHMinus = (TH1F*) HistoFile->Get(("WHMinus_2018_"+var).c_str());
  TH1F* ZH = (TH1F*) HistoFile->Get(("ZH_2018_"+var).c_str());

  TH1F* TTFinal = (TH1F*) TTToHadronic->Clone();
  TTFinal->Add(TTTo2L2Nu);
  TTFinal->Add(TTToSemiLeptonic);

  TH1F* VVFinal = (TH1F*) WW->Clone();
  VVFinal->Add(WZ);
  VVFinal->Add(ZZ);
  VVFinal->Add(ST_tW_top);
  
  TH1F* VHFinal = (TH1F*) WHPlus->Clone();
  VHFinal->Add(WHMinus);
  VHFinal->Add(ZH);

  TH1F* Other = (TH1F*) VHFinal->Clone();
  Other->Add(ggH);
  Other->Add(VBF);
  Other->Add(VVFinal);

  TH1F* AllHiggs = (TH1F*) VHFinal->Clone();
  AllHiggs->Add(ggH);
  AllHiggs->Add(VBF);

  Data->SetMarkerStyle(20);
  Data->Sumw2();
  
  Data_Fake->SetLineColor(kBlack);
  Data_Fake->SetFillColor(TColor::GetColor("#ffccff"));//FakesColor->GetNumber());
    
  DYTT->SetLineColor(kBlack);
  DYTT->SetFillColor(TColor::GetColor("#ffcc66"));

  DYMM->SetLineColor(kBlack);
  DYMM->SetFillColor(TColor::GetColor("#4496c8"));
  
  TTFinal->SetLineColor(kBlack);
  TTFinal->SetFillColor(TColor::GetColor("#9999cc"));

  Other->SetLineColor(kBlack);
  Other->SetFillColor(TColor::GetColor("#12cadd"));
  
  AllHiggs->SetLineColor(kRed);
  AllHiggs->Scale(30);

  std::cout<<"Fake Background Integral: "<<Data_Fake->Integral()<<std::endl;

  THStack* BackgroundStack = new THStack("BackgroundStack","BackgroundStack");  
  BackgroundStack->Add(Data_Fake,"hist");  
  BackgroundStack->Add(TTFinal,"hist");
  BackgroundStack->Add(DYMM,"hist");
  BackgroundStack->Add(Other,"hist");
  BackgroundStack->Add(DYTT,"hist");  

  TH1F* BackgroundStack_Errors = MakeStackErrors(BackgroundStack);

  TPad* PlotPad = MakeRatioPlot(Canvas,BackgroundStack, Data, axisLabel,0.7,1.3);
  PlotPad->SetTickx();
  PlotPad->SetTicky();

  BackgroundStack->SetMaximum(max(BackgroundStack->GetMaximum(),Data->GetMaximum()));
  
  BackgroundStack->Draw();
  BackgroundStack_Errors->Draw("SAME e2");
  BackgroundStack->SetTitle(axisLabel.c_str());
  Data->Draw("SAME e1");
  AllHiggs->Draw("SAME HIST");
  BackgroundStack->GetYaxis()->SetTitle("Events");
  BackgroundStack->GetYaxis()->SetTitleOffset(1.58);
  BackgroundStack->GetXaxis()->SetLabelSize(0.0);

  CMS_lumi(PlotPad,0,33);

  TLegend* Legend = new TLegend(0.61,0.41,0.88,0.68);        
  Legend->AddEntry(Data,"Observed","pe");
  Legend->AddEntry(DYTT,"Embedded","f");
  Legend->AddEntry(Other,"Other","f");  
  Legend->AddEntry(DYMM,"DY #rightarrow ll","f");  
  Legend->AddEntry(TTFinal,"t#bar{t}","f");  
  Legend->AddEntry(Data_Fake,"Fakes","f");
  Legend->AddEntry(AllHiggs,"All Higgs (#times 30)","l");

  Legend->Draw();
  if(UseEmbedded)
    {
      Canvas->SaveAs(("FinalPlots/"+var+"_2018_Embedded.png").c_str());
      Canvas->SaveAs(("FinalPlots/"+var+"_2018_Embedded.pdf").c_str());
    }
  else
    {
      Canvas->SaveAs(("FinalPlots/"+var+"_2018_MC.png").c_str());
      Canvas->SaveAs(("FinalPlots/"+var+"_2018_MC.pdf").c_str());
    }
  
  //HistoFile->Close();
}

void Draw2018ControlPlots()
{  

  bool UsingEmbedded = true;

  DrawControlPlot("MuPt",UsingEmbedded,"#mu p_{t}");
  DrawControlPlot("MuEta",UsingEmbedded,"#mu #eta");
  DrawControlPlot("TauPt",UsingEmbedded, "#tau p_{t}");
  DrawControlPlot("TauEta",UsingEmbedded,"#tau #eta");
  DrawControlPlot("MT",UsingEmbedded,"Transverse Mass");

  DrawControlPlot("mvis",UsingEmbedded,"m_{vis}");
  DrawControlPlot("msv", UsingEmbedded, "m_{#tau#tau}");
  DrawControlPlot("Njets",UsingEmbedded,"N_{jets}");
  DrawControlPlot("HiggsPt",UsingEmbedded,"Higgs p_{t}");
  DrawControlPlot("MET",UsingEmbedded,"MET");
  DrawControlPlot("DR",UsingEmbedded,"#Delta r_{#mu,#tau}");

  DrawControlPlot("mjj",UsingEmbedded,"m_{jj}");
  DrawControlPlot("detajj",UsingEmbedded,"#Delta#eta_{jj}");
  DrawControlPlot("j1pt",UsingEmbedded,"p_{t} j_{1}");
  DrawControlPlot("j1eta",UsingEmbedded,"#eta j_{1}");
  DrawControlPlot("j2pt",UsingEmbedded,"p_{t} j_{2}");
  DrawControlPlot("j2eta",UsingEmbedded,"#eta j_{2}");

  DrawControlPlot("METPhi",UsingEmbedded,"MET_{#phi}");      
  DrawControlPlot("trigger",UsingEmbedded,"trigger");  
}
