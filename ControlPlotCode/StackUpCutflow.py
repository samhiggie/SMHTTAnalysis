import ROOT

ResultsFile = ROOT.TFile("CecileCode/CutflowResults.root")

#get the usual suspects
data_obs_Cutflow = ResultsFile.Get("data_obs_Cutflow")
Fake_Cutflow = ResultsFile.Get("data_obs_Fake_Cutflow")
embedded_Cutflow = ResultsFile.Get("embedded_Cutflow")
DY_Cutflow = ResultsFile.Get("DY_Cutflow")
DYlow_Cutflow = ResultsFile.Get("DYlow_Cutflow")
TTToHadronic_Cutflow = ResultsFile.Get("TTToHadronic_Cutflow")
TTTo2L2Nu_Cutflow = ResultsFile.Get("TTTo2L2Nu_Cutflow")
TTToSemiLeptonic_Cutflow = ResultsFile.Get("TTToSemiLeptonic_Cutflow")
WW4Q_Cutflow = ResultsFile.Get("WW4Q_Cutflow")
WWLNuQQ_Cutflow = ResultsFile.Get("WWLNuQQ_Cutflow")
WZ2L2Q_Cutflow = ResultsFile.Get("WZ2L2Q_Cutflow")
WZ1L3Nu_Cutflow = ResultsFile.Get("WZ1L3Nu_Cutflow")
WZ3LNu_Cutflow = ResultsFile.Get("WZ3LNu_Cutflow")
WZ1L1Nu2Q_Cutflow = ResultsFile.Get("WZ1L1Nu2Q_Cutflow")
ZZ4L_Cutflow = ResultsFile.Get("ZZ4L_Cutflow")
ZZ2L2Nu_Cutflow = ResultsFile.Get("ZZ2L2Nu_Cutflow")
ZZ2L2Q_Cutflow = ResultsFile.Get("ZZ2L2Q_Cutflow")
ST_t_antitop_Cutflow = ResultsFile.Get("ST_t_antitop_Cutflow")
ST_t_top_Cutflow = ResultsFile.Get("ST_t_antitop_Cutflow")
ST_tW_antitop_Cutflow = ResultsFile.Get("ST_tW_antitop_Cutflow")
ST_tW_top_Cutflow = ResultsFile.Get("ST_tW_top_Cutflow")
ggH_htt125_Cutflow = ResultsFile.Get("ggH_htt125_Cutflow")
qqH_htt125_Cutflow = ResultsFile.Get("qqH_htt125_Cutflow")
WplusH125_Cutflow = ResultsFile.Get("WplusH125_Cutflow")
WminusH125_Cutflow = ResultsFile.Get("WminusH125_Cutflow")
ZH125_Cutflow = ResultsFile.Get("ZH125_Cutflow")
EWKZLL_Cutflow = ResultsFile.Get("EWKZLL_Cutflow")
EWKZNuNu_Cutflow = ResultsFile.Get("EWKZNuNu_Cutflow")

DYAll_Cutflow = DY_Cutflow.Clone()
DYAll_Cutflow.Add(DYlow_Cutflow)

TT_Cutflow = TTToHadronic_Cutflow.Clone();
TT_Cutflow.Add(TTTo2L2Nu_Cutflow)
TT_Cutflow.Add(TTToSemiLeptonic_Cutflow)

VV_Cutflow = WW4Q_Cutflow.Clone()
VV_Cutflow.Add(WWLNuQQ_Cutflow)
VV_Cutflow.Add(WZ2L2Q_Cutflow)
VV_Cutflow.Add(WZ1L3Nu_Cutflow)
VV_Cutflow.Add(WZ3LNu_Cutflow)
VV_Cutflow.Add(WZ1L1Nu2Q_Cutflow)
VV_Cutflow.Add(ZZ4L_Cutflow)
VV_Cutflow.Add(ZZ2L2Nu_Cutflow)
VV_Cutflow.Add(ZZ4L_Cutflow)
VV_Cutflow.Add(ZZ2L2Nu_Cutflow)
VV_Cutflow.Add(ZZ2L2Q_Cutflow)

ST_Cutflow = ST_t_antitop_Cutflow.Clone()
ST_Cutflow.Add(ST_t_top_Cutflow)
ST_Cutflow.Add(ST_tW_antitop_Cutflow)
ST_Cutflow.Add(ST_tW_top_Cutflow)
#handle this like we do in the other thing
VV_Cutflow.Add(ST_Cutflow)

WH_Cutflow = WplusH125_Cutflow.Clone()
WH_Cutflow.Add(WminusH125_Cutflow)

EWK_Cutflow = EWKZLL_Cutflow.Clone()
EWK_Cutflow.Add(EWKZNuNu_Cutflow)

data_obs_Cutflow.SetMarkerStyle(20)

Fake_Cutflow.SetLineColor(ROOT.kBlack)
Fake_Cutflow.SetFillColor(ROOT.kRed)

embedded_Cutflow.SetLineColor(ROOT.kBlack)
embedded_Cutflow.SetFillColor(ROOT.kYellow)

DY_Cutflow.SetLineColor(ROOT.kBlack)
DY_Cutflow.SetFillColor(ROOT.kBlue)

TT_Cutflow.SetLineColor(ROOT.kBlack)
TT_Cutflow.SetLineColor(ROOT.kViolet)

VV_Cutflow.SetLineColor(ROOT.kBlack)
VV_Cutflow.SetFillColor(ROOT.kOrange)

ggH_htt125_Cutflow.SetLineColor(ROOT.kBlack)
ggH_htt125_Cutflow.SetFillColor(ROOT.kCyan)

qqH_htt125_Cutflow.SetLineColor(ROOT.kBlack)
qqH_htt125_Cutflow.SetFillColor(ROOT.kGreen)

WH_Cutflow.SetLineColor(ROOT.kBlack)
WH_Cutflow.SetFillColor(ROOT.kPink+6)

ZH125_Cutflow.SetLineColor(ROOT.kBlack)
ZH125_Cutflow.SetFillColor(ROOT.kGreen+3)

EWK_Cutflow.SetLineColor(ROOT.kBlack)
EWK_Cutflow.SetFillColor(ROOT.kBlue-2)

Cutflow_Stack = ROOT.THStack("Cutflow_Stack","Cutflow_Stack")
Cutflow_Stack.Add(Fake_Cutflow, "HIST")
Cutflow_Stack.Add(embedded_Cutflow,"HIST")
Cutflow_Stack.Add(DY_Cutflow,"HIST")
Cutflow_Stack.Add(TT_Cutflow,"HIST")
Cutflow_Stack.Add(VV_Cutflow,"HIST")
Cutflow_Stack.Add(ggH_htt125_Cutflow,"HIST")
Cutflow_Stack.Add(qqH_htt125_Cutflow,"HIST")
Cutflow_Stack.Add(WH_Cutflow,"HIST")
Cutflow_Stack.Add(ZH125_Cutflow,"HIST")
Cutflow_Stack.Add(EWK_Cutflow,"HIST")

Cutflow_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
Cutflow_Legend.AddEntry(EWK_Cutflow,"EWK","f")
Cutflow_Legend.AddEntry(ZH125_Cutflow,"ZH","f")
Cutflow_Legend.AddEntry(WH_Cutflow,"WH","f")
Cutflow_Legend.AddEntry(qqH_htt125_Cutflow,"qqH","f")
Cutflow_Legend.AddEntry(ggH_htt125_Cutflow,"ggH","f")
Cutflow_Legend.AddEntry(VV_Cutflow,"VV+ST","f")
Cutflow_Legend.AddEntry(TT_Cutflow,"t#bar{t}","f")
Cutflow_Legend.AddEntry(DY_Cutflow,"Z#rightarrow ll","f")
Cutflow_Legend.AddEntry(embedded_Cutflow,"Z#rightarrow #tau#tau", "f")
Cutflow_Legend.AddEntry(Fake_Cutflow,"fakes","f")

#write this all out to be drawn later
Outfile = ROOT.TFile("CutflowPlots.root","RECREATE")
data_obs_Cutflow.Write()
Cutflow_Stack.Write()
Cutflow_Legend.Write()
