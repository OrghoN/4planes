void plot_field(){
  #include "data_70_2D_11.txt"
  TGraph *gc = new TGraph(5000,w_2D_g_0_x,w_2D_g_0_y);
  gc->Draw("AL");
  
  TGraph *gi = new TGraph(5000,u_2D_g_0_x,u_2D_g_0_y);
  gi->Draw("AL");
  
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(2,2);
  c1->cd(1);
  TH1F *hc = new TH1F("hc","hc",500,0,100);
  for (Int_t i=0;i!=500;i++){
    Double_t x = hc->GetBinCenter(i+1);
    Double_t y = gc->Eval(x-50);
    hc->SetBinContent(i+1,y);
  }
  hc->Draw();
  hc->SetTitle("Collection Plane");
  hc->SetXTitle("Time (#mus)");
  hc->SetYTitle("Current (A.U.)");
  
  c1->cd(3);
  TH1F *hi = new TH1F("hi","hi",500,0,100);
  for (Int_t i=0;i!=500;i++){
    Double_t x = hi->GetBinCenter(i+1);
    Double_t y = gi->Eval(x-50);
    hi->SetBinContent(i+1,y);
  }
  hi->Draw();
  hi->SetTitle("Induction Plane");
  hi->SetXTitle("Time (#mus)");
  hi->SetYTitle("Current (A.U.)");
  
  
  c1->cd(2);
  TH1 *hcm = hc->FFT(0,"MAG");
  hcm->Draw();
  TH1F *hcw = new TH1F("hcw","hcw",250,0,2.5);
  for (Int_t i=0;i!=250;i++){
    hcw->SetBinContent(i+1,hcm->GetBinContent(i+1));
  }
  hcw->Draw();
  hcw->SetXTitle("Frequency (MHz)");
  hcw->SetTitle("Collection Plane");

  c1->cd(4);
  TH1 *him = hi->FFT(0,"MAG");
  him->Draw();
  TH1F *hiw = new TH1F("hiw","hiw",250,0,2.5);
  for (Int_t i=0;i!=250;i++){
    hiw->SetBinContent(i+1,him->GetBinContent(i+1));
  }
  hiw->Draw();
  hiw->SetXTitle("Frequency (MHz)");
  hiw->SetTitle("Induction Plane");
  
}
