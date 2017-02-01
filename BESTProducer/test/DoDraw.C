{
//gROOT->LoadMacro("draw.C");

/*
draw("h1_top", "H_{1} (Top Frame)", 50, 0, 1);
draw("h2_top", "H_{2} (Top Frame)", 50, 0, 1);
draw("h3_top", "H_{3} (Top Frame)", 50, 0, 1);
draw("h4_top", "H_{4} (Top Frame)", 50, 0, 1);
draw("h1_W", "H_{1} (W Frame)", 50, 0, 1);
draw("h2_W", "H_{2} (W Frame)", 50, 0, 1);
draw("h3_W", "H_{3} (W Frame)", 50, 0, 1);
draw("h4_W", "H_{4} (W Frame)", 50, 0, 1);
draw("h1_Z", "H_{1} (Z Frame)", 50, 0, 1);
draw("h2_Z", "H_{2} (Z Frame)", 50, 0, 1);
draw("h3_Z", "H_{3} (Z Frame)", 50, 0, 1);
draw("h4_Z", "H_{4} (Z Frame)", 50, 0, 1);
draw("h1_H", "H_{1} (H Frame)", 50, 0, 1);
draw("h2_H", "H_{2} (H Frame)", 50, 0, 1);
draw("h3_H", "H_{3} (H Frame)", 50, 0, 1);
draw("h4_H", "H_{4} (H Frame)", 50, 0, 1);




draw("isotropy_top", "Isotropy (Top Frame)", 50, 0, 1);
draw("aplanarity_top", "Aplanarity (Top Frame)", 50, 0, 1);
draw("sphericity_top", "Sphericity (Top Frame)", 50, 0, 1);
draw("thrust_top", "Jet Thrust (Top Frame)", 50, 0, 1);
draw("isotropy_W", "Isotropy (W Frame)", 50, 0, 1);
draw("aplanarity_W", "Aplanarity (W Frame)", 50, 0, 1);
draw("sphericity_W", "Sphericity (W Frame)", 50, 0, 1);
draw("thrust_W", "Jet Thrust (W Frame)", 50, 0, 1);
draw("isotropy_Z", "Isotropy (Z Frame)", 50, 0, 1);
draw("aplanarity_Z", "Aplanarity (Z Frame)", 50, 0, 1);
draw("sphericity_Z", "Sphericity (Z Frame)", 50, 0, 1);
draw("thrust_Z", "Jet Thrust (Z Frame)", 50, 0, 1);
draw("isotropy_H", "Isotropy (H Frame)", 50, 0, 1);
draw("aplanarity_H", "Aplanarity (H Frame)", 50, 0, 1);
draw("sphericity_H", "Sphericity (H Frame)", 50, 0, 1);
draw("thrust_H", "Jet Thrust (H Frame)", 50, 0, 1);

*/


draw("et", "Jet p_{T} [GeV]", 100, 500, 3000);
draw("eta", "Jet #eta", 100, -3, 3);
draw("SDmass", "Jet Soft Drop Mass [GeV]", 50, 0, 300);


draw("NNoutX", "NN Output 1", 100, -1.2, 1.2);
draw("NNoutY", "NN Output 2", 100, -1.2, 1.2);
draw("NNout3", "NN Output 3", 100, -1.2, 1.2);
draw("NNout4", "NN Output 4", 100, -1.2, 1.2);


draw("PzOverP_Z", "A_{L} (Z Frame)", 50, -1.1, 1.1);
draw("PzOverP_W", "A_{L} (W Frame)", 50, -1.1, 1.1);
draw("PzOverP_H", "A_{L} (H Frame)", 50, -1.1, 1.1);
draw("PzOverP_top", "A_{L} (Top Frame)", 50, -1.1, 1.1);


}
