#include "../inc/AliAnalysisPhiPair.h"
// !TODO: [INFO] About trees in input

void Anls_PreProcessing_MonteCarlo ( string fFileName = "" )
{
    if ( fFileName == "" )
    {
        cout << "[WARNING] Must Specify an input root file" << endl;
        cout << "[INFO] Usage Anls_PreProcessing_MonteCarlo(\"Root_file_name.root\")" << endl;
        return;
    }
    
    //Retrieving Event data
    TFile *insFileMC        =   new TFile   (fFileName.c_str());
    
    //Retrieving Event data TTree
    TTree   *TPhiCandidate  =   (TTree*)insFileMC->Get(fPhiCandidateEff_Tree);
    TTree   *TKaonCandidate =   (TTree*)insFileMC->Get(fKaonCandidateEff_Tree);
    
    if ( !TPhiCandidate && !TKaonCandidate )
    {
        cout << "Input Data Tree not found!" << endl;
        return;
    }
    /*
    if ( !TPhiCandidate )
    {
        cout << "[INFO] " << endl;
    }
    */
    
    // Define tree data structures
    Struct_PhiEfficiency    evPhiEfficiency;
    Struct_KaonEfficiency   evKaonEfficiency;
    
    TPhiCandidate-> SetBranchAddress    ("nPhi",            &evPhiEfficiency.nPhi);
    TPhiCandidate-> SetBranchAddress    ("Px",              &evPhiEfficiency.Px);
    TPhiCandidate-> SetBranchAddress    ("Py",              &evPhiEfficiency.Py);
    TPhiCandidate-> SetBranchAddress    ("Pz",              &evPhiEfficiency.Pz);
    TPhiCandidate-> SetBranchAddress    ("Selection",       &evPhiEfficiency.Selection);
    
    TKaonCandidate-> SetBranchAddress   ("nKaon",           &evKaonEfficiency.nKaon);
    TKaonCandidate-> SetBranchAddress   ("Px",              &evKaonEfficiency.Px);
    TKaonCandidate-> SetBranchAddress   ("Py",              &evKaonEfficiency.Py);
    TKaonCandidate-> SetBranchAddress   ("Pz",              &evKaonEfficiency.Pz);
    TKaonCandidate-> SetBranchAddress   ("Charge",          &evKaonEfficiency.Charge);
    TKaonCandidate-> SetBranchAddress   ("Selection",       &evKaonEfficiency.Selection);
    
    //---------------------//
    //  Setting up output  //
    //---------------------//
    
    // Generating the binning array--------------------------------------------------------------------------
    fSetBinPT1D();
    fSetBinIM1D();
    fSetBinPT2D();
    fSetBinIM2D();
    
    // Creating 1D Efficiency histograms---------------------------------------------------------------------
    hName   = "hNP_1D_Gen_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 1D analysis";
    TH1F * hPhiGen_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiGen_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiGen_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiGen_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiGen_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Rec_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 1D analysis";
    TH1F * hPhiRec_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiRec_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiRec_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiRec_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiRec_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Gen_X2_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 1D analysis";
    TH1F * hPhiG1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPhiG1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiG1D_2X->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiG1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPhiG1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Rec_X2_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 1D analysis";
    TH1F * hPhiR1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPhiR1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiR1D_2X->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiR1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPhiR1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Tru_PT_S";
    hTitle  = "Generated #phi per |y|<5, 1D analysis";
    TH1F * hPhiTru_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiTru_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiTru_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiTru_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiTru_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Eff_PT_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis";
    TH1F * hPhiEff_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiEff_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiEff_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiEff_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Eff_X2_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis";
    TH1F * hPEff1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPEff1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPEff1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPEff1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    // Creating 2D Efficiency histograms---------------------------------------------------------------------
    hName   = "hNP_2D_Gen_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 2D analysis";
    TH2F * hPhiGen_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiGen_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiGen_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiGen_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiGen_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Rec_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 2D analysis";
    TH2F * hPhiRec_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiRec_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiRec_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiRec_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiRec_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Tru_PT_S";
    hTitle  = "Generated #phi per |y|<5, 2D analysis";
    TH2F * hPhiTru_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiTru_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiTru_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiTru_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiTru_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Eff_PT_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 2D analysis";
    TH2F * hPhiEff_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiEff_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiEff_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiEff_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiEff_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Eff_X2_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis in 2D";
    TH2F * hPEff2D_2X   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPEff2D_2X->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPEff2D_2X->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPEff2D_2X->GetXaxis()->SetTitleOffset(1.5);
    hPEff2D_2X->GetYaxis()->SetTitleOffset(1.5);
    
    hName = "hREC_1D_in_Rap";
    hTitle= "Rapidity difference for #phi meson candidates";
    TH1F       *hREC_1D_in_Rap  =   new TH1F (hName,hTitle,160,-.3,.3);
    hName = "hREC_1D_in_Rap1";
    hTitle= "Rapidity difference for #phi meson candidates";
    TH1F       *hREC_1D_in_Rap1  =   new TH1F (hName,hTitle,130,-.3,.3);
    hName = "hREC_1D_in_Rap2";
    hTitle= "Rapidity difference for #phi meson candidates";
    TH1F       *hREC_1D_in_Rap2  =   new TH1F (hName,hTitle,100,-.3,.3);
    hName = "hREC_1D_in_Rap3";
    hTitle= "Rapidity difference for #phi meson candidates";
    TH1F       *hREC_1D_in_Rap3  =   new TH1F (hName,hTitle,70,-.3,.3);
    
    // Creating the Target Result Histogram------------------------------------------------------------------
    hName   = "MC_Results";
    hTitle  = "Multidimensional #phi production statistics";
    TH1F *          hUtlTarget  = new TH1F (hName,hTitle,2,0.5,2.5);
    hUtlTarget->GetXaxis()->SetTitle("N-Tuples");
    hUtlTarget->GetYaxis()->SetTitle("#frac{1}{N_{evs}}#times#frac{dN_{#phi}}{dy}");
    
    hName   = "Entry_MC";
    hTitle  = "Events in MC";
    TH1F *          hUtlEntry   = new TH1F (hName,hTitle,2,0.5,2.5);
    hUtlEntry                   ->GetXaxis()->SetTitle("");
    hUtlEntry                   ->GetYaxis()->SetTitle("Events");
    
    //-------------------------//
    //  Filling output objects //
    //-------------------------//
    
    // Evaluating entries
    Int_t nEntries  =   TPhiCandidate->GetEntries();
    hUtlEntry       ->  SetBinContent(1,nEntries);
    
    // Starting cycle
    for ( Int_t iEvent = 0; iEvent < nEntries; iEvent++ )
    {
        TPhiCandidate->GetEntry(iEvent);
        
        TLorentzVector  LPhi_candidate1,    LPhi_candidate2;
        
        for ( Int_t iPhi = 0; iPhi < evPhiEfficiency.nPhi; iPhi++ )
        {
            LPhi_candidate1.SetXYZM(evPhiEfficiency.Px[iPhi],evPhiEfficiency.Py[iPhi],evPhiEfficiency.Pz[iPhi],kParticleMass_);
            if ( !fRapidityCut ( LPhi_candidate1.Rapidity() ) ) continue;

            // All True Phi                                                                 #TRU
            hPhiTru_1D-> Fill(LPhi_candidate1.Pt());
            hUtlTarget-> Fill(1);
            
            // Only |y| < 0.5 Phi in K+- Candidates                                         #GEN
            if ( evPhiEfficiency.Selection[iPhi] >= 1 )    { hPhiGen_1D-> Fill(LPhi_candidate1.Pt());  hPhiG1D_2X ->  Fill(LPhi_candidate1.Pt()); }

            // Only Recordable Phi in K+- Candidates                                        #REC
            if ( evPhiEfficiency.Selection[iPhi] >= 2 )    { hPhiRec_1D-> Fill(LPhi_candidate1.Pt());  hPhiR1D_2X ->  Fill(LPhi_candidate1.Pt()); }
            
            for ( Int_t jPhi = 0; jPhi < evPhiEfficiency.nPhi; jPhi++ )
            {
                // Non equal candidates
                if ( iPhi == jPhi ) continue;
                
                LPhi_candidate2.SetXYZM(evPhiEfficiency.Px[jPhi],evPhiEfficiency.Py[jPhi],evPhiEfficiency.Pz[jPhi],kParticleMass_);
                if ( !fRapidityCut ( LPhi_candidate2.Rapidity() ) ) continue;
                
                // All True Phi                                                             #TRU
                hPhiTru_2D-> Fill(LPhi_candidate1.Pt(),LPhi_candidate2.Pt(),0.5);
                hUtlTarget->Fill(2,0.5);

                // Only |y| < 0.5 Phi  in K+- Candidates                                    #GEN
                if ( evPhiEfficiency.Selection[iPhi] >= 1 && evPhiEfficiency.Selection[iPhi] >= 1 ) hPhiGen_2D-> Fill(LPhi_candidate1.Pt(),LPhi_candidate2.Pt(),0.5);
                
                // Only Recordable Phi in K+- Candidates                                    #REC
                if ( evPhiEfficiency.Selection[iPhi] >= 2 && evPhiEfficiency.Selection[iPhi] >= 2 ) hPhiRec_2D-> Fill(LPhi_candidate1.Pt(),LPhi_candidate2.Pt(),0.5);
                
                if ( jPhi < iPhi ) continue;
                hREC_1D_in_Rap  ->  Fill( LPhi_candidate1.Rapidity() - LPhi_candidate2.Rapidity() );
                hREC_1D_in_Rap1  ->  Fill( LPhi_candidate1.Rapidity() - LPhi_candidate2.Rapidity() );
                hREC_1D_in_Rap2  ->  Fill( LPhi_candidate1.Rapidity() - LPhi_candidate2.Rapidity() );
                hREC_1D_in_Rap3  ->  Fill( LPhi_candidate1.Rapidity() - LPhi_candidate2.Rapidity() );
            }
        }
    }
    
    // Evaluating the Target value
    hUtlTarget->Scale(1./(nEntries));

    // Fixing the Histograms per binwidth
    hPhiGen_1D    ->Scale(1.,"width");
    hPhiRec_1D    ->Scale(1.,"width");
    hPhiTru_1D    ->Scale(1.,"width");
    hPhiG1D_2X    ->Scale(1.,"width");
    hPhiR1D_2X    ->Scale(1.,"width");
    hPhiGen_2D    ->Scale(1.,"width");
    hPhiRec_2D    ->Scale(1.,"width");
    hPhiTru_2D    ->Scale(1.,"width");
    
    // Fixing the Histograms per Events
    hPhiGen_1D    ->Scale(1./(nEntries));
    hPhiRec_1D    ->Scale(1./(nEntries));
    hPhiTru_1D    ->Scale(1./(nEntries));
    hPhiG1D_2X    ->Scale(1./(nEntries));
    hPhiR1D_2X    ->Scale(1./(nEntries));
    hPhiGen_2D    ->Scale(1./(nEntries));
    hPhiRec_2D    ->Scale(1./(nEntries));
    hPhiTru_2D    ->Scale(1./(nEntries));
    
    // Evalutaing the Efficiencies
    hPhiEff_1D->Divide(hPhiRec_1D,hPhiGen_1D,1.,1.,"b");
    hPhiEff_2D->Divide(hPhiRec_2D,hPhiGen_2D,1.,1.,"b");
    hPEff1D_2X->Divide(hPhiR1D_2X,hPhiG1D_2X,1.,1.,"b");
    for ( Int_t iEff = 0; iEff <= nBinPT2D; iEff++ )
    {
        for ( Int_t jEff = 0; jEff <= nBinPT2D; jEff++ )
        {
            auto Val1 = hPEff1D_2X->GetBinContent(iEff+1);
            auto Val2 = hPEff1D_2X->GetBinContent(jEff+1);
            auto Err1 = hPEff1D_2X->GetBinError(iEff+1);
            auto Err2 = hPEff1D_2X->GetBinError(jEff+1);
            hPEff2D_2X  ->SetBinContent (hPEff2D_2X->GetBin(iEff+1,jEff+1),Val1*Val2);
            hPEff2D_2X  ->SetBinError   (hPEff2D_2X->GetBin(iEff+1,jEff+1),Err1+Err2);
        }
    }
    
    //--------------------------//
    //  Printing output objects //
    //--------------------------//
    TFile * outFile         =   new TFile   (fEfficiHist,"recreate");
    
    // Writing Histograms to Output File
    hUtlEntry       ->Write();
    hREC_1D_in_Rap  ->Write();
    hREC_1D_in_Rap1  ->Write();
    hREC_1D_in_Rap2  ->Write();
    hREC_1D_in_Rap3  ->Write();
    hPhiGen_1D      ->Write();
    hPhiG1D_2X      ->Write();
    hPhiGen_2D      ->Write();
    hPhiRec_1D      ->Write();
    hPhiR1D_2X      ->Write();
    hPhiRec_2D      ->Write();
    hPhiTru_1D      ->Write();
    hPhiTru_2D      ->Write();
    hPhiEff_1D      ->Write();
    hPhiEff_2D      ->Write();
    hPEff2D_2X      ->Write();
    hUtlTarget      ->Write();
    hPhiRec_1D->Write();
    
    outFile->Close();
    insFileMC->Close();
}
