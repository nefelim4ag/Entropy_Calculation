#include "log2_lshift16.h"

/*
 * Precalculated log2 values
 * Shifting used for avoiding floating point
 * Fraction must be left shifted by 16
 * Return of log are left shifted by 6
 */
int log2_lshift16(long long unsigned lshift16) {
	if (lshift16 < 1)
		return -1024;
	if (lshift16 < 2)
		return -960;
	if (lshift16 < 3)
		return -922;
	if (lshift16 < 4)
		return -896;
	if (lshift16 < 5)
		return -875;
	if (lshift16 < 6)
		return -858;
	if (lshift16 < 7)
		return -844;
	if (lshift16 < 8)
		return -832;
	if (lshift16 < 9)
		return -821;
	if (lshift16 < 10)
		return -811;
	if (lshift16 < 11)
		return -802;
	if (lshift16 < 12)
		return -794;
	if (lshift16 < 13)
		return -787;
	if (lshift16 < 14)
		return -780;
	if (lshift16 < 15)
		return -773;
	if (lshift16 < 16)
		return -768;
	if (lshift16 < 17)
		return -762;
	if (lshift16 < 18)
		return -757;
	if (lshift16 < 19)
		return -752;
	if (lshift16 < 20)
		return -747;
	if (lshift16 < 21)
		return -742;
	if (lshift16 < 22)
		return -738;
	if (lshift16 < 23)
		return -734;
	if (lshift16 < 24)
		return -730;
	if (lshift16 < 25)
		return -726;
	if (lshift16 < 26)
		return -723;
	if (lshift16 < 27)
		return -719;
	if (lshift16 < 28)
		return -716;
	if (lshift16 < 29)
		return -713;
	if (lshift16 < 30)
		return -709;
	if (lshift16 < 31)
		return -706;
	if (lshift16 < 32)
		return -704;
	if (lshift16 < 33)
		return -701;
	if (lshift16 < 34)
		return -698;
	if (lshift16 < 35)
		return -695;
	if (lshift16 < 36)
		return -693;
	if (lshift16 < 37)
		return -690;
	if (lshift16 < 38)
		return -688;
	if (lshift16 < 39)
		return -685;
	if (lshift16 < 40)
		return -683;
	if (lshift16 < 41)
		return -681;
	if (lshift16 < 42)
		return -678;
	if (lshift16 < 43)
		return -676;
	if (lshift16 < 44)
		return -674;
	if (lshift16 < 45)
		return -672;
	if (lshift16 < 46)
		return -670;
	if (lshift16 < 47)
		return -668;
	if (lshift16 < 48)
		return -666;
	if (lshift16 < 49)
		return -664;
	if (lshift16 < 50)
		return -662;
	if (lshift16 < 51)
		return -660;
	if (lshift16 < 52)
		return -659;
	if (lshift16 < 53)
		return -657;
	if (lshift16 < 54)
		return -655;
	if (lshift16 < 55)
		return -653;
	if (lshift16 < 56)
		return -652;
	if (lshift16 < 57)
		return -650;
	if (lshift16 < 58)
		return -649;
	if (lshift16 < 59)
		return -647;
	if (lshift16 < 60)
		return -645;
	if (lshift16 < 61)
		return -644;
	if (lshift16 < 62)
		return -642;
	if (lshift16 < 63)
		return -641;
	if (lshift16 < 64)
		return -640;
	if (lshift16 < 65)
		return -638;
	if (lshift16 < 66)
		return -637;
	if (lshift16 < 67)
		return -635;
	if (lshift16 < 68)
		return -634;
	if (lshift16 < 69)
		return -633;
	if (lshift16 < 70)
		return -631;
	if (lshift16 < 71)
		return -630;
	if (lshift16 < 72)
		return -629;
	if (lshift16 < 73)
		return -627;
	if (lshift16 < 74)
		return -626;
	if (lshift16 < 75)
		return -625;
	if (lshift16 < 76)
		return -624;
	if (lshift16 < 77)
		return -622;
	if (lshift16 < 78)
		return -621;
	if (lshift16 < 79)
		return -620;
	if (lshift16 < 80)
		return -619;
	if (lshift16 < 81)
		return -618;
	if (lshift16 < 82)
		return -617;
	if (lshift16 < 83)
		return -615;
	if (lshift16 < 84)
		return -614;
	if (lshift16 < 85)
		return -613;
	if (lshift16 < 86)
		return -612;
	if (lshift16 < 87)
		return -611;
	if (lshift16 < 88)
		return -610;
	if (lshift16 < 89)
		return -609;
	if (lshift16 < 90)
		return -608;
	if (lshift16 < 91)
		return -607;
	if (lshift16 < 92)
		return -606;
	if (lshift16 < 93)
		return -605;
	if (lshift16 < 94)
		return -604;
	if (lshift16 < 95)
		return -603;
	if (lshift16 < 96)
		return -602;
	if (lshift16 < 97)
		return -601;
	if (lshift16 < 98)
		return -600;
	if (lshift16 < 99)
		return -599;
	if (lshift16 < 100)
		return -598;
	if (lshift16 < 101)
		return -597;
	if (lshift16 < 103)
		return -596;
	if (lshift16 < 104)
		return -595;
	if (lshift16 < 105)
		return -594;
	if (lshift16 < 106)
		return -593;
	if (lshift16 < 107)
		return -592;
	if (lshift16 < 108)
		return -591;
	if (lshift16 < 109)
		return -590;
	if (lshift16 < 111)
		return -589;
	if (lshift16 < 112)
		return -588;
	if (lshift16 < 113)
		return -587;
	if (lshift16 < 114)
		return -586;
	if (lshift16 < 116)
		return -585;
	if (lshift16 < 117)
		return -584;
	if (lshift16 < 118)
		return -583;
	if (lshift16 < 119)
		return -582;
	if (lshift16 < 121)
		return -581;
	if (lshift16 < 122)
		return -580;
	if (lshift16 < 123)
		return -579;
	if (lshift16 < 125)
		return -578;
	if (lshift16 < 126)
		return -577;
	if (lshift16 < 128)
		return -576;
	if (lshift16 < 129)
		return -575;
	if (lshift16 < 130)
		return -574;
	if (lshift16 < 132)
		return -573;
	if (lshift16 < 133)
		return -572;
	if (lshift16 < 135)
		return -571;
	if (lshift16 < 136)
		return -570;
	if (lshift16 < 138)
		return -569;
	if (lshift16 < 139)
		return -568;
	if (lshift16 < 141)
		return -567;
	if (lshift16 < 142)
		return -566;
	if (lshift16 < 144)
		return -565;
	if (lshift16 < 145)
		return -564;
	if (lshift16 < 147)
		return -563;
	if (lshift16 < 148)
		return -562;
	if (lshift16 < 150)
		return -561;
	if (lshift16 < 152)
		return -560;
	if (lshift16 < 153)
		return -559;
	if (lshift16 < 155)
		return -558;
	if (lshift16 < 157)
		return -557;
	if (lshift16 < 158)
		return -556;
	if (lshift16 < 160)
		return -555;
	if (lshift16 < 162)
		return -554;
	if (lshift16 < 164)
		return -553;
	if (lshift16 < 165)
		return -552;
	if (lshift16 < 167)
		return -551;
	if (lshift16 < 169)
		return -550;
	if (lshift16 < 171)
		return -549;
	if (lshift16 < 173)
		return -548;
	if (lshift16 < 175)
		return -547;
	if (lshift16 < 177)
		return -546;
	if (lshift16 < 179)
		return -545;
	if (lshift16 < 181)
		return -544;
	if (lshift16 < 182)
		return -543;
	if (lshift16 < 184)
		return -542;
	if (lshift16 < 186)
		return -541;
	if (lshift16 < 189)
		return -540;
	if (lshift16 < 191)
		return -539;
	if (lshift16 < 193)
		return -538;
	if (lshift16 < 195)
		return -537;
	if (lshift16 < 197)
		return -536;
	if (lshift16 < 199)
		return -535;
	if (lshift16 < 201)
		return -534;
	if (lshift16 < 203)
		return -533;
	if (lshift16 < 206)
		return -532;
	if (lshift16 < 208)
		return -531;
	if (lshift16 < 210)
		return -530;
	if (lshift16 < 212)
		return -529;
	if (lshift16 < 215)
		return -528;
	if (lshift16 < 217)
		return -527;
	if (lshift16 < 219)
		return -526;
	if (lshift16 < 222)
		return -525;
	if (lshift16 < 224)
		return -524;
	if (lshift16 < 227)
		return -523;
	if (lshift16 < 229)
		return -522;
	if (lshift16 < 232)
		return -521;
	if (lshift16 < 234)
		return -520;
	if (lshift16 < 237)
		return -519;
	if (lshift16 < 239)
		return -518;
	if (lshift16 < 242)
		return -517;
	if (lshift16 < 245)
		return -516;
	if (lshift16 < 247)
		return -515;
	if (lshift16 < 250)
		return -514;
	if (lshift16 < 253)
		return -513;
	if (lshift16 < 256)
		return -512;
	if (lshift16 < 258)
		return -511;
	if (lshift16 < 261)
		return -510;
	if (lshift16 < 264)
		return -509;
	if (lshift16 < 267)
		return -508;
	if (lshift16 < 270)
		return -507;
	if (lshift16 < 273)
		return -506;
	if (lshift16 < 276)
		return -505;
	if (lshift16 < 279)
		return -504;
	if (lshift16 < 282)
		return -503;
	if (lshift16 < 285)
		return -502;
	if (lshift16 < 288)
		return -501;
	if (lshift16 < 291)
		return -500;
	if (lshift16 < 294)
		return -499;
	if (lshift16 < 297)
		return -498;
	if (lshift16 < 301)
		return -497;
	if (lshift16 < 304)
		return -496;
	if (lshift16 < 307)
		return -495;
	if (lshift16 < 311)
		return -494;
	if (lshift16 < 314)
		return -493;
	if (lshift16 < 317)
		return -492;
	if (lshift16 < 321)
		return -491;
	if (lshift16 < 324)
		return -490;
	if (lshift16 < 328)
		return -489;
	if (lshift16 < 331)
		return -488;
	if (lshift16 < 335)
		return -487;
	if (lshift16 < 339)
		return -486;
	if (lshift16 < 342)
		return -485;
	if (lshift16 < 346)
		return -484;
	if (lshift16 < 350)
		return -483;
	if (lshift16 < 354)
		return -482;
	if (lshift16 < 358)
		return -481;
	if (lshift16 < 362)
		return -480;
	if (lshift16 < 365)
		return -479;
	if (lshift16 < 369)
		return -478;
	if (lshift16 < 373)
		return -477;
	if (lshift16 < 378)
		return -476;
	if (lshift16 < 382)
		return -475;
	if (lshift16 < 386)
		return -474;
	if (lshift16 < 390)
		return -473;
	if (lshift16 < 394)
		return -472;
	if (lshift16 < 399)
		return -471;
	if (lshift16 < 403)
		return -470;
	if (lshift16 < 407)
		return -469;
	if (lshift16 < 412)
		return -468;
	if (lshift16 < 416)
		return -467;
	if (lshift16 < 421)
		return -466;
	if (lshift16 < 425)
		return -465;
	if (lshift16 < 430)
		return -464;
	if (lshift16 < 435)
		return -463;
	if (lshift16 < 439)
		return -462;
	if (lshift16 < 444)
		return -461;
	if (lshift16 < 449)
		return -460;
	if (lshift16 < 454)
		return -459;
	if (lshift16 < 459)
		return -458;
	if (lshift16 < 464)
		return -457;
	if (lshift16 < 469)
		return -456;
	if (lshift16 < 474)
		return -455;
	if (lshift16 < 479)
		return -454;
	if (lshift16 < 485)
		return -453;
	if (lshift16 < 490)
		return -452;
	if (lshift16 < 495)
		return -451;
	if (lshift16 < 501)
		return -450;
	if (lshift16 < 506)
		return -449;
	if (lshift16 < 512)
		return -448;
	if (lshift16 < 517)
		return -447;
	if (lshift16 < 523)
		return -446;
	if (lshift16 < 528)
		return -445;
	if (lshift16 < 534)
		return -444;
	if (lshift16 < 540)
		return -443;
	if (lshift16 < 546)
		return -442;
	if (lshift16 < 552)
		return -441;
	if (lshift16 < 558)
		return -440;
	if (lshift16 < 564)
		return -439;
	if (lshift16 < 570)
		return -438;
	if (lshift16 < 576)
		return -437;
	if (lshift16 < 583)
		return -436;
	if (lshift16 < 589)
		return -435;
	if (lshift16 < 595)
		return -434;
	if (lshift16 < 602)
		return -433;
	if (lshift16 < 608)
		return -432;
	if (lshift16 < 615)
		return -431;
	if (lshift16 < 622)
		return -430;
	if (lshift16 < 628)
		return -429;
	if (lshift16 < 635)
		return -428;
	if (lshift16 < 642)
		return -427;
	if (lshift16 < 649)
		return -426;
	if (lshift16 < 656)
		return -425;
	if (lshift16 < 663)
		return -424;
	if (lshift16 < 671)
		return -423;
	if (lshift16 < 678)
		return -422;
	if (lshift16 < 685)
		return -421;
	if (lshift16 < 693)
		return -420;
	if (lshift16 < 700)
		return -419;
	if (lshift16 < 708)
		return -418;
	if (lshift16 < 716)
		return -417;
	if (lshift16 < 724)
		return -416;
	if (lshift16 < 731)
		return -415;
	if (lshift16 < 739)
		return -414;
	if (lshift16 < 747)
		return -413;
	if (lshift16 < 756)
		return -412;
	if (lshift16 < 764)
		return -411;
	if (lshift16 < 772)
		return -410;
	if (lshift16 < 781)
		return -409;
	if (lshift16 < 789)
		return -408;
	if (lshift16 < 798)
		return -407;
	if (lshift16 < 806)
		return -406;
	if (lshift16 < 815)
		return -405;
	if (lshift16 < 824)
		return -404;
	if (lshift16 < 833)
		return -403;
	if (lshift16 < 842)
		return -402;
	if (lshift16 < 851)
		return -401;
	if (lshift16 < 861)
		return -400;
	if (lshift16 < 870)
		return -399;
	if (lshift16 < 879)
		return -398;
	if (lshift16 < 889)
		return -397;
	if (lshift16 < 899)
		return -396;
	if (lshift16 < 908)
		return -395;
	if (lshift16 < 918)
		return -394;
	if (lshift16 < 928)
		return -393;
	if (lshift16 < 939)
		return -392;
	if (lshift16 < 949)
		return -391;
	if (lshift16 < 959)
		return -390;
	if (lshift16 < 970)
		return -389;
	if (lshift16 < 980)
		return -388;
	if (lshift16 < 991)
		return -387;
	if (lshift16 < 1002)
		return -386;
	if (lshift16 < 1012)
		return -385;
	if (lshift16 < 1024)
		return -384;
	if (lshift16 < 1035)
		return -383;
	if (lshift16 < 1046)
		return -382;
	if (lshift16 < 1057)
		return -381;
	if (lshift16 < 1069)
		return -380;
	if (lshift16 < 1080)
		return -379;
	if (lshift16 < 1092)
		return -378;
	if (lshift16 < 1104)
		return -377;
	if (lshift16 < 1116)
		return -376;
	if (lshift16 < 1128)
		return -375;
	if (lshift16 < 1141)
		return -374;
	if (lshift16 < 1153)
		return -373;
	if (lshift16 < 1166)
		return -372;
	if (lshift16 < 1178)
		return -371;
	if (lshift16 < 1191)
		return -370;
	if (lshift16 < 1204)
		return -369;
	if (lshift16 < 1217)
		return -368;
	if (lshift16 < 1231)
		return -367;
	if (lshift16 < 1244)
		return -366;
	if (lshift16 < 1257)
		return -365;
	if (lshift16 < 1271)
		return -364;
	if (lshift16 < 1285)
		return -363;
	if (lshift16 < 1299)
		return -362;
	if (lshift16 < 1313)
		return -361;
	if (lshift16 < 1327)
		return -360;
	if (lshift16 < 1342)
		return -359;
	if (lshift16 < 1357)
		return -358;
	if (lshift16 < 1371)
		return -357;
	if (lshift16 < 1386)
		return -356;
	if (lshift16 < 1401)
		return -355;
	if (lshift16 < 1417)
		return -354;
	if (lshift16 < 1432)
		return -353;
	if (lshift16 < 1448)
		return -352;
	if (lshift16 < 1463)
		return -351;
	if (lshift16 < 1479)
		return -350;
	if (lshift16 < 1495)
		return -349;
	if (lshift16 < 1512)
		return -348;
	if (lshift16 < 1528)
		return -347;
	if (lshift16 < 1545)
		return -346;
	if (lshift16 < 1562)
		return -345;
	if (lshift16 < 1579)
		return -344;
	if (lshift16 < 1596)
		return -343;
	if (lshift16 < 1613)
		return -342;
	if (lshift16 < 1631)
		return -341;
	if (lshift16 < 1649)
		return -340;
	if (lshift16 < 1667)
		return -339;
	if (lshift16 < 1685)
		return -338;
	if (lshift16 < 1703)
		return -337;
	if (lshift16 < 1722)
		return -336;
	if (lshift16 < 1740)
		return -335;
	if (lshift16 < 1759)
		return -334;
	if (lshift16 < 1779)
		return -333;
	if (lshift16 < 1798)
		return -332;
	if (lshift16 < 1817)
		return -331;
	if (lshift16 < 1837)
		return -330;
	if (lshift16 < 1857)
		return -329;
	if (lshift16 < 1878)
		return -328;
	if (lshift16 < 1898)
		return -327;
	if (lshift16 < 1919)
		return -326;
	if (lshift16 < 1940)
		return -325;
	if (lshift16 < 1961)
		return -324;
	if (lshift16 < 1982)
		return -323;
	if (lshift16 < 2004)
		return -322;
	if (lshift16 < 2025)
		return -321;
	if (lshift16 < 2048)
		return -320;
	if (lshift16 < 2070)
		return -319;
	if (lshift16 < 2092)
		return -318;
	if (lshift16 < 2115)
		return -317;
	if (lshift16 < 2138)
		return -316;
	if (lshift16 < 2161)
		return -315;
	if (lshift16 < 2185)
		return -314;
	if (lshift16 < 2209)
		return -313;
	if (lshift16 < 2233)
		return -312;
	if (lshift16 < 2257)
		return -311;
	if (lshift16 < 2282)
		return -310;
	if (lshift16 < 2307)
		return -309;
	if (lshift16 < 2332)
		return -308;
	if (lshift16 < 2357)
		return -307;
	if (lshift16 < 2383)
		return -306;
	if (lshift16 < 2409)
		return -305;
	if (lshift16 < 2435)
		return -304;
	if (lshift16 < 2462)
		return -303;
	if (lshift16 < 2488)
		return -302;
	if (lshift16 < 2515)
		return -301;
	if (lshift16 < 2543)
		return -300;
	if (lshift16 < 2571)
		return -299;
	if (lshift16 < 2599)
		return -298;
	if (lshift16 < 2627)
		return -297;
	if (lshift16 < 2655)
		return -296;
	if (lshift16 < 2684)
		return -295;
	if (lshift16 < 2714)
		return -294;
	if (lshift16 < 2743)
		return -293;
	if (lshift16 < 2773)
		return -292;
	if (lshift16 < 2803)
		return -291;
	if (lshift16 < 2834)
		return -290;
	if (lshift16 < 2865)
		return -289;
	if (lshift16 < 2896)
		return -288;
	if (lshift16 < 2927)
		return -287;
	if (lshift16 < 2959)
		return -286;
	if (lshift16 < 2991)
		return -285;
	if (lshift16 < 3024)
		return -284;
	if (lshift16 < 3057)
		return -283;
	if (lshift16 < 3090)
		return -282;
	if (lshift16 < 3124)
		return -281;
	if (lshift16 < 3158)
		return -280;
	if (lshift16 < 3192)
		return -279;
	if (lshift16 < 3227)
		return -278;
	if (lshift16 < 3262)
		return -277;
	if (lshift16 < 3298)
		return -276;
	if (lshift16 < 3334)
		return -275;
	if (lshift16 < 3370)
		return -274;
	if (lshift16 < 3407)
		return -273;
	if (lshift16 < 3444)
		return -272;
	if (lshift16 < 3481)
		return -271;
	if (lshift16 < 3519)
		return -270;
	if (lshift16 < 3558)
		return -269;
	if (lshift16 < 3596)
		return -268;
	if (lshift16 < 3635)
		return -267;
	if (lshift16 < 3675)
		return -266;
	if (lshift16 < 3715)
		return -265;
	if (lshift16 < 3756)
		return -264;
	if (lshift16 < 3796)
		return -263;
	if (lshift16 < 3838)
		return -262;
	if (lshift16 < 3880)
		return -261;
	if (lshift16 < 3922)
		return -260;
	if (lshift16 < 3965)
		return -259;
	if (lshift16 < 4008)
		return -258;
	if (lshift16 < 4051)
		return -257;
	if (lshift16 < 4096)
		return -256;
	if (lshift16 < 4140)
		return -255;
	if (lshift16 < 4185)
		return -254;
	if (lshift16 < 4231)
		return -253;
	if (lshift16 < 4277)
		return -252;
	if (lshift16 < 4323)
		return -251;
	if (lshift16 < 4371)
		return -250;
	if (lshift16 < 4418)
		return -249;
	if (lshift16 < 4466)
		return -248;
	if (lshift16 < 4515)
		return -247;
	if (lshift16 < 4564)
		return -246;
	if (lshift16 < 4614)
		return -245;
	if (lshift16 < 4664)
		return -244;
	if (lshift16 < 4715)
		return -243;
	if (lshift16 < 4766)
		return -242;
	if (lshift16 < 4818)
		return -241;
	if (lshift16 < 4870)
		return -240;
	if (lshift16 < 4924)
		return -239;
	if (lshift16 < 4977)
		return -238;
	if (lshift16 < 5031)
		return -237;
	if (lshift16 < 5086)
		return -236;
	if (lshift16 < 5142)
		return -235;
	if (lshift16 < 5198)
		return -234;
	if (lshift16 < 5254)
		return -233;
	if (lshift16 < 5311)
		return -232;
	if (lshift16 < 5369)
		return -231;
	if (lshift16 < 5428)
		return -230;
	if (lshift16 < 5487)
		return -229;
	if (lshift16 < 5547)
		return -228;
	if (lshift16 < 5607)
		return -227;
	if (lshift16 < 5668)
		return -226;
	if (lshift16 < 5730)
		return -225;
	if (lshift16 < 5792)
		return -224;
	if (lshift16 < 5855)
		return -223;
	if (lshift16 < 5919)
		return -222;
	if (lshift16 < 5983)
		return -221;
	if (lshift16 < 6049)
		return -220;
	if (lshift16 < 6114)
		return -219;
	if (lshift16 < 6181)
		return -218;
	if (lshift16 < 6248)
		return -217;
	if (lshift16 < 6316)
		return -216;
	if (lshift16 < 6385)
		return -215;
	if (lshift16 < 6455)
		return -214;
	if (lshift16 < 6525)
		return -213;
	if (lshift16 < 6596)
		return -212;
	if (lshift16 < 6668)
		return -211;
	if (lshift16 < 6741)
		return -210;
	if (lshift16 < 6814)
		return -209;
	if (lshift16 < 6888)
		return -208;
	if (lshift16 < 6963)
		return -207;
	if (lshift16 < 7039)
		return -206;
	if (lshift16 < 7116)
		return -205;
	if (lshift16 < 7193)
		return -204;
	if (lshift16 < 7271)
		return -203;
	if (lshift16 < 7351)
		return -202;
	if (lshift16 < 7431)
		return -201;
	if (lshift16 < 7512)
		return -200;
	if (lshift16 < 7593)
		return -199;
	if (lshift16 < 7676)
		return -198;
	if (lshift16 < 7760)
		return -197;
	if (lshift16 < 7844)
		return -196;
	if (lshift16 < 7930)
		return -195;
	if (lshift16 < 8016)
		return -194;
	if (lshift16 < 8103)
		return -193;
	if (lshift16 < 8192)
		return -192;
	if (lshift16 < 8281)
		return -191;
	if (lshift16 < 8371)
		return -190;
	if (lshift16 < 8462)
		return -189;
	if (lshift16 < 8554)
		return -188;
	if (lshift16 < 8647)
		return -187;
	if (lshift16 < 8742)
		return -186;
	if (lshift16 < 8837)
		return -185;
	if (lshift16 < 8933)
		return -184;
	if (lshift16 < 9030)
		return -183;
	if (lshift16 < 9129)
		return -182;
	if (lshift16 < 9228)
		return -181;
	if (lshift16 < 9328)
		return -180;
	if (lshift16 < 9430)
		return -179;
	if (lshift16 < 9533)
		return -178;
	if (lshift16 < 9637)
		return -177;
	if (lshift16 < 9741)
		return -176;
	if (lshift16 < 9848)
		return -175;
	if (lshift16 < 9955)
		return -174;
	if (lshift16 < 10063)
		return -173;
	if (lshift16 < 10173)
		return -172;
	if (lshift16 < 10284)
		return -171;
	if (lshift16 < 10396)
		return -170;
	if (lshift16 < 10509)
		return -169;
	if (lshift16 < 10623)
		return -168;
	if (lshift16 < 10739)
		return -167;
	if (lshift16 < 10856)
		return -166;
	if (lshift16 < 10974)
		return -165;
	if (lshift16 < 11094)
		return -164;
	if (lshift16 < 11214)
		return -163;
	if (lshift16 < 11336)
		return -162;
	if (lshift16 < 11460)
		return -161;
	if (lshift16 < 11585)
		return -160;
	if (lshift16 < 11711)
		return -159;
	if (lshift16 < 11838)
		return -158;
	if (lshift16 < 11967)
		return -157;
	if (lshift16 < 12098)
		return -156;
	if (lshift16 < 12229)
		return -155;
	if (lshift16 < 12363)
		return -154;
	if (lshift16 < 12497)
		return -153;
	if (lshift16 < 12633)
		return -152;
	if (lshift16 < 12771)
		return -151;
	if (lshift16 < 12910)
		return -150;
	if (lshift16 < 13051)
		return -149;
	if (lshift16 < 13193)
		return -148;
	if (lshift16 < 13336)
		return -147;
	if (lshift16 < 13482)
		return -146;
	if (lshift16 < 13628)
		return -145;
	if (lshift16 < 13777)
		return -144;
	if (lshift16 < 13927)
		return -143;
	if (lshift16 < 14078)
		return -142;
	if (lshift16 < 14232)
		return -141;
	if (lshift16 < 14387)
		return -140;
	if (lshift16 < 14543)
		return -139;
	if (lshift16 < 14702)
		return -138;
	if (lshift16 < 14862)
		return -137;
	if (lshift16 < 15024)
		return -136;
	if (lshift16 < 15187)
		return -135;
	if (lshift16 < 15353)
		return -134;
	if (lshift16 < 15520)
		return -133;
	if (lshift16 < 15689)
		return -132;
	if (lshift16 < 15860)
		return -131;
	if (lshift16 < 16032)
		return -130;
	if (lshift16 < 16207)
		return -129;
	if (lshift16 < 16384)
		return -128;
	if (lshift16 < 16562)
		return -127;
	if (lshift16 < 16742)
		return -126;
	if (lshift16 < 16925)
		return -125;
	if (lshift16 < 17109)
		return -124;
	if (lshift16 < 17295)
		return -123;
	if (lshift16 < 17484)
		return -122;
	if (lshift16 < 17674)
		return -121;
	if (lshift16 < 17866)
		return -120;
	if (lshift16 < 18061)
		return -119;
	if (lshift16 < 18258)
		return -118;
	if (lshift16 < 18456)
		return -117;
	if (lshift16 < 18657)
		return -116;
	if (lshift16 < 18861)
		return -115;
	if (lshift16 < 19066)
		return -114;
	if (lshift16 < 19274)
		return -113;
	if (lshift16 < 19483)
		return -112;
	if (lshift16 < 19696)
		return -111;
	if (lshift16 < 19910)
		return -110;
	if (lshift16 < 20127)
		return -109;
	if (lshift16 < 20346)
		return -108;
	if (lshift16 < 20568)
		return -107;
	if (lshift16 < 20792)
		return -106;
	if (lshift16 < 21018)
		return -105;
	if (lshift16 < 21247)
		return -104;
	if (lshift16 < 21478)
		return -103;
	if (lshift16 < 21712)
		return -102;
	if (lshift16 < 21949)
		return -101;
	if (lshift16 < 22188)
		return -100;
	if (lshift16 < 22429)
		return -99;
	if (lshift16 < 22673)
		return -98;
	if (lshift16 < 22920)
		return -97;
	if (lshift16 < 23170)
		return -96;
	if (lshift16 < 23422)
		return -95;
	if (lshift16 < 23677)
		return -94;
	if (lshift16 < 23935)
		return -93;
	if (lshift16 < 24196)
		return -92;
	if (lshift16 < 24459)
		return -91;
	if (lshift16 < 24726)
		return -90;
	if (lshift16 < 24995)
		return -89;
	if (lshift16 < 25267)
		return -88;
	if (lshift16 < 25542)
		return -87;
	if (lshift16 < 25820)
		return -86;
	if (lshift16 < 26102)
		return -85;
	if (lshift16 < 26386)
		return -84;
	if (lshift16 < 26673)
		return -83;
	if (lshift16 < 26964)
		return -82;
	if (lshift16 < 27257)
		return -81;
	if (lshift16 < 27554)
		return -80;
	if (lshift16 < 27854)
		return -79;
	if (lshift16 < 28157)
		return -78;
	if (lshift16 < 28464)
		return -77;
	if (lshift16 < 28774)
		return -76;
	if (lshift16 < 29087)
		return -75;
	if (lshift16 < 29404)
		return -74;
	if (lshift16 < 29724)
		return -73;
	if (lshift16 < 30048)
		return -72;
	if (lshift16 < 30375)
		return -71;
	if (lshift16 < 30706)
		return -70;
	if (lshift16 < 31040)
		return -69;
	if (lshift16 < 31378)
		return -68;
	if (lshift16 < 31720)
		return -67;
	if (lshift16 < 32065)
		return -66;
	if (lshift16 < 32415)
		return -65;
	if (lshift16 < 32768)
		return -64;
	if (lshift16 < 33124)
		return -63;
	if (lshift16 < 33485)
		return -62;
	if (lshift16 < 33850)
		return -61;
	if (lshift16 < 34218)
		return -60;
	if (lshift16 < 34591)
		return -59;
	if (lshift16 < 34968)
		return -58;
	if (lshift16 < 35348)
		return -57;
	if (lshift16 < 35733)
		return -56;
	if (lshift16 < 36122)
		return -55;
	if (lshift16 < 36516)
		return -54;
	if (lshift16 < 36913)
		return -53;
	if (lshift16 < 37315)
		return -52;
	if (lshift16 < 37722)
		return -51;
	if (lshift16 < 38132)
		return -50;
	if (lshift16 < 38548)
		return -49;
	if (lshift16 < 38967)
		return -48;
	if (lshift16 < 39392)
		return -47;
	if (lshift16 < 39821)
		return -46;
	if (lshift16 < 40254)
		return -45;
	if (lshift16 < 40693)
		return -44;
	if (lshift16 < 41136)
		return -43;
	if (lshift16 < 41584)
		return -42;
	if (lshift16 < 42037)
		return -41;
	if (lshift16 < 42494)
		return -40;
	if (lshift16 < 42957)
		return -39;
	if (lshift16 < 43425)
		return -38;
	if (lshift16 < 43898)
		return -37;
	if (lshift16 < 44376)
		return -36;
	if (lshift16 < 44859)
		return -35;
	if (lshift16 < 45347)
		return -34;
	if (lshift16 < 45841)
		return -33;
	if (lshift16 < 46340)
		return -32;
	if (lshift16 < 46845)
		return -31;
	if (lshift16 < 47355)
		return -30;
	if (lshift16 < 47871)
		return -29;
	if (lshift16 < 48392)
		return -28;
	if (lshift16 < 48919)
		return -27;
	if (lshift16 < 49452)
		return -26;
	if (lshift16 < 49990)
		return -25;
	if (lshift16 < 50535)
		return -24;
	if (lshift16 < 51085)
		return -23;
	if (lshift16 < 51641)
		return -22;
	if (lshift16 < 52204)
		return -21;
	if (lshift16 < 52772)
		return -20;
	if (lshift16 < 53347)
		return -19;
	if (lshift16 < 53928)
		return -18;
	if (lshift16 < 54515)
		return -17;
	if (lshift16 < 55108)
		return -16;
	if (lshift16 < 55709)
		return -15;
	if (lshift16 < 56315)
		return -14;
	if (lshift16 < 56928)
		return -13;
	if (lshift16 < 57548)
		return -12;
	if (lshift16 < 58175)
		return -11;
	if (lshift16 < 58809)
		return -10;
	if (lshift16 < 59449)
		return -9;
	if (lshift16 < 60096)
		return -8;
	if (lshift16 < 60751)
		return -7;
	if (lshift16 < 61412)
		return -6;
	if (lshift16 < 62081)
		return -5;
	if (lshift16 < 62757)
		return -4;
	if (lshift16 < 63440)
		return -3;
	if (lshift16 < 64131)
		return -2;
	if (lshift16 < 64830)
		return -1;
	return 0;
}
