{
  gROOT->ProcessLine(".L raw2root.cpp");

  gROOT->ProcessLine("raw2root(\"target3\", \"270\")");
  gROOT->ProcessLine("raw2root(\"target3\", \"280\")");
}
