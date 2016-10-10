{

bool doReduce = 1;

runTree("root://cmseos.fnal.gov//store/user/pilot/BESTFiles/histo_TTall.root", "out_TTall.root", "weight_TTall.root", 1, 0,0,0, doReduce);
runTree("root://cmseos.fnal.gov//store/user/pilot/BESTFiles/histo_WWall.root", "out_WWall.root", "weight_WWall.root", 0,0,0,1, doReduce);
runTree("root://cmseos.fnal.gov//store/user/pilot/BESTFiles/histo_ZZall.root", "out_ZZall.root", "weight_ZZall.root", 0,0,1,0, doReduce);
runTree("root://cmseos.fnal.gov//store/user/pilot/BESTFiles/histo_HHall.root", "out_HHall.root", "weight_HHall.root", 0,1,0,0, doReduce);
runTree("root://cmseos.fnal.gov//store/user/pilot/BESTFiles/histo_QCDall.root", "out_QCDall.root", "weight_QCDall.root", 0, 0,0,0, doReduce);

}

