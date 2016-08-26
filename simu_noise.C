#include <iostream>
#include "math.h"
#include "TMath.h"
#include "TF1.h"
#include "TRandom.h"

Double_t PoissonReal(const Double_t *k,  const Double_t *lambda) {
  return TMath::Exp(k[0]*TMath::Log(lambda[0])-lambda[0]) / TMath::Gamma(k[0]+1.);
}

void simu_noise(){
  Double_t MaxPoissArg = 100.; 
  
  TF1 *MyPoisson = new TF1("MyPoisson", PoissonReal,0.,MaxPoissArg,1);
  //**Setting lambda**//
  Double_t params[1] = {3.3708}; //2us
  MyPoisson->SetParameters(params);

  TF1 *f1 = new TF1("f","[0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4]))"); // x in MHz
  Double_t fitpar[5]={4.27132e+01,6.22750e+02,-2.53535e-01,8.07578e-05,1.35510e+00}; //2us (Final Fit)
  f1->SetParameters(fitpar);
  f1->Draw();

  Double_t value_re[10000], value_im[10000];
  Double_t value_re1[10000], value_im1[10000];
  Int_t  n  = 9600; // window size 
  
  #include "data_70_2D_11.txt"
  TGraph *gc = new TGraph(5000,w_2D_g_0_x,w_2D_g_0_y);
  gc->Draw("AL");
  TH1F *hc = new TH1F("hc","hc",9600,0,4800);
  for (Int_t i=0;i!=9600;i++){
    Double_t x = hc->GetBinCenter(i+1);
    Double_t y = gc->Eval(x-50);
    hc->SetBinContent(i+1,y);
  }
  TH1 *hm1 = hc->FFT(0,"MAG");
  TH1 *hp1 = hc->FFT(0,"PH");

  TF1 *filter_time = new TF1("filter_time","(x>0.0)*exp(-0.5*pow(x/[0],[1]))");
  double par2[2]={1.45874e+01/200.*2.,5.02219e+00};
  filter_time->SetParameters(par2);

  for (Int_t i=0;i!=n;i++){
    Double_t freq;
    if (i<n/2.){
      freq = (i)*2./n; // assume 2 MHz digitization 
    }else{
      freq = (n-i)*2./n;
    }
   
    Double_t rho = f1->Eval(freq) * sqrt(n/9592.) * MyPoisson->GetRandom()/params[0];
    if (i==0) rho = 0;
    Double_t rho1 = hm1->GetBinContent(i+1);
    Double_t phi1 = hp1->GetBinContent(i+1);
    Double_t phi = gRandom->Uniform(0,2*3.1415926);
    value_re[i] = rho*cos(phi)/n;
    value_im[i] = rho*sin(phi)/n;
    value_re1[i] = rho/rho1*cos(phi-phi1)/n * filter_time->Eval(freq);
    value_im1[i] = rho/rho1*sin(phi-phi1)/n * filter_time->Eval(freq);
  }

  TVirtualFFT *ifft = TVirtualFFT::FFT(1,&n,"C2R M K");
  ifft->SetPointsComplex(value_re,value_im);
  ifft->Transform();
  TH1 *fb = 0;
  fb = TH1::TransformHisto(ifft,fb,"Re");
  fb->Draw();

  // calculate RMS 
  Double_t count = 0;
  Double_t rms = 0;
  Double_t rms1 = 0;
  for (Int_t i=0;i!=n;i++){
    Double_t content = fb->GetBinContent(i+1);
    content = int(content);
    rms += pow(content,2);
    count ++;
  }
  rms = sqrt(rms/count);
  cout << rms*198 << endl;
  
  ifft->SetPointsComplex(value_re1,value_im1);
  ifft->Transform();
  TH1 *fb1 = 0;
  fb1 = TH1::TransformHisto(ifft,fb1,"Re");
  fb1->Draw();
  
  TH1F *hraw = new TH1F("h1","h1",9600,0,9600);
  TH1F *hdecon = new TH1F("hdecon","hdecon",9600,0,9600);
  for (Int_t i=0;i!=9600;i++){
    hraw->SetBinContent(i+1,fb->GetBinContent(i+1)*198);
    hdecon->SetBinContent(i+1,fb1->GetBinContent(i+1)/14./1.1/4092.*2000.);
  }

  count = 0;
  rms = 0;
  rms1 = 0;
  for (Int_t i=0;i!=n;i++){
    Double_t content = hdecon->GetBinContent(i+1);
    content = int(content);
    rms += pow(content,2);
    count ++;
  }
  rms = sqrt(rms/count);
  cout << rms << endl;


  hraw->Draw();
  hraw->SetLineColor(1);
  hdecon->Draw("same");
  hdecon->SetLineColor(2);

  hraw->SetXTitle("Time Tick");
  hraw->SetTitle("Collection Plane");
  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  le1->AddEntry(hraw,"ENC ~400","l");
  le1->AddEntry(hdecon,"DNC ~100","l");
  le1->Draw();
  
  
  
 
}
