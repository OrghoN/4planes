void plot_conv(){
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

  
  #include "data_70_2D_11.txt"
  TGraph *gc = new TGraph(5000,w_2D_g_0_x,w_2D_g_0_y);
  gc->Draw("AL");
  
  TGraph *gi = new TGraph(5000,u_2D_g_0_x,u_2D_g_0_y);
  gi->Draw("AL");
  TH1F *hc = new TH1F("hc","hc",10000,0,2000);
  for (Int_t i=0;i!=5000;i++){
    Double_t x = hc->GetBinCenter(i+1);
    Double_t y = gc->Eval(x-50);
    hc->SetBinContent(i+1,y);
  }
  // hc->Draw();
  // hc->SetTitle("Collection Plane");
  // hc->SetXTitle("Time (#mus)");
  // hc->SetYTitle("Current (A.U.)");
  TH1F *hi = new TH1F("hi","hi",10000,0,2000);
  for (Int_t i=0;i!=5000;i++){
    Double_t x = hi->GetBinCenter(i+1);
    Double_t y = gi->Eval(x-50);
    hi->SetBinContent(i+1,y);
  }
  TH1 *hcm = hc->FFT(0,"MAG");
  TH1 *him = hi->FFT(0,"MAG");
  

  TGraph *gw1 = new TGraph();
  TGraph *gw2 = new TGraph();
  TGraph *gw3 = new TGraph();
  TGraph *gw4 = new TGraph();
  
  for (Int_t i=0;i!=5000;i++){
    // hmw1->SetBinContent(i+1,hm1->GetBinContent(i+1));
    // hmw2->SetBinContent(i+1,hm2->GetBinContent(i+1));
    // hmw3->SetBinContent(i+1,hm3->GetBinContent(i+1));
    // hmw4->SetBinContent(i+1,hm4->GetBinContent(i+1));
    gw1->SetPoint(i,2.5/5000.*i,hm1->GetBinContent(i+1)*him->GetBinContent(i+1));
    gw2->SetPoint(i,2.5/5000.*i,hm2->GetBinContent(i+1)*him->GetBinContent(i+1)/10.);
    gw3->SetPoint(i,2.5/5000.*i,hm3->GetBinContent(i+1)*him->GetBinContent(i+1)/100.);
    gw4->SetPoint(i,2.5/5000.*i,hm4->GetBinContent(i+1)*him->GetBinContent(i+1)/1000.);
  }

  


  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->SetLogx(1);
  c1->SetLogy(1);
  
  gw4->Draw("AL");
  gw3->Draw("Lsame");
  gw2->Draw("Lsame");
  gw1->Draw("Lsame");
  //gw4->GetYaxis()->SetRangeUser(0,1e7);
  gw4->GetXaxis()->SetRangeUser(1e-5,1);
  gw4->GetXaxis()->SetTitle("Frequency (MHz)");
  gw4->SetTitle("Frequency Content (Induction)");
  gw4->GetYaxis()->SetRangeUser(1e-4,100);

  gw1->SetLineColor(1);
  gw2->SetLineColor(2);
  gw3->SetLineColor(4);
  gw4->SetLineColor(6);

  TF1 *f1 = new TF1("f","([0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4])))*sqrt(2./9592)/14./1.1/4096*2000./sqrt(1000.)"); // x in MHz
  TF1 *f2 = new TF1("f","([0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4])))*sqrt(2./9592)/14./1.1/4096*2000./sqrt(100.)"); // x in MHz
  TF1 *f3 = new TF1("f","([0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4])))*sqrt(2./9592)/14./1.1/4096*2000./sqrt(10.)"); // x in MHz
  TF1 *f4 = new TF1("f","([0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4])))*sqrt(2./9592)/14./1.1/4096*2000./sqrt(1.)"); // x in MHz
  Double_t fitpar[5]={4.27132e+01,6.22750e+02,-2.53535e-01,8.07578e-05,1.35510e+00}; //2us (Final Fit)
  f1->SetParameters(fitpar);
  f2->SetParameters(fitpar);
  f3->SetParameters(fitpar);
  f4->SetParameters(fitpar);
  f1->Draw("same");
  f2->Draw("same");
  f3->Draw("same");
  f4->Draw("same");
  f1->SetLineColor(6);
  f2->SetLineColor(4);
  f3->SetLineColor(2);
  f4->SetLineColor(1);

  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  le1->AddEntry(gw1,"1    #mus","l");
  le1->AddEntry(gw2,"10   #mus x1/10","l");
  le1->AddEntry(gw3,"100  #mus x1/100","l");
  le1->AddEntry(gw4,"1000 #mus x1/1000","l");
  le1->AddEntry(f1,"Electronic Noise 1000 #mus x1/1000","l");
  le1->AddEntry(f2,"Electronic Noise 100 #mus x1/100","l");
  le1->AddEntry(f3,"Electronic Noise 10 #mus x1/10","l");
  le1->AddEntry(f4,"Electronic Noise 1 #mus","l");
  le1->Draw();
  
}
