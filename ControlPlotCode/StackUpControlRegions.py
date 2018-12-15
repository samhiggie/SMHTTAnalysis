import ROOT

ResultsFile  = ROOT.TFile("CecileCode/ControlRegionResults.root")
#Stack up the same sign, mvis plots

data_obs_SS_mvis = ResultsFile.Get("data_obs_SS_mvis")
Fake_SS_mvis = ResultsFile.Get("data_obs_SS_Fake_mvis")
embedded_SS_mvis = ResultsFile.Get("embedded_SS_mvis")
DY_SS_mvis = ResultsFile.Get("DY_SS_mvis")
DYlow_SS_mvis = ResultsFile.Get("DYlow_SS_mvis")
TTToHadronic_SS_mvis = ResultsFile.Get("TTToHadronic_SS_mvis")
TTTo2L2Nu_SS_mvis = ResultsFile.Get("TTTo2L2Nu_SS_mvis")
TTToSemiLeptonic_SS_mvis = ResultsFile.Get("TTToSemiLeptonic_SS_mvis")
WW4Q_SS_mvis = ResultsFile.Get("WW4Q_SS_mvis")
WWLNuQQ_SS_mvis = ResultsFile.Get("WWLNuQQ_SS_mvis")
WZ2L2Q_SS_mvis = ResultsFile.Get("WZ2L2Q_SS_mvis")
WZ1L3Nu_SS_mvis = ResultsFile.Get("WZ1L3Nu_SS_mvis")
WZ3LNu_SS_mvis = ResultsFile.Get("WZ3LNu_SS_mvis")
WZ1L1Nu2Q_SS_mvis = ResultsFile.Get("WZ1L1Nu2Q_SS_mvis")
ZZ4L_SS_mvis = ResultsFile.Get("ZZ4L_SS_mvis")
ZZ2L2Nu_SS_mvis = ResultsFile.Get("ZZ2L2Nu_SS_mvis")
ZZ2L2Q_SS_mvis = ResultsFile.Get("ZZ2L2Q_SS_mvis")
ST_t_antitop_SS_mvis = ResultsFile.Get("ST_t_antitop_SS_mvis")
ST_t_top_SS_mvis = ResultsFile.Get("ST_t_antitop_SS_mvis")
ST_tW_antitop_SS_mvis = ResultsFile.Get("ST_tW_antitop_SS_mvis")
ST_tW_top_SS_mvis = ResultsFile.Get("ST_tW_top_SS_mvis")
ggH_htt125_SS_mvis = ResultsFile.Get("ggH_htt125_SS_mvis")
qqH_htt125_SS_mvis = ResultsFile.Get("qqH_htt125_SS_mvis")
WplusH125_SS_mvis = ResultsFile.Get("WplusH125_SS_mvis")
WminusH125_SS_mvis = ResultsFile.Get("WminusH125_SS_mvis")
ZH125_SS_mvis = ResultsFile.Get("ZH125_SS_mvis")
EWKZLL_SS_mvis = ResultsFile.Get("EWKZLL_SS_mvis")
EWKZNuNu_SS_mvis = ResultsFile.Get("EWKZNuNu_SS_mvis")

DYAll_SS_mvis = DY_SS_mvis.Clone()
DYAll_SS_mvis.Add(DYlow_SS_mvis)

TT_SS_mvis = TTToHadronic_SS_mvis.Clone();
TT_SS_mvis.Add(TTTo2L2Nu_SS_mvis)
TT_SS_mvis.Add(TTToSemiLeptonic_SS_mvis)

VV_SS_mvis = WW4Q_SS_mvis.Clone()
VV_SS_mvis.Add(WWLNuQQ_SS_mvis)
VV_SS_mvis.Add(WZ2L2Q_SS_mvis)
VV_SS_mvis.Add(WZ1L3Nu_SS_mvis)
VV_SS_mvis.Add(WZ3LNu_SS_mvis)
VV_SS_mvis.Add(WZ1L1Nu2Q_SS_mvis)
VV_SS_mvis.Add(ZZ4L_SS_mvis)
VV_SS_mvis.Add(ZZ2L2Nu_SS_mvis)
VV_SS_mvis.Add(ZZ4L_SS_mvis)
VV_SS_mvis.Add(ZZ2L2Nu_SS_mvis)
VV_SS_mvis.Add(ZZ2L2Q_SS_mvis)

ST_SS_mvis = ST_t_antitop_SS_mvis.Clone()
ST_SS_mvis.Add(ST_t_top_SS_mvis)
ST_SS_mvis.Add(ST_tW_antitop_SS_mvis)
ST_SS_mvis.Add(ST_tW_top_SS_mvis)
#handle this like we do in the other thing
VV_SS_mvis.Add(ST_SS_mvis)

WH_SS_mvis = WplusH125_SS_mvis.Clone()
WH_SS_mvis.Add(WminusH125_SS_mvis)

EWK_SS_mvis = EWKZLL_SS_mvis.Clone()
EWK_SS_mvis.Add(EWKZNuNu_SS_mvis)

data_obs_SS_mvis.SetMarkerStyle(20)

Fake_SS_mvis.SetLineColor(ROOT.kBlack)
Fake_SS_mvis.SetFillColor(ROOT.kRed)

embedded_SS_mvis.SetLineColor(ROOT.kBlack)
embedded_SS_mvis.SetFillColor(ROOT.kYellow)

DYAll_SS_mvis.SetLineColor(ROOT.kBlack)
DYAll_SS_mvis.SetFillColor(ROOT.kBlue)

TT_SS_mvis.SetLineColor(ROOT.kBlack)
TT_SS_mvis.SetLineColor(ROOT.kViolet)

VV_SS_mvis.SetLineColor(ROOT.kBlack)
VV_SS_mvis.SetFillColor(ROOT.kOrange)

ggH_htt125_SS_mvis.SetLineColor(ROOT.kBlack)
ggH_htt125_SS_mvis.SetFillColor(ROOT.kCyan)

qqH_htt125_SS_mvis.SetLineColor(ROOT.kBlack)
qqH_htt125_SS_mvis.SetFillColor(ROOT.kGreen)

WH_SS_mvis.SetLineColor(ROOT.kBlack)
WH_SS_mvis.SetFillColor(ROOT.kPink+6)

ZH125_SS_mvis.SetLineColor(ROOT.kBlack)
ZH125_SS_mvis.SetFillColor(ROOT.kGreen+3)

EWK_SS_mvis.SetLineColor(ROOT.kBlack)
EWK_SS_mvis.SetFillColor(ROOT.kBlue-2)

SS_mvis_Stack = ROOT.THStack("SS_mvis_Stack","SS_mvis_Stack")
SS_mvis_Stack.Add(Fake_SS_mvis, "HIST")
SS_mvis_Stack.Add(embedded_SS_mvis,"HIST")
SS_mvis_Stack.Add(DYAll_SS_mvis,"HIST")
SS_mvis_Stack.Add(TT_SS_mvis,"HIST")
SS_mvis_Stack.Add(VV_SS_mvis,"HIST")
SS_mvis_Stack.Add(ggH_htt125_SS_mvis,"HIST")
SS_mvis_Stack.Add(qqH_htt125_SS_mvis,"HIST")
SS_mvis_Stack.Add(WH_SS_mvis,"HIST")
SS_mvis_Stack.Add(ZH125_SS_mvis,"HIST")
SS_mvis_Stack.Add(EWK_SS_mvis,"HIST")

SS_mvis_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
SS_mvis_Legend.AddEntry(EWK_SS_mvis,"EWK","f")
SS_mvis_Legend.AddEntry(ZH125_SS_mvis,"ZH","f")
SS_mvis_Legend.AddEntry(WH_SS_mvis,"WH","f")
SS_mvis_Legend.AddEntry(qqH_htt125_SS_mvis,"qqH","f")
SS_mvis_Legend.AddEntry(ggH_htt125_SS_mvis,"ggH","f")
SS_mvis_Legend.AddEntry(VV_SS_mvis,"VV+ST","f")
SS_mvis_Legend.AddEntry(TT_SS_mvis,"t#bar{t}","f")
SS_mvis_Legend.AddEntry(DYAll_SS_mvis,"Z#rightarrow ll","f")
SS_mvis_Legend.AddEntry(embedded_SS_mvis,"Z#rightarrow #tau#tau", "f")
SS_mvis_Legend.AddEntry(Fake_SS_mvis,"fakes","f")

#Stack up the same sign, Tau PT plots
data_obs_SS_TauPt = ResultsFile.Get("data_obs_SS_TauPt")
Fake_SS_TauPt = ResultsFile.Get("data_obs_SS_Fake_TauPt")
embedded_SS_TauPt = ResultsFile.Get("embedded_SS_TauPt")
DY_SS_TauPt = ResultsFile.Get("DY_SS_TauPt")
DYlow_SS_TauPt = ResultsFile.Get("DYlow_SS_TauPt")
TTToHadronic_SS_TauPt = ResultsFile.Get("TTToHadronic_SS_TauPt")
TTTo2L2Nu_SS_TauPt = ResultsFile.Get("TTTo2L2Nu_SS_TauPt")
TTToSemiLeptonic_SS_TauPt = ResultsFile.Get("TTToSemiLeptonic_SS_TauPt")
WW4Q_SS_TauPt = ResultsFile.Get("WW4Q_SS_TauPt")
WWLNuQQ_SS_TauPt = ResultsFile.Get("WWLNuQQ_SS_TauPt")
WZ2L2Q_SS_TauPt = ResultsFile.Get("WZ2L2Q_SS_TauPt")
WZ1L3Nu_SS_TauPt = ResultsFile.Get("WZ1L3Nu_SS_TauPt")
WZ3LNu_SS_TauPt = ResultsFile.Get("WZ3LNu_SS_TauPt")
WZ1L1Nu2Q_SS_TauPt = ResultsFile.Get("WZ1L1Nu2Q_SS_TauPt")
ZZ4L_SS_TauPt = ResultsFile.Get("ZZ4L_SS_TauPt")
ZZ2L2Nu_SS_TauPt = ResultsFile.Get("ZZ2L2Nu_SS_TauPt")
ZZ2L2Q_SS_TauPt = ResultsFile.Get("ZZ2L2Q_SS_TauPt")
ST_t_antitop_SS_TauPt = ResultsFile.Get("ST_t_antitop_SS_TauPt")
ST_t_top_SS_TauPt = ResultsFile.Get("ST_t_antitop_SS_TauPt")
ST_tW_antitop_SS_TauPt = ResultsFile.Get("ST_tW_antitop_SS_TauPt")
ST_tW_top_SS_TauPt = ResultsFile.Get("ST_tW_top_SS_TauPt")
ggH_htt125_SS_TauPt = ResultsFile.Get("ggH_htt125_SS_TauPt")
qqH_htt125_SS_TauPt = ResultsFile.Get("qqH_htt125_SS_TauPt")
WplusH125_SS_TauPt = ResultsFile.Get("WplusH125_SS_TauPt")
WminusH125_SS_TauPt = ResultsFile.Get("WminusH125_SS_TauPt")
ZH125_SS_TauPt = ResultsFile.Get("ZH125_SS_TauPt")
EWKZLL_SS_TauPt = ResultsFile.Get("EWKZLL_SS_TauPt")
EWKZNuNu_SS_TauPt = ResultsFile.Get("EWKZNuNu_SS_TauPt")

DYAll_SS_TauPt = DY_SS_TauPt.Clone()
DYAll_SS_TauPt.Add(DYlow_SS_TauPt)

TT_SS_TauPt = TTToHadronic_SS_TauPt.Clone();
TT_SS_TauPt.Add(TTTo2L2Nu_SS_TauPt)
TT_SS_TauPt.Add(TTToSemiLeptonic_SS_TauPt)

VV_SS_TauPt = WW4Q_SS_TauPt.Clone()
VV_SS_TauPt.Add(WWLNuQQ_SS_TauPt)
VV_SS_TauPt.Add(WZ2L2Q_SS_TauPt)
VV_SS_TauPt.Add(WZ1L3Nu_SS_TauPt)
VV_SS_TauPt.Add(WZ3LNu_SS_TauPt)
VV_SS_TauPt.Add(WZ1L1Nu2Q_SS_TauPt)
VV_SS_TauPt.Add(ZZ4L_SS_TauPt)
VV_SS_TauPt.Add(ZZ2L2Nu_SS_TauPt)
VV_SS_TauPt.Add(ZZ4L_SS_TauPt)
VV_SS_TauPt.Add(ZZ2L2Nu_SS_TauPt)
VV_SS_TauPt.Add(ZZ2L2Q_SS_TauPt)

ST_SS_TauPt = ST_t_antitop_SS_TauPt.Clone()
ST_SS_TauPt.Add(ST_t_top_SS_TauPt)
ST_SS_TauPt.Add(ST_tW_antitop_SS_TauPt)
ST_SS_TauPt.Add(ST_tW_top_SS_TauPt)
#handle this like we do in the other thing
VV_SS_TauPt.Add(ST_SS_TauPt)

WH_SS_TauPt = WplusH125_SS_TauPt.Clone()
WH_SS_TauPt.Add(WminusH125_SS_TauPt)

EWK_SS_TauPt = EWKZLL_SS_TauPt.Clone()
EWK_SS_TauPt.Add(EWKZNuNu_SS_TauPt)

data_obs_SS_TauPt.SetMarkerStyle(20)

Fake_SS_TauPt.SetLineColor(ROOT.kBlack)
Fake_SS_TauPt.SetFillColor(ROOT.kRed)

embedded_SS_TauPt.SetLineColor(ROOT.kBlack)
embedded_SS_TauPt.SetFillColor(ROOT.kYellow)

DYAll_SS_TauPt.SetLineColor(ROOT.kBlack)
DYAll_SS_TauPt.SetFillColor(ROOT.kBlue)

TT_SS_TauPt.SetLineColor(ROOT.kBlack)
TT_SS_TauPt.SetLineColor(ROOT.kViolet)

VV_SS_TauPt.SetLineColor(ROOT.kBlack)
VV_SS_TauPt.SetFillColor(ROOT.kOrange)

ggH_htt125_SS_TauPt.SetLineColor(ROOT.kBlack)
ggH_htt125_SS_TauPt.SetFillColor(ROOT.kCyan)

qqH_htt125_SS_TauPt.SetLineColor(ROOT.kBlack)
qqH_htt125_SS_TauPt.SetFillColor(ROOT.kGreen)

WH_SS_TauPt.SetLineColor(ROOT.kBlack)
WH_SS_TauPt.SetFillColor(ROOT.kPink+6)

ZH125_SS_TauPt.SetLineColor(ROOT.kBlack)
ZH125_SS_TauPt.SetFillColor(ROOT.kGreen+3)

EWK_SS_TauPt.SetLineColor(ROOT.kBlack)
EWK_SS_TauPt.SetFillColor(ROOT.kBlue-2)

SS_TauPt_Stack = ROOT.THStack("SS_TauPt_Stack","SS_TauPt_Stack")
SS_TauPt_Stack.Add(Fake_SS_TauPt, "HIST")
SS_TauPt_Stack.Add(embedded_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(DYAll_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(TT_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(VV_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(ggH_htt125_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(qqH_htt125_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(WH_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(ZH125_SS_TauPt,"HIST")
SS_TauPt_Stack.Add(EWK_SS_TauPt,"HIST")

SS_TauPt_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
SS_TauPt_Legend.AddEntry(EWK_SS_TauPt,"EWK","f")
SS_TauPt_Legend.AddEntry(ZH125_SS_TauPt,"ZH","f")
SS_TauPt_Legend.AddEntry(WH_SS_TauPt,"WH","f")
SS_TauPt_Legend.AddEntry(qqH_htt125_SS_TauPt,"qqH","f")
SS_TauPt_Legend.AddEntry(ggH_htt125_SS_TauPt,"ggH","f")
SS_TauPt_Legend.AddEntry(VV_SS_TauPt,"VV+ST","f")
SS_TauPt_Legend.AddEntry(TT_SS_TauPt,"t#bar{t}","f")
SS_TauPt_Legend.AddEntry(DYAll_SS_TauPt,"Z#rightarrow ll","f")
SS_TauPt_Legend.AddEntry(embedded_SS_TauPt,"Z#rightarrow #tau#tau", "f")
SS_TauPt_Legend.AddEntry(Fake_SS_TauPt,"fakes","f")

#Now the high mt region
data_obs_HighMT_mvis = ResultsFile.Get("data_obs_mt_mvis")
Fake_HighMT_mvis = ResultsFile.Get("data_obs_mt_Fake_mvis")
embedded_HighMT_mvis = ResultsFile.Get("embedded_mt_mvis")
DY_HighMT_mvis = ResultsFile.Get("DY_mt_mvis")
DYlow_HighMT_mvis = ResultsFile.Get("DYlow_mt_mvis")
TTToHadronic_HighMT_mvis = ResultsFile.Get("TTToHadronic_mt_mvis")
TTTo2L2Nu_HighMT_mvis = ResultsFile.Get("TTTo2L2Nu_mt_mvis")
TTToSemiLeptonic_HighMT_mvis = ResultsFile.Get("TTToSemiLeptonic_mt_mvis")
WW4Q_HighMT_mvis = ResultsFile.Get("WW4Q_mt_mvis")
WWLNuQQ_HighMT_mvis = ResultsFile.Get("WWLNuQQ_mt_mvis")
WZ2L2Q_HighMT_mvis = ResultsFile.Get("WZ2L2Q_mt_mvis")
WZ1L3Nu_HighMT_mvis = ResultsFile.Get("WZ1L3Nu_mt_mvis")
WZ3LNu_HighMT_mvis = ResultsFile.Get("WZ3LNu_mt_mvis")
WZ1L1Nu2Q_HighMT_mvis = ResultsFile.Get("WZ1L1Nu2Q_mt_mvis")
ZZ4L_HighMT_mvis = ResultsFile.Get("ZZ4L_mt_mvis")
ZZ2L2Nu_HighMT_mvis = ResultsFile.Get("ZZ2L2Nu_mt_mvis")
ZZ2L2Q_HighMT_mvis = ResultsFile.Get("ZZ2L2Q_mt_mvis")
ST_t_antitop_HighMT_mvis = ResultsFile.Get("ST_t_antitop_mt_mvis")
ST_t_top_HighMT_mvis = ResultsFile.Get("ST_t_antitop_mt_mvis")
ST_tW_antitop_HighMT_mvis = ResultsFile.Get("ST_tW_antitop_mt_mvis")
ST_tW_top_HighMT_mvis = ResultsFile.Get("ST_tW_top_mt_mvis")
ggH_htt125_HighMT_mvis = ResultsFile.Get("ggH_htt125_mt_mvis")
qqH_htt125_HighMT_mvis = ResultsFile.Get("qqH_htt125_mt_mvis")
WplusH125_HighMT_mvis = ResultsFile.Get("WplusH125_mt_mvis")
WminusH125_HighMT_mvis = ResultsFile.Get("WminusH125_mt_mvis")
ZH125_HighMT_mvis = ResultsFile.Get("ZH125_mt_mvis")
EWKZLL_HighMT_mvis = ResultsFile.Get("EWKZLL_mt_mvis")
EWKZNuNu_HighMT_mvis = ResultsFile.Get("EWKZNuNu_mt_mvis")

DYAll_HighMT_mvis = DY_HighMT_mvis.Clone()
DYAll_HighMT_mvis.Add(DYlow_HighMT_mvis)

TT_HighMT_mvis = TTToHadronic_HighMT_mvis.Clone();
TT_HighMT_mvis.Add(TTTo2L2Nu_HighMT_mvis)
TT_HighMT_mvis.Add(TTToSemiLeptonic_HighMT_mvis)

VV_HighMT_mvis = WW4Q_HighMT_mvis.Clone()
VV_HighMT_mvis.Add(WWLNuQQ_HighMT_mvis)
VV_HighMT_mvis.Add(WZ2L2Q_HighMT_mvis)
VV_HighMT_mvis.Add(WZ1L3Nu_HighMT_mvis)
VV_HighMT_mvis.Add(WZ3LNu_HighMT_mvis)
VV_HighMT_mvis.Add(WZ1L1Nu2Q_HighMT_mvis)
VV_HighMT_mvis.Add(ZZ4L_HighMT_mvis)
VV_HighMT_mvis.Add(ZZ2L2Nu_HighMT_mvis)
VV_HighMT_mvis.Add(ZZ4L_HighMT_mvis)
VV_HighMT_mvis.Add(ZZ2L2Nu_HighMT_mvis)
VV_HighMT_mvis.Add(ZZ2L2Q_HighMT_mvis)

ST_HighMT_mvis = ST_t_antitop_HighMT_mvis.Clone()
ST_HighMT_mvis.Add(ST_t_top_HighMT_mvis)
ST_HighMT_mvis.Add(ST_tW_antitop_HighMT_mvis)
ST_HighMT_mvis.Add(ST_tW_top_HighMT_mvis)
#handle this like we do in the other thing
VV_HighMT_mvis.Add(ST_HighMT_mvis)

WH_HighMT_mvis = WplusH125_HighMT_mvis.Clone()
WH_HighMT_mvis.Add(WminusH125_HighMT_mvis)

EWK_HighMT_mvis = EWKZLL_HighMT_mvis.Clone()
EWK_HighMT_mvis.Add(EWKZNuNu_HighMT_mvis)

data_obs_HighMT_mvis.SetMarkerStyle(20)

Fake_HighMT_mvis.SetLineColor(ROOT.kBlack)
Fake_HighMT_mvis.SetFillColor(ROOT.kRed)

embedded_HighMT_mvis.SetLineColor(ROOT.kBlack)
embedded_HighMT_mvis.SetFillColor(ROOT.kYellow)

DYAll_HighMT_mvis.SetLineColor(ROOT.kBlack)
DYAll_HighMT_mvis.SetFillColor(ROOT.kBlue)

TT_HighMT_mvis.SetLineColor(ROOT.kBlack)
TT_HighMT_mvis.SetLineColor(ROOT.kViolet)

VV_HighMT_mvis.SetLineColor(ROOT.kBlack)
VV_HighMT_mvis.SetFillColor(ROOT.kOrange)

ggH_htt125_HighMT_mvis.SetLineColor(ROOT.kBlack)
ggH_htt125_HighMT_mvis.SetFillColor(ROOT.kCyan)

qqH_htt125_HighMT_mvis.SetLineColor(ROOT.kBlack)
qqH_htt125_HighMT_mvis.SetFillColor(ROOT.kGreen)

WH_HighMT_mvis.SetLineColor(ROOT.kBlack)
WH_HighMT_mvis.SetFillColor(ROOT.kPink+6)

ZH125_HighMT_mvis.SetLineColor(ROOT.kBlack)
ZH125_HighMT_mvis.SetFillColor(ROOT.kGreen+3)

EWK_HighMT_mvis.SetLineColor(ROOT.kBlack)
EWK_HighMT_mvis.SetFillColor(ROOT.kBlue-2)

HighMT_mvis_Stack = ROOT.THStack("HighMT_mvis_Stack","HighMT_mvis_Stack")
HighMT_mvis_Stack.Add(Fake_HighMT_mvis, "HIST")
HighMT_mvis_Stack.Add(embedded_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(DYAll_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(TT_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(VV_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(ggH_htt125_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(qqH_htt125_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(WH_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(ZH125_HighMT_mvis,"HIST")
HighMT_mvis_Stack.Add(EWK_HighMT_mvis,"HIST")

HighMT_mvis_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
HighMT_mvis_Legend.AddEntry(EWK_HighMT_mvis,"EWK","f")
HighMT_mvis_Legend.AddEntry(ZH125_HighMT_mvis,"ZH","f")
HighMT_mvis_Legend.AddEntry(WH_HighMT_mvis,"WH","f")
HighMT_mvis_Legend.AddEntry(qqH_htt125_HighMT_mvis,"qqH","f")
HighMT_mvis_Legend.AddEntry(ggH_htt125_HighMT_mvis,"ggH","f")
HighMT_mvis_Legend.AddEntry(VV_HighMT_mvis,"VV+ST","f")
HighMT_mvis_Legend.AddEntry(TT_HighMT_mvis,"t#bar{t}","f")
HighMT_mvis_Legend.AddEntry(DYAll_HighMT_mvis,"Z#rightarrow ll","f")
HighMT_mvis_Legend.AddEntry(embedded_HighMT_mvis,"Z#rightarrow #tau#tau", "f")
HighMT_mvis_Legend.AddEntry(Fake_HighMT_mvis,"fakes","f")

#and the high mt Tau PT
data_obs_HighMT_TauPt = ResultsFile.Get("data_obs_mt_TauPt")
Fake_HighMT_TauPt = ResultsFile.Get("data_obs_mt_Fake_TauPt")
embedded_HighMT_TauPt = ResultsFile.Get("embedded_mt_TauPt")
DY_HighMT_TauPt = ResultsFile.Get("DY_mt_TauPt")
DYlow_HighMT_TauPt = ResultsFile.Get("DYlow_mt_TauPt")
TTToHadronic_HighMT_TauPt = ResultsFile.Get("TTToHadronic_mt_TauPt")
TTTo2L2Nu_HighMT_TauPt = ResultsFile.Get("TTTo2L2Nu_mt_TauPt")
TTToSemiLeptonic_HighMT_TauPt = ResultsFile.Get("TTToSemiLeptonic_mt_TauPt")
WW4Q_HighMT_TauPt = ResultsFile.Get("WW4Q_mt_TauPt")
WWLNuQQ_HighMT_TauPt = ResultsFile.Get("WWLNuQQ_mt_TauPt")
WZ2L2Q_HighMT_TauPt = ResultsFile.Get("WZ2L2Q_mt_TauPt")
WZ1L3Nu_HighMT_TauPt = ResultsFile.Get("WZ1L3Nu_mt_TauPt")
WZ3LNu_HighMT_TauPt = ResultsFile.Get("WZ3LNu_mt_TauPt")
WZ1L1Nu2Q_HighMT_TauPt = ResultsFile.Get("WZ1L1Nu2Q_mt_TauPt")
ZZ4L_HighMT_TauPt = ResultsFile.Get("ZZ4L_mt_TauPt")
ZZ2L2Nu_HighMT_TauPt = ResultsFile.Get("ZZ2L2Nu_mt_TauPt")
ZZ2L2Q_HighMT_TauPt = ResultsFile.Get("ZZ2L2Q_mt_TauPt")
ST_t_antitop_HighMT_TauPt = ResultsFile.Get("ST_t_antitop_mt_TauPt")
ST_t_top_HighMT_TauPt = ResultsFile.Get("ST_t_antitop_mt_TauPt")
ST_tW_antitop_HighMT_TauPt = ResultsFile.Get("ST_tW_antitop_mt_TauPt")
ST_tW_top_HighMT_TauPt = ResultsFile.Get("ST_tW_top_mt_TauPt")
ggH_htt125_HighMT_TauPt = ResultsFile.Get("ggH_htt125_mt_TauPt")
qqH_htt125_HighMT_TauPt = ResultsFile.Get("qqH_htt125_mt_TauPt")
WplusH125_HighMT_TauPt = ResultsFile.Get("WplusH125_mt_TauPt")
WminusH125_HighMT_TauPt = ResultsFile.Get("WminusH125_mt_TauPt")
ZH125_HighMT_TauPt = ResultsFile.Get("ZH125_mt_TauPt")
EWKZLL_HighMT_TauPt = ResultsFile.Get("EWKZLL_mt_TauPt")
EWKZNuNu_HighMT_TauPt = ResultsFile.Get("EWKZNuNu_mt_TauPt")

DYAll_HighMT_TauPt = DY_HighMT_TauPt.Clone()
DYAll_HighMT_TauPt.Add(DYlow_HighMT_TauPt)

TT_HighMT_TauPt = TTToHadronic_HighMT_TauPt.Clone();
TT_HighMT_TauPt.Add(TTTo2L2Nu_HighMT_TauPt)
TT_HighMT_TauPt.Add(TTToSemiLeptonic_HighMT_TauPt)

VV_HighMT_TauPt = WW4Q_HighMT_TauPt.Clone()
VV_HighMT_TauPt.Add(WWLNuQQ_HighMT_TauPt)
VV_HighMT_TauPt.Add(WZ2L2Q_HighMT_TauPt)
VV_HighMT_TauPt.Add(WZ1L3Nu_HighMT_TauPt)
VV_HighMT_TauPt.Add(WZ3LNu_HighMT_TauPt)
VV_HighMT_TauPt.Add(WZ1L1Nu2Q_HighMT_TauPt)
VV_HighMT_TauPt.Add(ZZ4L_HighMT_TauPt)
VV_HighMT_TauPt.Add(ZZ2L2Nu_HighMT_TauPt)
VV_HighMT_TauPt.Add(ZZ4L_HighMT_TauPt)
VV_HighMT_TauPt.Add(ZZ2L2Nu_HighMT_TauPt)
VV_HighMT_TauPt.Add(ZZ2L2Q_HighMT_TauPt)

ST_HighMT_TauPt = ST_t_antitop_HighMT_TauPt.Clone()
ST_HighMT_TauPt.Add(ST_t_top_HighMT_TauPt)
ST_HighMT_TauPt.Add(ST_tW_antitop_HighMT_TauPt)
ST_HighMT_TauPt.Add(ST_tW_top_HighMT_TauPt)
#handle this like we do in the other thing
VV_HighMT_TauPt.Add(ST_HighMT_TauPt)

WH_HighMT_TauPt = WplusH125_HighMT_TauPt.Clone()
WH_HighMT_TauPt.Add(WminusH125_HighMT_TauPt)

EWK_HighMT_TauPt = EWKZLL_HighMT_TauPt.Clone()
EWK_HighMT_TauPt.Add(EWKZNuNu_HighMT_TauPt)

data_obs_HighMT_TauPt.SetMarkerStyle(20)

Fake_HighMT_TauPt.SetLineColor(ROOT.kBlack)
Fake_HighMT_TauPt.SetFillColor(ROOT.kRed)

embedded_HighMT_TauPt.SetLineColor(ROOT.kBlack)
embedded_HighMT_TauPt.SetFillColor(ROOT.kYellow)

DYAll_HighMT_TauPt.SetLineColor(ROOT.kBlack)
DYAll_HighMT_TauPt.SetFillColor(ROOT.kBlue)

TT_HighMT_TauPt.SetLineColor(ROOT.kBlack)
TT_HighMT_TauPt.SetLineColor(ROOT.kViolet)

VV_HighMT_TauPt.SetLineColor(ROOT.kBlack)
VV_HighMT_TauPt.SetFillColor(ROOT.kOrange)

ggH_htt125_HighMT_TauPt.SetLineColor(ROOT.kBlack)
ggH_htt125_HighMT_TauPt.SetFillColor(ROOT.kCyan)

qqH_htt125_HighMT_TauPt.SetLineColor(ROOT.kBlack)
qqH_htt125_HighMT_TauPt.SetFillColor(ROOT.kGreen)

WH_HighMT_TauPt.SetLineColor(ROOT.kBlack)
WH_HighMT_TauPt.SetFillColor(ROOT.kPink+6)

ZH125_HighMT_TauPt.SetLineColor(ROOT.kBlack)
ZH125_HighMT_TauPt.SetFillColor(ROOT.kGreen+3)

EWK_HighMT_TauPt.SetLineColor(ROOT.kBlack)
EWK_HighMT_TauPt.SetFillColor(ROOT.kBlue-2)

HighMT_TauPt_Stack = ROOT.THStack("HighMT_TauPt_Stack","HighMT_TauPt_Stack")
HighMT_TauPt_Stack.Add(Fake_HighMT_TauPt, "HIST")
HighMT_TauPt_Stack.Add(embedded_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(DYAll_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(TT_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(VV_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(ggH_htt125_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(qqH_htt125_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(WH_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(ZH125_HighMT_TauPt,"HIST")
HighMT_TauPt_Stack.Add(EWK_HighMT_TauPt,"HIST")

HighMT_TauPt_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
HighMT_TauPt_Legend.AddEntry(EWK_HighMT_TauPt,"EWK","f")
HighMT_TauPt_Legend.AddEntry(ZH125_HighMT_TauPt,"ZH","f")
HighMT_TauPt_Legend.AddEntry(WH_HighMT_TauPt,"WH","f")
HighMT_TauPt_Legend.AddEntry(qqH_htt125_HighMT_TauPt,"qqH","f")
HighMT_TauPt_Legend.AddEntry(ggH_htt125_HighMT_TauPt,"ggH","f")
HighMT_TauPt_Legend.AddEntry(VV_HighMT_TauPt,"VV+ST","f")
HighMT_TauPt_Legend.AddEntry(TT_HighMT_TauPt,"t#bar{t}","f")
HighMT_TauPt_Legend.AddEntry(DYAll_HighMT_TauPt,"Z#rightarrow ll","f")
HighMT_TauPt_Legend.AddEntry(embedded_HighMT_TauPt,"Z#rightarrow #tau#tau", "f")
HighMT_TauPt_Legend.AddEntry(Fake_HighMT_TauPt,"fakes","f")

#do the ttbar enriched region
data_obs_TTBar_PZeta = ResultsFile.Get("data_obs_tt_PZeta")
Fake_TTBar_PZeta = ResultsFile.Get("data_obs_SS_Fake_mvis")
embedded_TTBar_PZeta = ResultsFile.Get("embedded_tt_PZeta")
DY_TTBar_PZeta = ResultsFile.Get("DY_tt_PZeta")
DYlow_TTBar_PZeta = ResultsFile.Get("DYlow_tt_PZeta")
TTToHadronic_TTBar_PZeta = ResultsFile.Get("TTToHadronic_tt_PZeta")
TTTo2L2Nu_TTBar_PZeta = ResultsFile.Get("TTTo2L2Nu_tt_PZeta")
TTToSemiLeptonic_TTBar_PZeta = ResultsFile.Get("TTToSemiLeptonic_tt_PZeta")
WW4Q_TTBar_PZeta = ResultsFile.Get("WW4Q_tt_PZeta")
WWLNuQQ_TTBar_PZeta = ResultsFile.Get("WWLNuQQ_tt_PZeta")
WZ2L2Q_TTBar_PZeta = ResultsFile.Get("WZ2L2Q_tt_PZeta")
WZ1L3Nu_TTBar_PZeta = ResultsFile.Get("WZ1L3Nu_tt_PZeta")
WZ3LNu_TTBar_PZeta = ResultsFile.Get("WZ3LNu_tt_PZeta")
WZ1L1Nu2Q_TTBar_PZeta = ResultsFile.Get("WZ1L1Nu2Q_tt_PZeta")
ZZ4L_TTBar_PZeta = ResultsFile.Get("ZZ4L_tt_PZeta")
ZZ2L2Nu_TTBar_PZeta = ResultsFile.Get("ZZ2L2Nu_tt_PZeta")
ZZ2L2Q_TTBar_PZeta = ResultsFile.Get("ZZ2L2Q_tt_PZeta")
ST_t_antitop_TTBar_PZeta = ResultsFile.Get("ST_t_antitop_tt_PZeta")
ST_t_top_TTBar_PZeta = ResultsFile.Get("ST_t_antitop_tt_PZeta")
ST_tW_antitop_TTBar_PZeta = ResultsFile.Get("ST_tW_antitop_tt_PZeta")
ST_tW_top_TTBar_PZeta = ResultsFile.Get("ST_tW_top_tt_PZeta")
ggH_htt125_TTBar_PZeta = ResultsFile.Get("ggH_htt125_tt_PZeta")
qqH_htt125_TTBar_PZeta = ResultsFile.Get("qqH_htt125_tt_PZeta")
WplusH125_TTBar_PZeta = ResultsFile.Get("WplusH125_tt_PZeta")
WminusH125_TTBar_PZeta = ResultsFile.Get("WminusH125_tt_PZeta")
ZH125_TTBar_PZeta = ResultsFile.Get("ZH125_tt_PZeta")
EWKZLL_TTBar_PZeta = ResultsFile.Get("EWKZLL_tt_PZeta")
EWKZNuNu_TTBar_PZeta = ResultsFile.Get("EWKZNuNu_tt_PZeta")

DYAll_TTBar_PZeta = DY_TTBar_PZeta.Clone()
DYAll_TTBar_PZeta.Add(DYlow_TTBar_PZeta)

TT_TTBar_PZeta = TTToHadronic_TTBar_PZeta.Clone();
TT_TTBar_PZeta.Add(TTTo2L2Nu_TTBar_PZeta)
TT_TTBar_PZeta.Add(TTToSemiLeptonic_TTBar_PZeta)

VV_TTBar_PZeta = WW4Q_TTBar_PZeta.Clone()
VV_TTBar_PZeta.Add(WWLNuQQ_TTBar_PZeta)
VV_TTBar_PZeta.Add(WZ2L2Q_TTBar_PZeta)
VV_TTBar_PZeta.Add(WZ1L3Nu_TTBar_PZeta)
VV_TTBar_PZeta.Add(WZ3LNu_TTBar_PZeta)
VV_TTBar_PZeta.Add(WZ1L1Nu2Q_TTBar_PZeta)
VV_TTBar_PZeta.Add(ZZ4L_TTBar_PZeta)
VV_TTBar_PZeta.Add(ZZ2L2Nu_TTBar_PZeta)
VV_TTBar_PZeta.Add(ZZ4L_TTBar_PZeta)
VV_TTBar_PZeta.Add(ZZ2L2Nu_TTBar_PZeta)
VV_TTBar_PZeta.Add(ZZ2L2Q_TTBar_PZeta)

ST_TTBar_PZeta = ST_t_antitop_TTBar_PZeta.Clone()
ST_TTBar_PZeta.Add(ST_t_top_TTBar_PZeta)
ST_TTBar_PZeta.Add(ST_tW_antitop_TTBar_PZeta)
ST_TTBar_PZeta.Add(ST_tW_top_TTBar_PZeta)
#handle this like we do in the other thing
VV_TTBar_PZeta.Add(ST_TTBar_PZeta)

WH_TTBar_PZeta = WplusH125_TTBar_PZeta.Clone()
WH_TTBar_PZeta.Add(WminusH125_TTBar_PZeta)

EWK_TTBar_PZeta = EWKZLL_TTBar_PZeta.Clone()
EWK_TTBar_PZeta.Add(EWKZNuNu_TTBar_PZeta)

data_obs_TTBar_PZeta.SetMarkerStyle(20)

Fake_TTBar_PZeta.SetLineColor(ROOT.kBlack)
Fake_TTBar_PZeta.SetFillColor(ROOT.kRed)

embedded_TTBar_PZeta.SetLineColor(ROOT.kBlack)
embedded_TTBar_PZeta.SetFillColor(ROOT.kYellow)

DYAll_TTBar_PZeta.SetLineColor(ROOT.kBlack)
DYAll_TTBar_PZeta.SetFillColor(ROOT.kBlue)

TT_TTBar_PZeta.SetLineColor(ROOT.kBlack)
TT_TTBar_PZeta.SetLineColor(ROOT.kViolet)

VV_TTBar_PZeta.SetLineColor(ROOT.kBlack)
VV_TTBar_PZeta.SetFillColor(ROOT.kOrange)

ggH_htt125_TTBar_PZeta.SetLineColor(ROOT.kBlack)
ggH_htt125_TTBar_PZeta.SetFillColor(ROOT.kCyan)

qqH_htt125_TTBar_PZeta.SetLineColor(ROOT.kBlack)
qqH_htt125_TTBar_PZeta.SetFillColor(ROOT.kGreen)

WH_TTBar_PZeta.SetLineColor(ROOT.kBlack)
WH_TTBar_PZeta.SetFillColor(ROOT.kPink+6)

ZH125_TTBar_PZeta.SetLineColor(ROOT.kBlack)
ZH125_TTBar_PZeta.SetFillColor(ROOT.kGreen+3)

EWK_TTBar_PZeta.SetLineColor(ROOT.kBlack)
EWK_TTBar_PZeta.SetFillColor(ROOT.kBlue-2)

TTBar_PZeta_Stack = ROOT.THStack("TTBar_PZeta_Stack","TTBar_PZeta_Stack")
TTBar_PZeta_Stack.Add(Fake_TTBar_PZeta, "HIST")
TTBar_PZeta_Stack.Add(embedded_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(DYAll_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(TT_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(VV_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(ggH_htt125_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(qqH_htt125_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(WH_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(ZH125_TTBar_PZeta,"HIST")
TTBar_PZeta_Stack.Add(EWK_TTBar_PZeta,"HIST")

TTBar_PZeta_Legend = ROOT.TLegend(0.9,0.6,1.0,0.9)
TTBar_PZeta_Legend.AddEntry(EWK_TTBar_PZeta,"EWK","f")
TTBar_PZeta_Legend.AddEntry(ZH125_TTBar_PZeta,"ZH","f")
TTBar_PZeta_Legend.AddEntry(WH_TTBar_PZeta,"WH","f")
TTBar_PZeta_Legend.AddEntry(qqH_htt125_TTBar_PZeta,"qqH","f")
TTBar_PZeta_Legend.AddEntry(ggH_htt125_TTBar_PZeta,"ggH","f")
TTBar_PZeta_Legend.AddEntry(VV_TTBar_PZeta,"VV+ST","f")
TTBar_PZeta_Legend.AddEntry(TT_TTBar_PZeta,"t#bar{t}","f")
TTBar_PZeta_Legend.AddEntry(DYAll_TTBar_PZeta,"Z#rightarrow ll","f")
TTBar_PZeta_Legend.AddEntry(embedded_TTBar_PZeta,"Z#rightarrow #tau#tau", "f")
TTBar_PZeta_Legend.AddEntry(Fake_TTBar_PZeta,"fakes","f")

#Create a file and write our objects there.
OutFile = ROOT.TFile("ExtraControlRegions.root","RECREATE")
SS_mvis_dir = OutFile.mkdir("SS_mvis")
SS_mvis_dir.cd()
data_obs_SS_mvis.Write()
SS_mvis_Stack.Write()
SS_mvis_Legend.Write()

SS_TauPt_dir = OutFile.mkdir("SS_TauPt")
SS_TauPt_dir.cd()
data_obs_SS_TauPt.Write()
SS_TauPt_Stack.Write()
SS_TauPt_Legend.Write()

HighMT_mvis_dir = OutFile.mkdir("HighMT_mvis")
HighMT_mvis_dir.cd()
data_obs_HighMT_mvis.Write()
HighMT_mvis_Stack.Write()
HighMT_mvis_Legend.Write()

HighMT_TauPt_dir = OutFile.mkdir("HighMT_TauPt")
HighMT_TauPt_dir.cd()
data_obs_HighMT_TauPt.Write()
HighMT_TauPt_Stack.Write()
HighMT_TauPt_Legend.Write()

TTBar_PZeta_dir = OutFile.mkdir("TTBar_PZeta")
TTBar_PZeta_dir.cd()
data_obs_TTBar_PZeta.Write()
TTBar_PZeta_Stack.Write()
TTBar_PZeta_Legend.Write()
