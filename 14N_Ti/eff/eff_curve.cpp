
void eff_curve()
{
  TF1 *tf = new TF1("tf", "1/TMath::Power(([0]+[1]+[2]*x),2.)*TMath::Exp([3]+[4]*TMath::Log(x))", 500, 10000);
  tf->SetParameter(0, 18);
  tf->SetParameter(1, 8.75);
  tf->SetParameter(2, -3.21*1.e-4);
  tf->SetParameter(3, 6.22);
  tf->SetParameter(4, -0.77);

  auto c1 = new TCanvas();
  c1->cd();
  tf->Draw();

}
