import ROOT
import sys
from tqdm import tqdm
import argparse
import math

def GenerateControlPlots(TheFile,OutFile,args):
    #Let's start with 6 possible control plots
    # Tau pt, Tau Eta, Mu Pt, Mu Eta, MET, MET phi.
    TheHisto = TheFile[TheFile.rfind("/")+1:]    
    TheHisto = TheHisto.split(".")[0]
    FullHistoName = TheHisto+"_"+args.Year
    UseFakeFactor = False
    try:
        if TheFile in args.UseFakeFactorOnFiles:
            UseFakeFactor = True
    except:
        pass    
    
    print("Histogram Name: "+FullHistoName)

    TreeFile = ROOT.TFile(TheFile)
    TheTree = TreeFile.mt_Selected    

    TauPtHisto = ROOT.TH1F(FullHistoName+"_TauPt",FullHistoName+"_TauPt",25,30.0,80.0)
    TauEtaHisto = ROOT.TH1F(FullHistoName+"_TauEta",FullHistoName+"_TauEta",45, -2.5, 2.5)
    MuPtHisto  = ROOT.TH1F(FullHistoName+"_MuPt",FullHistoName+"_MuPt",30,20.0,80.0)
    MuEtaHisto = ROOT.TH1F(FullHistoName+"_MuEta",FullHistoName+"_MuEta",48,-2.4,2.4)    
    MTHisto = ROOT.TH1F(FullHistoName+"_MT",FullHistoName+"_MT",20,0.0,200.0)

    mvisHisto = ROOT.TH1F(FullHistoName+"_mvis",FullHistoName+"_mvis",30,50.0,200.0)
    msvHisto = ROOT.TH1F(FullHistoName+"_msv",FullHistoName+"_msv",30,0.0,300.0)
    NJetsHisto = ROOT.TH1F(FullHistoName+"_Njets",FullHistoName+"_Njets",6,0.0,6.0)
    HiggsPtHisto = ROOT.TH1F(FullHistoName+"_HiggsPt",FullHistoName+"_HiggsPt",24,0.0,120.0)
    METHisto = ROOT.TH1F(FullHistoName+"_MET",FullHistoName+"_MET",20,0.0,200.0)
    DRHisto = ROOT.TH1F(FullHistoName+"_DR",FullHistoName+"_DR",40,0,6.0)

    mjjHisto = ROOT.TH1F(FullHistoName+"_mjj",FullHistoName+"_mjj",20,0.0,500.0)
    DEtaJJHisto = ROOT.TH1F(FullHistoName+"_detajj",FullHistoName+"_detajj",45,0,2.5)
    LeadingJetPtHisto = ROOT.TH1F(FullHistoName+"_j1pt",FullHistoName+"_j1pt",50,0.0,200.0)
    LeadingJetEtaHisto = ROOT.TH1F(FullHistoName+"_j1eta",FullHistoName+"_j1eta", 50, -5.0, 5.0)    
    SubLeadingJetPtHisto = ROOT.TH1F(FullHistoName+"_j2pt",FullHistoName+"_j2pt",50,0.0,200.0)
    SubLeadingJetEtaHisto = ROOT.TH1F(FullHistoName+"_j2eta",FullHistoName+"_j2eta",50,-5.0,5.0)
        
    METPhiHisto = ROOT.TH1F(FullHistoName+"_METPhi",FullHistoName+"_METPhi",20,-3.14,3.14)
    TriggerHisto = ROOT.TH1F(FullHistoName+"_trigger",FullHistoName+"_trigger",3,0.0,3.0)

    TauPtHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_TauPt",FullHistoName+"_genmatch_low_TauPt",25,30.0,80.0)
    TauEtaHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_TauEta",FullHistoName+"_genmatch_low_TauEta",45, -2.5, 2.5)
    MuPtHisto_DYll  = ROOT.TH1F(FullHistoName+"_genmatch_low_MuPt",FullHistoName+"_genmatch_low_MuPt",30,20.0,80.0)
    MuEtaHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_MuEta",FullHistoName+"_genmatch_low_MuEta",48,-2.4,2.4)
    MTHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_MT",FullHistoName+"_genmatch_low_MT",20,0.0,200.0)

    mvisHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_mvis",FullHistoName+"_genmatch_low_mvis",30,50.0,200.0)
    msvHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_msv",FullHistoName+"_genmatch_low_msv",30,0.0,300.0)
    NJetsHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_Njets",FullHistoName+"_genmatch_low_Njets",6,0.0,6.0)
    HiggsPtHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_HiggsPt",FullHistoName+"_genmatch_low_HiggsPt",24,0.0,120.0)
    METHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_MET",FullHistoName+"_genmatch_low_MET",20,0.0,200.0)
    DRHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_DR",FullHistoName+"_genmatch_low_DR",40,0,6.0)
    
    mjjHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_mjj",FullHistoName+"_genmatch_low_mjj",20,0.0,500.0)
    DEtaJJHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_detajj",FullHistoName+"_genmatch_low_deteajj",45,0,2.5)
    LeadingJetPtHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_j1pt",FullHistoName+"_genmatch_low_j1pt",50,0.0,200.0)
    LeadingJetEtaHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_j1eta",FullHistoName+"_genmatch_low_j1eta", 50, -5.0, 5.0)
    SubLeadingJetPtHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_j2pt",FullHistoName+"_genmatch_low_j2pt", 50, 0.0, 200.0)
    SubLeadingJetEtaHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_j2eta",FullHistoName+"_genmatch_low_j2eta", 50, -5.0, 5.0)

    TriggerHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_trigger",FullHistoName+"_genmatch_low_trigger",3,0.0,3.0)
    METPhiHisto_DYll = ROOT.TH1F(FullHistoName+"_genmatch_low_METPhi",FullHistoName+"_genmatch_low_METPhi",20,-3.14,3.14)

    TauPtHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_TauPt",FullHistoName+"_genmatch_tt_TauPt",25,30.0,80.0)
    TauEtaHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_TauEta",FullHistoName+"_genmatch_tt_TauEta",45, -2.5, 2.5)
    MuPtHisto_DYtt  = ROOT.TH1F(FullHistoName+"_genmatch_tt_MuPt",FullHistoName+"_genmatch_tt_MuPt",30,20.0,80.0)
    MuEtaHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_MuEta",FullHistoName+"_genmatch_tt_MuEta",48,-2.4,2.4)
    MTHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_MT",FullHistoName+"_genmatch_tt_MT",20,0.0,200.0)

    mvisHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_mvis",FullHistoName+"_genmatch_tt_mvis",30,50.0,200.0)
    msvHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_msv",FullHistoName+"_genmatch_tt_msv",30,0.0,300.0)
    NJetsHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_Njets",FullHistoName+"_genmatch_tt_Njets",6,0.0,6.0)
    HiggsPtHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_HiggsPt",FullHistoName+"_genmatch_tt_HiggsPt",24,0.0,120.0)
    METHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_MET",FullHistoName+"_genmatch_tt_MET",20,0.0,200.0)
    DRHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_DR",FullHistoName+"_genmatch_tt_DR",40,0,6.0)
    
    mjjHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_mjj",FullHistoName+"_genmatch_tt_mjj",20,0.0,500.0)
    DEtaJJHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_detajj",FullHistoName+"_genmatch_tt_deteajj",45,0,2.5)
    LeadingJetPtHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_j1pt",FullHistoName+"_genmatch_tt_j1pt",50,0.0,200.0)
    LeadingJetEtaHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_j1eta",FullHistoName+"_genmatch_tt_j1eta", 50, -5.0, 5.0)
    SubLeadingJetPtHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_j2pt",FullHistoName+"_genmatch_tt_j2pt", 50, 0.0, 200.0)
    SubLeadingJetEtaHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_j2eta",FullHistoName+"_genmatch_tt_j2eta", 50, -5.0, 5.0)

    TriggerHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_trigger",FullHistoName+"_genmatch_tt_trigger",3,0.0,3.0)
    METPhiHisto_DYtt = ROOT.TH1F(FullHistoName+"_genmatch_tt_METPhi",FullHistoName+"_genmatch_tt_METPhi",20,-3.14,3.14)

    passesTauCut = 0
    passesMvisCut = 0
    passesMTCut = 0
    #numAccepted=1
    for i in tqdm(range(TheTree.GetEntries())):
        TheTree.GetEntry(i)
        MuVector = ROOT.TLorentzVector()
        TauVector = ROOT.TLorentzVector()
        METVector = ROOT.TLorentzVector()
        MuVector.SetPtEtaPhiM(TheTree.pt_1,TheTree.eta_1,TheTree.phi_1,TheTree.m_1)
        TauVector.SetPtEtaPhiM(TheTree.pt_2,TheTree.eta_2,TheTree.phi_2,TheTree.m_2)        
        METVector.SetPtEtaPhiM(TheTree.met,0.0,TheTree.metphi,0.0)
        MT = math.sqrt(2.0*MuVector.Pt()*METVector.Pt()*(1.0-math.cos(MuVector.DeltaPhi(METVector))))

        TheWeighting = TheTree.FinalWeighting        
        if UseFakeFactor:
            TheWeighting = TheWeighting*TheTree.Event_Fake_Factor

        if(TauVector.Pt() < 30.0):            
            continue              
        if TheTree.gen_match_2 == 5:
            passesTauCut+=1
            
        if((TauVector + MuVector).M() < 50.0):
            continue
        if TheTree.gen_match_2 == 5:
            passesMvisCut +=1

        MTHisto.Fill(MT,TheWeighting)        
        if TheHisto == "Embedded" or (args.UseMC and TheHisto == "DY" and TheTree.gen_match_2 == 5):
            MTHisto_DYtt.Fill(MT,TheWeighting)
        if TheHisto=="DY" and TheTree.gen_match_2 < 5:
            MTHisto_DYll.Fill(MT,TheWeighting)        

        if(MT > 50.0):
            continue
        if TheTree.gen_match_2 == 5:
            passesMTCut+=1
        #print("FinalWeight #"+str(numAccepted)+": "+str(TheWeighting))
        #numAccepted+=1
        
        TauPtHisto.Fill(TauVector.Pt(),TheWeighting)
        TauEtaHisto.Fill(TauVector.Eta(),TheWeighting)
        MuPtHisto.Fill(MuVector.Pt(),TheWeighting)
        MuEtaHisto.Fill(MuVector.Eta(),TheWeighting)

        mvisHisto.Fill((TauVector+MuVector).M(),TheWeighting)
        msvHisto.Fill(TheTree.m_sv,TheWeighting)
        NJetsHisto.Fill(TheTree.njets,TheWeighting)
        HiggsPtHisto.Fill((TauVector+MuVector+METVector).Pt(),TheWeighting)
        METHisto.Fill(TheTree.met,TheWeighting)
        DRHisto.Fill(TauVector.DeltaR(MuVector),TheWeighting)
        
        METPhiHisto.Fill(TheTree.metphi,TheWeighting)                                

        if TheTree.njets >= 1:
            LeadingJetEtaHisto.Fill(TheTree.jeta_1,TheWeighting)
            LeadingJetPtHisto.Fill(TheTree.jpt_1,TheWeighting)
        if TheTree.njets >= 2:
            SubLeadingJetPtHisto.Fill(TheTree.jpt_2,TheWeighting)
            SubLeadingJetEtaHisto.Fill(TheTree.jeta_2,TheWeighting)
            DEtaJJHisto.Fill(abs(TheTree.jeta_1-TheTree.jeta_2),TheWeighting)
            mjjHisto.Fill(TheTree.mjj,TheWeighting)
            
        if args.Year == "2018" or args.Year == "2017":
            if TheTree.Trigger24:
                TriggerHisto.Fill(0,TheWeighting)
            if TheTree.Trigger27:
                TriggerHisto.Fill(1,TheWeighting)
            if TheTree.Trigger2027:
                TriggerHisto.Fill(2,TheWeighting)
        else:
            if TheTree.Trigger22:
                TriggerHisto.Fill(0,TheWeighting)
            if TheTree.Trigger1920:
                TriggerHisto.Fill(1,TheWeighting)
                                        
        if (TheHisto == "DY" and TheTree.gen_match_2 <5):
            TauPtHisto_DYll.Fill(TauVector.Pt(),TheWeighting)
            TauEtaHisto_DYll.Fill(TauVector.Eta(),TheWeighting)
            MuPtHisto_DYll.Fill(MuVector.Pt(),TheWeighting)
            MuEtaHisto_DYll.Fill(MuVector.Eta(),TheWeighting)
            
            mvisHisto_DYll.Fill((TauVector+MuVector).M(),TheWeighting)
            msvHisto_DYll.Fill(TheTree.m_sv,TheWeighting)
            NJetsHisto_DYll.Fill(TheTree.njets,TheWeighting)
            HiggsPtHisto_DYll.Fill((TauVector+MuVector+METVector).Pt(),TheWeighting)
            METHisto_DYll.Fill(TheTree.met,TheWeighting)
            DRHisto_DYll.Fill(TauVector.DeltaR(MuVector),TheWeighting)
            
            METPhiHisto_DYll.Fill(TheTree.metphi,TheWeighting)                                
            
            if TheTree.njets >= 1:
                LeadingJetEtaHisto_DYll.Fill(TheTree.jeta_1,TheWeighting)
                LeadingJetPtHisto_DYll.Fill(TheTree.jpt_1,TheWeighting)
            if TheTree.njets >= 2:
                SubLeadingJetPtHisto_DYll.Fill(TheTree.jpt_2,TheWeighting)
                SubLeadingJetEtaHisto_DYll.Fill(TheTree.jeta_2,TheWeighting)
                DEtaJJHisto_DYll.Fill(abs(TheTree.jeta_1-TheTree.jeta_2),TheWeighting)
                mjjHisto_DYll.Fill(TheTree.mjj,TheWeighting)
            if args.Year == "2017" or args.Year == "2018":
                if TheTree.Trigger24:
                    TriggerHisto_DYll.Fill(0,TheWeighting)
                if TheTree.Trigger27:
                    TriggerHisto_DYll.Fill(1,TheWeighting)
                if TheTree.Trigger2027:
                    TriggerHisto_DYll.Fill(2,TheWeighting)
            elif args.Year == "2016":
                if TheTree.Trigger22:
                    TriggerHisto_DYll.Fill(0,TheWeighting) 
                if TheTree.Trigger1920:
                    TriggerHisto_DYll.Fill(1,TheWeighting)

        elif TheHisto == "Embedded" or (args.UseMC and TheHisto == "DY" and TheTree.gen_match_2 == 5):
            TauPtHisto_DYtt.Fill(TauVector.Pt(),TheWeighting)
            TauEtaHisto_DYtt.Fill(TauVector.Eta(),TheWeighting)
            MuPtHisto_DYtt.Fill(MuVector.Pt(),TheWeighting)
            MuEtaHisto_DYtt.Fill(MuVector.Eta(),TheWeighting)
        
            mvisHisto_DYtt.Fill((TauVector+MuVector).M(),TheWeighting)
            msvHisto_DYtt.Fill(TheTree.m_sv,TheWeighting)
            NJetsHisto_DYtt.Fill(TheTree.njets,TheWeighting)
            HiggsPtHisto_DYtt.Fill((TauVector+MuVector+METVector).Pt(),TheWeighting)
            METHisto_DYtt.Fill(TheTree.met,TheWeighting)
            DRHisto_DYtt.Fill(TauVector.DeltaR(MuVector),TheWeighting)
            
            METPhiHisto_DYtt.Fill(TheTree.metphi,TheWeighting)                                
            
            if TheTree.njets >= 1:
                LeadingJetEtaHisto_DYtt.Fill(TheTree.jeta_1,TheWeighting)
                LeadingJetPtHisto_DYtt.Fill(TheTree.jpt_1,TheWeighting)
            if TheTree.njets >= 2:
                SubLeadingJetPtHisto_DYtt.Fill(TheTree.jpt_2,TheWeighting)
                SubLeadingJetEtaHisto_DYtt.Fill(TheTree.jeta_2,TheWeighting)
                DEtaJJHisto_DYtt.Fill(abs(TheTree.jeta_1-TheTree.jeta_2),TheWeighting)
                mjjHisto_DYtt.Fill(TheTree.mjj,TheWeighting)
            if args.Year == "2017" or args.Year == "2018":
                if TheTree.Trigger24:
                    TriggerHisto_DYtt.Fill(0,TheWeighting)
                if TheTree.Trigger27:
                    TriggerHisto_DYtt.Fill(1,TheWeighting)
                if TheTree.Trigger2027:
                    TriggerHisto_DYtt.Fill(2,TheWeighting)
            elif args.Year == "2016":
                if TheTree.Trigger22:
                    TriggerHisto_DYtt.Fill(0,TheWeighting) 
                if TheTree.Trigger1920:
                    TriggerHisto_DYtt.Fill(1,TheWeighting)

    OutFile.cd()
    TauPtHisto.Write()
    TauEtaHisto.Write()
    MuPtHisto.Write()
    MuEtaHisto.Write()
    MTHisto.Write()

    mvisHisto.Write()
    msvHisto.Write()
    NJetsHisto.Write()
    HiggsPtHisto.Write()
    METHisto.Write()
    DRHisto.Write()

    mjjHisto.Write()
    DEtaJJHisto.Write()
    LeadingJetPtHisto.Write()
    LeadingJetEtaHisto.Write()
    SubLeadingJetPtHisto.Write()
    SubLeadingJetEtaHisto.Write()
        
    METPhiHisto.Write()
    TriggerHisto.Write()

    if TheHisto == "Embedded" or (args.UseMC and TheHisto == "DY"):
        METPhiHisto_DYtt.Write()
        TriggerHisto_DYtt.Write()
        
        TauPtHisto_DYtt.Write()
        TauEtaHisto_DYtt.Write()
        MuPtHisto_DYtt.Write()
        MuEtaHisto_DYtt.Write()
        MTHisto_DYtt.Write()
        
        mvisHisto_DYtt.Write()
        msvHisto_DYtt.Write()
        NJetsHisto_DYtt.Write()
        HiggsPtHisto_DYtt.Write()
        METHisto_DYtt.Write()
        DRHisto_DYtt.Write()
        
        mjjHisto_DYtt.Write()
        DEtaJJHisto_DYtt.Write()
        LeadingJetPtHisto_DYtt.Write()
        LeadingJetEtaHisto_DYtt.Write()
        SubLeadingJetPtHisto_DYtt.Write()
        SubLeadingJetEtaHisto_DYtt.Write()
        
        METPhiHisto_DYtt.Write()
        TriggerHisto_DYtt.Write()

    if TheHisto == "DY":
        TauPtHisto_DYll.Write()
        TauEtaHisto_DYll.Write()
        MuPtHisto_DYll.Write()
        MuEtaHisto_DYll.Write()
        MTHisto_DYll.Write()
        
        mvisHisto_DYll.Write()
        msvHisto_DYll.Write()
        NJetsHisto_DYll.Write()
        HiggsPtHisto_DYll.Write()
        METHisto_DYll.Write()
        DRHisto_DYll.Write()
        
        mjjHisto_DYll.Write()
        DEtaJJHisto_DYll.Write()
        LeadingJetPtHisto_DYll.Write()
        LeadingJetEtaHisto_DYll.Write()
        SubLeadingJetPtHisto_DYll.Write()
        SubLeadingJetEtaHisto_DYll.Write()
        
        METPhiHisto_DYll.Write()
        TriggerHisto_DYll.Write()
    print("passesTauCut: "+str(passesTauCut))
    print("passesMvisCut: "+str(passesMvisCut))
    print("passesMTCut: "+str(passesMTCut))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate control plots.")
    parser.add_argument('Year',choices=["2016","2017","2018"],help="Select which year's plots to generate.")
    parser.add_argument('Files',nargs="+",help="List of files to generate control plots from.")
    parser.add_argument('--UseFakeFactorOnFiles',nargs="+",help="Use the file's fake factor weightings when making plots for these files.")
    parser.add_argument('--UseMC',help="Use MC instead of embedded for genuine tau contribution",action="store_true")
    
    args = parser.parse_args()
    
    if(args.UseMC):
        OutFile = ROOT.TFile("TemporaryFiles/ControlRegion_"+args.Year+"_MC.root","RECREATE")
    else:
        OutFile = ROOT.TFile("TemporaryFiles/ControlRegion_"+args.Year+".root","RECREATE")
        
    for File in args.Files:
        print("Making control plots for: "+File)
        GenerateControlPlots(File,OutFile,args)
