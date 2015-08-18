void fourSignalBrazilPlot(bool BrOnly)
{ // code beginning

  //double xsecWH[6] = {0.085, 0.083, 0.09, 0.00138, 0.00087, 0.00075}; //0.09 pb calculated by Pythia for WH signal
  //double xsecggH[6] = {7.135, 6.967, 7.555, 0.116, 0.0730, 0.0630};//7.555 pb = 0.09*sig_SM[ggH]/sig_SM[WH] at mH = 125 GeV
  double SMxsecggH = 19.27; //SM xsec for ggH production @ 8 TeV is 19.27 pb
  double SMxsecWH = 0.7046; //SM xsec for WH production @ 8 TeV is 0.7046 pb
  double SMxsecVBF = 1.578;
  double SMxsecZH = 0.4153;
  double BrWlep = 3*0.1086; //branching ratio for leptonic W decay
  double BrZmu = 3*0.034;

  // plot low MT limits for WH
  TCanvas *cLow_WH = new TCanvas("cLow_WH", "Expected CLs limits for low MT bin", 600, 600);
  cLow_WH->cd();
  gPad->SetLogy();
  const int lowMassPoints = 6;
  double low_m[lowMassPoints] = {5, 7, 9, 11, 13, 15};

  //latest limits  
  double low_min2sig[lowMassPoints] = {17.5341, 0.2076, 0.0995, 0.0753, 0.0856, 0.1445};
  double low_min1sig[lowMassPoints] = {22.3158, 0.2651, 0.1275, 0.0969, 0.1101, 0.1852};
  double low_median[lowMassPoints] = {30.025, 0.3578, 0.1727, 0.1316, 0.1496, 0.2508};
  double low_plus1sig[lowMassPoints] = {41.8734, 0.5019, 0.2422, 0.1846, 0.2098, 0.3517};
  double low_plus2sig[lowMassPoints] = {57.8990, 0.6919, 0.3361, 0.2562, 0.2912, 0.4882};
  

  double low_YLowerLimit = 999999999.;
  double low_YUpperLimit = -999999999.;
  
  for (int i = 0; i < lowMassPoints; ++i)
    {

      if (BrOnly)
	{
	  cout << "Limits on branching ratios for low MT, mass point " << low_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << low_min2sig[i] << "\t" << low_min1sig[i] << "\t" << low_median[i] << "\t" << low_plus1sig[i] << "\t" << low_plus2sig[i] << endl;
	}
      else
	{
	  low_min2sig[i] *= (SMxsecggH+SMxsecVBF);
	  low_min1sig[i] *= (SMxsecggH+SMxsecVBF);
	  low_median[i] *= (SMxsecggH+SMxsecVBF);
	  low_plus1sig[i] *= (SMxsecggH+SMxsecVBF);
	  low_plus2sig[i] *= (SMxsecggH+SMxsecVBF);
	  cout << "Limits on xsec*Br for WH, low MT, mass point " << low_m[i]  << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << low_min2sig[i] << "\t" << low_min1sig[i] << "\t" << low_median[i] << "\t" << low_plus1sig[i] << "\t" << low_plus2sig[i] << endl;
	}
      
      if (low_min2sig[i] < low_YLowerLimit)
	low_YLowerLimit = low_min2sig[i];
      if (low_plus2sig[i] > low_YUpperLimit)
	low_YUpperLimit = low_plus2sig[i];
    }
  
  gr_low_min2sig = new TGraph(lowMassPoints, low_m, low_min2sig);
  gr_low_min1sig = new TGraph(lowMassPoints, low_m, low_min1sig);
  gr_low_median = new TGraph(lowMassPoints, low_m, low_median);
  gr_low_plus1sig = new TGraph(lowMassPoints, low_m, low_plus1sig);
  gr_low_plus2sig = new TGraph(lowMassPoints, low_m, low_plus2sig);

  gr_low_min2sig->SetLineColor(kOrange);
  gr_low_plus2sig->SetLineColor(kOrange);
  gr_low_min2sig->SetLineWidth(4);
  gr_low_plus2sig->SetLineWidth(4);
  gr_low_min2sig->SetMarkerColor(kOrange);
  gr_low_plus2sig->SetMarkerColor(kOrange);
  gr_low_min1sig->SetLineColor(kGreen);
  gr_low_plus1sig->SetLineColor(kGreen);
  gr_low_min1sig->SetLineWidth(4);
  gr_low_plus1sig->SetLineWidth(4);
  gr_low_min1sig->SetMarkerColor(kGreen);
  gr_low_plus1sig->SetMarkerColor(kGreen);
  gr_low_median->SetLineColor(kBlack);
  gr_low_median->SetLineWidth(4);
  gr_low_median->SetMarkerColor(kBlack);

  gr_low_min2sig->SetTitle("Limits for M_{T} < 50 GeV");
  gr_low_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //gr_low_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    gr_low_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    gr_low_min2sig->GetYaxis()->SetTitle("#sigma(ggH+VBF) Br(H->aa->4#tau) (pb)");
  
  //gr_low_min2sig->GetYaxis()->SetRangeUser(low_min2sig[lowMassPoints - 1]*0.1, low_plus2sig[0]*1.1);
  gr_low_min2sig->GetYaxis()->SetRangeUser(-10., low_YUpperLimit*1.1);

  gr_low_min2sig->Draw("ALP");
  gr_low_min1sig->Draw("LPSAME");
  gr_low_median->Draw("LPSAME");
  gr_low_plus1sig->Draw("LPSAME");
  gr_low_plus2sig->Draw("LPSAME");
  
  // plot high MT limits for WH
  TCanvas *cHigh_WH = new TCanvas("cHigh_WH", "Expected CLs limits for high MT bin, WH", 600, 600);
  cHigh_WH->cd();
  gPad->SetLogy();
  const int highMassPoints = 6;
  double high_m[highMassPoints] = {5, 7, 9, 11, 13, 15};

  //latest limits

  double high_min2sig[highMassPoints] = {79.255, 0.9743, 0.3320, 0.2555, 0.2017, 0.2776};
  double high_min1sig[highMassPoints] = {100.5231, 1.2444, 0.4240, 0.3274, 0.2595, 0.3545};
  double high_median[highMassPoints] = {134.8125, 1.6797, 0.5723, 0.4434, 0.3525, 0.4785};
  double high_plus1sig[highMassPoints] = {185.8625, 2.3291, 0.7981, 0.6183, 0.4945, 0.6712};
  double high_plus2sig[highMassPoints] = {254.1377, 3.2083, 1.1035, 0.8550, 0.6817, 0.9253};


  double high_YLowerLimit = 999999999.;
  double high_YUpperLimit = -999999999.;
  
  for (int i = 0; i < highMassPoints; ++i)
    {
      if (BrOnly)
	{
	  cout << "Limits on branching ratios for high MT, mass point " << high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << high_min2sig[i] << "\t" << high_min1sig[i] << "\t" << high_median[i] << "\t" << high_plus1sig[i] << "\t" << high_plus2sig[i] << endl;
	}
      else
	{
	  high_min2sig[i] *= (SMxsecggH+SMxsecWH);
	  high_min1sig[i] *= (SMxsecggH+SMxsecWH);
	  high_median[i] *= (SMxsecggH+SMxsecWH);
	  high_plus1sig[i] *= (SMxsecggH+SMxsecWH);
	  high_plus2sig[i] *= (SMxsecggH+SMxsecWH);
	  cout << "Limits on xsec*Br for ggH+WH, high MT, mass point " << high_m[i] << endl;
	  cout << "-2sig\t-1sig\tmed\t+1sig\t+2sig" << endl;
	  cout << high_min2sig[i] << "\t" << high_min1sig[i] << "\t" << high_median[i] << "\t" << high_plus1sig[i] << "\t" << high_plus2sig[i] << endl;
	}
      
      if (high_min2sig[i] < high_YLowerLimit)
	high_YLowerLimit = high_min2sig[i];
      if (high_plus2sig[i] > high_YUpperLimit)
	high_YUpperLimit = high_plus2sig[i];

    }

  gr_high_min2sig = new TGraph(highMassPoints, high_m, high_min2sig);
  gr_high_min1sig = new TGraph(highMassPoints, high_m, high_min1sig);
  gr_high_median = new TGraph(highMassPoints, high_m, high_median);
  gr_high_plus1sig = new TGraph(highMassPoints, high_m, high_plus1sig);
  gr_high_plus2sig = new TGraph(highMassPoints, high_m, high_plus2sig);

  gr_high_min2sig->SetLineColor(kOrange);
  gr_high_plus2sig->SetLineColor(kOrange);
  gr_high_min2sig->SetLineWidth(4);
  gr_high_plus2sig->SetLineWidth(4);
  gr_high_min2sig->SetMarkerColor(kOrange);
  gr_high_plus2sig->SetMarkerColor(kOrange);
  gr_high_min1sig->SetLineColor(kGreen);
  gr_high_plus1sig->SetLineWidth(4);
  gr_high_min1sig->SetLineWidth(4);
  gr_high_plus1sig->SetLineColor(kGreen);
  gr_high_min1sig->SetMarkerColor(kGreen);
  gr_high_plus1sig->SetMarkerColor(kGreen);
  gr_high_median->SetLineColor(kBlack);
  gr_high_median->SetLineWidth(4);
  gr_high_median->SetMarkerColor(kBlack);

  gr_high_min2sig->SetTitle("Limits for M_{T} > 50 GeV");
  gr_high_min2sig->GetXaxis()->SetTitle("m_{a1} (GeV)");
  //gr_high_min2sig->GetYaxis()->SetTitle("Expected limit on signal strength");
  if (BrOnly)
    gr_high_min2sig->GetYaxis()->SetTitle("Br(H->aa->4#tau)");
  else
    gr_high_min2sig->GetYaxis()->SetTitle("#sigma(WH) Br(H->aa->4#tau) (pb)");

  //gr_high_min2sig->GetYaxis()->SetRangeUser(high_min2sig[highMassPoints - 1]*0.1, high_plus2sig[0]*1.1);
  gr_high_min2sig->GetYaxis()->SetRangeUser(-10., high_YUpperLimit*1.1);

  gr_high_min2sig->Draw("ALP");
  gr_high_min1sig->Draw("LPSAME");
  gr_high_median->Draw("LPSAME");
  gr_high_plus1sig->Draw("LPSAME");
  gr_high_plus2sig->Draw("LPSAME");


} // code end
