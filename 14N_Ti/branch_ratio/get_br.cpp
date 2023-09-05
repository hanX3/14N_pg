
void get_br()
{
  //
  // {7556, 6859, 6792, 6172, 5240, 5181}
  double area[6] = {215.017, 0., 3083.73, 8366.74, 0., 2902.79};

  ifstream fi1;
  fi1.open("../../sim/14N_pg_JUNA_eff/analysis/dis_140mm/y1y2.txt");
  if(!fi1){
    cout << "can not open y1y2.txt" << endl;
    return;
  }
  
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
  fi2.open("../../sim/14N_pg_JUNA_eff/analysis/dis_140mm/eff.txt");
  if(!fi2){
    cout << "can not open eff.txt" << endl;
    return;
  }

  double eff[6];
  i = 0;
  while(1){
    fi2 >> a >> b;
    if(!fi2.good()) break;

    eff[i] = b;
    i++;
  }
  fi2.close();

  for(int i=0;i<6;i++){
    cout << e[i] << " " << y1[i] << " " << y2[i] << " " << eff[i] << " " << area[i] << endl;
  }

  //cali
  double area_cor[6];
  for(int i=0;i<6;i++){
    if(y1[i]==0 || y2[i]==0 || area[i]==0){
      area_cor[i] = 0;
      continue;
    }
    area_cor[i] = area[i]*y1[i];
    area_cor[i] /= y2[i];
    
    area_cor[i] /= eff[i];
    cout << e[i] << " " << area_cor[i] << endl;
  }

  double sum = 0;
  for(int i=0;i<6;i++) sum += area_cor[i];

  double br[6];
  double br_err[6];
  for(int i=0;i<6;i++){
    br[i] = 100.*area_cor[i]/sum;
    br_err[i] = br[i]/sqrt(area[i]);
    cout << e[i] << "keV br " << br[i] << "%" << " error " << br_err[i] << endl;
  } 
}
