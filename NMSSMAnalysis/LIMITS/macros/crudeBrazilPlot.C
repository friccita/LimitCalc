void crudeBrazilPlot(bool BrOnly)
{ // code beginning

  //double xsecWH[6] = {0.085, 0.083, 0.09, 0.00138, 0.00087, 0.00075}; //0.09 pb calculated by Pythia for WH signal
  //double xsecggH[6] = {7.135, 6.967, 7.555, 0.116, 0.0730, 0.0630};//7.555 pb = 0.09*sig_SM[ggH]/sig_SM[WH] at mH = 125 GeV
  double SMxsecggH = 19.27; //SM xsec for ggH production @ 8 TeV is 19.27 pb
  double SMxsecWH = 0.7046; //SM xsec for WH production @ 8 TeV is 0.7046 pb
  double BrWlep = 3*0.1086; //branching ratio for leptonic W decay

  // plot low MT limits for WH
  TCanvas *cLow_WH = new TCanvas("cLow_WH", "Expected CLs limits for low MT bin, WH", 600, 600);
  cLow_WH->cd();
  gPad->SetLogy();
  const int lowMassPointsW = 6;
  double WH_low_m[lowMassPointsW] = {5, 7, 9, 11, 13, 15};
  /*  double WH_low_min2sig[lowMassPointsW] = {56.680100, 3.979400, 2.154400, 1.580200, 1.798500, 1.926700};
  double WH_low_min1sig[lowMassPointsW] = {71.275800, 4.980200, 2.709200, 1.987200, 2.261700, 2.422800};
  double WH_low_median[lowMassPointsW] = {93.312500, 6.593800, 3.546900, 2.601600, 2.960900, 3.171900};
  double WH_low_plus1sig[lowMassPointsW] = {126.415800, 8.880400, 4.805200, 3.524500, 4.011400, 4.297100};
  double WH_low_plus2sig[lowMassPointsW] = {170.051400, 11.978400, 6.463800, 4.741100, 5.396000, 5.780400};
  */

  //latest limits
  /*
  double WH_low_min2sig[lowMassPointsW] = {53.855300, 3.791400, 2.050300, 1.503200, 1.708000, 1.838300};
  double WH_low_min1sig[lowMassPointsW] = {68.418600, 4.808300, 2.587300, 1.909700, 2.169900, 2.315900};
  double WH_low_median[lowMassPointsW] = {90.406200, 6.343800, 3.453100, 2.523400, 2.867200, 3.085900};
  double WH_low_plus1sig[lowMassPointsW] = {123.199300, 8.670100, 4.705700, 3.438800, 3.907200, 4.205300};
  double WH_low_plus2sig[lowMassPointsW] = {166.461200, 11.698600, 6.358100, 4.646300, 5.279200, 5.682000};
  */
  //with tau pT > 20
  double WH_low_min2sig[lowMassPointsW] = {60.062300, 4.172100, 2.336000, 1.514100, 1.750300, 1.754400};
  double WH_low_min1sig[lowMassPointsW] = {74.441700, 5.170900, 2.895200, 1.876500, 2.165900, 2.174400};
  double WH_low_median[lowMassPointsW] = {97.625000, 6.781200, 3.796900, 2.460900, 2.835900, 2.851600};
  double WH_low_plus1sig[lowMassPointsW] = {133.036500, 9.241000, 5.174100, 3.353600, 3.864600, 3.885900};
  double WH_low_plus2sig[lowMassPointsW] = {181.032700, 12.574900, 7.040800, 4.563500, 5.258900, 5.287800};

  double WH_low_YLowerLimit = 999999999.;
  double WH_low_YUpperLimit = -999999999.;
  
  for (int i = 0; i < lowMassPointsW; ++i)
    {

      if (BrOnly)
	{
	  /*WH_low_min2sig[i] *= (1./BrWlep);
	  WH_low_min1sig[i] *= (1./BrWlep);
	  WH_low_median[i] *= (1./BrWlep);
	  WH_low_plus1sig[i] *= (1./BrWlep);
	  WH_low_plus2sig[i] *= (1./BrWlep);*/
	  cout << "Limits on branching ratios for WH, low MT, mass point " << WH_low_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << WH_low_min2sig[i] << "\t" << WH_low_min1sig[i] << "\t" << WH_low_median[i] << "\t" << WH_low_plus1sig[i] << "\t" << WH_low_plus2sig[i] << endl;
	}
      else
	{
	  WH_low_min2sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_low_min1sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_low_median[i] *= SMxsecWH/*/BrWlep*/;
	  WH_low_plus1sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_low_plus2sig[i] *= SMxsecWH/*/BrWlep*/;
	  cout << "Limits on xsec*Br for WH, low MT, mass point " << WH_low_m[i]  << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << WH_low_min2sig[i] << "\t" << WH_low_min1sig[i] << "\t" << WH_low_median[i] << "\t" << WH_low_plus1sig[i] << "\t" << WH_low_plus2sig[i] << endl;
	}
      
      if (WH_low_min2sig[i] < WH_low_YLowerLimit)
	WH_low_YLowerLimit = WH_low_min2sig[i];
      if (WH_low_plus2sig[i] > WH_low_YUpperLimit)
	WH_low_YUpperLimit = WH_low_plus2sig[i];
    }
  
  WH_gr_low_min2sig = new TGraph(lowMassPointsW, WH_low_m, WH_low_min2sig);
  WH_gr_low_min1sig = new TGraph(lowMassPointsW, WH_low_m, WH_low_min1sig);
  WH_gr_low_median = new TGraph(lowMassPointsW, WH_low_m, WH_low_median);
  WH_gr_low_plus1sig = new TGraph(lowMassPointsW, WH_low_m, WH_low_plus1sig);
  WH_gr_low_plus2sig = new TGraph(lowMassPointsW, WH_low_m, WH_low_plus2sig);

  WH_gr_low_min2sig->SetLineColor(kOrange);
  WH_gr_low_plus2sig->SetLineColor(kOrange);
  WH_gr_low_min2sig->SetLineWidth(4);
  WH_gr_low_plus2sig->SetLineWidth(4);
  WH_gr_low_min2sig->SetMarkerColor(kOrange);
  WH_gr_low_plus2sig->SetMarkerColor(kOrange);
  WH_gr_low_min1sig->SetLineColor(kGreen);
  WH_gr_low_plus1sig->SetLineColor(kGreen);
  WH_gr_low_min1sig->SetLineWidth(4);
  WH_gr_low_plus1sig->SetLineWidth(4);
  WH_gr_low_min1sig->SetMarkerColor(kGreen);
  WH_gr_low_plus1sig->SetMarkerColor(kGreen);
  WH_gr_low_median->SetLineColor(kBlack);
  WH_gr_low_median->SetLineWidth(4);
  WH_gr_low_median->SetMarkerColor(kBlack);

  WH_gr_low_min2sig->SetTitle("Limits for M_{T} < 50 GeV");
  WH_gr_low_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //WH_gr_low_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    WH_gr_low_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    WH_gr_low_min2sig->GetYaxis()->SetTitle("#sigma(WH) Br(H->aa->4#tau) (pb)");
  
  //WH_gr_low_min2sig->GetYaxis()->SetRangeUser(WH_low_min2sig[lowMassPointsW - 1]*0.1, WH_low_plus2sig[0]*1.1);
  WH_gr_low_min2sig->GetYaxis()->SetRangeUser(-10., WH_low_YUpperLimit*1.1);

  WH_gr_low_min2sig->Draw("ALP");
  WH_gr_low_min1sig->Draw("LPSAME");
  WH_gr_low_median->Draw("LPSAME");
  WH_gr_low_plus1sig->Draw("LPSAME");
  WH_gr_low_plus2sig->Draw("LPSAME");
  
  // plot high MT limits for WH
  TCanvas *cHigh_WH = new TCanvas("cHigh_WH", "Expected CLs limits for high MT bin, WH", 600, 600);
  cHigh_WH->cd();
  gPad->SetLogy();
  const int highMassPointsW = 6;
  double WH_high_m[highMassPointsW] = {5, 7, 9, 11, 13, 15};
  /*  double WH_high_min2sig[highMassPointsW] = {71.676300, 1.390400, 0.731000, 0.587900, 0.534300, 0.637100};
  double WH_high_min1sig[highMassPointsW] = {92.185000, 1.788300, 0.940100, 0.756100, 0.687100, 0.819400};
  double WH_high_median[highMassPointsW] = {125.250000, 2.429700, 1.277300, 1.027300, 0.933600, 1.113300};
  double WH_high_plus1sig[highMassPointsW] = {174.176700, 3.369100, 1.771200, 1.424600, 1.294600, 1.543700};
  double WH_high_plus2sig[highMassPointsW] = {239.574800, 4.609400, 2.423300, 1.949000, 1.771100, 2.112000};
  */

  //latest limits
  /*
  double WH_high_min2sig[highMassPointsW] = {85.171100, 1.656200, 0.869900, 0.700200, 0.634200, 0.756800};
  double WH_high_min1sig[highMassPointsW] = {107.465300, 2.082700, 1.097600, 0.883400, 0.800200, 0.954800};
  double WH_high_median[highMassPointsW] = {141.125000, 2.726600, 1.441400, 1.160200, 1.050800, 1.253900};
  double WH_high_plus1sig[highMassPointsW] = {191.190200, 3.693800, 1.941300, 1.562500, 1.415200, 1.688700};
  double WH_high_plus2sig[highMassPointsW] = {257.184200, 4.932900, 2.599400, 2.092200, 1.895000, 2.261300};
  */
  //with tau pT > 20 GeV
  double WH_high_min2sig[highMassPointsW] = {55.582600, 3.502000, 0.758500, 0.600900, 0.528900, 0.634600};
  double WH_high_min1sig[highMassPointsW] = {71.234300, 4.488200, 0.972100, 0.770100, 0.677800, 0.811900};
  double WH_high_median[highMassPointsW] = {96.468800, 6.078100, 1.316400, 1.043000, 0.918000, 1.097700};
  double WH_high_plus1sig[highMassPointsW] = {135.306100, 8.525100, 1.846400, 1.462900, 1.287500, 1.548300};
  double WH_high_plus2sig[highMassPointsW] = {189.015500, 11.831300, 2.56240, 2.043500, 1.786900, 2.142500};

  double WH_high_YLowerLimit = 999999999.;
  double WH_high_YUpperLimit = -999999999.;
  
  for (int i = 0; i < highMassPointsW; ++i)
    {
      if (BrOnly)
	{
	  /*WH_high_min2sig[i] *= (1./BrWlep);
	  WH_high_min1sig[i] *= (1./BrWlep);
	  WH_high_median[i] *= (1./BrWlep);
	  WH_high_plus1sig[i] *= (1./BrWlep);
	  WH_high_plus2sig[i] *= (1./BrWlep);*/
	  cout << "Limits on branching ratios for WH, high MT, mass point " << WH_high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << WH_high_min2sig[i] << "\t" << WH_high_min1sig[i] << "\t" << WH_high_median[i] << "\t" << WH_high_plus1sig[i] << "\t" << WH_high_plus2sig[i] << endl;
	}
      else
	{
	  WH_high_min2sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_high_min1sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_high_median[i] *= SMxsecWH/*/BrWlep*/;
	  WH_high_plus1sig[i] *= SMxsecWH/*/BrWlep*/;
	  WH_high_plus2sig[i] *= SMxsecWH/*/BrWlep*/;
	  cout << "Limits on xsec*Br for WH, high MT, mass point " << WH_high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << WH_high_min2sig[i] << "\t" << WH_high_min1sig[i] << "\t" << WH_high_median[i] << "\t" << WH_high_plus1sig[i] << "\t" << WH_high_plus2sig[i] << endl;
	}
      
      if (WH_high_min2sig[i] < WH_high_YLowerLimit)
	WH_high_YLowerLimit = WH_high_min2sig[i];
      if (WH_high_plus2sig[i] > WH_high_YUpperLimit)
	WH_high_YUpperLimit = WH_high_plus2sig[i];

    }

  WH_gr_high_min2sig = new TGraph(highMassPointsW, WH_high_m, WH_high_min2sig);
  WH_gr_high_min1sig = new TGraph(highMassPointsW, WH_high_m, WH_high_min1sig);
  WH_gr_high_median = new TGraph(highMassPointsW, WH_high_m, WH_high_median);
  WH_gr_high_plus1sig = new TGraph(highMassPointsW, WH_high_m, WH_high_plus1sig);
  WH_gr_high_plus2sig = new TGraph(highMassPointsW, WH_high_m, WH_high_plus2sig);

  WH_gr_high_min2sig->SetLineColor(kOrange);
  WH_gr_high_plus2sig->SetLineColor(kOrange);
  WH_gr_high_min2sig->SetLineWidth(4);
  WH_gr_high_plus2sig->SetLineWidth(4);
  WH_gr_high_min2sig->SetMarkerColor(kOrange);
  WH_gr_high_plus2sig->SetMarkerColor(kOrange);
  WH_gr_high_min1sig->SetLineColor(kGreen);
  WH_gr_high_plus1sig->SetLineWidth(4);
  WH_gr_high_min1sig->SetLineWidth(4);
  WH_gr_high_plus1sig->SetLineColor(kGreen);
  WH_gr_high_min1sig->SetMarkerColor(kGreen);
  WH_gr_high_plus1sig->SetMarkerColor(kGreen);
  WH_gr_high_median->SetLineColor(kBlack);
  WH_gr_high_median->SetLineWidth(4);
  WH_gr_high_median->SetMarkerColor(kBlack);

  WH_gr_high_min2sig->SetTitle("Limits for M_{T} > 50 GeV");
  WH_gr_high_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //WH_gr_high_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    WH_gr_high_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    WH_gr_high_min2sig->GetYaxis()->SetTitle("#sigma(WH) Br(H->aa->4#tau) (pb)");

  //WH_gr_high_min2sig->GetYaxis()->SetRangeUser(WH_high_min2sig[highMassPointsW - 1]*0.1, WH_high_plus2sig[0]*1.1);
  WH_gr_high_min2sig->GetYaxis()->SetRangeUser(-10., WH_high_YUpperLimit*1.1);

  WH_gr_high_min2sig->Draw("ALP");
  WH_gr_high_min1sig->Draw("LPSAME");
  WH_gr_high_median->Draw("LPSAME");
  WH_gr_high_plus1sig->Draw("LPSAME");
  WH_gr_high_plus2sig->Draw("LPSAME");

  /////////////////////////////////////////////////////////////////////////////////////////
  
  
  // plot low MT limits for ggH
  TCanvas *cLow_ggH = new TCanvas("cLow_ggH", "Expected CLs limits for low MT bin, ggH", 600, 600);
  cLow_ggH->cd();
  gPad->SetLogy();
  const int lowMassPointsG = 6;
  double ggH_low_m[lowMassPointsG] = {5,7,9, 11, 13, 15};
  /*  double ggH_low_min2sig[lowMassPointsG] = {17.901800,0.206500,0.096300,0.071200,0.082100,0.139000};
  double ggH_low_min1sig[lowMassPointsG] = {22.587700,0.260600,0.121100,0.088900,0.103000,0.173400};
  double ggH_low_median[lowMassPointsG] = {29.662500,0.342200,0.158600,0.117600,0.135500,0.228900};
  double ggH_low_plus1sig[lowMassPointsG] = {40.185500,0.460900,0.214900,0.158400,0.182600,0.308300};
  double ggH_low_plus2sig[lowMassPointsG] = {54.447300,0.621600,0.289000,0.212000,0.244400,0.415800};
  */

  //latest limits
  /*
  double ggH_low_min2sig[lowMassPointsG] = {17.111600, 0.197000, 0.091700, 0.067900, 0.078000, 0.131700};
  double ggH_low_min1sig[lowMassPointsG] = {21.557300, 0.249900, 0.116500, 0.085400, 0.099000, 0.167300};
  double ggH_low_median[lowMassPointsG] = {28.725000, 0.329700, 0.153900, 0.113700, 0.130900, 0.221100};
  double ggH_low_plus1sig[lowMassPointsG] = {39.373400, 0.449300, 0.209700, 0.154900, 0.178300, 0.301300};
  double ggH_low_plus2sig[lowMassPointsG] = {53.428600, 0.607000, 0.283400, 0.209300, 0.240900, 0.407100};
  */

  //with tau pT > 20
  double ggH_low_min2sig[lowMassPointsG] = {14.596400, 0.238900, 0.120600, 0.088200, 0.097200, 0.142700};
  double ggH_low_min1sig[lowMassPointsG] = {18.091000, 0.295200, 0.149500, 0.109300, 0.120100, 0.176300};
  double ggH_low_median[lowMassPointsG] = {23.725000, 0.385900, 0.196100, 0.143400, 0.157000, 0.230500};
  double ggH_low_plus1sig[lowMassPointsG] = {32.330800, 0.525900, 0.265700, 0.195400, 0.214000, 0.314100};
  double ggH_low_plus2sig[lowMassPointsG] = {44.305900, 0.715700, 0.362500, 0.265800, 0.291200, 0.427400};

  double ggH_low_YLowerLimit = 999999999.;
  double ggH_low_YUpperLimit = -999999999.;

  for (int i = 0; i < lowMassPointsG; ++i)
    {
      if (BrOnly)
	{
	  cout << "Limits on branching ratios for ggH, low MT, mass point" << ggH_low_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << ggH_low_min2sig[i] << "\t" << ggH_low_min1sig[i] << "\t" << ggH_low_median[i] << "\t" << ggH_low_plus1sig[i] << "\t" << ggH_low_plus2sig[i] << endl;    
	}
      else
	{
	  ggH_low_min2sig[i] *= SMxsecggH;
	  ggH_low_min1sig[i] *= SMxsecggH;
	  ggH_low_median[i] *= SMxsecggH;
	  ggH_low_plus1sig[i] *= SMxsecggH;
	  ggH_low_plus2sig[i] *= SMxsecggH;
	  cout << "Limits on xsec*Br for ggH, low MT, mass point " << ggH_low_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << ggH_low_min2sig[i] << "\t" << ggH_low_min1sig[i] << "\t" << ggH_low_median[i] << "\t" << ggH_low_plus1sig[i] << "\t" << ggH_low_plus2sig[i] << endl;
	}

      /*ggH_low_min2sig[i] *= SMxsecggH/SMxsecggH;
	ggH_low_min1sig[i] *= SMxsecggH/SMxsecggH;
	ggH_low_median[i] *= SMxsecggH/SMxsecggH;
	ggH_low_plus1sig[i] *= SMxsecggH/SMxsecggH;
	ggH_low_plus2sig[i] *= SMxsecggH/SMxsecggH;*/
      
      if (ggH_low_min2sig[i] < ggH_low_YLowerLimit)
	ggH_low_YLowerLimit = ggH_low_min2sig[i];
      if (ggH_low_plus2sig[i] > ggH_low_YUpperLimit)
	ggH_low_YUpperLimit = ggH_low_plus2sig[i];
    }

  ggH_gr_low_min2sig = new TGraph(lowMassPointsG, ggH_low_m, ggH_low_min2sig);
  ggH_gr_low_min1sig = new TGraph(lowMassPointsG, ggH_low_m, ggH_low_min1sig);
  ggH_gr_low_median = new TGraph(lowMassPointsG, ggH_low_m, ggH_low_median);
  ggH_gr_low_plus1sig = new TGraph(lowMassPointsG, ggH_low_m, ggH_low_plus1sig);
  ggH_gr_low_plus2sig = new TGraph(lowMassPointsG, ggH_low_m, ggH_low_plus2sig);

  ggH_gr_low_min2sig->SetLineColor(kOrange);
  ggH_gr_low_plus2sig->SetLineColor(kOrange);
  ggH_gr_low_min2sig->SetLineWidth(4);
  ggH_gr_low_plus2sig->SetLineWidth(4);
  ggH_gr_low_min2sig->SetMarkerColor(kOrange);
  ggH_gr_low_plus2sig->SetMarkerColor(kOrange);
  ggH_gr_low_min1sig->SetLineColor(kGreen);
  ggH_gr_low_plus1sig->SetLineColor(kGreen);
  ggH_gr_low_min1sig->SetLineWidth(4);
  ggH_gr_low_plus1sig->SetLineWidth(4);
  ggH_gr_low_min1sig->SetMarkerColor(kGreen);
  ggH_gr_low_plus1sig->SetMarkerColor(kGreen);
  ggH_gr_low_median->SetLineColor(kBlack);
  ggH_gr_low_median->SetLineWidth(4);
  ggH_gr_low_median->SetMarkerColor(kBlack);

  ggH_gr_low_min2sig->SetTitle("Limits for M_{T} < 50 GeV");
  ggH_gr_low_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //ggH_gr_low_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    ggH_gr_low_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    ggH_gr_low_min2sig->GetYaxis()->SetTitle("#sigma(ggH) Br(H->aa->4#tau) (pb)");

  //ggH_gr_low_min2sig->GetYaxis()->SetRangeUser(ggH_low_min2sig[lowMassPointsG - 1]*0.1, ggH_low_plus2sig[0]*1.1);
  ggH_gr_low_min2sig->GetYaxis()->SetRangeUser(-10., ggH_low_YUpperLimit*1.1);

  ggH_gr_low_min2sig->Draw("ALP");
  ggH_gr_low_min1sig->Draw("LPSAME");
  ggH_gr_low_median->Draw("LPSAME");
  ggH_gr_low_plus1sig->Draw("LPSAME");
  ggH_gr_low_plus2sig->Draw("LPSAME");
  
  // plot high MT limits for ggH
  TCanvas *cHigh_ggH = new TCanvas("cHigh_ggH", "Expected CLs limits for high MT bin, ggH", 600, 600);
  cHigh_ggH->cd();
  gPad->SetLogy();
  const int highMassPointsG = 5;
  double ggH_high_m[highMassPointsG] = {7, 9, 11, 13, 15};
  /*double ggH_high_min2sig[highMassPointsG] = {2.286000,0.460500,0.336400,0.242500,0.368800};
  double ggH_high_min1sig[highMassPointsG] = {2.972000,0.592300,0.436600,0.311900,0.474400};
  double ggH_high_median[highMassPointsG] = {4.078100,0.804700,0.587900,0.423800,0.644500};
  double ggH_high_plus1sig[highMassPointsG] = {5.817500,1.119000,0.819900,0.587700,0.893700};
  double ggH_high_plus2sig[highMassPointsG] = {8.260600,1.539200,1.118500,0.804100,1.222800};
  */

  //latest limits
  /*
  double ggH_high_min2sig[highMassPointsG] = {2.709800, 0.545700, 0.400900, 0.288800, 0.440100};
  double ggH_high_min1sig[highMassPointsG] = {3.437000, 0.690900, 0.505000, 0.364400, 0.553500};
  double ggH_high_median[highMassPointsG] = {4.609400, 0.910200, 0.662100, 0.478500, 0.724600};
  double ggH_high_plus1sig[highMassPointsG] = {6.428300, 1.225800, 0.897000, 0.644500, 0.981700};
  double ggH_high_plus2sig[highMassPointsG] = {8.918200, 1.653400, 1.206600, 0.863000, 1.311000};
  */

  //with tau pT > 20
  double ggH_high_min2sig[highMassPointsG] = {2.548900, 0.654900, 0.508700, 0.311700, 0.449000};
  double ggH_high_min1sig[highMassPointsG] = {3.301800, 0.839400, 0.651900, 0.399500, 0.575400};
  double ggH_high_median[highMassPointsG] = {4.515600, 1.136700, 0.882800, 0.541000, 0.779300};
  double ggH_high_plus1sig[highMassPointsG] = {6.513600, 1.598900, 1.238200, 0.758800, 1.093000};
  double ggH_high_plus2sig[highMassPointsG] = {9.361200, 2.230200, 1.729700, 1.053100, 1.516900};

  double ggH_high_YLowerLimit = 999999999.;
  double ggH_high_YUpperLimit = -999999999.;
  
  for (int i = 0; i < highMassPointsG; ++i)
    {
      if (BrOnly)
	{
	  cout << "Limits on branching ratios for ggH, high MT, mass point " << ggH_high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << ggH_high_min2sig[i] << "\t" << ggH_high_min1sig[i] << "\t" << ggH_high_median[i] << "\t" << ggH_high_plus1sig[i] << "\t" << ggH_high_plus2sig[i] << endl;
	}
      else
	{
	  ggH_high_min2sig[i] *= SMxsecggH;
	  ggH_high_min1sig[i] *= SMxsecggH;
	  ggH_high_median[i] *= SMxsecggH;
	  ggH_high_plus1sig[i] *= SMxsecggH;
	  ggH_high_plus2sig[i] *= SMxsecggH;
	  cout << "Limits on xsec*Br for ggH, high MT, mass point " << ggH_high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << ggH_high_min2sig[i] << "\t" << ggH_high_min1sig[i] << "\t" << ggH_high_median[i] << "\t" << ggH_high_plus1sig[i] << "\t" << ggH_high_plus2sig[i] << endl;	  
	}
      /*ggH_high_min2sig[i] *= SMxsecggH/SMxsecggH;
	ggH_high_min1sig[i] *= SMxsecggH/SMxsecggH;
	ggH_high_median[i] *= SMxsecggH/SMxsecggH;
	ggH_high_plus1sig[i] *= SMxsecggH/SMxsecggH;
	ggH_high_plus2sig[i] *= SMxsecggH/SMxsecggH;*/
      
      if (ggH_high_min2sig[i] < ggH_high_YLowerLimit)
	ggH_high_YLowerLimit = ggH_high_min2sig[i];
      if (ggH_high_plus2sig[i] > ggH_high_YUpperLimit)
	ggH_high_YUpperLimit = ggH_high_plus2sig[i];
    }
  
  ggH_gr_high_min2sig = new TGraph(highMassPointsG, ggH_high_m, ggH_high_min2sig);
  ggH_gr_high_min1sig = new TGraph(highMassPointsG, ggH_high_m, ggH_high_min1sig);
  ggH_gr_high_median = new TGraph(highMassPointsG, ggH_high_m, ggH_high_median);
  ggH_gr_high_plus1sig = new TGraph(highMassPointsG, ggH_high_m, ggH_high_plus1sig);
  ggH_gr_high_plus2sig = new TGraph(highMassPointsG, ggH_high_m, ggH_high_plus2sig);
  
  ggH_gr_high_min2sig->SetLineColor(kOrange);
  ggH_gr_high_plus2sig->SetLineColor(kOrange);
  ggH_gr_high_min2sig->SetLineWidth(4);
  ggH_gr_high_plus2sig->SetLineWidth(4);
  ggH_gr_high_min2sig->SetMarkerColor(kOrange);
  ggH_gr_high_plus2sig->SetMarkerColor(kOrange);
  ggH_gr_high_min1sig->SetLineColor(kGreen);
  ggH_gr_high_plus1sig->SetLineColor(kGreen);
  ggH_gr_high_min1sig->SetLineWidth(4);
  ggH_gr_high_plus1sig->SetLineWidth(4);
  ggH_gr_high_min1sig->SetMarkerColor(kGreen);
  ggH_gr_high_plus1sig->SetMarkerColor(kGreen);
  ggH_gr_high_median->SetLineColor(kBlack);
  ggH_gr_high_median->SetLineWidth(4);
  ggH_gr_high_median->SetMarkerColor(kBlack);

  ggH_gr_high_min2sig->SetTitle("Limits for M_{T} > 50 GeV");
  ggH_gr_high_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //ggH_gr_high_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    ggH_gr_high_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    ggH_gr_high_min2sig->GetYaxis()->SetTitle("#sigma(ggH) Br(H->aa->4#tau) (pb)");

  //ggH_gr_high_min2sig->GetYaxis()->SetRangeUser(ggH_high_min2sig[highMassPointsG - 1]*0.1, ggH_high_plus2sig[0]*1.1);
  ggH_gr_high_min2sig->GetYaxis()->SetRangeUser(-10., ggH_high_YUpperLimit*1.1);

  ggH_gr_high_min2sig->Draw("ALP");
  ggH_gr_high_min1sig->Draw("LPSAME");
  ggH_gr_high_median->Draw("LPSAME");
  ggH_gr_high_plus1sig->Draw("LPSAME");
  ggH_gr_high_plus2sig->Draw("LPSAME");

} // code end
