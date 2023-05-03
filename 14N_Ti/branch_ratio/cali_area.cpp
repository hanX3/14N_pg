
void cali_area()
{
  double area[5] = {345.43, 5419.2, 13916, 0, 4356.86};
  double eff[5] = {0.00125599, 0.00133111, 0.0014056, 0.00154928, 0.00156023};

  double area_cali[5];
  for(int i=0;i<5;i++){ 
    area_cali[i] = area[i]/eff[i];
    cout << area_cali[i] << ",  ";
  }

  cout << endl;
}
