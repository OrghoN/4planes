void plot_plane(){
  TChain *t2 = new TChain("T","T");
  t2->AddFile("plane_2.root");
  TH1F *h2_1 = new TH1F("h2_1","h2_1",30,0,30);
  TH1F *h2_2 = new TH1F("h2_2","h2_2",30,0,30);
  t2->Project("h2_1","nhit");
  t2->Project("h2_2","nhit","nphit");
  h2_2->Divide(h2_1);
  h2_2->Draw();

  TChain *t3 = new TChain("T","T");
  t3->AddFile("plane_3.root");
  TH1F *h3_1 = new TH1F("h3_1","h3_1",30,0,30);
  TH1F *h3_2 = new TH1F("h3_2","h3_2",30,0,30);
  t3->Project("h3_1","nhit");
  t3->Project("h3_2","nhit","nphit");
  h3_2->Divide(h3_1);
  h3_2->Draw();

  
  TChain *t4 = new TChain("T","T");
  t4->AddFile("plane_4.root");
  TH1F *h4_1 = new TH1F("h4_1","h4_1",30,0,30);
  TH1F *h4_2 = new TH1F("h4_2","h4_2",30,0,30);
  t4->Project("h4_1","nhit");
  t4->Project("h4_2","nhit","nphit");
  h4_2->Divide(h4_1);
  h4_2->Draw();

  
  TChain *t5 = new TChain("T","T");
  t5->AddFile("plane_5.root");
  TH1F *h5_1 = new TH1F("h5_1","h5_1",30,0,30);
  TH1F *h5_2 = new TH1F("h5_2","h5_2",30,0,30);
  t5->Project("h5_1","nhit");
  t5->Project("h5_2","nhit","nphit");
  h5_2->Divide(h5_1);
  h5_2->Draw();

  TChain *t6 = new TChain("T","T");
  t6->AddFile("plane_6.root");
  TH1F *h6_1 = new TH1F("h6_1","h6_1",30,0,30);
  TH1F *h6_2 = new TH1F("h6_2","h6_2",30,0,30);
  t6->Project("h6_1","nhit");
  t6->Project("h6_2","nhit","nphit");
  h6_2->Divide(h6_1);
  h6_2->Draw();


  h2_2->Draw();
  h3_2->Draw("same");
  h4_2->Draw("same");
  h5_2->Draw("same");
  h6_2->Draw("same");
  
  h2_2->SetLineColor(1);
  h3_2->SetLineColor(2);
  h4_2->SetLineColor(4);
  h5_2->SetLineColor(6);
  h6_2->SetLineColor(8);
  h2_2->SetXTitle("# of real hits");
  h2_2->SetYTitle("# of potential hits");
  
  h2_2->SetTitle("1x1 m^{2} 3 mm pitch");

  TH1F *h1_2 = new TH1F("h1_2","h1_2",30,0,30);
  for (Int_t i=0;i!=30;i++){
    h1_2->SetBinContent(i+1,i);
  }
  h1_2->Draw("same");
  h1_2->SetLineColor(12);

  Double_t p = 0.9;
  Double_t e3 = p*p*p+3*p*p*(1-p);
  Double_t e4 = p*p*p*p+4*p*p*p*(1-p);
  Double_t e5 = p*p*p*p*p+5*p*p*p*p*(1-p);
  Double_t e6 = p*p*p*p*p*p+6*p*p*p*p*p*(1-p);

  TH1F *h3_3 = (TH1F*)h3_2->Clone("h3_3");
  TH1F *h4_3 = (TH1F*)h3_2->Clone("h4_3");
  TH1F *h5_3 = (TH1F*)h3_2->Clone("h5_3");
  TH1F *h6_3 = (TH1F*)h3_2->Clone("h6_3");
  
  h3_3->Add(h2_2,h3_2,e3*(1-p),e3*p);
  h4_3->Add(h3_2,h4_2,e4*(1-p),e4*p);
  h5_3->Add(h4_2,h5_2,e5*(1-p),e5*p);
  h6_3->Add(h5_2,h6_2,e6*(1-p),e6*p);
  
  h3_3->SetLineColor(2);
  h4_3->SetLineColor(4);
  h5_3->SetLineColor(6);
  h6_3->SetLineColor(8);
  
  h3_3->Draw("same");
  h4_3->Draw("same");
  h5_3->Draw("same");
  h6_3->Draw("same");
  h3_3->SetLineStyle(2);
  h4_3->SetLineStyle(2);
  h5_3->SetLineStyle(2);
  h6_3->SetLineStyle(2);

  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  //  le1->AddEntry(h2_2,"2 planes","l");
  le1->AddEntry(h3_2,"3 planes","l");
  le1->AddEntry(h4_2,"4 planes","l");
  le1->AddEntry(h5_2,"5 planes","l");
  le1->AddEntry(h6_2,"6 planes","l");
  le1->AddEntry(h1_2,"real == potential","l");
  le1->Draw();


 
  
}
