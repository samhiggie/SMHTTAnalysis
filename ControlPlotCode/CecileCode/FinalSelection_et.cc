#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "et_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTGraph.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH2F.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH3D.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTFormula.h"
#include "HTTutilities/Jet2TauFakes/interface/IFunctionWrapper.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeWG1Unc.h"
#include "SFtautrigger.h"
#include "btagSF.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("etau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=41300;
    if (sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="WZ1L1Nu2Q") {xs=11.66; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.293; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu") {xs=5.052; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=6.331; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.325; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=13.97; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu") {xs=11.08; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu") {xs=0.6008; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.688; weight=luminosity*xs/ngen;}
    else if (sample=="WW4Q") {xs=47.73; weight=luminosity*xs/ngen;}
    else if (sample=="WWLNuQQ") {xs=45.99; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=26.23; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=44.07; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarMuMu") {xs=2.793; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarEE") {xs=3.526; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage0_cat", &Rivet_stage0_cat);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);

    arbre->SetBranchAddress("passEle27", &passEle27);
    arbre->SetBranchAddress("passEle32", &passEle32);
    arbre->SetBranchAddress("passEle35", &passEle35);
    arbre->SetBranchAddress("passEle24Tau30", &passEle24Tau30);

    arbre->SetBranchAddress("matchEle27_1", &matchEle27_1);
    arbre->SetBranchAddress("matchEle32_1", &matchEle32_1);
    arbre->SetBranchAddress("matchEle35_1", &matchEle35_1);
    arbre->SetBranchAddress("matchEle24Tau30_1", &matchEle24Tau30_1);
    arbre->SetBranchAddress("matchEle24Tau30_2", &matchEle24Tau30_2);
    arbre->SetBranchAddress("filterEle27_1", &filterEle27_1);
    arbre->SetBranchAddress("filterEle32_1", &filterEle32_1);
    arbre->SetBranchAddress("filterEle35_1", &filterEle35_1);
    arbre->SetBranchAddress("filterEle24Tau30_1", &filterEle24Tau30_1);
    arbre->SetBranchAddress("filterEle24Tau30_2", &filterEle24Tau30_2);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("isoDB_1", &isoDB_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("nbtagWoNoisyJets", &nbtagWoNoisyJets);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    arbre->SetBranchAddress("m_sv_UP", &m_sv_UP);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("njetsWoNoisyJets", &njetsWoNoisyJets);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta0to3Down", &njetsWoNoisyJets_JetEta0to3Down);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta0to3Up", &njetsWoNoisyJets_JetEta0to3Up);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetRelativeSampleDown", &njetsWoNoisyJets_JetRelativeSampleDown);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetRelativeSampleUp", &njetsWoNoisyJets_JetRelativeSampleUp);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetRelativeBalDown", &njetsWoNoisyJets_JetRelativeBalDown);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetRelativeBalUp", &njetsWoNoisyJets_JetRelativeBalUp);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta0to5Down", &njetsWoNoisyJets_JetEta0to5Down);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta0to5Up", &njetsWoNoisyJets_JetEta0to5Up);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta3to5Down", &njetsWoNoisyJets_JetEta3to5Down);
    arbre->SetBranchAddress("njetsWoNoisyJets_JetEta3to5Up", &njetsWoNoisyJets_JetEta3to5Up);
    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("jeta_1", &jeta_1);
    arbre->SetBranchAddress("jphi_1", &jphi_1);
    arbre->SetBranchAddress("jpt_2", &jpt_2);
    arbre->SetBranchAddress("jeta_2", &jeta_2);
    arbre->SetBranchAddress("jphi_2", &jphi_2);
    arbre->SetBranchAddress("bpt_1", &bpt_1);
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
    arbre->SetBranchAddress("bpt_2", &bpt_2);
    arbre->SetBranchAddress("beta_2", &beta_2);
    arbre->SetBranchAddress("bphi_2", &bphi_2);
    arbre->SetBranchAddress("bflavor_1", &bflavor_1);
    arbre->SetBranchAddress("bflavor_2", &bflavor_2);
    arbre->SetBranchAddress("mjj", &mjj);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta0to3Down", &mjjWoNoisyJets_JetEta0to3Down);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta0to3Up", &mjjWoNoisyJets_JetEta0to3Up);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta3to5Down", &mjjWoNoisyJets_JetEta3to5Down);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta3to5Up", &mjjWoNoisyJets_JetEta3to5Up);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta0to5Down", &mjjWoNoisyJets_JetEta0to5Down);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetEta0to5Up", &mjjWoNoisyJets_JetEta0to5Up);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetRelativeBalDown", &mjjWoNoisyJets_JetRelativeBalDown);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetRelativeBalUp", &mjjWoNoisyJets_JetRelativeBalUp);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetRelativeSampleDown", &mjjWoNoisyJets_JetRelativeSampleDown);
    arbre->SetBranchAddress("mjjWoNoisyJets_JetRelativeSampleUp", &mjjWoNoisyJets_JetRelativeSampleUp);
    arbre->SetBranchAddress("mjjWoNoisyJets", &mjjWoNoisyJets);
    arbre->SetBranchAddress("genweight", &genweight);
    arbre->SetBranchAddress("byVLooseIsolationMVArun2v2DBoldDMwLT_2",&byVLooseIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byLooseIsolationMVArun2v2DBoldDMwLT_2",&byLooseIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byMediumIsolationMVArun2v2DBoldDMwLT_2",&byMediumIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byTightIsolationMVArun2v2DBoldDMwLT_2",&byTightIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byVTightIsolationMVArun2v2DBoldDMwLT_2",&byVTightIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2",&byIsolationMVA3oldDMwLTraw_2);
    arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
    arbre->SetBranchAddress("againstElectronTightMVA6_2",&againstElectronTightMVA6_2);
    arbre->SetBranchAddress("againstMuonLoose3_2",&againstMuonLoose3_2);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("flag_BadChargedCandidate",&flag_BadChargedCandidate);
    arbre->SetBranchAddress("flag_BadPFMuon",&flag_BadPFMuon);
    arbre->SetBranchAddress("flag_EcalDeadCellTriggerPrimitive",&flag_EcalDeadCellTriggerPrimitive);
    arbre->SetBranchAddress("flag_HBHENoise",&flag_HBHENoise);
    arbre->SetBranchAddress("flag_HBHENoiseIso",&flag_HBHENoiseIso);
    arbre->SetBranchAddress("flag_eeBadSc",&flag_eeBadSc);
    arbre->SetBranchAddress("flag_globalTightHalo2016",&flag_globalTightHalo2016);
    arbre->SetBranchAddress("flag_goodVertices",&flag_goodVertices);
    arbre->SetBranchAddress("flag_globalSuperTightHalo2016",&flag_globalSuperTightHalo2016);
    arbre->SetBranchAddress("flag_ecalBadCalib",&flag_ecalBadCalib);
    arbre->SetBranchAddress("flag_duplicateMuons",&flag_duplicateMuons);
    arbre->SetBranchAddress("flag_badMuons",&flag_badMuons);

   bool is_ggh=(name.find("ggH") < 140);
   int nbhist=1;
   if (sample=="data_obs") nbhist=31;
   else if (is_ggh) nbhist=45; 
   else nbhist=27;

   /*TH1F *h0tau_OS=new TH1F ("h0tau_OS","Invariant mass",20,0,200);h0tau_OS->Sumw2();
   TH1F *h1tau_OS=new TH1F ("h1tau_OS","Invariant mass",20,0,200);h1tau_OS->Sumw2();
   TH1F *h2tau_OS=new TH1F ("h2tau_OS","Invariant mass",20,0,200);h2tau_OS->Sumw2();
   TH1F *h0ell_OS=new TH1F ("h0ell_OS","Invariant mass",20,0,200);h0ell_OS->Sumw2();
   TH1F *h1ell_OS=new TH1F ("h1ell_OS","Invariant mass",20,0,200);h1ell_OS->Sumw2();
   TH1F *h2ell_OS=new TH1F ("h2ell_OS","Invariant mass",20,0,200);h2ell_OS->Sumw2();
   TH1F *h0jet_OS=new TH1F ("h0jet_OS","Invariant mass",20,0,200);h0jet_OS->Sumw2();
   TH1F *h1jet_OS=new TH1F ("h1jet_OS","Invariant mass",20,0,200);h1jet_OS->Sumw2();
   TH1F *h2jet_OS=new TH1F ("h2jet_OS","Invariant mass",20,0,200);h2jet_OS->Sumw2();
   TH1F *h0tau_AI=new TH1F ("h0tau_AI","Invariant mass",20,0,200);h0tau_AI->Sumw2();
   TH1F *h1tau_AI=new TH1F ("h1tau_AI","Invariant mass",20,0,200);h1tau_AI->Sumw2();
   TH1F *h2tau_AI=new TH1F ("h2tau_AI","Invariant mass",20,0,200);h2tau_AI->Sumw2();
   TH1F *h0ell_AI=new TH1F ("h0ell_AI","Invariant mass",20,0,200);h0ell_AI->Sumw2();
   TH1F *h1ell_AI=new TH1F ("h1ell_AI","Invariant mass",20,0,200);h1ell_AI->Sumw2();
   TH1F *h2ell_AI=new TH1F ("h2ell_AI","Invariant mass",20,0,200);h2ell_AI->Sumw2();
   TH1F *h0jet_AI=new TH1F ("h0jet_AI","Invariant mass",20,0,200);h0jet_AI->Sumw2();
   TH1F *h1jet_AI=new TH1F ("h1jet_AI","Invariant mass",20,0,200);h1jet_AI->Sumw2();
   TH1F *h2jet_AI=new TH1F ("h2jet_AI","Invariant mass",20,0,200);h2jet_AI->Sumw2();*/

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h0jet_OS;
   std::vector<TH2F*> h1jet_OS;
   std::vector<TH2F*> h2jet_OS;
   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h0ell_AI;
   std::vector<TH2F*> h1ell_AI;
   std::vector<TH2F*> h2ell_AI;
   std::vector<TH2F*> h0jet_AI;
   std::vector<TH2F*> h1jet_AI;
   std::vector<TH2F*> h2jet_AI;

   std::vector<TH1F*> h3tau_OS;
   std::vector<TH1F*> h4tau_OS;
   std::vector<TH1F*> h5tau_OS;
   std::vector<TH1F*> h6tau_OS;
   std::vector<TH1F*> h3ell_OS;
   std::vector<TH1F*> h4ell_OS;
   std::vector<TH1F*> h5ell_OS;
   std::vector<TH1F*> h6ell_OS;
   std::vector<TH1F*> h3jet_OS;
   std::vector<TH1F*> h4jet_OS;
   std::vector<TH1F*> h5jet_OS;
   std::vector<TH1F*> h6jet_OS;
   std::vector<TH1F*> h3tau_AI;
   std::vector<TH1F*> h4tau_AI;
   std::vector<TH1F*> h5tau_AI;
   std::vector<TH1F*> h6tau_AI;
   std::vector<TH1F*> h3ell_AI;
   std::vector<TH1F*> h4ell_AI;
   std::vector<TH1F*> h5ell_AI;
   std::vector<TH1F*> h6ell_AI;
   std::vector<TH1F*> h3jet_AI;
   std::vector<TH1F*> h4jet_AI;
   std::vector<TH1F*> h5jet_AI;
   std::vector<TH1F*> h6jet_AI;

   float bins_mtt0[] = {0,45,65,75,85,95,105,115,155,405};
   int  binnum_mtt0 = sizeof(bins_mtt0)/sizeof(Float_t) - 1;
   float bins_mtt1[] = {0,40,80,90,100,110,120,130,140,150,160,180,200,250};
   int  binnum_mtt1 = sizeof(bins_mtt1)/sizeof(Float_t) - 1;
   float bins_mtt2[] = {0,50,95,115,135,155,200,400};
   int  binnum_mtt2 = sizeof(bins_mtt2)/sizeof(Float_t) - 1;

   float bins_mtt[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   int  binnum_mtt = sizeof(bins_mtt)/sizeof(Float_t) - 1;

   float bins_mjj[] = {400,700,1000,1300,1600,1900,10000};
   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   float bins_pth[] = {0,100,150,200,250,10000};
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   float bins_taupt[] = {20,25,30,40,50,1000};
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h0tau_OS.push_back(new TH2F (HNS0tauOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_OS[k]->Sumw2();
        h1tau_OS.push_back(new TH2F (HNS1tauOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_OS[k]->Sumw2();
        h2tau_OS.push_back(new TH2F (HNS2tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_OS[k]->Sumw2();
        ostringstream HNS0jetOS; HNS0jetOS << "h0jet_OS" << k;
        ostringstream HNS1jetOS; HNS1jetOS << "h1jet_OS" << k;
        ostringstream HNS2jetOS; HNS2jetOS << "h2jet_OS" << k;
        h0jet_OS.push_back(new TH2F (HNS0jetOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_OS[k]->Sumw2();
        h1jet_OS.push_back(new TH2F (HNS1jetOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_OS[k]->Sumw2();
        h2jet_OS.push_back(new TH2F (HNS2jetOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_OS[k]->Sumw2();
        ostringstream HNS0ellOS; HNS0ellOS << "h0ell_OS" << k;
        ostringstream HNS1ellOS; HNS1ellOS << "h1ell_OS" << k;
        ostringstream HNS2ellOS; HNS2ellOS << "h2ell_OS" << k;
        h0ell_OS.push_back(new TH2F (HNS0ellOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_OS[k]->Sumw2();
        h1ell_OS.push_back(new TH2F (HNS1ellOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_OS[k]->Sumw2();
        h2ell_OS.push_back(new TH2F (HNS2ellOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_OS[k]->Sumw2();

        ostringstream HNS3tauOS; HNS3tauOS << "h3tau_OS" << k;
        ostringstream HNS4tauOS; HNS4tauOS << "h4tau_OS" << k;
        ostringstream HNS5tauOS; HNS5tauOS << "h5tau_OS" << k;
        ostringstream HNS6tauOS; HNS6tauOS << "h6tau_OS" << k;
        h3tau_OS.push_back(new TH1F (HNS3tauOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3tau_OS[k]->Sumw2();
        h4tau_OS.push_back(new TH1F (HNS4tauOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4tau_OS[k]->Sumw2();
        h5tau_OS.push_back(new TH1F (HNS5tauOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5tau_OS[k]->Sumw2();
        h6tau_OS.push_back(new TH1F (HNS6tauOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6tau_OS[k]->Sumw2();
        ostringstream HNS3jetOS; HNS3jetOS << "h3jet_OS" << k;
        ostringstream HNS4jetOS; HNS4jetOS << "h4jet_OS" << k;
        ostringstream HNS5jetOS; HNS5jetOS << "h5jet_OS" << k;
        ostringstream HNS6jetOS; HNS6jetOS << "h6jet_OS" << k;
        h3jet_OS.push_back(new TH1F (HNS3jetOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3jet_OS[k]->Sumw2();
        h4jet_OS.push_back(new TH1F (HNS4jetOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4jet_OS[k]->Sumw2();
        h5jet_OS.push_back(new TH1F (HNS5jetOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5jet_OS[k]->Sumw2();
        h6jet_OS.push_back(new TH1F (HNS6jetOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6jet_OS[k]->Sumw2();
        ostringstream HNS3ellOS; HNS3ellOS << "h3ell_OS" << k;
        ostringstream HNS4ellOS; HNS4ellOS << "h4ell_OS" << k;
        ostringstream HNS5ellOS; HNS5ellOS << "h5ell_OS" << k;
        ostringstream HNS6ellOS; HNS6ellOS << "h6ell_OS" << k;
        h3ell_OS.push_back(new TH1F (HNS3ellOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3ell_OS[k]->Sumw2();
        h4ell_OS.push_back(new TH1F (HNS4ellOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4ell_OS[k]->Sumw2();
        h5ell_OS.push_back(new TH1F (HNS5ellOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5ell_OS[k]->Sumw2();
        h6ell_OS.push_back(new TH1F (HNS6ellOS.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6ell_OS[k]->Sumw2();

        ostringstream HNS0tauAI; HNS0tauAI << "h0tau_AI" << k;
        ostringstream HNS1tauAI; HNS1tauAI << "h1tau_AI" << k;
        ostringstream HNS2tauAI; HNS2tauAI << "h2tau_AI" << k;
        h0tau_AI.push_back(new TH2F (HNS0tauAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_AI[k]->Sumw2();
        h1tau_AI.push_back(new TH2F (HNS1tauAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_AI[k]->Sumw2();
        h2tau_AI.push_back(new TH2F (HNS2tauAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_AI[k]->Sumw2();
        ostringstream HNS0jetAI; HNS0jetAI << "h0jet_AI" << k;
        ostringstream HNS1jetAI; HNS1jetAI << "h1jet_AI" << k;
        ostringstream HNS2jetAI; HNS2jetAI << "h2jet_AI" << k;
        h0jet_AI.push_back(new TH2F (HNS0jetAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_AI[k]->Sumw2();
        h1jet_AI.push_back(new TH2F (HNS1jetAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_AI[k]->Sumw2();
        h2jet_AI.push_back(new TH2F (HNS2jetAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_AI[k]->Sumw2();
        ostringstream HNS0ellAI; HNS0ellAI << "h0ell_AI" << k;
        ostringstream HNS1ellAI; HNS1ellAI << "h1ell_AI" << k;
        ostringstream HNS2ellAI; HNS2ellAI << "h2ell_AI" << k;
        h0ell_AI.push_back(new TH2F (HNS0ellAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_AI[k]->Sumw2();
        h1ell_AI.push_back(new TH2F (HNS1ellAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_AI[k]->Sumw2();
        h2ell_AI.push_back(new TH2F (HNS2ellAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_AI[k]->Sumw2();

        ostringstream HNS3tauAI; HNS3tauAI << "h3tau_AI" << k;
        ostringstream HNS4tauAI; HNS4tauAI << "h4tau_AI" << k;
        ostringstream HNS5tauAI; HNS5tauAI << "h5tau_AI" << k;
        ostringstream HNS6tauAI; HNS6tauAI << "h6tau_AI" << k;
        h3tau_AI.push_back(new TH1F (HNS3tauAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3tau_AI[k]->Sumw2();
        h4tau_AI.push_back(new TH1F (HNS4tauAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4tau_AI[k]->Sumw2();
        h5tau_AI.push_back(new TH1F (HNS5tauAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5tau_AI[k]->Sumw2();
        h6tau_AI.push_back(new TH1F (HNS6tauAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6tau_AI[k]->Sumw2();
        ostringstream HNS3jetAI; HNS3jetAI << "h3jet_AI" << k;
        ostringstream HNS4jetAI; HNS4jetAI << "h4jet_AI" << k;
        ostringstream HNS5jetAI; HNS5jetAI << "h5jet_AI" << k;
        ostringstream HNS6jetAI; HNS6jetAI << "h6jet_AI" << k;
        h3jet_AI.push_back(new TH1F (HNS3jetAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3jet_AI[k]->Sumw2();
        h4jet_AI.push_back(new TH1F (HNS4jetAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4jet_AI[k]->Sumw2();
        h5jet_AI.push_back(new TH1F (HNS5jetAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5jet_AI[k]->Sumw2();
        h6jet_AI.push_back(new TH1F (HNS6jetAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6jet_AI[k]->Sumw2();
        ostringstream HNS3ellAI; HNS3ellAI << "h3ell_AI" << k;
        ostringstream HNS4ellAI; HNS4ellAI << "h4ell_AI" << k;
        ostringstream HNS5ellAI; HNS5ellAI << "h5ell_AI" << k;
        ostringstream HNS6ellAI; HNS6ellAI << "h6ell_AI" << k;
        h3ell_AI.push_back(new TH1F (HNS3ellAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h3ell_AI[k]->Sumw2();
        h4ell_AI.push_back(new TH1F (HNS4ellAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h4ell_AI[k]->Sumw2();
        h5ell_AI.push_back(new TH1F (HNS5ellAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h5ell_AI[k]->Sumw2();
        h6ell_AI.push_back(new TH1F (HNS6ellAI.str().c_str(),"InvMa",binnum_mtt,bins_mtt)); h6ell_AI[k]->Sumw2();
     }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting(input, "MyDataPileupHistogram.root", "pileup_mc", "pileup");
   //LumiWeights_12 = new reweight::LumiReWeighting("pudistributions_mc_2017.root", "pudistributions_data_2017.root", "pileup", "pileup");

   TFile *ffrac=new TFile("files_nominal_et/fractions.root");
   TH1F* frac_w_0jet=(TH1F*) ffrac->Get("frac_w_0jet");
   TH1F* frac_tt_0jet=(TH1F*) ffrac->Get("frac_tt_0jet");
   TH1F* frac_qcd_0jet=(TH1F*) ffrac->Get("frac_qcd_0jet");
   TH1F* frac_data_0jet=(TH1F*) ffrac->Get("frac_data_0jet");
   TH1F* frac_w_boosted=(TH1F*) ffrac->Get("frac_w_boosted");
   TH1F* frac_tt_boosted=(TH1F*) ffrac->Get("frac_tt_boosted");
   TH1F* frac_qcd_boosted=(TH1F*) ffrac->Get("frac_qcd_boosted");
   TH1F* frac_data_boosted=(TH1F*) ffrac->Get("frac_data_boosted");
   TH1F* frac_w_vbf=(TH1F*) ffrac->Get("frac_w_vbf");
   TH1F* frac_tt_vbf=(TH1F*) ffrac->Get("frac_tt_vbf");
   TH1F* frac_qcd_vbf=(TH1F*) ffrac->Get("frac_qcd_vbf");
   TH1F* frac_data_vbf=(TH1F*) ffrac->Get("frac_data_vbf");

   TFile* f_btag_eff=new TFile("tagging_efficiencies_march2018_btageff-all_samp-inc-DeepCSV_medium.root","r");
   TH2F* h_btag_eff_b=(TH2F*) f_btag_eff->Get("btag_eff_b");
   TH2F* h_btag_eff_c=(TH2F*) f_btag_eff->Get("btag_eff_c");
   TH2F* h_btag_eff_oth=(TH2F*) f_btag_eff->Get("btag_eff_oth");

   TFile fw("htt_scalefactors_v17_5.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_2017_v2.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   TFile* ff_file = TFile::Open("HTTutilities/Jet2TauFakes/data/SM2017/tight/vloose/et/fakeFactors.root");
   FakeFactor* ff = (FakeFactor*)ff_file->Get("ff_comb");
   const std::vector<std::string>& inputNames = ff->inputs();
   std::vector<double> inputs(9);

   TString postfixMC[45]={"","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_JetEta0to3_13TeVDown","_CMS_JetEta0to3_13TeVUp","_CMS_JetEta0to5_13TeVDown","_CMS_JetEta0to5_13TeVUp","_CMS_JetEta3to5_13TeVDown","_CMS_JetEta3to5_13TeVUp","_CMS_JetRelativeSample_13TeVDown","_CMS_JetRelativeSample_13TeVUp","_CMS_JetRelativeBal_13TeVDown","_CMS_JetRelativeBal_13TeVUp","_CMS_scale_efaket_1prong_13TeVDown","_CMS_scale_efaket_1prong_13TeVUp","_CMS_scale_efaket_1prong1pizero_13TeVDown","_CMS_scale_efaket_1prong1pizero_13TeVUp","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_htt_ttbarShape_13TeVDown","_CMS_htt_ttbarShape_13TeVUp","_CMS_htt_dyShape_13TeVDown","_CMS_htt_dyShape_13TeVUp","_THU_ggH_Mu_13TeVUp","_THU_ggH_Mu_13TeVDown","_THU_ggH_Res_13TeVUp","_THU_ggH_Res_13TeVDown","_THU_ggH_Mig01_13TeVUp","_THU_ggH_Mig01_13TeVDown","_THU_ggH_Mig12_13TeVUp","_THU_ggH_Mig12_13TeVDown","_THU_ggH_VBF2j_13TeVUp","_THU_ggH_VBF2j_13TeVDown","_THU_ggH_VBF3j_13TeVUp","_THU_ggH_VBF3j_13TeVDown","_THU_ggH_PT60_13TeVUp","_THU_ggH_PT60_13TeVDown","_THU_ggH_PT120_13TeVUp","_THU_ggH_PT120_13TeVDown","_THU_ggH_qmtop_13TeVUp","_THU_ggH_qmtop_13TeVDown"};


   TString postfixFF[31]={"","_norm_ff_qcd_et_systUp","_norm_ff_qcd_et_systDown","_norm_ff_qcd_dm0_njet0_et_statUp","_norm_ff_qcd_dm0_njet0_et_statDown","_norm_ff_qcd_dm0_njet1_et_statUp","_norm_ff_qcd_dm0_njet1_et_statDown","_norm_ff_qcd_dm1_njet0_et_statUp","_norm_ff_qcd_dm1_njet0_et_statDown","_norm_ff_qcd_dm1_njet1_et_statUp","_norm_ff_qcd_dm1_njet1_et_statDown","_norm_ff_w_et_systUp","_norm_ff_w_et_systDown","_norm_ff_w_dm0_njet0_et_statUp","_norm_ff_w_dm0_njet0_et_statDown","_norm_ff_w_dm0_njet1_et_statUp","_norm_ff_w_dm0_njet1_et_statDown","_norm_ff_w_dm1_njet0_et_statUp","_norm_ff_w_dm1_njet0_et_statDown","_norm_ff_w_dm1_njet1_et_statUp","_norm_ff_w_dm1_njet1_et_statDown","_norm_ff_tt_et_systUp","_norm_ff_tt_et_systDown","_norm_ff_tt_dm0_njet0_et_statUp","_norm_ff_tt_dm0_njet0_et_statDown","_norm_ff_tt_dm0_njet1_et_statUp","_norm_ff_tt_dm0_njet1_et_statDown","_norm_ff_tt_dm1_njet0_et_statUp","_norm_ff_tt_dm1_njet0_et_statDown","_norm_ff_tt_dm1_njet1_et_statUp","_norm_ff_tt_dm1_njet1_et_statDown"};

   std::string FFsys[30]={"ff_qcd_syst_up","ff_qcd_syst_down","ff_qcd_dm0_njet0_stat_up","ff_qcd_dm0_njet0_stat_down","ff_qcd_dm0_njet1_stat_up","ff_qcd_dm0_njet1_stat_down","ff_qcd_dm1_njet0_stat_up","ff_qcd_dm1_njet0_stat_down","ff_qcd_dm1_njet1_stat_up","ff_qcd_dm1_njet1_stat_down","ff_w_syst_up","ff_w_syst_down","ff_w_dm0_njet0_stat_up","ff_w_dm0_njet0_stat_down","ff_w_dm0_njet1_stat_up","ff_w_dm0_njet1_stat_down","ff_w_dm1_njet0_stat_up","ff_w_dm1_njet0_stat_down","ff_w_dm1_njet1_stat_up","ff_w_dm1_njet1_stat_down","ff_tt_syst_up","ff_tt_syst_down","ff_tt_dm0_njet0_stat_up","ff_tt_dm0_njet0_stat_down","ff_tt_dm0_njet1_stat_up","ff_tt_dm0_njet1_stat_down","ff_tt_dm1_njet0_stat_up","ff_tt_dm1_njet0_stat_down","ff_tt_dm1_njet1_stat_up","ff_tt_dm1_njet1_stat_down"};

   TFile *fTylerN = new TFile("TauTriggerSFs2017/data/tauTriggerEfficiencies2017_New.root");
   TFile *fTyler = new TFile("TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root");
   TH1F* eTauData_ =(TH1F*) fTylerN->Get("hist_ETauTriggerEfficiency_tightTauMVA_DATA");
   TH1F* eTauMC_ =(TH1F*) fTylerN->Get("hist_ETauTriggerEfficiency_tightTauMVA_MC");
   TH2F* eTauEtaPhiData_ =(TH2F*) fTyler->Get("eTau_tight_DATA");
   TH2F* eTauEtaPhiMC_ =(TH2F*) fTyler->Get("eTau_tight_MC");
   TH2F* eTauEtaPhiAvgData_ =(TH2F*) fTyler->Get("eTau_tight_AVG_DATA");
   TH2F* eTauEtaPhiAvgMC_ =(TH2F*) fTyler->Get("eTau_tight_AVG_MC");

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);
   if (sample=="ggH_htt125" or sample=="qqH_htt125" or sample=="WplusH125" or sample=="WminusH125" or sample=="ZH125") do_rivet=false;

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	// Rivet splitting
	if (do_rivet){
           if (name.find("ggH_fwd_htt1") < 140 && Rivet_stage0_cat!=10) continue;
           if (name.find("ggH_stage0_htt1") < 140 && Rivet_stage0_cat!=11) continue;
           if (name.find("qqH_fwd_htt1") < 140 && Rivet_stage0_cat!=20) continue;
           if (name.find("qqH_stage0_htt1") < 140 && Rivet_stage0_cat!=21) continue;
           if ((name.find("VH_had_htt1") < 140 or name.find("WH_had_htt1") < 140 or name.find("ZH_had_htt1") < 140) && Rivet_stage0_cat!=23) continue;
           if (name.find("WH_lep_fwd_htt1") < 140 && Rivet_stage0_cat!=30) continue;
           if (name.find("WH_lep_htt1") < 140 && Rivet_stage0_cat!=31) continue;
           if ((name.find("VH_had_fwd_htt1") < 140 or name.find("WH_had_fwd_htt1") < 140 or name.find("ZH_had_fwd_htt1") < 140) && Rivet_stage0_cat!=22) continue;
           if (name.find("ZH_lep_fwd_htt1") < 140 && Rivet_stage0_cat!=40) continue;
           if (name.find("ZH_lep_htt1") < 140 && Rivet_stage0_cat!=41) continue;
           if (name.find("ggH_VBFTOPO_JET3VETO_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=101) continue;
           if (name.find("ggH_VBFTOPO_JET3_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=102) continue;
           if (name.find("ggH_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=103) continue;
           if (name.find("ggH_1J_PTH_0_60_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=104) continue;
           if (name.find("ggH_1J_PTH_60_120_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=105) continue;
           if (name.find("ggH_1J_PTH_120_200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=106) continue;
           if (name.find("ggH_1J_PTH_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=107) continue;
           if (name.find("ggH_GE2J_PTH_0_60_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=108) continue;
           if (name.find("ggH_GE2J_PTH_60_120_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=109) continue;
           if (name.find("ggH_GE2J_PTH_120_200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=110) continue;
           if (name.find("ggH_GE2J_PTH_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=111) continue;
           if (name.find("qqH_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=200) continue;
           if (name.find("qqH_VBFTOPO_JET3VETO_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=201) continue;
           if (name.find("qqH_VBFTOPO_JET3_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=202) continue;
           if (name.find("qqH_VH2JET_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=203) continue;
           if (name.find("qqH_REST_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=204) continue;
           if (name.find("qqH_PTJET1_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=205) continue;
           if ((name.find("VH_had_VBFTOPO_JET3VETO_htt1") < 140 or name.find("WH_had_VBFTOPO_JET3VETO_htt1") < 140 or name.find("ZH_had_VBFTOPO_JET3VETO_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=201) continue;
           if ((name.find("VH_had_VBFTOPO_JET3_htt1") < 140 or name.find("WH_had_VBFTOPO_JET3_htt1") < 140 or name.find("ZH_had_VBFTOPO_JET3_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=202) continue;
           if ((name.find("VH_had_VH2JET_htt1") < 140 or name.find("WH_had_VH2JET_htt1") < 140 or name.find("ZH_had_VH2JET_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=203) continue;
           if ((name.find("VH_had_REST_htt1") < 140 or name.find("WH_had_REST_htt1") < 140 or name.find("ZH_had_REST_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=204) continue;
           if ((name.find("VH_had_PTJET1_GT200_htt1") < 140 or name.find("WH_had_PTJET1_GT200_htt1") < 140 or name.find("ZH_had_PTJET1_GT200_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=205) continue;
           if (name.find("WH_lep_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=300) continue;
           if (name.find("WH_lep_PTV_0_150_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=301) continue;
           if (name.find("WH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=302) continue;
           if (name.find("WH_lep_PTV_150_250_GE1J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=303) continue;
           if (name.find("WH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=304) continue;
           if ((name.find("VH_had_FWDH_htt1") < 140 or name.find("WH_had_FWDH_htt1") < 140 or name.find("ZH_had_FWDH_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=200) continue;
           if (name.find("ZH_lep_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=400) continue;
           if (name.find("ZH_lep_PTV_0_150_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=401) continue;
           if (name.find("ZH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=402) continue;
           if (name.find("ZH_lep_PTV_150_250_Ge1J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=403) continue;
           if (name.find("ZH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=404) continue;
	}

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.3) continue;

	if (flag_goodVertices) continue;
	if (flag_globalTightHalo2016) continue;
	if (flag_HBHENoise) continue;
	if (flag_HBHENoiseIso) continue;
	if (flag_EcalDeadCellTriggerPrimitive) continue;
	if (flag_BadPFMuon) continue;
	if (flag_BadChargedCandidate) continue;
	if (sample=="data_obs" && flag_eeBadSc) continue;
	if (flag_ecalBadCalib) continue;

        bool trigger27=(passEle27 && matchEle27_1 && filterEle27_1 && pt_1>28);
	bool trigger32=(passEle32 && matchEle32_1 && filterEle32_1 && pt_1>33);
        bool trigger35=(passEle35 && matchEle35_1 && filterEle35_1 && pt_1>36);
        bool trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && filterEle24Tau30_2 && pt_1>25 && pt_2>34 && pt_1<28 && fabs(eta_2)<2.1); // looser tau pt to cut in the loop after shifts
	if (sample=="embedded"){
           trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && pt_1>25 && pt_2>34 && pt_1<28 && fabs(eta_2)<2.1); // no tau trigger matching in embedded
	}
        if (!trigger27 && !trigger32 && !trigger35 && !trigger2430) continue;
	if (!againstElectronTightMVA6_2 or !againstMuonLoose3_2) continue;

        float signalRegion=(byTightIsolationMVArun2v2DBoldDMwLT_2 && iso_1<0.15);
        float antiisoRegion=(byVLooseIsolationMVArun2v2DBoldDMwLT_2 && !byTightIsolationMVArun2v2DBoldDMwLT_2 && iso_1<0.15);

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

        if (sample=="W"){
            weight=32.7;
            if (numGenJets==1) weight=5.91;
            else if (numGenJets==2) weight=12.57;
            else if (numGenJets==3) weight=2.25;
            else if (numGenJets==4) weight=2.16;
        }

        if (sample=="DY"){
            weight=2.63;
            if (numGenJets==1)
                weight=0.21;
            else if (numGenJets==2)
                weight=0.956;
            else if (numGenJets==3)
                weight=0.602;
            else if (numGenJets==4)
                weight=0.229;
        }
	if ((sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue; // remove overlap with embedded samples

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;
	if (sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*0.89;
        if (sample=="embedded") aweight=aweight*0.97;
	if (gen_match_2==2 or gen_match_2==4){
	   if (fabs(mytau.Eta()<0.4)) aweight=aweight*1.06;
           else if (fabs(mytau.Eta()<0.8)) aweight=aweight*1.02;
           else if (fabs(mytau.Eta()<1.2)) aweight=aweight*1.10;
           else if (fabs(mytau.Eta()<1.7)) aweight=aweight*1.03;
           else if (fabs(mytau.Eta()<2.3)) aweight=aweight*1.94;
	}
        if (gen_match_2==1 or gen_match_2==3){
           if (fabs(mytau.Eta()<1.460)) aweight=aweight*1.80;
           else if (fabs(mytau.Eta()>1.558)) aweight=aweight*1.53;
	}

	//NNLOPS weights
        if (name.find("ggH")<100 && name.find("NNLOPS")>100 && name.find("hww")>100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

	if (sample=="data_obs") aweight=1.0;
        if (sample=="embedded"){
          if (l2_decayMode==0) aweight=aweight*0.975; // track reconstruction
          else if (l2_decayMode==1) aweight=aweight*0.975*1.051; // track reconstruction
          else if (l2_decayMode==10) aweight=aweight*0.975*0.975*0.975; // track reconstruction
          w->var("e_pt")->setVal(myele.Pt());
          w->var("e_eta")->setVal(myele.Eta());
          w->var("gt_pt")->setVal(myele.Pt());
          w->var("gt_eta")->setVal(myele.Eta());
          aweight=aweight*w->function("m_sel_idEmb_ratio")->getVal();
          w->var("gt_pt")->setVal(mytau.Pt());
          w->var("gt_eta")->setVal(mytau.Eta());
          aweight=aweight*w->function("m_sel_idEmb_ratio")->getVal();
          w->var("gt1_pt")->setVal(myele.Pt());
          w->var("gt1_eta")->setVal(myele.Eta());
          w->var("gt2_pt")->setVal(mytau.Pt());
          w->var("gt2_eta")->setVal(mytau.Eta());
          aweight=aweight*w->function("m_sel_trg_ratio")->getVal();
          aweight=aweight*w->function("e_iso_binned_embed_kit_ratio")->getVal();
          aweight=aweight*w->function("e_id90_embed_kit_ratio")->getVal();
          if (trigger27 or trigger32 or trigger35) aweight=aweight*w->function("e_trg27_trg32_trg35_embed_kit_ratio")->getVal();
          else aweight=aweight*1.0; //FIXME
	}

	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT"){
           float pttop1=pt_top1;
           if (pttop1>400) pttop1=400;
           float pttop2=pt_top2;
           if (pttop2>400) pttop2=400;
           topfactor=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
	if (sample!="embedded" && sample!="data_obs"){
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
          aweight=aweight*wmc->function("e_iso_kit_ratio")->getVal();
          aweight=aweight*wmc->function("e_id90_kit_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*0.991;//z vtx electron HLT
	  zptweight=wmc->function("zptmass_weight_nom")->getVal();
	  if (sample=="DY") aweight=aweight*zptweight;
	  if (trigger27 or trigger32 or trigger35) aweight*wmc->function("e_trg27_trg32_trg35_kit_data")->getVal()/wmc->function("e_trg27_trg32_trg35_kit_mc")->getVal();
	  else aweight=aweight*(wmc->function("e_trg_EleTau_Ele24Leg_desy_data")->getVal()/wmc->function("e_trg_EleTau_Ele24Leg_desy_mc")->getVal())*getDiTauScaleFactor(pt_2,eta_2,phi_2,0,eTauMC_,eTauEtaPhiMC_,eTauEtaPhiAvgMC_,eTauData_,eTauEtaPhiData_,eTauEtaPhiAvgData_);
	}

	//************************ Compute fake factors ******************
	float frac_qcd=0.2;
	float frac_w=0.7;
	float frac_tt=0.1;

	if (njetsWoNoisyJets==0){
	    frac_qcd=frac_qcd_0jet->GetBinContent(frac_qcd_0jet->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_0jet->GetBinContent(frac_data_0jet->GetXaxis()->FindBin((myele+mytau).M()));
            frac_w=frac_w_0jet->GetBinContent(frac_w_0jet->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_0jet->GetBinContent(frac_data_0jet->GetXaxis()->FindBin((myele+mytau).M()));
            frac_tt=frac_tt_0jet->GetBinContent(frac_tt_0jet->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_0jet->GetBinContent(frac_data_0jet->GetXaxis()->FindBin((myele+mytau).M()));
	    /*frac_qcd=frac_qcd_0jet->Integral()/frac_data_0jet->Integral();
            frac_w=frac_w_0jet->Integral()/frac_data_0jet->Integral();
            frac_tt=frac_tt_0jet->Integral()/frac_data_0jet->Integral();*/
	}
	else if (njetsWoNoisyJets==1){
            frac_qcd=frac_qcd_boosted->GetBinContent(frac_qcd_boosted->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_boosted->GetBinContent(frac_data_boosted->GetXaxis()->FindBin((myele+mytau).M()));
            frac_w=frac_w_boosted->GetBinContent(frac_w_boosted->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_boosted->GetBinContent(frac_data_boosted->GetXaxis()->FindBin((myele+mytau).M()));
            frac_tt=frac_tt_boosted->GetBinContent(frac_tt_boosted->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_boosted->GetBinContent(frac_data_boosted->GetXaxis()->FindBin((myele+mytau).M()));
            /*frac_qcd=frac_qcd_boosted->Integral()/frac_data_boosted->Integral();
            frac_w=frac_w_boosted->Integral()/frac_data_boosted->Integral();
            frac_tt=frac_tt_boosted->Integral()/frac_data_boosted->Integral();*/
        }
	else{
            frac_qcd=frac_qcd_vbf->GetBinContent(frac_qcd_vbf->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_vbf->GetBinContent(frac_data_vbf->GetXaxis()->FindBin((myele+mytau).M()));
            frac_w=frac_w_vbf->GetBinContent(frac_w_vbf->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_vbf->GetBinContent(frac_data_vbf->GetXaxis()->FindBin((myele+mytau).M()));
            frac_tt=frac_tt_vbf->GetBinContent(frac_tt_vbf->GetXaxis()->FindBin((myele+mytau).M()))/frac_data_vbf->GetBinContent(frac_data_vbf->GetXaxis()->FindBin((myele+mytau).M()));
            /*frac_qcd=frac_qcd_vbf->Integral()/frac_data_vbf->Integral();
            frac_w=frac_w_vbf->Integral()/frac_data_vbf->Integral();
            frac_tt=frac_tt_vbf->Integral()/frac_data_vbf->Integral();*/
        }

	float mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());

        inputs[0] = mytau.Pt();
        inputs[1] = l2_decayMode;
        inputs[2] = njetsWoNoisyJets;
        inputs[3] = (myele+mytau).M();
        inputs[4] = mt;
        inputs[5] = isoDB_1;
        inputs[6] = frac_qcd;
        inputs[7] = frac_w;
        inputs[8] = frac_tt;

	//************************* Fill histograms **********************
	double FF=ff->value(inputs);
	float myvar=(myele+mytau).M();
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njetsWoNoisyJets;
	int rawnbtag=nbtag;
	float mtt=m_sv;
	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

           trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && filterEle24Tau30_2 && pt_1>25 && mytau.Pt()>35 && pt_1<28 && fabs(eta_2)<2.1);
           if (sample=="embedded") trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && pt_1>25 && mytau.Pt()>35 && pt_1<28 && fabs(eta_2)<2.1); // no tau trigger matching in embedded
           if (!trigger27 && !trigger32 && !trigger35 && !trigger2430) continue;
	
	   nbtag=rawnbtag;
	   if (sample!="data_obs" && sample!="embedded" && nbtag>0) nbtag=PromoteDemote(h_btag_eff_b, h_btag_eff_c, h_btag_eff_oth, nbtag, bpt_1, bflavor_1, beta_1, 0);
           if (nbtag>0) continue;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njetsWoNoisyJets;
	   mytau=myrawtau;
	   mymet=myrawmet;
	   massJets=mjj;

           if (sample!="data_obs"){
              if (k>0 && k<7 && gen_match_2==5){ // TES x 6
                if (k==1 && l2_decayMode==0){mytau*=0.992; mymet=mymet+(0.008/0.991)*mytau; mtt=m_sv_DOWN;}
                else if (k==2 && l2_decayMode==0){mytau*=1.008; mymet=mymet-(0.008/1.008)*mytau; mtt=m_sv_UP;}
                else if (k==3 && l2_decayMode==1){mytau*=0.992; mymet=mymet+(0.008/0.992)*mytau; mtt=m_sv_DOWN;}
                else if (k==4 && l2_decayMode==1){mytau*=1.008; mymet=mymet-(0.008/1.008)*mytau; mtt=m_sv_UP;}
                else if (k==5 && l2_decayMode==10){mytau*=0.992; mymet=mymet+(0.008/0.992)*mytau; mtt=m_sv_DOWN;}
                else if (k==6 && l2_decayMode==10){mytau*=1.008; mymet=mymet-(0.008/1.008)*mytau; mtt=m_sv_UP;}
              }
              else if (k>6 && k<17){ // JES x 10
                if (k==7){numberJets=njetsWoNoisyJets_JetEta0to3Down; massJets=mjjWoNoisyJets_JetEta0to3Down; mymet=myrawmet;}
                else if (k==8){numberJets=njetsWoNoisyJets_JetEta0to3Up; massJets=mjjWoNoisyJets_JetEta0to3Up; mymet=myrawmet;}
                else if (k==9){numberJets=njetsWoNoisyJets_JetEta0to5Down; massJets=mjjWoNoisyJets_JetEta0to5Down; mymet=myrawmet;}
                else if (k==10){numberJets=njetsWoNoisyJets_JetEta0to5Up; massJets=mjjWoNoisyJets_JetEta0to5Up; mymet=myrawmet;}
                else if (k==11){numberJets=njetsWoNoisyJets_JetEta3to5Down; massJets=mjjWoNoisyJets_JetEta3to5Down; mymet=myrawmet;}
                else if (k==12){numberJets=njetsWoNoisyJets_JetEta3to5Up; massJets=mjjWoNoisyJets_JetEta3to5Up; mymet=myrawmet;}
                else if (k==13){numberJets=njetsWoNoisyJets_JetRelativeSampleDown; massJets=mjjWoNoisyJets_JetRelativeSampleDown; mymet=myrawmet;}
                else if (k==14){numberJets=njetsWoNoisyJets_JetRelativeSampleUp; massJets=mjjWoNoisyJets_JetRelativeSampleUp; mymet=myrawmet;}
                else if (k==15){numberJets=njetsWoNoisyJets_JetRelativeBalDown; massJets=mjjWoNoisyJets_JetRelativeBalDown; mymet=myrawmet;}
                else if (k==16){numberJets=njetsWoNoisyJets_JetRelativeBalUp; massJets=mjjWoNoisyJets_JetRelativeBalUp; mymet=myrawmet;}
              }
              else if (k>16 && k<21 && (gen_match_2<5)){ // EES x 4
                if (k==17 && l2_decayMode==0){mytau*=0.993; mymet=mymet+(0.007/0.993)*mytau; mtt=m_sv_DOWN;}
                else if (k==18 && l2_decayMode==0){mytau*=1.007; mymet=mymet-(0.007/1.007)*mytau; mtt=m_sv_UP;}
                else if (k==19 && l2_decayMode==1){mytau*=0.993; mymet=mymet+(0.007/0.993)*mytau; mtt=m_sv_DOWN;}
                else if (k==20 && l2_decayMode==1){mytau*=1.007; mymet=mymet-(0.007/1.007)*mytau; mtt=m_sv_UP;}
              }
              else if ((name=="TT" or name=="VV") && k>20 && k<23){ // UES x 2
                if (k==21){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESDown, 0, metphi_UESDown, 0); mtt=m_sv_UESDown;}
                else if (k==22){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESUp, 0, metphi_UESUp, 0); mtt=m_sv_UESUp;}
              }
              else if (k>22 && k<25 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==23) weight2=1.0/topfactor;
                else if (k==24) weight2=topfactor;
              }
              else if (k>24 && k<27 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==25) weight2=1.0/zptweight;
                else if (k==26) weight2=zptweight;
              }
              else if (is_ggh && k>26 && k<45){ // WG1 x 18
                if (k==27) weight2=1+WG1unc[0];
                else if (k==28) weight2=1-WG1unc[0];
                else if (k==29) weight2=1+WG1unc[1];
                else if (k==30) weight2=1-WG1unc[1];
                else if (k==31) weight2=1+WG1unc[2];
                else if (k==32) weight2=1-WG1unc[2];
                else if (k==33) weight2=1+WG1unc[3];
                else if (k==34) weight2=1-WG1unc[3];
                else if (k==35) weight2=1+WG1unc[4];
                else if (k==36) weight2=1-WG1unc[4];
                else if (k==37) weight2=1+WG1unc[5];
                else if (k==38) weight2=1-WG1unc[5];
                else if (k==39) weight2=1+WG1unc[6];
                else if (k==40) weight2=1-WG1unc[6];
                else if (k==41) weight2=1+WG1unc[7];
                else if (k==42) weight2=1-WG1unc[7];
                else if (k==43) weight2=1+WG1unc[8];
                else if (k==44) weight2=1-WG1unc[8];
              }
           }

           if (sample=="data_obs"){
              if (k>0 && k<31){ // FF x 30
                FF=ff->value(inputs,FFsys[k-1]);
              }
           }


    	   mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());
	   myvar=mtt;
	   if (njetsWoNoisyJets==0) myvar=(myele+mytau).M();
	   float myvar0=mytau.Pt();
	   float myvar1=(myele+mytau+mymet).Pt();
	   float myvar2=massJets;

	   if (mytau.Pt()<20 or (njetsWoNoisyJets>0 && mytau.Pt()<30)) continue;
           if (njetsWoNoisyJets==0 && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h0tau_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h0ell_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h0jet_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h0tau_AI[k]->Fill(myvar0,myvar,FF);
                   h0jet_AI[k]->Fill(myvar0,myvar);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && antiisoRegion)
                   h0tau_AI[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && antiisoRegion)
                   h0ell_AI[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h0jet_AI[k]->Fill(myvar0,myvar,aweight*weight2);
           }
           if ((njetsWoNoisyJets==1 or ((myvar1<50 or massJets<400) && njetsWoNoisyJets>1)) && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h1tau_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h1ell_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h1jet_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h1tau_AI[k]->Fill(myvar1,myvar,FF);
                   h1jet_AI[k]->Fill(myvar1,myvar);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && antiisoRegion)
                   h1tau_AI[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && antiisoRegion)
                   h1ell_AI[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h1jet_AI[k]->Fill(myvar1,myvar,aweight*weight2);
           }
           if (njetsWoNoisyJets>=2 && massJets>400 && myvar1>50 && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h2tau_OS[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h2ell_OS[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h2jet_OS[k]->Fill(myvar2,myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h2tau_AI[k]->Fill(myvar2,myvar,FF);
                   h2jet_AI[k]->Fill(myvar2,myvar);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && signalRegion)
                   h2tau_AI[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && signalRegion)
                   h2ell_AI[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && signalRegion)
                   h2jet_AI[k]->Fill(myvar2,myvar,aweight*weight2);
           }
           if (njetsWoNoisyJets==1 && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h3tau_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h3ell_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h3jet_OS[k]->Fill(myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h3tau_AI[k]->Fill(myvar,FF);
                   h3jet_AI[k]->Fill(myvar);
               }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && signalRegion)
                   h3tau_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && signalRegion)
                   h3ell_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && signalRegion)
                   h3jet_AI[k]->Fill(myvar,aweight*weight2);
           }
           if (njetsWoNoisyJets>=2 && (massJets>400 or massJets<60 or (massJets<400 && massJets>120)) && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h4tau_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h4ell_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h4jet_OS[k]->Fill(myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h4tau_AI[k]->Fill(myvar,FF);
                   h4jet_AI[k]->Fill(myvar);
               }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && signalRegion)
                   h4tau_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && signalRegion)
                   h4ell_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && signalRegion)
                   h4jet_AI[k]->Fill(myvar,aweight*weight2);
           }
           if (njetsWoNoisyJets>=2 && massJets>60 && massJets<120 && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h5tau_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h5ell_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h5jet_OS[k]->Fill(myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h5tau_AI[k]->Fill(myvar,FF);
                   h5jet_AI[k]->Fill(myvar);
               }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && signalRegion)
                   h5tau_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && signalRegion)
                   h5ell_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && signalRegion)
                   h5jet_AI[k]->Fill(myvar,aweight*weight2);
           }
           if (njetsWoNoisyJets>=2 && massJets>400 && mt<50 && q_1*q_2<0){
               if ((sample=="data_obs" or gen_match_2==5) && signalRegion)
                   h6tau_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2<5) && signalRegion)
                   h6ell_OS[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h6jet_OS[k]->Fill(myvar,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h6tau_AI[k]->Fill(myvar,FF);
                   h6jet_AI[k]->Fill(myvar);
               }
               if ((sample!="data_obs" && (sample=="embedded" or gen_match_2==5)) && signalRegion)
                   h6tau_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2<5) && signalRegion)
                   h6ell_AI[k]->Fill(myvar,aweight*weight2);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && signalRegion)
                   h6jet_AI[k]->Fill(myvar,aweight*weight2);
           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    TString postfix=postfixFF[0];

    TDirectory *OS0jet =fout->mkdir("et_0jet");
    OS0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h0tau_OS[k]->SetName("ZTT"+postfix);
          h0ell_OS[k]->SetName("ZL"+postfix);
          h0jet_OS[k]->SetName("ZJ"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h0tau_OS[k]->SetName("TTT"+postfix);
          h0ell_OS[k]->SetName("TTL"+postfix);
          h0jet_OS[k]->SetName("TTJ"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h0tau_OS[k]->SetName("VVT"+postfix);
          h0ell_OS[k]->SetName("VVL"+postfix);
          h0jet_OS[k]->SetName("VVJ"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else{
          h0tau_OS[k]->SetName(name.c_str()+postfix);
          h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->Add(h0jet_OS[k]);
          h0tau_OS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h0tau_AI[k]->SetName("ZTT"+postfix);
          h0ell_AI[k]->SetName("ZL"+postfix);
          h0jet_AI[k]->SetName("ZJ"+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h0tau_AI[k]->SetName("TTT"+postfix);
          h0ell_AI[k]->SetName("TTL"+postfix);
          h0jet_AI[k]->SetName("TTJ"+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h0tau_AI[k]->SetName("VVT"+postfix);
          h0ell_AI[k]->SetName("VVL"+postfix);
          h0jet_AI[k]->SetName("VVJ"+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h0tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h0jet_AI[k]->SetName("data_obs"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else{
          h0tau_AI[k]->SetName(name.c_str()+postfix);
          h0tau_AI[k]->Add(h0ell_AI[k]);
          h0tau_AI[k]->Add(h0jet_AI[k]);
          h0tau_AI[k]->Write();
       }
    }

    TDirectory *OS1jet =fout->mkdir("et_boosted");
    OS1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h1tau_OS[k]->SetName("ZTT"+postfix);
          h1ell_OS[k]->SetName("ZL"+postfix);
          h1jet_OS[k]->SetName("ZJ"+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->Write();
          h1jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h1tau_OS[k]->SetName("TTT"+postfix);
          h1ell_OS[k]->SetName("TTL"+postfix);
          h1jet_OS[k]->SetName("TTJ"+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->Write();
          h1jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h1tau_OS[k]->SetName("VVT"+postfix);
          h1ell_OS[k]->SetName("VVL"+postfix);
          h1jet_OS[k]->SetName("VVJ"+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->Write();
          h1jet_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->Add(h1jet_OS[k]);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h1tau_AI[k]->SetName("ZTT"+postfix);
          h1ell_AI[k]->SetName("ZL"+postfix);
          h1jet_AI[k]->SetName("ZJ"+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h1tau_AI[k]->SetName("TTT"+postfix);
          h1ell_AI[k]->SetName("TTL"+postfix);
          h1jet_AI[k]->SetName("TTJ"+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h1tau_AI[k]->SetName("VVT"+postfix);
          h1ell_AI[k]->SetName("VVL"+postfix);
          h1jet_AI[k]->SetName("VVJ"+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h1tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h1jet_AI[k]->SetName("data_obs"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else{
          h1tau_AI[k]->SetName(name.c_str()+postfix);
          h1tau_AI[k]->Add(h1ell_AI[k]);
          h1tau_AI[k]->Add(h1jet_AI[k]);
          h1tau_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("et_vbf");
    OS2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h2tau_OS[k]->SetName("ZTT"+postfix);
          h2ell_OS[k]->SetName("ZL"+postfix);
          h2jet_OS[k]->SetName("ZJ"+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->Write();
          h2jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h2tau_OS[k]->SetName("TTT"+postfix);
          h2ell_OS[k]->SetName("TTL"+postfix);
          h2jet_OS[k]->SetName("TTJ"+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->Write();
          h2jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h2tau_OS[k]->SetName("VVT"+postfix);
          h2ell_OS[k]->SetName("VVL"+postfix);
          h2jet_OS[k]->SetName("VVJ"+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->Write();
          h2jet_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->Add(h2jet_OS[k]);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h2tau_AI[k]->SetName("ZTT"+postfix);
          h2ell_AI[k]->SetName("ZL"+postfix);
          h2jet_AI[k]->SetName("ZJ"+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h2tau_AI[k]->SetName("TTT"+postfix);
          h2ell_AI[k]->SetName("TTL"+postfix);
          h2jet_AI[k]->SetName("TTJ"+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h2tau_AI[k]->SetName("VVT"+postfix);
          h2ell_AI[k]->SetName("VVL"+postfix);
          h2jet_AI[k]->SetName("VVJ"+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h2tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h2jet_AI[k]->SetName("data_obs"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else{
          h2tau_AI[k]->SetName(name.c_str()+postfix);
          h2tau_AI[k]->Add(h2ell_AI[k]);
          h2tau_AI[k]->Add(h2jet_AI[k]);
          h2tau_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("et_1jet");
    OS3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h3tau_OS[k]->SetName("ZTT"+postfix);
          h3ell_OS[k]->SetName("ZL"+postfix);
          h3jet_OS[k]->SetName("ZJ"+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->Write();
          h3jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h3tau_OS[k]->SetName("TTT"+postfix);
          h3ell_OS[k]->SetName("TTL"+postfix);
          h3jet_OS[k]->SetName("TTJ"+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->Write();
          h3jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h3tau_OS[k]->SetName("VVT"+postfix);
          h3ell_OS[k]->SetName("VVL"+postfix);
          h3jet_OS[k]->SetName("VVJ"+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->Write();
          h3jet_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->Add(h3jet_OS[k]);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *AI3jet =fout->mkdir("AI1jet");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h3tau_AI[k]->SetName("ZTT"+postfix);
          h3ell_AI[k]->SetName("ZL"+postfix);
          h3jet_AI[k]->SetName("ZJ"+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h3tau_AI[k]->SetName("TTT"+postfix);
          h3ell_AI[k]->SetName("TTL"+postfix);
          h3jet_AI[k]->SetName("TTJ"+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h3tau_AI[k]->SetName("VVT"+postfix);
          h3ell_AI[k]->SetName("VVL"+postfix);
          h3jet_AI[k]->SetName("VVJ"+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h3tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h3jet_AI[k]->SetName("data_obs"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else{
          h3tau_AI[k]->SetName(name.c_str()+postfix);
          h3tau_AI[k]->Add(h3ell_AI[k]);
          h3tau_AI[k]->Add(h3jet_AI[k]);
          h3tau_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("et_gg2jets");
    OS4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h4tau_OS[k]->SetName("ZTT"+postfix);
          h4ell_OS[k]->SetName("ZL"+postfix);
          h4jet_OS[k]->SetName("ZJ"+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->Write();
          h4jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h4tau_OS[k]->SetName("TTT"+postfix);
          h4ell_OS[k]->SetName("TTL"+postfix);
          h4jet_OS[k]->SetName("TTJ"+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->Write();
          h4jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h4tau_OS[k]->SetName("VVT"+postfix);
          h4ell_OS[k]->SetName("VVL"+postfix);
          h4jet_OS[k]->SetName("VVJ"+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->Write();
          h4jet_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->Add(h4jet_OS[k]);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *AI4jet =fout->mkdir("AIgg2jets");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h4tau_AI[k]->SetName("ZTT"+postfix);
          h4ell_AI[k]->SetName("ZL"+postfix);
          h4jet_AI[k]->SetName("ZJ"+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h4tau_AI[k]->SetName("TTT"+postfix);
          h4ell_AI[k]->SetName("TTL"+postfix);
          h4jet_AI[k]->SetName("TTJ"+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h4tau_AI[k]->SetName("VVT"+postfix);
          h4ell_AI[k]->SetName("VVL"+postfix);
          h4jet_AI[k]->SetName("VVJ"+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h4tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h4jet_AI[k]->SetName("data_obs"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else{
          h4tau_AI[k]->SetName(name.c_str()+postfix);
          h4tau_AI[k]->Add(h4ell_AI[k]);
          h4tau_AI[k]->Add(h4jet_AI[k]);
          h4tau_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("et_vh2jets");
    OS5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h5tau_OS[k]->SetName("ZTT"+postfix);
          h5ell_OS[k]->SetName("ZL"+postfix);
          h5jet_OS[k]->SetName("ZJ"+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->Write();
          h5jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h5tau_OS[k]->SetName("TTT"+postfix);
          h5ell_OS[k]->SetName("TTL"+postfix);
          h5jet_OS[k]->SetName("TTJ"+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->Write();
          h5jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h5tau_OS[k]->SetName("VVT"+postfix);
          h5ell_OS[k]->SetName("VVL"+postfix);
          h5jet_OS[k]->SetName("VVJ"+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->Write();
          h5jet_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->Add(h5jet_OS[k]);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *AI5jet =fout->mkdir("AIvh2jets");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h5tau_AI[k]->SetName("ZTT"+postfix);
          h5ell_AI[k]->SetName("ZL"+postfix);
          h5jet_AI[k]->SetName("ZJ"+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h5tau_AI[k]->SetName("TTT"+postfix);
          h5ell_AI[k]->SetName("TTL"+postfix);
          h5jet_AI[k]->SetName("TTJ"+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h5tau_AI[k]->SetName("VVT"+postfix);
          h5ell_AI[k]->SetName("VVL"+postfix);
          h5jet_AI[k]->SetName("VVJ"+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h5tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h5jet_AI[k]->SetName("data_obs"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else{
          h5tau_AI[k]->SetName(name.c_str()+postfix);
          h5tau_AI[k]->Add(h5ell_AI[k]);
          h5tau_AI[k]->Add(h5jet_AI[k]);
          h5tau_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("et_vbf2");
    OS6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h6tau_OS[k]->SetName("ZTT"+postfix);
          h6ell_OS[k]->SetName("ZL"+postfix);
          h6jet_OS[k]->SetName("ZJ"+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->Write();
          h6jet_OS[k]->Write();
       }
       else if (name=="TT"){
          h6tau_OS[k]->SetName("TTT"+postfix);
          h6ell_OS[k]->SetName("TTL"+postfix);
          h6jet_OS[k]->SetName("TTJ"+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->Write();
          h6jet_OS[k]->Write();
       }
       else if (name=="VV"){
          h6tau_OS[k]->SetName("VVT"+postfix);
          h6ell_OS[k]->SetName("VVL"+postfix);
          h6jet_OS[k]->SetName("VVJ"+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->Write();
          h6jet_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->Add(h6jet_OS[k]);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIvbf2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h6tau_AI[k]->SetName("ZTT"+postfix);
          h6ell_AI[k]->SetName("ZL"+postfix);
          h6jet_AI[k]->SetName("ZJ"+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h6tau_AI[k]->SetName("TTT"+postfix);
          h6ell_AI[k]->SetName("TTL"+postfix);
          h6jet_AI[k]->SetName("TTJ"+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h6tau_AI[k]->SetName("VVT"+postfix);
          h6ell_AI[k]->SetName("VVL"+postfix);
          h6jet_AI[k]->SetName("VVJ"+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h6tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h6jet_AI[k]->SetName("data_obs"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else{
          h6tau_AI[k]->SetName(name.c_str()+postfix);
          h6tau_AI[k]->Add(h6ell_AI[k]);
          h6tau_AI[k]->Add(h6jet_AI[k]);
          h6tau_AI[k]->Write();
       }
    }

    fout->Close();
    delete ff;
    ff_file->Close();
    delete wmc;
    delete w;
} 

