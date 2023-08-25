// 

void batch()
{
  TString pro_line;
  ofstream fo;
  fo.open("temp.cpp");

  fo << "{" << endl;
  fo << "  gROOT->ProcessLine(\".L tr2hist.cpp\");" << endl;

  for(int dis=20; dis<=300; dis+=20){
    pro_line = TString::Format("\".! mkdir dis_%dmm\"", dis);
    fo << "  gROOT->ProcessLine(" << pro_line << ");" << endl;

    pro_line = TString::Format("\".! mkdir dis_%dmm/hist\"", dis);
    fo << "  gROOT->ProcessLine(" << pro_line << ");" << endl;

    for(int energy=1000;energy<=12500;energy+=500){
      pro_line = TString::Format("\"tr2hist(\\\"../b_%dmm/data/dis_%dmm_gamma_%dkeV_10000k.root\\\", %d, %f)\"", dis, dis, energy, energy, 2.0);
      fo << "  gROOT->ProcessLine(" << pro_line << ");" << endl;
    }


    pro_line = TString::Format("\".! mv *.root dis_%dmm/hist/\"", dis);
    fo << "  gROOT->ProcessLine(" << pro_line << ");" << endl;
    
    fo << endl;
    fo << endl;
  }
    
  fo << "  gROOT->ProcessLine(\".q\");" << endl;
  fo << "}" << endl;

  fo.close();

  //
  gROOT->ProcessLine(".x temp.cpp");
  gROOT->ProcessLine(".q");
}