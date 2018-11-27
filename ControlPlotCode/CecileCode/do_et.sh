./Make.sh FinalSelection_et.cc
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/Data.root files_nominal_et/Data.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/Embedded.root files_nominal_et/Embedded.root embedded embedded 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/DYall.root files_nominal_et/DY.root DY DY 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/DYlow.root files_nominal_et/DYlow.root DYlow DYlow 0
#./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/DY.root files_nominal_et/DY.root DY DY 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/Wall.root files_nominal_et/W.root W W 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/TTToHadronic.root files_nominal_et/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/TTTo2L2Nu.root files_nominal_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/TTToSemiLeptonic.root files_nominal_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_nominal_et/TT.root files_nominal_et/TTToHadronic.root files_nominal_et/TTTo2L2Nu.root files_nominal_et/TTToSemiLeptonic.root
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WWTo4Q.root files_nominal_et/WW4Q.root WW4Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WWToLNuQQ.root files_nominal_et/WWLNuQQ.root WWLNuQQ VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WZTo2L2Q.root files_nominal_et/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WZTo1L3Nu.root files_nominal_et/WZ1L3Nu.root WZ1L3Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WZTo3LNu.root files_nominal_et/WZ3LNu.root WZ3LNu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WZTo1L1Nu2Q.root files_nominal_et/WZ1L1Nu2Q.root WZ1L1Nu2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ZZTo4L.root files_nominal_et/ZZ4L.root ZZ4L VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ZZTo2L2Nu.root files_nominal_et/ZZ2L2Nu.root ZZ2L2Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ZZTo2L2Q.root files_nominal_et/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ST_t_antitop.root files_nominal_et/ST_t_antitop.root ST_t_antitop VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ST_t_top.root files_nominal_et/ST_t_top.root ST_t_top VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ST_tW_antitop.root files_nominal_et/ST_tW_antitop.root ST_tW_antitop VV 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ST_tW_top.root files_nominal_et/ST_tW_top.root ST_tW_top VV 0
hadd -f files_nominal_et/VV.root files_nominal_et/ST_t_antitop.root files_nominal_et/ST_t_top.root files_nominal_et/ST_tW_antitop.root files_nominal_et/ST_tW_top.root files_nominal_et/WW4Q.root files_nominal_et/WWLNuQQ.root files_nominal_et/WZ2L2Q.root files_nominal_et/WZ1L3Nu.root files_nominal_et/WZ3LNu.root files_nominal_et/WZ1L1Nu2Q.root files_nominal_et/ZZ4L.root files_nominal_et/ZZ2L2Nu.root files_nominal_et/ZZ2L2Q.root
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ggH125.root files_nominal_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/VBF125.root files_nominal_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WplusH125.root files_nominal_et/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/WminusH125.root files_nominal_et/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/ZH125.root files_nominal_et/ZH125.root ZH125 ZH_htt125 0
hadd -f files_nominal_et/signal.root files_nominal_et/ggH_htt125.root files_nominal_et/qqH_htt125.root files_nominal_et/Wplus125.root files_nominal_et/WminusH125.root files_nominal_et/ZH125.root
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/EWKZLL.root files_nominal_et/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_et.exe /data/ccaillol/smhet_svfitted_15nov_svfit/EWKZNuNu.root files_nominal_et/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_et/EWKZ.root files_nominal_et/EWKZLL.root files_nominal_et/EWKZNuNu.root
python Create_fake_et.py
#sh do_rivet.sh

hadd -f smh_et_2D.root files_nominal_et/Data.root files_nominal_et/DY.root files_nominal_et/W.root files_nominal_et/TT.root files_nominal_et/VV.root files_nominal_et/Embedded.root files_nominal_et/Fake.root files_nominal_et/DYlow.root files_nominal_et/signal.root files_nominal_et/EWKZ.root #files_nominal_et/rivet.root
python Create_1D_et.py

