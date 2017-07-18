{

string presel = "(bDisc > -1)*";

/*
makeStack("h1_top", "H_{1} (Top Frame)", presel + "1", 50, 0, 1);
makeStack("h2_top", "H_{2} (Top Frame)", presel + "1", 50, 0, 1);
makeStack("h3_top", "H_{3} (Top Frame)", presel + "1", 50, 0, 1);
makeStack("h4_top", "H_{4} (Top Frame)", presel + "1", 50, 0, 1);
makeStack("h1_W", "H_{1} (W Frame)", presel + "1", 50, 0, 1);
makeStack("h2_W", "H_{2} (W Frame)", presel + "1", 50, 0, 1);
makeStack("h3_W", "H_{3} (W Frame)", presel + "1", 50, 0, 1);
makeStack("h4_W", "H_{4} (W Frame)", presel + "1", 50, 0, 1);
makeStack("h1_Z", "H_{1} (Z Frame)", presel + "1", 50, 0, 1);
makeStack("h2_Z", "H_{2} (Z Frame)", presel + "1", 50, 0, 1);
makeStack("h3_Z", "H_{3} (Z Frame)", presel + "1", 50, 0, 1);
makeStack("h4_Z", "H_{4} (Z Frame)", presel + "1", 50, 0, 1);
makeStack("h1_H", "H_{1} (H Frame)", presel + "1", 50, 0, 1);
makeStack("h2_H", "H_{2} (H Frame)", presel + "1", 50, 0, 1);
makeStack("h3_H", "H_{3} (H Frame)", presel + "1", 50, 0, 1);
makeStack("h4_H", "H_{4} (H Frame)", presel + "1", 50, 0, 1);

makeStack("isotropy_top", "Isotropy (Top Frame)", presel + "1", 50, 0, 1);
makeStack("aplanarity_top", "Aplanarity (Top Frame)", presel + "1", 50, 0, 1);
makeStack("sphericity_top", "Sphericity (Top Frame)", presel + "1", 50, 0, 1);
makeStack("thrust_top", "Jet Thrust (Top Frame)", presel + "1", 50, 0, 1);
makeStack("isotropy_W", "Isotropy (W Frame)", presel + "1", 50, 0, 1);
makeStack("aplanarity_W", "Aplanarity (W Frame)", presel + "1", 50, 0, 1);
makeStack("sphericity_W", "Sphericity (W Frame)", presel + "1", 50, 0, 1);
makeStack("thrust_W", "Jet Thrust (W Frame)", presel + "1", 50, 0, 1);
makeStack("isotropy_Z", "Isotropy (Z Frame)", presel + "1", 50, 0, 1);
makeStack("aplanarity_Z", "Aplanarity (Z Frame)", presel + "1", 50, 0, 1);
makeStack("sphericity_Z", "Sphericity (Z Frame)", presel + "1", 50, 0, 1);
makeStack("thrust_Z", "Jet Thrust (Z Frame)", presel + "1", 50, 0, 1);
makeStack("isotropy_H", "Isotropy (H Frame)", presel + "1", 50, 0, 1);
makeStack("aplanarity_H", "Aplanarity (H Frame)", presel + "1", 50, 0, 1);
makeStack("sphericity_H", "Sphericity (H Frame)", presel + "1", 50, 0, 1);
makeStack("thrust_H", "Jet Thrust (H Frame)", presel + "1", 50, 0, 1);

makeStack("PzOverP_top", "A_L (Top Frame)", presel + "1", 50, -1, 1);
makeStack("PzOverP_W", "A_L (W Frame)", presel + "1", 50, -1, 1);
makeStack("PzOverP_Z", "A_L (Z Frame)", presel + "1", 50, -1, 1);
makeStack("PzOverP_H", "A_L (H Frame)", presel + "1", 50, -1, 1);

makeStack("NNoutX", "NN Output 1", presel + "1", 50, 0, 1);
makeStack("NNoutY", "NN Output 2", presel + "1", 50, 0, 1);
makeStack("NNout3", "NN Output 3", presel + "1", 50, 0, 1);
makeStack("NNout4", "NN Output 4", presel + "1", 50, 0, 1);
*/


makeStack("distTo1", "Distance to Node 1", presel + "1", 50, 0, 3);
makeStack("distTo0", "Distance to Node 0", presel + "1", 50, 0, 3);
makeStack("distTo2", "Distance to Node 2", presel + "1", 50, 0, 3);
makeStack("distTo3", "Distance to Node 3", presel + "1", 50, 0, 3);
makeStack("distTo4", "Distance to Node 4", presel + "1", 50, 0, 3);

//makeStack("et", "Jet p_{T}", presel + "1", 50, 0, 5000);
//makeStack("eta", "Jet #eta", presel + "1", 50, -3, 3);
//makeStack("SDmass", "Jet SD Mass", presel + "1", 50, 0, 500);
//makeStack("tau32", "Jet #tau_{32}", presel + "1", 50, 0, 1);
//makeStack("tau21", "Jet #tau_{21}", presel + "1", 50, 0, 1);

makeStack("minDist", "Classifier", presel + "1", 5, 0, 5);

}
