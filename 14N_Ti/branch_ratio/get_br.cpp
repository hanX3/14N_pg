
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

void get_br_g4()
{
  ifstream fi1;
  fi1.open("../../sim/14N_pg_JUNA_eff/analysis/y1y2.txt");
  
  double e[6];
  double y1[6];
  double y2[6];

  double a, b, c;
  int i = 0;
  while(1){
    fi1 >> a >> b >> c;
    if(!fi1.good()) break;

    e[i] = a;
    y1[i] = b;
    y2[i] = c;
    i++;
  }
  fi1.close();
  
  //
  ifstream fi2;
  fi2.open("../../sim/14N_pg_JUNA_eff/analysis/eff.txt");
  double eff[6];
  i = 0;
  while(1){
    fi2 >> a >> b;
    if(!fi2.good()) break;

    eff[i] = b;
    i++;
  }
  fi2.close();

  //
  ifstream fi3;
  fi3.open("area.txt");
  double area[6];
  i = 0;
  while(1){
    fi3 >> a >> b;
    if(!fi3.good()) break;

    area[i] = b;
    i++;
  }
  fi3.close();

  for(int i=0;i<6;i++){
    cout << e[i] << " " << y1[i] << " " << y2[i] << " " << eff[i] << " " << area[i] << endl;
  }

  //cali
  for(int i=0;i<6;i++){
    area[i] *= y1[i];
    area[i] /= y2[i];
    
    area[i] /= eff[i];
  }

  double sum = 0;
  for(int i=0;i<6;i++) sum += area[i];

  for(int i=0;i<6;i++){
    cout << e[i] << "keV br " << 100.*area[i]/sum << "%" << endl;
  }
}
