//plotLimits(string filename, TString name, TString channel, TString lepton){
plotLimits(const string& bin){

string filename;
string name;
 filename = Form("%s_unblinded_limits.txt", bin.c_str());
 name = Form("%s", bin.c_str());
 cout << filename.c_str() << endl;
//filename = Form("lowMT_limits.txt");
//name = Form("comb_lowMT");
//gROOT->LoadMacro("CMS_lumi.C");

//gROOT->ProcessLine(".L tdrstyle.C");
//setTDRStyle();


 TGraph * limit_obs = new TGraph();
 TGraph * limit_exp = new TGraph();
 TGraphAsymmErrors * band_exp1 = new TGraphAsymmErrors();
 TGraphAsymmErrors * band_exp2 = new TGraphAsymmErrors();
 
 ifstream infile(filename.c_str());
 
 double mass, exp, obs, up1, up2, dn1, dn2;
 //double mass, exp, up1, up2, dn1, dn2;
 int point = 0;
 
while (!infile.eof()){
  
  //infile >> mass >> obs >>  dn2 >> dn1 >> exp >> up1 >> up2;
  infile >> mass >>  dn2 >> dn1 >> exp >> up1 >> up2 >> obs;
  
  
  
  cout << mass << " & " << exp << " & " << obs << " & " << "["<<dn1<<", "<<up1<<"] & ["<<dn2<<", "<<up2<<"] \\" << endl;
  
  
  limit_obs->SetPoint(point, mass, obs);
  limit_exp->SetPoint(point, mass, exp);
  band_exp1->SetPoint(point, mass, exp);
  band_exp2->SetPoint(point, mass, exp);
  
  band_exp1->SetPointEYhigh(point, up1 - exp);
  band_exp1->SetPointEYlow(point, exp - dn1);
  band_exp2->SetPointEYhigh(point, up2 - exp);
  band_exp2->SetPointEYlow(point, exp - dn2);
  point++;
  if (point > 5) { break; }
  
 }

double max = band_exp2->GetHistogram()->GetMaximum()*50;

  TCanvas *canvas = new TCanvas(Form("limit set %s",name.c_str()),Form("limit set %s",name.c_str()), 500,500);

  limit_exp->Draw("AL");
  limit_exp->GetXaxis()->SetTitle("m_{a} [GeV]");
  limit_exp->GetYaxis()->SetTitle("95% CL limit on Br(H#rightarrowaa#rightarrow4#tau)");
  limit_exp->GetYaxis()->SetTitleOffset(1.2);
  limit_exp->SetTitle("Limits for M_{T} < 50 GeV");
  //limit_exp->SetTitle("Limits for M_{T} > 50 GeV");

  band_exp2->SetFillColor(5);
  band_exp2->SetLineColor(0);
  //band_exp2->SetFillStyle(4000);
  band_exp2->Draw("3same");

  band_exp1->SetFillColor(3);
  band_exp1->SetLineColor(0);
  //band_exp1->SetFillStyle(4000);
  band_exp1->Draw("3same");

  limit_obs->Draw("Lsame");
  limit_obs->SetLineWidth(2);
  limit_obs->SetMarkerSize(1.0);
  limit_obs->SetMaximum(max);
  limit_obs->SetMinimum(0.01);
  limit_obs->SetMarkerStyle(20);
   
  limit_exp->Draw("Lsame");
  limit_exp->SetLineStyle(2);
  limit_exp->SetLineWidth(2);
  limit_exp->SetMarkerSize(1.0);
  limit_exp->SetMaximum(max);
  limit_exp->SetMinimum(0.01);
  limit_exp->SetMarkerStyle(20);


  //Legend
  TLegend *l = new TLegend(0.15,0.60,0.45,0.84);
  l->AddEntry(limit_obs,"Observed", "L");
  l->AddEntry(limit_exp,"Expected", "L");
  l->AddEntry(band_exp1,"#pm1 #sigma Exp.", "F");
  l->AddEntry(band_exp2,"#pm2 #sigma Exp.", "F");
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  TLatex * label = new TLatex();
  label->SetNDC();
  label->SetTextSize(0.04);
  //label->DrawLatex(0.1,0.91,"CMS Preliminary, #sqrt{s} = 8 TeV, 19.7 fb^{-1}");
  //CMS_lumi(canvas, 2, 33, "Preliminary");


  // if (tag == 1) label->DrawLatex(0.15, 0.85, "1 b-tag");
  // if (tag == 2) label->DrawLatex(0.15, 0.85, "2 b-tags");
  // if (tag == 3) label->DrawLatex(0.15, 0.85, "1+2 b-tags");

   canvas->SetLogy(1);


   canvas->Print(Form("comb_%s_limit.pdf",bin.c_str()));
   canvas->Print(Form("comb_%s_limit.png",bin.c_str()));
   //canvas->Print(Form("comb_lowMT_limit.pdf"));
   //canvas->Print(Form("comb_lowMT_limit.png"));

}




