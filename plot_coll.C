void plot_coll(){
  #include "data_70_2D_11.txt"
  TGraph *g1 = new TGraph(5000,w_2D_g_0_x,w_2D_g_0_y);
  TGraph *g2 = new TGraph(5000,w_2D_g_1_x,w_2D_g_1_y);
  TGraph *g3 = new TGraph(5000,w_2D_g_2_x,w_2D_g_2_y);
  g1->Draw("AL");
  g2->Draw("Lsame");
  g2->SetLineColor(2);
  g3->Draw("Lsame");
  g3->SetLineColor(4);
  g1->SetTitle("Collection Signal");
  g1->GetXaxis()->SetTitle("Time (#mu s)");
  TLegend *le1 = new TLegend(0.6,0.6,0.89,0.89);
  le1->SetFillColor(10);
  le1->AddEntry(g1,"0th wire","l");
  le1->AddEntry(g2,"#pm1 wire","l");
  le1->AddEntry(g3,"#pm2 wire","l");
  le1->Draw();

  
}
