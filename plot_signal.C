void plot_signal(){
  TH1F *h1 = new TH1F("h1","h1",10000,0,2000);
  // 1us
  for (Int_t i=0;i!=5*1;i++){
    h1->SetBinContent(i+1,18e3/5.);
  }
  TH1 *hm1 = h1->FFT(0,"MAG");
  //hm1->Draw();
  h1->Reset();
  for (Int_t i=0;i!=5*10;i++){
    h1->SetBinContent(i+1,18e3/5.);
  }
  TH1 *hm2 = h1->FFT(0,"MAG");
  hm2->Draw();

  h1->Reset();
  for (Int_t i=0;i!=5*100;i++){
    h1->SetBinContent(i+1,18e3/5.);
  }
  TH1 *hm3 = h1->FFT(0,"MAG");

  h1->Reset();
  for (Int_t i=0;i!=5*1000;i++){
    h1->SetBinContent(i+1,18e3/5.);
  }
  TH1 *hm4 = h1->FFT(0,"MAG");

  TH1F *hmw1 = new TH1F("hmw1","hmw1",5000,0,2.5);
  TH1F *hmw2 = new TH1F("hmw2","hmw2",5000,0,2.5);
  TH1F *hmw3 = new TH1F("hmw3","hmw3",5000,0,2.5);
  TH1F *hmw4 = new TH1F("hmw4","hmw4",5000,0,2.5);
  TGraph *gw1 = new TGraph();
  TGraph *gw2 = new TGraph();
  TGraph *gw3 = new TGraph();
  TGraph *gw4 = new TGraph();
  
  for (Int_t i=0;i!=5000;i++){
    // hmw1->SetBinContent(i+1,hm1->GetBinContent(i+1));
    // hmw2->SetBinContent(i+1,hm2->GetBinContent(i+1));
    // hmw3->SetBinContent(i+1,hm3->GetBinContent(i+1));
    // hmw4->SetBinContent(i+1,hm4->GetBinContent(i+1));
    gw1->SetPoint(i,2.5/5000.*i,hm1->GetBinContent(i+1));
    gw2->SetPoint(i,2.5/5000.*i,hm2->GetBinContent(i+1)/10.);
    gw3->SetPoint(i,2.5/5000.*i,hm3->GetBinContent(i+1)/100.);
    gw4->SetPoint(i,2.5/5000.*i,hm4->GetBinContent(i+1)/1000.);
  }
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  // c1->SetLogx(1);
  c1->SetLogy(1);
  
  gw4->Draw("AL");
  gw3->Draw("Lsame");
  gw2->Draw("Lsame");
  gw1->Draw("Lsame");
  //gw4->GetYaxis()->SetRangeUser(0,1e7);
  gw4->GetXaxis()->SetTitle("Frequency (MHz)");
  gw4->SetTitle("Frequency Content");

  gw1->SetLineColor(1);
  gw2->SetLineColor(2);
  gw3->SetLineColor(4);
  gw4->SetLineColor(6);

  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  le1->AddEntry(gw1,"1    #mus","l");
  le1->AddEntry(gw2,"10   #mus x1/10","l");
  le1->AddEntry(gw3,"100  #mus x1/100","l");
  le1->AddEntry(gw4,"1000 #mus x1/1000","l");
  le1->Draw();
  
}
