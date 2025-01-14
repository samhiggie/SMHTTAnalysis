#include "TROOT.h"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/CMS_lumi.C"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/tdrstyle.C"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/MakeRatioPlot.cc"
#include "/afs/cern.ch/user/a/aloelige/private/ScriptsAndMacros/MakeStackErrors.cc"
#include <string>

void DrawCombinePlots(string year)
{
  TString DYT_Prediction;
  if (year == "2017") DYT_Prediction = "embedded";
  else if (year == "2018") DYT_Prediction = "ZT";
  
  setTDRStyle();

  writeExtraText = true;
  extraText = "Preliminary";
  if(year == "2017")lumi_sqrtS = "41.5 fb^{-1}, 13 TeV";
  else if(year == "2018")lumi_sqrtS = "60 fb^{-1}, 13 TeV";
  
  //Color Corrections
  TColor* DYColor = new TColor((4.0*16.0+4.0)/256.0,(9.0*16.0+6.0)/256.0,(12.0*16.0+8.0)/256.0);
  TColor* OtherColor = new TColor((16.0+2.0)/256.0,(12.0*16.0+10.0)/256.0,(13.0*16.0+13.0)/256.0);

  TLatex latex;
  int numCategories;

  TFile* HistoFile = new TFile("HistoFile.root","READ");

  //ZeroJet
  TCanvas* CanvasOne = new TCanvas("CanvasOne","ZeroJet",550,550);
  CanvasOne->SetTickx();
  CanvasOne->SetTicky();  

  gStyle->SetOptStat(0);
  TDirectory* ZeroJetDir = (TDirectory*) HistoFile->Get("ZeroJet");
  TH1F* ZeroJet_Data = (TH1F*) ZeroJetDir->Get("data_obs");
  TH1F* ZeroJet_Fakes = (TH1F*) ZeroJetDir->Get("jetFakes");
  TH1F* ZeroJet_Embedded = (TH1F*) ZeroJetDir->Get(DYT_Prediction);
  TH1F* ZeroJet_ZMM = (TH1F*) ZeroJetDir->Get("ZL");
  TH1F* ZeroJet_TT = (TH1F*) ZeroJetDir->Get("TTL");
  TH1F* ZeroJet_Other = (TH1F*) ZeroJetDir->Get("Other");
  TH1F* ZeroJet_Higgs_Upscale = (TH1F*) ZeroJetDir->Get("Higgs_Upscale");

  // Do Signal Blinding
  for(int i=1;i<=ZeroJet_Data->GetNbinsX();++i)
    {
      float SignalContribution = ZeroJet_Higgs_Upscale->GetBinContent(i)/30.0; //curently upscaled by x30
      float NonHiggsOtherContribution = ZeroJet_Other->GetBinContent(i)-ZeroJet_Higgs_Upscale->GetBinContent(i)/30.0;
      float TotalBackgroundContribution = NonHiggsOtherContribution
	+ZeroJet_Fakes->GetBinContent(i)
	+ZeroJet_Embedded->GetBinContent(i)
	+ZeroJet_ZMM->GetBinContent(i)
	+ZeroJet_TT->GetBinContent(i);
      if (SignalContribution/std::sqrt(TotalBackgroundContribution) > 0.5)
	{
	  ZeroJet_Data->SetBinContent(i,-1.0);
	}
    }

  //Color Corections
  ZeroJet_ZMM->SetFillColor(DYColor->GetNumber());
  ZeroJet_Other->SetFillColor(OtherColor->GetNumber());

  THStack* ZeroJetStack = new THStack("ZeroJetStack","ZeroJetStack");
  ZeroJetStack->Add(ZeroJet_Other,"HIST");
  ZeroJetStack->Add(ZeroJet_TT,"HIST");  
  ZeroJetStack->Add(ZeroJet_ZMM,"HIST");  
  ZeroJetStack->Add(ZeroJet_Fakes,"HIST");
  ZeroJetStack->Add(ZeroJet_Embedded,"HIST");

  TH1F* ZeroJet_Errors = MakeStackErrors(ZeroJetStack);
  
  TPad* ZeroJet_PlotPad = MakeRatioPlot(CanvasOne,ZeroJetStack,ZeroJet_Data,"m_{vis}",0.7,1.3);
  ZeroJet_PlotPad->SetTickx();
  ZeroJet_PlotPad->SetTicky();
  ZeroJet_PlotPad->SetGridx();
  ZeroJet_PlotPad->SetLogy();
  
  ZeroJetStack->SetMaximum(max(ZeroJetStack->GetMaximum(),ZeroJet_Data->GetMaximum())*1.1);
  
  ZeroJetStack->Draw();
  ZeroJet_Errors->Draw("SAME e2");
  ZeroJetStack->SetTitle("0 Jet");
  ZeroJet_Data->Draw("SAME e1");
  ZeroJet_Higgs_Upscale->Draw("SAME HIST");
  ZeroJetStack->GetYaxis()->SetTitle("Events");
  ZeroJetStack->GetYaxis()->SetTitleOffset(1.58);
  ZeroJetStack->GetXaxis()->SetLabelSize(0.0);

  CMS_lumi(ZeroJet_PlotPad,0,33);
  
  TLegend* ZeroJetLegend = new TLegend(0.9,0.6,1.0,0.9);
  ZeroJetLegend->AddEntry(ZeroJet_Data,"Observed","pe");
  ZeroJetLegend->AddEntry(ZeroJet_Embedded,"DY #rightarrow #tau#tau","f");
  ZeroJetLegend->AddEntry(ZeroJet_Other,"Other","f");
  ZeroJetLegend->AddEntry(ZeroJet_ZMM,"DY #rightarrow ll","f");
  ZeroJetLegend->AddEntry(ZeroJet_TT,"t#bar{t}","f");
  ZeroJetLegend->AddEntry(ZeroJet_Fakes,"Fakes","f");
  ZeroJetLegend->AddEntry(ZeroJet_Higgs_Upscale,"All Higgs (#times 30)","l");
  ZeroJetLegend->Draw();

  numCategories = 6;
  TH1F* ZeroJetGridDivision = new TH1F("ZeroJetGrid","ZeroJetGrid",
				 ZeroJet_Higgs_Upscale->GetNbinsX(),
				 ZeroJet_Higgs_Upscale->GetXaxis()->GetXmin(),
				 ZeroJet_Higgs_Upscale->GetXaxis()->GetXmax());
  ZeroJetStack->GetXaxis()->SetNdivisions(-500-numCategories);
  ZeroJetGridDivision->GetXaxis()->SetNdivisions(-500-numCategories);
  ZeroJetGridDivision->Draw("SAME");
  
  latex.SetTextSize(0.025);
  latex.SetTextAlign(13);  
  latex.DrawLatex(1.0,18000,"30 #leq #tau_{p_{t}} #leq 40");
  latex.DrawLatex(11.0,18000,"40 #leq #tau_{p_{t}} #leq 50");
  latex.DrawLatex(21.0,18000,"50 #leq #tau_{p_{t}} #leq 60");
  latex.DrawLatex(31.0,18000,"60 #leq #tau_{p_{t}} #leq 70");
  latex.DrawLatex(41.0,1000,"70 #leq #tau_{p_{t}} #leq 80");
  latex.DrawLatex(51.0,1000,"80 #leq #tau_{p_{t}}");
  //latex.DrawLatex(52.0,5000,"80 #leq #tau_{p_{t}}");

  CanvasOne->Draw();
  CanvasOne->SaveAs("PrefitChecks/ZeroJet.png");

  //Boosted
  TCanvas* CanvasTwo = new TCanvas("CanvasTwo","Boosted",550,550);
  CanvasTwo->SetTickx();
  CanvasTwo->SetTicky();  

  gStyle->SetOptStat(0);
  TDirectory* BoostedDir = (TDirectory*) HistoFile->Get("Boosted");
  TH1F* Boosted_Data = (TH1F*) BoostedDir->Get("data_obs");
  TH1F* Boosted_Fakes = (TH1F*) BoostedDir->Get("jetFakes");
  TH1F* Boosted_Embedded = (TH1F*) BoostedDir->Get(DYT_Prediction);
  TH1F* Boosted_ZMM = (TH1F*) BoostedDir->Get("ZL");
  TH1F* Boosted_TT = (TH1F*) BoostedDir->Get("TTL");
  TH1F* Boosted_Other = (TH1F*) BoostedDir->Get("Other");
  TH1F* Boosted_Higgs_Upscale = (TH1F*) BoostedDir->Get("Higgs_Upscale");

  // Do Signal Blinding
  for(int i=1;i<=Boosted_Data->GetNbinsX();++i)
    {
      float SignalContribution = Boosted_Higgs_Upscale->GetBinContent(i)/30.0; //curently upscaled by x30
      float NonHiggsOtherContribution = Boosted_Other->GetBinContent(i)-Boosted_Higgs_Upscale->GetBinContent(i)/30.0;
      float TotalBackgroundContribution = NonHiggsOtherContribution
	+Boosted_Fakes->GetBinContent(i)
	+Boosted_Embedded->GetBinContent(i)
	+Boosted_ZMM->GetBinContent(i)
	+Boosted_TT->GetBinContent(i);
      if (SignalContribution/std::sqrt(TotalBackgroundContribution) > 0.5)
	{
	  Boosted_Data->SetBinContent(i,-1.0);
	}
    }

  //Color Corections
  Boosted_ZMM->SetFillColor(DYColor->GetNumber());
  Boosted_Other->SetFillColor(OtherColor->GetNumber());

  THStack* BoostedStack = new THStack("BoostedStack","BoostedStack");
  BoostedStack->Add(Boosted_Other,"HIST");
  BoostedStack->Add(Boosted_TT,"HIST");
  BoostedStack->Add(Boosted_ZMM,"HIST");  
  BoostedStack->Add(Boosted_Fakes,"HIST");
  BoostedStack->Add(Boosted_Embedded,"HIST");

  TH1F* Boosted_Errors = MakeStackErrors(BoostedStack);
  
  TPad* Boosted_PlotPad = MakeRatioPlot(CanvasTwo,BoostedStack,Boosted_Data,"m_{sv}",0.7,1.3);
  Boosted_PlotPad->SetTickx();
  Boosted_PlotPad->SetTicky();
  Boosted_PlotPad->SetGridx();
  Boosted_PlotPad->SetLogy();
  
  BoostedStack->SetMaximum(max(BoostedStack->GetMaximum(),Boosted_Data->GetMaximum())*1.1);
  
  BoostedStack->Draw();
  Boosted_Errors->Draw("SAME e2");
  BoostedStack->SetTitle("Boosted");
  Boosted_Data->Draw("SAME e1");
  Boosted_Higgs_Upscale->Draw("SAME HIST");
  BoostedStack->GetYaxis()->SetTitle("Events");
  BoostedStack->GetYaxis()->SetTitleOffset(1.58);
  BoostedStack->GetXaxis()->SetLabelSize(0.0);

  CMS_lumi(Boosted_PlotPad,0,33);
  
  TLegend* BoostedLegend = new TLegend(0.9,0.6,1.0,0.9);
  BoostedLegend->AddEntry(Boosted_Data,"Observed","pe");
  BoostedLegend->AddEntry(Boosted_Embedded,"DY #rightarrow #tau#tau","f");
  BoostedLegend->AddEntry(Boosted_Other,"Other","f");
  BoostedLegend->AddEntry(Boosted_ZMM,"DY #rightarrow ll","f");
  BoostedLegend->AddEntry(Boosted_TT,"t#bar{t}","f");
  BoostedLegend->AddEntry(Boosted_Fakes,"Fakes","f");
  BoostedLegend->AddEntry(Boosted_Higgs_Upscale,"All Higgs (#times 30)","l");
  BoostedLegend->Draw();

  numCategories = 4;
  TH1F* BoostedGridDivision = new TH1F("BoostedGrid","BoostedGrid",
				 Boosted_Higgs_Upscale->GetNbinsX(),
				 Boosted_Higgs_Upscale->GetXaxis()->GetXmin(),
				 Boosted_Higgs_Upscale->GetXaxis()->GetXmax());
  BoostedStack->GetXaxis()->SetNdivisions(-500-numCategories);
  BoostedGridDivision->GetXaxis()->SetNdivisions(-500-numCategories);
  BoostedGridDivision->Draw("SAME");

  latex.SetTextSize(0.017);
  latex.SetTextAlign(13);
  latex.DrawLatex(2.0,30000.0,"0.0 #leq H_{p_{t}} #leq 100.0");
  latex.DrawLatex(12.0,8000.0,"100.0 #leq H_{p_{t}} #leq 170.0");
  latex.DrawLatex(22.0,5000.0,"170.0 #leq H_{p_{t}} #leq 300.0");
  //latex.DrawLatex(62.0,4500.0,"100.0 #leq H_{p_{t}} #leq 150.0");  
  latex.DrawLatex(32.0,4000.0,"300.0 #leq H_{p_{t}}");

  CanvasTwo->Draw();
  CanvasTwo->SaveAs("PrefitChecks/Boosted.png");
  
  //VBF
  
  TCanvas* CanvasThree = new TCanvas("CanvasThree","VBF",550,550);
  CanvasThree->SetTickx();
  CanvasThree->SetTicky();  

  gStyle->SetOptStat(0);
  TDirectory* VBFDir = (TDirectory*) HistoFile->Get("VBF");
  TH1F* VBF_Data = (TH1F*) VBFDir->Get("data_obs");
  TH1F* VBF_Fakes = (TH1F*) VBFDir->Get("jetFakes");
  TH1F* VBF_Embedded = (TH1F*) VBFDir->Get(DYT_Prediction);
  TH1F* VBF_ZMM = (TH1F*) VBFDir->Get("ZL");
  TH1F* VBF_TT = (TH1F*) VBFDir->Get("TTL");
  TH1F* VBF_Other = (TH1F*) VBFDir->Get("Other");
  TH1F* VBF_Higgs_Upscale = (TH1F*) VBFDir->Get("Higgs_Upscale");

  // Do Signal Blinding
  for(int i=1;i<=VBF_Data->GetNbinsX();++i)
    {
      float SignalContribution = VBF_Higgs_Upscale->GetBinContent(i)/30.0; //curently upscaled by x30
      float NonHiggsOtherContribution = VBF_Other->GetBinContent(i)-VBF_Higgs_Upscale->GetBinContent(i)/30.0;
      float TotalBackgroundContribution = NonHiggsOtherContribution
	+VBF_Fakes->GetBinContent(i)
	+VBF_Embedded->GetBinContent(i)
	+VBF_ZMM->GetBinContent(i)
	+VBF_TT->GetBinContent(i);
      if (SignalContribution/std::sqrt(TotalBackgroundContribution) > 0.5)
	{
	  VBF_Data->SetBinContent(i,-1.0);
	}
    }

  //Color Corections
  VBF_ZMM->SetFillColor(DYColor->GetNumber());
  VBF_Other->SetFillColor(OtherColor->GetNumber());

  THStack* VBFStack = new THStack("VBFStack","VBFStack");  
  VBFStack->Add(VBF_Other,"HIST");
  VBFStack->Add(VBF_TT,"HIST");
  VBFStack->Add(VBF_ZMM,"HIST");  
  VBFStack->Add(VBF_Fakes,"HIST");
  VBFStack->Add(VBF_Embedded,"HIST");

  TH1F* VBF_Errors = MakeStackErrors(VBFStack);
  
  TPad* VBF_PlotPad = MakeRatioPlot(CanvasThree,VBFStack,VBF_Data,"m_{sv}",0.7,1.3);
  VBF_PlotPad->SetTickx();
  VBF_PlotPad->SetTicky();
  VBF_PlotPad->SetGridx();
  VBF_PlotPad->SetLogy();
  
  VBFStack->SetMaximum(max(VBFStack->GetMaximum(),VBF_Data->GetMaximum())*1.1);
  
  VBFStack->Draw();
  VBF_Errors->Draw("SAME e2");
  VBFStack->SetTitle("VBF");
  VBF_Data->Draw("SAME e1");
  VBF_Higgs_Upscale->Draw("SAME HIST");
  VBFStack->GetYaxis()->SetTitle("Events");
  VBFStack->GetYaxis()->SetTitleOffset(1.58);
  VBFStack->GetXaxis()->SetLabelSize(0.0);

  CMS_lumi(VBF_PlotPad,0,33);
  
  TLegend* VBFLegend = new TLegend(0.9,0.6,1.0,0.9);
  VBFLegend->AddEntry(VBF_Data,"Observed","pe");
  VBFLegend->AddEntry(VBF_Embedded,"DY #rightarrow #tau#tau","f");
  VBFLegend->AddEntry(VBF_Other,"Other","f");
  VBFLegend->AddEntry(VBF_ZMM,"DY #rightarrow ll","f");
  VBFLegend->AddEntry(VBF_TT,"t#bar{t}","f");
  VBFLegend->AddEntry(VBF_Fakes,"Fakes","f");
  VBFLegend->AddEntry(VBF_Higgs_Upscale,"All Higgs (#times 30)","l");
  VBFLegend->Draw();

  numCategories = 4;
  TH1F* VBFGridDivision = new TH1F("VBFGrid","VBFGrid",
				 VBF_Higgs_Upscale->GetNbinsX(),
				 VBF_Higgs_Upscale->GetXaxis()->GetXmin(),
				 VBF_Higgs_Upscale->GetXaxis()->GetXmax());
  VBFStack->GetXaxis()->SetNdivisions(-500-numCategories);
  VBFGridDivision->GetXaxis()->SetNdivisions(-500-numCategories);
  VBFGridDivision->Draw("SAME");

  latex.SetTextSize(0.017);
  latex.SetTextAlign(13);
  latex.DrawLatex(2.0,3000.0,"300.0 #leq m_{jj} #leq 700.0");
  latex.DrawLatex(12.0,600.0,"700.0 #leq m_{jj} #leq 1100.0");
  latex.DrawLatex(22.0,600.0,"1100.0 #leq m_{jj} #leq 1500.0");
  //latex.DrawLatex(62.0,1800.0,"1100.0 #leq m_{jj} #leq 1500.0");
  latex.DrawLatex(32.0,600.0,"1500.0 #leq m_{jj}");

  CanvasThree->Draw();
  CanvasThree->SaveAs("PrefitChecks/VBF.png");

}
