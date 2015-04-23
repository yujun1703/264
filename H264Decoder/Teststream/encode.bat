::encode.bat
:: to product h264 stream in annuxB format
:: by sensong 201406
::
:: encoder version :http://tc-svn.tencent.com/basic/basic_videocodec_rep/H264Encoder_x86_proj  (r5670)
::
::
::emME:
::   emME1: emMe_I_P_SP_P = 1,    //I P SP P SP P SP P SP P GF P SP P SP P SP P SP P
::   emME2: emMe_I_P_P_P  = 2,    //I P P P P P P P P P P P I P P P P P P P P P P
::   emME3: emMe_I_P_GF_P = 3,    //I P P P P P P P P P P P GF P P P P P P P P P P 
::profile: BP(cavlc+b_transform_8x8_disable),MP(cabac+b_transform_8x8_disable),HP(cabac+b_transform_8x8_enable)
::SPEEDOPT 0(best),1(normal),2(fast)
::

::320x240
test.exe -input tcOffice_320x240_15.yuv -output BP320x240_15_1S_emMe1_fast.264     -profile BP -SPEEDOPT 2 -gop 15 -gfgop 10 -spgop 1 -fps 15 -width 320 -height 240 -kbps 310
test.exe -input tcOffice_320x240_15.yuv -output MP320x240_15_1_5S_emMe2_normal.264 -profile MP -SPEEDOPT 1 -gop 23                    -fps 15 -width 320 -height 240 -kbps 310
test.exe -input tcOffice_320x240_15.yuv -output HP320x240_15_2S_emMe3_best.264     -profile HP -SPEEDOPT 0 -gop 30 -gfgop 12          -fps 15 -width 320 -height 240 -kbps 310

::480x360
test.exe -input tcOffice_480x360_15.yuv -output BP480x360_15_1S_emMe1_fast.264     -profile BP -SPEEDOPT 2 -gop 15 -gfgop 10 -spgop 1 -fps 15 -width 480 -height 360 -kbps 310
test.exe -input tcOffice_480x360_15.yuv -output MP480x360_15_1_5S_emMe2_normal.264 -profile MP -SPEEDOPT 1 -gop 23                    -fps 15 -width 480 -height 360 -kbps 310
test.exe -input tcOffice_480x360_15.yuv -output HP480x360_15_2S_emMe3_best.264     -profile HP -SPEEDOPT 0 -gop 30 -gfgop 12          -fps 15 -width 480 -height 360 -kbps 310

::640x480
test.exe -input tcOffice_640x480_15.yuv -output BP640x480_15_1S_emMe1_fast.264     -profile BP -SPEEDOPT 2 -gop 15 -gfgop 10 -spgop 1 -fps 15 -width 640 -height 480 -kbps 500
test.exe -input tcOffice_640x480_15.yuv -output MP640x480_15_1_5S_emMe2_normal.264 -profile MP -SPEEDOPT 1 -gop 23                    -fps 15 -width 640 -height 480 -kbps 500
test.exe -input tcOffice_640x480_15.yuv -output HP640x480_15_2S_emMe3_best.264     -profile HP -SPEEDOPT 0 -gop 30 -gfgop 12          -fps 15 -width 640 -height 480 -kbps 500

::960x540
test.exe -input m_m_960_540_20.yuv -output BP960x540_20_1S_emMe1_fast.264     -profile BP -SPEEDOPT 2 -gop 20 -gfgop 10 -spgop 1 -fps 20 -width 960 -height 540 -kbps 650
test.exe -input m_m_960_540_20.yuv -output MP960x540_20_1_5S_emMe2_normal.264 -profile MP -SPEEDOPT 1 -gop 30                    -fps 20 -width 960 -height 540 -kbps 650
test.exe -input m_m_960_540_20.yuv -output HP960x540_20_2S_emMe3_best.264     -profile HP -SPEEDOPT 0 -gop 40 -gfgop 12          -fps 20 -width 960 -height 540 -kbps 650

::1280x720
test.exe -input FourPeople_1280x720_20.yuv -output BP1280x720_20_1S_emMe1_fast.264     -profile BP -SPEEDOPT 2 -gop 20 -gfgop 10 -spgop 1 -fps 20 -width 1280 -height 720 -kbps 1050
test.exe -input FourPeople_1280x720_20.yuv -output MP1280x720_20_1_5S_emMe2_normal.264 -profile MP -SPEEDOPT 1 -gop 30                    -fps 20 -width 1280 -height 720 -kbps 1050
test.exe -input FourPeople_1280x720_20.yuv -output HP1280x720_20_2S_emMe3_best.264     -profile HP -SPEEDOPT 0 -gop 40 -gfgop 12          -fps 20 -width 1280 -height 720 -kbps 1050

::Add two stream:
::H264EncTest.exe -input TcOffice_192x144_move_big.yuv -output HP192x144_10_2_enMe2_normal.264 -profile HP -fps 10 -kbps 100 -gop 300 -GFGOP 20          -width 192 -height 144 -cmode 1
::H264EncTest.exe -input TcOffice_192x144_move_big.yuv -output HP192x144_10_2_ppSp_best.264    -profile HP -fps 10 -kbps 100 -gop 300 -GFGOP 20 -spgop 2 -width 192 -height 144 -cmode 0