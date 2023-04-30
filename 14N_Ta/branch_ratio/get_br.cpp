
void get_br()
{
  double beam_on[5] = {1498.9, 9881.9, 24053.9, 0, 8004.1};
  
  double sum = 0;
  for(int i=0;i<5;i++) sum += beam_on[i];

  cout << "7556keV level branch ratio " << beam_on[0]/sum*100. << "%\n"; 
  cout << "6792keV level branch ratio " << beam_on[1]/sum*100. << "%\n"; 
  cout << "6172keV level branch ratio " << beam_on[2]/sum*100. << "%\n"; 
  cout << "5241keV level branch ratio " << beam_on[3]/sum*100. << "%\n"; 
  cout << "5181keV level branch ratio " << beam_on[4]/sum*100. << "%\n"; 
}
