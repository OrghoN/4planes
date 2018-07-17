#include "TROOT.h"
#include "TRandom.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>


using namespace std;
Double_t cal_wire(Double_t x, Double_t y, Double_t i, Double_t n){
  // x, y position
  // i is the ith plane
  // n is the total number of plane

  Double_t dis = cos( i * 2 * 3.1415926/2./n) * y + sin(i*2*3.1415926/2./n) * x;
  Int_t wire = round(dis/0.003 + 250);
  return wire;
}

Double_t cal_xuv(Double_t u, Double_t v, Int_t n){
  Double_t x;
  x = ((v-250)*0.003 - cos(2*3.1415926/2./n) * (u-250)*0.003)/sin(2*3.1415926/2./n);
  return x;
}
Double_t cal_yuv(Double_t u, Double_t v, Int_t n){
  Double_t y;
  y = (u-250)*0.003;
  return y;
}

void cal_hits(){
  const Int_t nplane = 3;

  TFile *file = new TFile(Form("plane_%d.root",nplane),"RECREATE");
  TTree *T = new TTree("T","T");
  Int_t nhit;
  T->Branch("nhit",&nhit,"nhit/I");
  Int_t nphit;
  T->Branch("nphit",&nphit,"nphit/I");
  Int_t nwires;
  T->Branch("nwires",&nwires,"nwires/I");

  for (Int_t temp = 0; temp!=100000;temp++){
    if (temp%10000==0) std::cout << temp << std::endl;
  // initialized the fired wires
  std::vector<std::vector<int> > fired_wires;
  fired_wires.resize(nplane);
  // potential hits
  std::list<std::pair<double,double> > potential_hits, bad_hits;

  nhit = gRandom->Uniform(1,30);
  for (Int_t i=0;i!=nhit;i++){
      Double_t xp = gRandom->Uniform(-0.5,0.5);
      Double_t yp = gRandom->Uniform(-0.5,0.5);
      //cout << xp << " " << yp << endl;
      //int u,v;
      for (Int_t j=0;j!=nplane;j++){
	int wire = cal_wire(xp,yp,j,nplane);
	if (find(fired_wires.at(j).begin(),fired_wires.at(j).end(),wire) == fired_wires.at(j).end())
	  fired_wires.at(j).push_back(wire);
	//cout << cal_wire(xp,yp,j,nplane) << endl;
	//if (j==0) u = cal_wire(xp,yp,j,nplane);
	//if (j==1) v = cal_wire(xp,yp,j,nplane);
	//cout << j << " " << wire << endl;
      }

      //      cout << cal_xuv(u,v,nplane) << " " << cal_yuv(u,v,nplane) << endl;
  }

  //form potential hits from the first two planes
  for (size_t j=0;j!=fired_wires.at(0).size();j++){
    for (size_t k=0;k!=fired_wires.at(1).size();k++){
      // std::cout << fired_wires.at(0).at(j) << " " << fired_wires.at(1).at(k),nplane) << std::endl;
      potential_hits.push_back(std::make_pair(fired_wires.at(0).at(j),fired_wires.at(1).at(k)));
    }
  }

  // check the rest of the planes
  for (auto it = potential_hits.begin();it!=potential_hits.end();it++){
    //cout << x << " " << y << endl;
    int flag = 0;
    for (int i=2;i<nplane;i++){
      int flag1 = 0;
      for (int k1 = 0; k1!=3; k1++){
	for (int k2 = 0; k2!=3; k2++){
	  Double_t up = it->first -0.5+0.5*k1;
	  Double_t vp = it->second -0.5+0.5*k2;
	  Double_t x = cal_xuv(up,vp,nplane);
	  Double_t y = cal_yuv(up,vp,nplane);
	  int wire = cal_wire(x,y,i,nplane);
	  //cout << "xin2 " << x << " " << y << " " << wire << endl;
	  if (find(fired_wires.at(i).begin(),fired_wires.at(i).end(),wire) !=
	      fired_wires.at(i).end()){
	    flag1 = 1; // found
	    break;
	  }
	}
	if (flag1==1) break;
      }

      //cout << "xin " << flag1 << endl;
      if (flag1 == 0) {
	flag = 1;
	break;
      }
    }

    if (flag == 1)
      bad_hits.push_back(std::make_pair(1,1));
  }
  //std::cout << potential_hits.size() << " " << bad_hits.size() <<std::endl;
  nphit = potential_hits.size()-bad_hits.size();

  nwires = 0;
  for (Int_t i=0; i!= nplane ;i++){
    nwires += fired_wires.at(i).size();
  }

  T->Fill();
}
  file->Write();
  file->Close();



}
