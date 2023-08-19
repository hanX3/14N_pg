{
  const Int_t N = 6;
  Int_t energy[N] = {7556, 6859, 6792, 6172, 5240, 5180};
  double sigma = 2.0;

  TString counts1_str = "50M";
  TString counts2_str = "100M";

  TString pro_line1, pro_line2;
  ofstream fo;
  fo.open("temp.cpp");

  fo << "{" << endl;
  fo << "  gROOT->ProcessLine(\".L tr2hist.cpp\");" << endl;

  for(int i=0;i<N;i++){
    pro_line1 = TString::Format("\"tr2hist(\\\"%s\\\", %d, %f)\"", counts1_str.Data(), energy[i], sigma);
    pro_line2 = TString::Format("\"tr2hist(\\\"%s\\\", %d, %f)\"", counts2_str.Data(), energy[i], sigma);
    fo << "  gROOT->ProcessLine(" << pro_line1 << ");" << endl;
    fo << "  gROOT->ProcessLine(" << pro_line2 << ");" << endl;

    fo << endl;
  }

  fo << "  gROOT->ProcessLine(\".q\");" << endl;
  fo << "}" << endl;

  fo.close();

  //
  gROOT->ProcessLine(".x temp.cpp");
  gROOT->ProcessLine(".q");
}