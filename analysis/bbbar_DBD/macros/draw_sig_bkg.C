#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "TLine.h"
#include "../../style/Style.C"
#include "../../style/Labels.C"


void draw_sig_bkg() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleX(0.25); 
  gStyle->SetTitleY(1); 

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0);
  gStyle->SetLegendFont(42);

    
  TString pol="eL";
 
  TFile *f = new TFile("../output/bbbar_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");
  TH1F *h_parton = (TH1F*)f->Get("parton");
  TH1F *h_reco = (TH1F*)f->Get("reco");
  TH1F *h_bkg_qq = (TH1F*)f->Get("bkg_qq");
  TH1F *h_bkg_radreturn = (TH1F*)f->Get("bkg_radreturn");

  f = new TFile("../output/bkg_ZZ_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");
  TH1F *h_bkg_zz = (TH1F*)f->Get("reco");

  f = new TFile("../output/bkg_WW_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");
  TH1F *h_bkg_ww = (TH1F*)f->Get("reco");

  f = new TFile("../output/bkg_HZ_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");
  TH1F *h_bkg_hz = (TH1F*)f->Get("reco");

  if(pol=="eL") {
    h_parton->Scale(250./266.5);
    h_reco->Scale(250./266.5);
    h_bkg_qq->Scale(250./266.5);
    h_bkg_radreturn->Scale(250./266.5);
    
    h_bkg_ww->Scale(250./72.2);
    h_bkg_zz->Scale(250./1000.);
    h_bkg_hz->Scale(250./1000.);
  }

  if(pol=="eR") {
    h_parton->Scale(250./276.9);
    h_reco->Scale(250./276.9);
    h_bkg_qq->Scale(250./276.9);
    h_bkg_radreturn->Scale(250./276.9);
    
    h_bkg_ww->Scale(250./72.2);
    h_bkg_zz->Scale(250./1000.);
    h_bkg_hz->Scale(250./1000.);
  }

  double reco=100.*h_reco->Integral()/h_parton->Integral();
  double qq=100.*h_bkg_qq->Integral()/h_reco->Integral();
  double radreturn=100.*h_bkg_radreturn->Integral()/h_reco->Integral();
  double zz=100.*h_bkg_zz->Integral()/h_reco->Integral();
  double ww=100.*h_bkg_ww->Integral()/h_reco->Integral();
  double hz=100.*h_bkg_hz->Integral()/h_reco->Integral();

  
  h_reco->Add(h_bkg_qq);
  h_reco->Add(h_bkg_radreturn);
  h_reco->Add(h_bkg_zz);
  h_reco->Add(h_bkg_ww);
  h_reco->Add(h_bkg_hz);

  /*

  h_bkg_hz->Add(h_bkg_ww);
  h_bkg_hz->Add(h_bkg_zz);
  h_bkg_hz->Add(h_bkg_radreturn);
  h_bkg_hz->Add(h_bkg_qq);

  h_bkg_ww->Add(h_bkg_zz);
  h_bkg_ww->Add(h_bkg_radreturn);
  h_bkg_ww->Add(h_bkg_qq);

  h_bkg_zz->Add(h_bkg_radreturn);
  h_bkg_zz->Add(h_bkg_qq);
  
  h_bkg_radreturn->Add(h_bkg_qq);*/

  THStack * hreco = new THStack("Reco","Reco");
  hreco->Add(h_bkg_hz);
  hreco->Add(h_bkg_ww);
  hreco->Add(h_bkg_zz);
  hreco->Add(h_bkg_radreturn);
  hreco->Add(h_bkg_qq);
  hreco->Add(h_reco);

  if(pol=="eL") {
    h_bkg_hz->Scale(10);
    h_bkg_zz->Scale(10);
    h_bkg_ww->Scale(10);
    h_bkg_qq->Scale(10);
    h_bkg_radreturn->Scale(10);
  }

  if(pol=="eR") {
    h_bkg_hz->Scale(2);
    h_bkg_zz->Scale(2);
    h_bkg_ww->Scale(2);
    h_bkg_qq->Scale(2);
    h_bkg_radreturn->Scale(2);
  }

  THStack * bkg = new THStack("BKG","BKG");
  bkg->Add(h_bkg_hz);
  bkg->Add(h_bkg_ww);
  bkg->Add(h_bkg_zz);
  bkg->Add(h_bkg_radreturn);
  bkg->Add(h_bkg_qq);

  
  TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  canvas->cd(1);

  h_reco->SetLineColor(1);
  h_reco->SetMarkerColor(1);
  
  h_bkg_hz->SetLineColor(3);
  h_bkg_hz->SetFillColor(3);
  h_bkg_hz->SetFillStyle(3005);
  //  h_bkg_hz->Draw("histosame");
  
  h_bkg_ww->SetLineColor(kGray+2);
  h_bkg_ww->SetFillColor(kGray+2);
  h_bkg_ww->SetFillStyle(3006);
  // h_bkg_ww->Draw("histosame");
  
  h_bkg_zz->SetLineColor(2);
  h_bkg_zz->SetFillColor(2);
  h_bkg_zz->SetFillStyle(3001);
  // h_bkg_zz->Draw("histosame");

  h_bkg_radreturn->SetLineColor(4);
  h_bkg_radreturn->SetFillColor(4);
  h_bkg_radreturn->SetFillStyle(3004);
  //  h_bkg_radreturn->Draw("histosame");
  
  h_bkg_qq->SetLineColor(6);
  h_bkg_qq->SetFillColor(6);
  h_bkg_qq->SetFillStyle(1001);
  // h_bkg_qq->Draw("histosame");

  // bkg->GetYaxis()->SetRangeUser(0,10000);
  hreco->Draw("histo");
  hreco->GetXaxis()->SetTitle("cos#theta_{b}");
  hreco->GetYaxis()->SetTitle("entries / 0.05");
  hreco->GetYaxis()->SetTitleOffset(1.6);
  hreco->GetYaxis()->SetRangeUser(0,hreco->GetMaximum()*1.2);
  hreco->SetTitle("Before correction & bkg subtraction");
  
  //h_reco->SetFillStyle(3002);
  //  h_reco->SetFillColor(1);
  // h_reco->Draw("histosame");

  // bkg->GetYaxis()->SetRangeUser(0,10000);
  canvas->Update();
  
  QQBARLabel(0.2,0.85,"");
  //  h_bkg_qq->
  TLegend *leg = new TLegend(0.2,0.6,0.55,0.8);
  if(pol=="eL")leg->SetHeader("e_{L}^{-}e_{R}^{+} #rightarrow b#bar{b}, 250GeV, 250fb^{-1}");
  if(pol=="eR")leg->SetHeader("e_{R}^{-}e_{L}^{+} #rightarrow b#bar{b}, 250GeV, 250fb^{-1}");
  leg->AddEntry(h_reco,TString::Format("Signal, selection eff: %0.1f",reco)+"%","l");
  leg->AddEntry(h_bkg_qq,TString::Format("q#bar{q} %0.2f",qq)+"%","f");
  leg->AddEntry(h_bkg_radreturn,TString::Format("Radiative return %0.2f",radreturn)+"%","f");
  leg->AddEntry(h_bkg_ww,TString::Format("WW %0.2f",ww)+"%","f");
  leg->AddEntry(h_bkg_zz,TString::Format("ZZ %0.2f",zz)+"%","f");
  leg->AddEntry(h_bkg_hz,TString::Format("HZ %0.2f",hz)+"%","f");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);                                                                                                                         
  l.SetNDC();
  l.SetTextFont(11);
  l.SetTextColor(1);
 
  if(pol=="eL") l.DrawLatex(0.7,0.3,"bkg x 10");
  if(pol=="eR") l.DrawLatex(0.7,0.3,"bkg x 2");

  
  
}

