{
//gROOT->LoadMacro("draw.C");
/*

draw("h1_top", "H_{1} / H_{0} (Top Frame)", "bDisc > -1", 50, 0, 1);
draw("h2_top", "H_{2} / H_{0} (Top Frame)", "bDisc > -1", 50, 0, 1);
draw("h3_top", "H_{3} / H_{0} (Top Frame)", "bDisc > -1", 50, 0, 1);
draw("h4_top", "H_{4} / H_{0} (Top Frame)", "bDisc > -1", 50, 0, 1);
draw("h1_W", "H_{1} / H_{0} (W Frame)", "bDisc > -1", 50, 0, 1);
draw("h2_W", "H_{2} / H_{0} (W Frame)", "bDisc > -1",50, 0, 1);
draw("h3_W", "H_{3} / H_{0} (W Frame)", "bDisc > -1", 50, 0, 1);
draw("h4_W", "H_{4} / H_{0} (W Frame)", "bDisc > -1",50, 0, 1);
draw("h1_Z", "H_{1} / H_{0} (Z Frame)", "bDisc > -1",50, 0, 1);
draw("h2_Z", "H_{2} / H_{0} (Z Frame)", "bDisc > -1",50, 0, 1);
draw("h3_Z", "H_{3} / H_{0} (Z Frame)", "bDisc > -1",50, 0, 1);
draw("h4_Z", "H_{4} / H_{0} (Z Frame)", "bDisc > -1",50, 0, 1);
draw("h1_H", "H_{1} / H_{0} (H Frame)", "bDisc > -1",50, 0, 1);
draw("h2_H", "H_{2} / H_{0} (H Frame)", "bDisc > -1",50, 0, 1);
draw("h3_H", "H_{3} / H_{0} (H Frame)", "bDisc > -1",50, 0, 1);
draw("h4_H", "H_{4} / H_{0} (H Frame)", "bDisc > -1",50, 0, 1);




draw("isotropy_top", "Isotropy (Top Frame)", "bDisc > -1",50, 0, 1);
draw("aplanarity_top", "Aplanarity (Top Frame)", "bDisc > -1",50, 0, 0.1);
draw("sphericity_top", "Sphericity (Top Frame)", "bDisc > -1",50, 0, 1);
draw("thrust_top", "Jet Thrust (Top Frame)", "bDisc > -1",50, 0, 1);
draw("isotropy_W", "Isotropy (W Frame)", "bDisc > -1",50, 0, 1);
draw("aplanarity_W", "Aplanarity (W Frame)", "bDisc > -1",50, 0, 0.1);
draw("sphericity_W", "Sphericity (W Frame)", "bDisc > -1",50, 0, 1);
draw("thrust_W", "Jet Thrust (W Frame)", "bDisc > -1",50, 0, 1);
draw("isotropy_Z", "Isotropy (Z Frame)", "bDisc > -1",50, 0, 1);
draw("aplanarity_Z", "Aplanarity (Z Frame)", "bDisc > -1",50, 0, 0.1);
draw("sphericity_Z", "Sphericity (Z Frame)", "bDisc > -1",50, 0, 1);
draw("thrust_Z", "Jet Thrust (Z Frame)", "bDisc > -1",50, 0, 1);
draw("isotropy_H", "Isotropy (H Frame)", "bDisc > -1",50, 0, 1);
draw("aplanarity_H", "Aplanarity (H Frame)", "bDisc > -1",50, 0, 0.1);
draw("sphericity_H", "Sphericity (H Frame)", "bDisc > -1",50, 0, 1);
draw("thrust_H", "Jet Thrust (H Frame)", "bDisc > -1",50, 0, 1);




draw("et", "Jet p_{T} (GeV)", "bDisc > -1",100, 500, 3000);
draw("eta", "Jet #eta", "bDisc > -1",100, -3, 3);
draw("SDmass", "Jet Soft Drop Mass (GeV)", "bDisc > -1",50, 0, 300);
draw("tau32", "Jet #tau_{32}", "bDisc > -1", 100, 0, 1);
draw("tau21", "Jet #tau_{21}", "bDisc > -1", 100, 0, 1);


draw("PzOverP_Z", "A_{L} (Z Frame)", "bDisc > -1 && abs(PzOverP_Z) > 0.0001",50, -1.1, 1.1);
draw("PzOverP_W", "A_{L} (W Frame)", "bDisc > -1 && abs(PzOverP_W) > 0.0001",50, -1.1, 1.1);
draw("PzOverP_H", "A_{L} (H Frame)", "bDisc > -1 && abs(PzOverP_H) > 0.0001",50, -1.1, 1.1);
draw("PzOverP_top", "A_{L} (Top Frame)", "bDisc > -1 && abs(PzOverP_top) > 0.0001",50, -1.1, 1.1);
*/


draw("NNoutX", "NN Output Node 1 Value", "bDisc > -1", 100, -0.2, 1.2);
draw("NNoutY", "NN Output Node 2 Value", "bDisc > -1",100, -0.2, 1.2);
draw("NNout3", "NN Output Node 3 Value", "bDisc > -1",100, -0.2, 1.2);
draw("NNout4", "NN Output Node 4 Value", "bDisc > -1",100, -0.2, 1.2);
draw("NNout5", "NN Output Node 5 Value", "bDisc > -1",100, -0.2, 1.2);



draw("minDist", "Classifier", "bDisc > -1", 6, 0, 6);

draw("distTo0", "Distance to Light Jet Output Target", "bDisc > -1", 100, 0, 2);
draw("distTo1", "Distance to Top Jet Output Target", "bDisc > -1", 100, 0, 2);
draw("distTo2", "Distance to H Jet Output Target", "bDisc > -1",100, 0, 2);
draw("distTo3", "Distance to Z Jet Output Target", "bDisc > -1",100, 0, 2);
draw("distTo4", "Distance to W Jet Output Target", "bDisc > -1",100, 0, 2);


}
