void plot_noise(){
  TF1 *f1 = new TF1("f","([0]+([1]+[2]*x*9592./2.)*exp(-[3]*pow(x*9592./2.,[4])))*sqrt(2./9592)/14./1.1/4096*2000."); // x in MHz
  Double_t fitpar[5]={4.27132e+01,6.22750e+02,-2.53535e-01,8.07578e-05,1.35510e+00}; //2us (Final Fit)
  f1->SetParameters(fitpar);
  f1->Draw();
  
  
}
