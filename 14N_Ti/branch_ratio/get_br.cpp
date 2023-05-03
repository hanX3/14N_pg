
void get_br()
{
  // double beam_on[5] = {222.99, 2895.44, 7286.07, 0, 2104.57}; // g4
  double beam_on[5] = {275026,  4.07119e+06,  9.9004e+06,  0,  2.79245e+06}; // eff cali
  
  double sum = 0;
  for(int i=0;i<5;i++) sum += beam_on[i];

  cout << "7556keV level branch ratio " << beam_on[0]/sum*100. << "%\n"; 
  cout << "6792keV level branch ratio " << beam_on[1]/sum*100. << "%\n"; 
  cout << "6172keV level branch ratio " << beam_on[2]/sum*100. << "%\n"; 
  cout << "5241keV level branch ratio " << beam_on[3]/sum*100. << "%\n"; 
  cout << "5181keV level branch ratio " << beam_on[4]/sum*100. << "%\n"; 
}
